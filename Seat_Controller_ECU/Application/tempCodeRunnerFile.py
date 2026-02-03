import serial
import struct
import sys
import time

START = 0xAA
CMD_READ_BYTE   = 0x01
CMD_WRITE_BYTE  = 0x02
CMD_READ_ALL    = 0x03
CMD_WRITE_BLOCK = 0x04

STATUS_OK = 0x00

def checksum8(data: bytes) -> int:
    return sum(data) & 0xFF

def build_frame(cmd: int, payload: bytes=b"") -> bytes:
    body = bytes([cmd]) + payload
    LEN = len(body)
    chk = checksum8(bytes([LEN]) + body)
    return bytes([START, LEN]) + body + bytes([chk])

def read_exact(ser: serial.Serial, n: int, timeout_s=2.0) -> bytes:
    buf = b""
    t0 = time.time()
    while len(buf) < n:
        if ser.in_waiting:
            buf += ser.read(ser.in_waiting)
        if len(buf) < n and (time.time() - t0) > timeout_s:
            raise TimeoutError("Timeout waiting for serial data")
        time.sleep(0.001)
    return buf[:n]  # exact

def read_frame(ser: serial.Serial, timeout_s=3.0) -> (int, int, bytes):
    # returns (cmd, status, payload)
    t0 = time.time()
    # seek START
    while True:
        if (time.time() - t0) > timeout_s:
            raise TimeoutError("Timeout waiting for frame start")
        b = ser.read(1)
        if not b:
            continue
        if b[0] == START:
            break

    LEN = read_exact(ser, 1, timeout_s=timeout_s)[0]
    body = read_exact(ser, LEN, timeout_s=timeout_s)
    chk  = read_exact(ser, 1, timeout_s=timeout_s)[0]
    if checksum8(bytes([LEN]) + body) != chk:
        raise ValueError("Bad checksum from device")

    cmd = body[0]
    # responses have cmd with bit7=1
    status = body[1] if LEN >= 2 else 0xFF
    payload = body[2:] if LEN > 2 else b""
    return cmd, status, payload

class ArduinoEEPROM:
    def __init__(self, port: str, baud: int = 115200, eeprom_size: int = 1024, timeout=1.0):
        self.ser = serial.Serial(port, baudrate=baud, timeout=timeout)
        self.size = eeprom_size

    def close(self):
        self.ser.close()

    def read_byte(self, addr: int) -> int:
        req = build_frame(CMD_READ_BYTE, struct.pack("<H", addr))
        self.ser.write(req)
        cmd, status, payload = read_frame(self.ser)
        if status != STATUS_OK or (cmd & 0x7F) != CMD_READ_BYTE or len(payload) != 1:
            raise RuntimeError(f"READ_BYTE failed (status={status})")
        return payload[0]

    def write_byte(self, addr: int, value: int):
        req = build_frame(CMD_WRITE_BYTE, struct.pack("<HB", addr, value & 0xFF))
        self.ser.write(req)
        cmd, status, _ = read_frame(self.ser)
        if status != STATUS_OK or (cmd & 0x7F) != CMD_WRITE_BYTE:
            raise RuntimeError(f"WRITE_BYTE failed (status={status})")

    def read_all(self) -> bytes:
        req = build_frame(CMD_READ_ALL, b"")
        self.ser.write(req)
        buf = bytearray(self.size)
        got = 0
        while got < self.size:
            cmd, status, payload = read_frame(self.ser, timeout_s=5.0)
            if (cmd & 0x7F) != CMD_READ_ALL or status != STATUS_OK or len(payload) < 3:
                raise RuntimeError("Bad READ_ALL frame")
            base = struct.unpack_from("<H", payload, 0)[0]
            count = payload[2]
            data = payload[3:]
            if count != len(data):
                raise RuntimeError("Length mismatch in READ_ALL")
            buf[base:base+count] = data
            got += count
        return bytes(buf)

    def write_all(self, data: bytes, block: int = 32):
        if len(data) != self.size:
            raise ValueError(f"Expected image of {self.size} bytes, got {len(data)}")
        for base in range(0, self.size, block):
            chunk = data[base: base+block]
            payload = struct.pack("<HB", base, len(chunk)) + chunk
            req = build_frame(CMD_WRITE_BLOCK, payload)
            self.ser.write(req)
            cmd, status, _ = read_frame(self.ser)
            if status != STATUS_OK or (cmd & 0x7F) != CMD_WRITE_BLOCK:
                raise RuntimeError(f"WRITE_BLOCK failed at {base} (status={status})")

if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("Usage:")
        print("  python arduino_eeprom_tool.py <COM_PORT> <EEPROM_SIZE>")
        print("Example:")
        print("  python arduino_eeprom_tool.py COM5 1024")
        sys.exit(1)

    port = sys.argv[1]
    size = int(sys.argv[2])

    dev = ArduinoEEPROM(port, eeprom_size=size)
    try:
        # Demo:
        print("Reading byte at 0...")
        b0 = dev.read_byte(0)
        print("EEPROM[0] =", b0)

        print("Writing 0x42 to addr 10...")
        dev.write_byte(10, 0x42)
        print("Verifying...")
        v = dev.read_byte(10)
        print("EEPROM[10] =", v)

        print("Reading full EEPROM...")
        all_data = dev.read_all()
        print("Got", len(all_data), "bytes")

        print("Writing full EEPROM image back (no-op demo)...")
        dev.write_all(all_data, block=32)
        print("Done.")
    finally:
        dev.close()

#include <Arduino.h>
#include <EEPROM.h>

#define BAUDRATE 9600 // The Default Baudrate For EEPROM

// -------- helpers --------, This Function Handle the format that will be received to the eeprom from the test bench (EEPROM Simulator)
static long parseNum(const String &s) { return strtol(s.c_str(), nullptr, 0); }

static void splitDash(const String &line, String parts[], int &count, int maxParts=5) {
  count = 0;
  int start = 0;
  while (count < maxParts) {
    int idx = line.indexOf('-', start);
    if (idx < 0) { parts[count++] = line.substring(start); break; }
    parts[count++] = line.substring(start, idx);
    start = idx + 1;
  }
}

static void fillRangeFF(int start, int size) {
  for (int i = start; i < start + size; ++i) EEPROM.update(i, 0xFF);
}

static void printHex2(uint8_t v) {
  if (v < 16) Serial.print('0');
  Serial.print(v, HEX);
}

// -------- globals --------
static int EELEN = 0;   // actual EEPROM capacity on this board

void setup() {
  Serial.begin(BAUDRATE);
  while (!Serial) {}

  EELEN = EEPROM.length();

  Serial.println("EEPROM interface ready @9600");
  Serial.print("Hardware EEPROM bytes: ");
  Serial.println(EELEN);
    // The Format That Should Be Sent
  Serial.println("Commands:");
  Serial.println("  W-<addr>-<val>          (write byte)");
  Serial.println("  R-<addr>                (read byte)");
  Serial.println("  RA                      (read all, decimal, 8/line)");
  Serial.println("  RAH                     (read all, hex with addresses, 8/line)");
  Serial.println("  WA-<size>-<val>         (fill from 0)");
  Serial.println("  WA-<start>-<size>-<val> (fill range)");
  Serial.println("  ER                      (erase ALL to 0xFF)");
  Serial.println("  ER-<start>-<size>       (erase range to 0xFF)");
}

void loop() {
  if (!Serial.available()) return;

  String cmd = Serial.readStringUntil('\n');
  cmd.trim();
  if (cmd.length() == 0) return;

  if (cmd.startsWith("w-")) cmd.setCharAt(0, 'W');
  if (cmd.startsWith("r-")) cmd.setCharAt(0, 'R');
  if (cmd.startsWith("er")) cmd.setCharAt(0, 'E');

  // --- Write Byte: W-<addr>-<value> ---, This Function Used to write one byte to eeprom by Writing (W-any address in the memory- Value)
  if (cmd.startsWith("W-")) { 
    String parts[3]; int n=0; splitDash(cmd, parts, n, 3);
    if (n != 3) { Serial.println("ERR: Use W-<addr>-<value>"); return; }
    long addr = parseNum(parts[1]);
    long val  = parseNum(parts[2]);
    if (addr < 0 || addr >= EELEN) { Serial.println("ERR: Address out of range"); return; }
    if (val < 0 || val > 255) { Serial.println("ERR: Value must be 0..255"); return; }
    EEPROM.update((int)addr, (uint8_t)val);
    Serial.print("OK WROTE addr=0x"); Serial.print(addr, HEX);
    Serial.print(" value="); Serial.println(val);
    return;
  }

  // --- Read Byte: R-<addr> ---, This Function Used to read one byte from eeprom by Writing (R-any address in the memory)
  if (cmd.startsWith("R-")) { 
    long addr = parseNum(cmd.substring(2));
    if (addr < 0 || addr >= EELEN) { Serial.println("ERR: Address out of range"); return; }
    int v = EEPROM.read((int)addr);
    Serial.print("OK READ addr=0x"); Serial.print(addr, HEX);
    Serial.print(" value="); Serial.println(v);
    return;
  }

  // --- Read All: RA (decimal, 8 bytes per line) ---, This Function Used to Read all the eeprom in decimal by Writing (RA)
  if (cmd == "RA") {
    Serial.println("OK DUMP BEGIN");
    for (int i = 0; i < EELEN; ++i) {
      Serial.print(EEPROM.read(i), DEC);
      if ((i % 8) != 7 && i < EELEN - 1) Serial.print(",");
      if ((i % 8) == 7) Serial.println();
    }
    if ((EELEN % 8) != 0) Serial.println();
    Serial.println("OK DUMP END");
    return;
  }

  // --- Read All HEX: RAH (hex, address labels, 8 per line) ---, This Function Used to Read all the eeprom in hexa by Writing (RAH)
  if (cmd == "RAH") {
    Serial.println("OK HEX DUMP BEGIN");
    for (int i = 0; i < EELEN; i += 8) {
      Serial.print("0x");
      if (i < 0x100) Serial.print('0');
      if (i < 0x10)  Serial.print('0');
      Serial.print(i, HEX);
      Serial.print(": ");
      for (int j = 0; j < 8 && (i + j) < EELEN; ++j) {
        printHex2(EEPROM.read(i + j));
        if (j != 7 && (i + j) < EELEN - 1) Serial.print(' ');
      }
      Serial.println();
    }
    Serial.println("OK HEX DUMP END");
    return;
  }

  // --- Write All (fill): WA-<size>-<val> or WA-<start>-<size>-<val> ---, This Function Used to Write all the eeprom by Writing (WA - size of bytes you want to write in - then the value ) or (WA- you can give a start address - then size - then value)
  if (cmd.startsWith("WA-")) {
    String parts[4]; int n=0; splitDash(cmd, parts, n, 4);
    long start=0, size=-1, val=-1;
    if (n == 3) { size = parseNum(parts[1]); val = parseNum(parts[2]); }
    else if (n == 4) { start = parseNum(parts[1]); size = parseNum(parts[2]); val = parseNum(parts[3]); }
    else { Serial.println("ERR: Use WA-<size>-<val> or WA-<start>-<size>-<val>"); return; }

    if (size <= 0) { Serial.println("ERR: Size must be >0"); return; }
    if (val < 0 || val > 255) { Serial.println("ERR: Value must be 0..255"); return; }
    long endAddr = start + size;
    if (start < 0 || endAddr > EELEN) { Serial.println("ERR: Range out of EEPROM"); return; }

    for (long a = start; a < endAddr; ++a) EEPROM.update((int)a, (uint8_t)val);
    Serial.print("OK WRITE ALL start=0x"); Serial.print(start, HEX);
    Serial.print(" size="); Serial.print(size);
    Serial.print(" value="); Serial.println(val);
    return;
  }

  // --- ERASE (set to 0xFF) ---,This Function Used to Erase all the eeprom by Writing (ER, will erase all the memory and it will be 0xFF ) or (ER- you can give a start address - then size)
  if (cmd == "ER") {
    fillRangeFF(0, EELEN);
    Serial.println("OK ERASE ALL to 0xFF");
    return;
  }
  if (cmd.startsWith("ER-")) {
    String parts[3]; int n=0; splitDash(cmd, parts, n, 3);
    if (n != 3) { Serial.println("ERR: Use ER-<start>-<size>"); return; }
    long start = parseNum(parts[1]);
    long size  = parseNum(parts[2]);
    long endAddr = start + size;
    if (size <= 0) { Serial.println("ERR: Size must be >0"); return; }
    if (start < 0 || endAddr > EELEN) { Serial.println("ERR: Range out of EEPROM"); return; }
    fillRangeFF((int)start, (int)size);
    Serial.print("OK ERASE start=0x"); Serial.print(start, HEX);
    Serial.print(" size="); Serial.println(size);
    return;
  }

  Serial.println("ERR: Unknown command");
}

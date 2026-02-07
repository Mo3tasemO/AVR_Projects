using System;
using System.IO;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace EepromProgrammerUI
{
    public class EepromProgrammer
    {
        private SerialPort _serialPort;
        public event Action<string> OnLogMessage;

        public EepromProgrammer(string portName, int baudRate)
        {
            _serialPort = new SerialPort(portName, baudRate);
            _serialPort.ReadTimeout = 2000;
            _serialPort.WriteTimeout = 2000;
        }

        public void Connect()
        {
            if (_serialPort != null && !_serialPort.IsOpen)
            {
                _serialPort.Open();
                OnLogMessage?.Invoke("Connected to EEPROM simulator.");
            }
        }

        public void Disconnect()
        {
            if (_serialPort != null && _serialPort.IsOpen)
            {
                _serialPort.Close();
                OnLogMessage?.Invoke("Disconnected.");
            }
        }

        public bool IsConnected()
        {
            return _serialPort != null && _serialPort.IsOpen;
        }

        private byte[] SendFramedCommand(byte commandId, byte[] param1 = null, byte[] param2 = null)
        {
            if (_serialPort == null || !_serialPort.IsOpen) return null;

            byte cmdHeader = 0xAA;
            byte cmdReqId = commandId;
            byte cmdTail = 0x55;

            int payloadLength = 1;
            if (param1 != null) payloadLength += param1.Length;
            if (param2 != null) payloadLength += param2.Length;
            payloadLength += 1;

            byte[] frame = new byte[1 + 4 + payloadLength];
            int offset = 0;

            frame[offset++] = cmdHeader;

            Buffer.BlockCopy(BitConverter.GetBytes(payloadLength), 0, frame, offset, 4);
            offset += 4;

            frame[offset++] = cmdReqId;

            if (param1 != null)
            {
                Buffer.BlockCopy(param1, 0, frame, offset, param1.Length);
                offset += param1.Length;
            }

            if (param2 != null)
            {
                Buffer.BlockCopy(param2, 0, frame, offset, param2.Length);
                offset += param2.Length;
            }

            frame[offset] = cmdTail;

            try
            {
                _serialPort.Write(frame, 0, frame.Length);
                OnLogMessage?.Invoke($"Sent: {BitConverter.ToString(frame).Replace("-", " ")}");

                byte[] responseHeader = new byte[5];
                _serialPort.Read(responseHeader, 0, 5);

                int responseLength = BitConverter.ToInt32(responseHeader, 1);

                byte[] responseData = new byte[responseLength];
                _serialPort.Read(responseData, 0, responseLength);

                byte[] fullResponse = new byte[5 + responseLength];
                Buffer.BlockCopy(responseHeader, 0, fullResponse, 0, 5);
                Buffer.BlockCopy(responseData, 0, fullResponse, 5, responseLength);

                OnLogMessage?.Invoke($"Received: {BitConverter.ToString(fullResponse).Replace("-", " ")}");
                return fullResponse;
            }
            catch (Exception ex)
            {
                OnLogMessage?.Invoke($"Error during communication: {ex.Message}");
                return null;
            }
        }

        public string ReadByte(int address)
        {
            byte commandId = 0x01;
            byte[] addressBytes = BitConverter.GetBytes(address);

            byte[] response = SendFramedCommand(commandId, addressBytes);

            if (response != null && response.Length > 9)
            {
                byte value = response[10];
                return $"Read Byte OK. Address: {address}, Value: 0x{value:X2}";
            }
            return "Read Byte Failed.";
        }

        public string WriteByte(int address, byte value)
        {
            byte commandId = 0x02;
            byte[] addressBytes = BitConverter.GetBytes(address);
            byte[] valueBytes = new byte[] { value };

            byte[] response = SendFramedCommand(commandId, addressBytes, valueBytes);

            if (response != null && response.Length > 9)
            {
                return "Write Byte OK";
            }
            return "Write Byte Failed.";
        }

        public string ReadAll(int size)
        {
            byte commandId = 0x03;
            byte[] sizeBytes = BitConverter.GetBytes(size);

            byte[] response = SendFramedCommand(commandId, sizeBytes);

            if (response != null && response.Length > 9)
            {
                byte[] data = new byte[size];
                Buffer.BlockCopy(response, 10, data, 0, size);
                string dataString = BitConverter.ToString(data).Replace("-", " ");
                return $"Read All OK. Read {size} bytes: {dataString}";
            }
            return "Read All Failed.";
        }

        public string WriteAll(int size, byte[] values)
        {
            byte commandId = 0x04;
            byte[] sizeBytes = BitConverter.GetBytes(size);
            byte[] dataBytes = values;

            byte[] response = SendFramedCommand(commandId, sizeBytes, dataBytes);

            if (response != null && response.Length > 9)
            {
                return "Write All OK";
            }
            return "Write All Failed.";
        }
    }
}
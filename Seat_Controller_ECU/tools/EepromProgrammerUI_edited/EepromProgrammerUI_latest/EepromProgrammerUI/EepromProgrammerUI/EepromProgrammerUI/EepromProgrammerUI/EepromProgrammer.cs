using System;
using System.IO.Ports;
using System.Text;
using System.Threading;

namespace EepromProgrammerUI
{
    /// <summary>
    /// Text-based protocol to match the Arduino sketch:
    ///   W-<addr>-<val>\n        - Write byte to address
    ///   R-<addr>\n              - Read byte from address  
    ///   RA\n                    - Read all (decimal format)
    ///   RAH\n                   - Read all (hex format)
    ///   WA-<size>-<val>\n       - Write all (fill entire EEPROM)
    ///   WA-<start>-<size>-<val>\n - Write range
    ///   ER\n                    - Erase all
    ///   ER-<start>-<size>\n     - Erase range
    /// 
    /// The Arduino replies with lines beginning with "OK" or "ERR".
    /// For RA it prints:
    ///   OK DUMP BEGIN
    ///   <comma separated values, 8 per line>
    ///   OK DUMP END
    /// </summary>
    public class EepromProgrammer
    {
        private readonly SerialPort _serialPort;
        public event Action<string> OnLogMessage;

        public EepromProgrammer(string portName, int baudRate)
        {
            _serialPort = new SerialPort(portName, baudRate)
            {
                DtrEnable = true,
                RtsEnable = true,
                NewLine = "\n",
                ReadTimeout = 5000,     // Increased timeout for large operations
                WriteTimeout = 3000,
                Encoding = Encoding.ASCII
            };
        }

        private void Log(string msg) => OnLogMessage?.Invoke(msg);

        public void Connect()
        {
            if (_serialPort.IsOpen) return;

            _serialPort.Open();
            Thread.Sleep(200); // Allow Arduino reset (for native USB boards)

            // Drain any greeting lines or startup messages
            try
            {
                var start = DateTime.UtcNow;
                while ((DateTime.UtcNow - start).TotalMilliseconds < 800)
                {
                    if (_serialPort.BytesToRead > 0)
                    {
                        string line = _serialPort.ReadLine();
                        if (!string.IsNullOrWhiteSpace(line))
                            Log($"DEVICE> {line.Trim()}");
                    }
                    else
                    {
                        Thread.Sleep(20);
                    }
                }
            }
            catch (TimeoutException)
            {
                // Normal - no startup messages
            }
            catch (Exception ex)
            {
                Log($"DEVICE> Connection warning: {ex.Message}");
            }
        }

        public void Disconnect()
        {
            if (_serialPort.IsOpen)
            {
                try
                {
                    _serialPort.Close();
                }
                catch (Exception ex)
                {
                    Log($"DEVICE> Disconnect error: {ex.Message}");
                }
            }
        }

        public bool IsConnected() => _serialPort?.IsOpen ?? false;

        /// <summary>
        /// Send command and wait for single OK/ERR response
        /// </summary>
        private string SendAndWaitSingle(string cmd)
        {
            if (!IsConnected())
                throw new InvalidOperationException("Not connected to device");

            _serialPort.DiscardInBuffer();
            _serialPort.WriteLine(cmd);

            // Read until we get OK or ERR response
            string line;
            int attempts = 0;
            const int maxAttempts = 10;

            do
            {
                try
                {
                    line = _serialPort.ReadLine().Trim();
                    attempts++;

                    // Skip echo or info lines, wait for actual response
                    if (!(line.StartsWith("OK") || line.StartsWith("ERR")))
                    {
                        if (!string.IsNullOrWhiteSpace(line))
                            Log($"DEVICE> {line}");
                        continue;
                    }

                    return line;
                }
                catch (TimeoutException)
                {
                    throw new TimeoutException($"Device didn't respond to command: {cmd}");
                }
            }
            while (attempts < maxAttempts);

            throw new TimeoutException($"No valid response after {maxAttempts} attempts for: {cmd}");
        }

        /// <summary>
        /// Write a single byte to EEPROM
        /// </summary>
        public string WriteByte(int address, byte value)
        {
            string cmd = $"W-{address}-{value}";
            string resp = SendAndWaitSingle(cmd);
            return resp;
        }

        /// <summary>
        /// Read a single byte from EEPROM
        /// </summary>
        public string ReadByte(int address)
        {
            string cmd = $"R-{address}";
            string resp = SendAndWaitSingle(cmd);
            return resp;
        }

        /// <summary>
        /// Read entire EEPROM in decimal format
        /// </summary>
        public string ReadAll(int maxBytesToShow = -1)
        {
            if (!IsConnected())
                throw new InvalidOperationException("Not connected to device");

            _serialPort.DiscardInBuffer();
            _serialPort.WriteLine("RA");

            var sb = new StringBuilder();
            bool dumpStarted = false;
            int bytesShown = 0;
            var timeoutAt = DateTime.UtcNow.AddSeconds(10); // Longer timeout for full reads

            while (DateTime.UtcNow < timeoutAt)
            {
                try
                {
                    string line = _serialPort.ReadLine().Trim();

                    if (line.StartsWith("OK DUMP BEGIN"))
                    {
                        dumpStarted = true;
                        sb.AppendLine(line);
                        continue;
                    }

                    if (line.StartsWith("OK DUMP END"))
                    {
                        sb.AppendLine(line);
                        break;
                    }

                    if (!dumpStarted)
                    {
                        // Log any preamble messages
                        if (!string.IsNullOrWhiteSpace(line))
                            Log($"DEVICE> {line}");
                        continue;
                    }

                    // Process data lines
                    if (maxBytesToShow > 0)
                    {
                        var values = line.Split(',');
                        int remaining = maxBytesToShow - bytesShown;

                        if (remaining <= 0)
                            continue; // Skip rest if we have enough

                        if (values.Length > remaining)
                        {
                            // Truncate to requested count
                            var truncated = string.Join(",", values, 0, remaining);
                            sb.AppendLine(truncated);
                            bytesShown += remaining;
                        }
                        else
                        {
                            sb.AppendLine(line);
                            bytesShown += values.Length;
                        }
                    }
                    else
                    {
                        sb.AppendLine(line);
                    }
                }
                catch (TimeoutException)
                {
                    break; // Exit on timeout
                }
            }

            return sb.ToString().TrimEnd();
        }

        /// <summary>
        /// Read entire EEPROM in hexadecimal format
        /// </summary>
        public string ReadAllHex()
        {
            if (!IsConnected())
                throw new InvalidOperationException("Not connected to device");

            _serialPort.DiscardInBuffer();
            _serialPort.WriteLine("RAH");

            var sb = new StringBuilder();
            bool dumpStarted = false;
            var timeoutAt = DateTime.UtcNow.AddSeconds(10);

            while (DateTime.UtcNow < timeoutAt)
            {
                try
                {
                    string line = _serialPort.ReadLine().Trim();

                    if (line.StartsWith("OK HEX DUMP BEGIN"))
                    {
                        dumpStarted = true;
                        sb.AppendLine(line);
                        continue;
                    }

                    if (line.StartsWith("OK HEX DUMP END"))
                    {
                        sb.AppendLine(line);
                        break;
                    }

                    if (!dumpStarted)
                    {
                        if (!string.IsNullOrWhiteSpace(line))
                            Log($"DEVICE> {line}");
                        continue;
                    }

                    sb.AppendLine(line);
                }
                catch (TimeoutException)
                {
                    break;
                }
            }

            return sb.ToString().TrimEnd();
        }

        /// <summary>
        /// Fill entire EEPROM with a single value
        /// </summary>
        public string WriteAllFill(int size, byte value)
        {
            string cmd = $"WA-{size}-{value}";
            string resp = SendAndWaitSingle(cmd);
            return resp;
        }

        /// <summary>
        /// Fill a range of EEPROM with a single value
        /// </summary>
        public string WriteAllFillRange(int startAddress, int size, byte value)
        {
            string cmd = $"WA-{startAddress}-{size}-{value}";
            string resp = SendAndWaitSingle(cmd);
            return resp;
        }

        /// <summary>
        /// Erase entire EEPROM (set all bytes to 0xFF or 0x00)
        /// </summary>
        public string EraseAll()
        {
            string resp = SendAndWaitSingle("ER");
            return resp;
        }

        /// <summary>
        /// Erase a specific range of EEPROM
        /// </summary>
        public string EraseRange(int startAddress, int size)
        {
            string cmd = $"ER-{startAddress}-{size}";
            string resp = SendAndWaitSingle(cmd);
            return resp;
        }

        /// <summary>
        /// Get device information/status
        /// </summary>
        public string GetDeviceInfo()
        {
            try
            {
                string resp = SendAndWaitSingle("INFO");
                return resp;
            }
            catch
            {
                return "INFO command not supported";
            }
        }

        /// <summary>
        /// Send a custom command to the device
        /// </summary>
        public string SendCustomCommand(string command)
        {
            string resp = SendAndWaitSingle(command);
            return resp;
        }

        /// <summary>
        /// Dispose pattern for proper cleanup
        /// </summary>
        public void Dispose()
        {
            Disconnect();
            _serialPort?.Dispose();
        }
    }
}
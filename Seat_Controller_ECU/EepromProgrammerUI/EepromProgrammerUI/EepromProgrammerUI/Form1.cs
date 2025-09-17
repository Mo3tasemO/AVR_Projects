using System;
using System.Windows.Forms;
using System.IO.Ports;
using System.Text;

namespace EepromProgrammerUI
{
    public partial class Form1 : Form
    {
        private EepromProgrammer _programmer;

        public Form1()
        {
            InitializeComponent();
            InitializeControls();
        }

        private void InitializeControls()
        {
            string[] ports = SerialPort.GetPortNames();
            comboBox_Port.Items.AddRange(ports);
            if (ports.Length > 0)
            {
                comboBox_Port.SelectedIndex = 0;
            }

            btnConnect.Click += BtnConnect_Click;
            btnReadByte.Click += BtnReadByte_Click;
            btnWriteByte.Click += BtnWriteByte_Click;
            btnReadAll.Click += BtnReadAll_Click;
            btnWriteAll.Click += BtnWriteAll_Click;
        }

        private void BtnConnect_Click(object sender, EventArgs e)
        {
            if (_programmer != null && _programmer.IsConnected())
            {
                _programmer.Disconnect();
                btnConnect.Text = "Connect";
            }
            else
            {
                string portName = comboBox_Port.SelectedItem != null ? comboBox_Port.SelectedItem.ToString() : string.Empty;
                int baudRate = 0;
                if (!int.TryParse(txtBaud.Text, out baudRate))
                {
                    AppendLog("Invalid baud rate format.");
                    return;
                }

                _programmer = new EepromProgrammer(portName, baudRate);
                _programmer.OnLogMessage += AppendLog;

                try
                {
                    _programmer.Connect();
                    btnConnect.Text = "Disconnect";
                }
                catch (Exception ex)
                {
                    AppendLog($"Connection Error: {ex.Message}");
                }
            }
        }

        private void BtnReadByte_Click(object sender, EventArgs e)
        {
            if (_programmer == null || !_programmer.IsConnected())
            {
                AppendLog("Not connected to a device.");
                return;
            }

            try
            {
               // int address = int.Parse(txtAddress_Read.Text);
                int address = Convert.ToInt32(txtAddress_Read.Text, 16);

                string result = _programmer.ReadByte(address);
                AppendLog(result);
            }
            catch (FormatException)
            {
                AppendLog("Invalid address format.");
            }
        }

        private void BtnWriteByte_Click(object sender, EventArgs e)
        {
            if (_programmer == null || !_programmer.IsConnected())
            {
                AppendLog("Not connected to a device.");
                return;
            }

            try
            {
                //int address = int.Parse(txtAddress_Write.Text);
                int address = Convert.ToInt32(txtAddress_Write.Text, 16);
                //byte value = byte.Parse(txtValue_Write.Text);
                byte value = Convert.ToByte(txtValue_Write.Text, 16);
                string result = _programmer.WriteByte(address, value);
                AppendLog(result);
            }
            catch (FormatException)
            {
                AppendLog("Invalid address or value format.");
            }
        }

        private void BtnReadAll_Click(object sender, EventArgs e)
        {
            if (_programmer == null || !_programmer.IsConnected())
            {
                AppendLog("Not connected to a device.");
                return;
            }

            try
            {
                //int size = int.Parse(txtSize_ReadAll.Text);
                int size = Convert.ToInt32(txtSize_ReadAll.Text, 16);
                string result = _programmer.ReadAll(size);
                AppendLog(result);
            }
            catch (FormatException)
            {
                AppendLog("Invalid size format.");
            }
        }

        private void BtnWriteAll_Click(object sender, EventArgs e)
        {
            if (_programmer == null || !_programmer.IsConnected())
            {
                AppendLog("Not connected to a device.");
                return;
            }

            try
            {
                //int size = int.Parse(txtSize_WriteAll.Text);
                int size = Convert.ToInt32(txtSize_WriteAll.Text, 16);
                byte[] dataToWrite = Encoding.UTF8.GetBytes(rtbData_WriteAll.Text);

                string result = _programmer.WriteAll(dataToWrite.Length, dataToWrite);
                AppendLog(result);
            }
            catch (FormatException)
            {
                AppendLog("Invalid size format.");
            }
        }

        private void AppendLog(string message)
        {
            if (rtbLog.InvokeRequired)
            {
                rtbLog.Invoke(new Action<string>(AppendLog), message);
            }
            else
            {
                rtbLog.AppendText($"{DateTime.Now:HH:mm:ss} - {message}\n");
                rtbLog.ScrollToCaret();
            }
        }

        private void btnReadAll_Click_1(object sender, EventArgs e)
        {

        }

        private void btnReadByte_Click(object sender, EventArgs e)
        {

        }

        private void rtbLog_Click(object sender, EventArgs e)
        {

        }
    }
}
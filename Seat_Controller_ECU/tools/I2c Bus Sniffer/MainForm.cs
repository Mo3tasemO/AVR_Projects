using System;
using System.Drawing;
using System.IO.Ports;
using System.Text;
using System.Windows.Forms;

// حل مشكلة التعارض مع System.Threading.Timer
using WinTimer = System.Windows.Forms.Timer;

namespace SerialPanel.WinForms
{
    public class MainForm : Form
    {
        // --- Controls ---
        ComboBox cmbPorts = new() { DropDownStyle = ComboBoxStyle.DropDownList, Width = 120 };
        TextBox txtBaud = new() { Text = "115200", Width = 120 };
        CheckBox chkConnect = new() { Text = "ON / OFF", AutoSize = true };
        Panel ledConn = new() { Width = 24, Height = 24, BackColor = Color.Transparent };
        TextBox txtSignal = new() { Width = 300 };
        Button btnSend = new() { Text = "➤", Width = 38 };

        TextBox txtPer1 = new() { Text = "1000", Width = 80 };
        TextBox txtPayload1 = new() { Width = 260 };
        CheckBox chkTask1 = new() { Text = "Start", AutoSize = true };

        TextBox txtPer2 = new() { Text = "1000", Width = 80 };
        TextBox txtPayload2 = new() { Width = 260 };
        CheckBox chkTask2 = new() { Text = "Start", AutoSize = true };

        TextBox txtTrace = new()
        {
            Multiline = true,
            ReadOnly = true,
            ScrollBars = ScrollBars.Vertical,
            Height = 280,
            Anchor = AnchorStyles.Left | AnchorStyles.Top | AnchorStyles.Right | AnchorStyles.Bottom
        };

        Label lblStatus = new() { Text = "status", AutoSize = true, ForeColor = Color.DimGray };
        Panel ledStatus = new() { Width = 18, Height = 18, BackColor = Color.Transparent };
        Label lblStatusText = new() { AutoSize = true };

        // --- Runtime (الأسماء الصحيحة بالشرط السفلي) ---
        readonly SerialPort _port = new();
        readonly WinTimer _t1 = new() { Interval = 1000 };
        readonly WinTimer _t2 = new() { Interval = 1000 };

        public MainForm()
        {
            Text = "Settings";
            MinimumSize = new Size(760, 540);
            ClientSize = new Size(820, 620);
            Font = new Font("Segoe UI", 9F);

            // Layout (simple table)
            var root = new TableLayoutPanel { Dock = DockStyle.Fill, ColumnCount = 1, RowCount = 3 };
            root.RowStyles.Add(new RowStyle(SizeType.AutoSize));
            root.RowStyles.Add(new RowStyle(SizeType.Percent, 100));
            root.RowStyles.Add(new RowStyle(SizeType.AutoSize));
            Controls.Add(root);

            var header = new Label { Text = "Settings", Font = new Font(Font, FontStyle.Bold), AutoSize = true };
            header.Font = new Font(header.Font.FontFamily, 24, FontStyle.Bold);
            header.Margin = new Padding(10, 10, 10, 0);
            root.Controls.Add(header);

            var main = new TableLayoutPanel { Dock = DockStyle.Fill, ColumnCount = 3 };
            main.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 50));
            main.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 35));
            main.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 15));
            main.Padding = new Padding(10);
            main.AutoScroll = true;
            root.Controls.Add(main);

            // Left column: User Input
            var left = new FlowLayoutPanel { FlowDirection = FlowDirection.TopDown, Dock = DockStyle.Fill, AutoSize = true, WrapContents = false };
            left.Controls.Add(MakeHeader("User Input"));
            left.Controls.Add(Row(("Signal", txtSignal), (null, btnSend)));
            main.Controls.Add(left, 0, 0);

            // Middle: COM/Rate/Connect
            var mid = new FlowLayoutPanel { FlowDirection = FlowDirection.TopDown, Dock = DockStyle.Fill, AutoSize = true, WrapContents = false };
            mid.Controls.Add(Row(("COM", cmbPorts)));
            mid.Controls.Add(Row(("Rate", txtBaud)));
            var onoff = new FlowLayoutPanel { FlowDirection = FlowDirection.LeftToRight, AutoSize = true };
            onoff.Controls.Add(chkConnect);
            onoff.Controls.Add(ledConn);
            ledConn.Paint += (_, e) => PaintLed(e, _port.IsOpen);
            mid.Controls.Add(onoff);
            main.Controls.Add(mid, 1, 0);

            // Periodic tasks (span two columns)
            var tasks = new FlowLayoutPanel { FlowDirection = FlowDirection.TopDown, Dock = DockStyle.Fill, WrapContents = false, AutoSize = true };
            tasks.Margin = new Padding(0, 16, 0, 0);
            tasks.Controls.Add(MakeHeader("Periodic tasks"));
            tasks.Controls.Add(Row(("Periodic", txtPer1), ("User Input", txtPayload1), (null, chkTask1)));
            tasks.Controls.Add(Row(("Periodic", txtPer2), ("User Input", txtPayload2), (null, chkTask2)));
            main.SetColumnSpan(tasks, 2);
            main.Controls.Add(tasks, 0, 1);

            // Trace (span all)
            var tracePanel = new TableLayoutPanel { Dock = DockStyle.Fill, ColumnCount = 1, RowCount = 2, Padding = new Padding(0, 4, 0, 0) };
            tracePanel.RowStyles.Add(new RowStyle(SizeType.AutoSize));
            tracePanel.RowStyles.Add(new RowStyle(SizeType.Percent, 100));

            var traceLabel = MakeHeader("Trace");
            traceLabel.Font = new Font(traceLabel.Font.FontFamily, 18, FontStyle.Bold);

            txtTrace.Dock = DockStyle.Fill;
            txtTrace.Height = 280;

            tracePanel.Controls.Add(traceLabel, 0, 0);
            tracePanel.Controls.Add(txtTrace, 0, 1);

            main.SetColumnSpan(tracePanel, 3);
            main.Controls.Add(tracePanel, 0, 2);

            // Status bar
            var statusBar = new FlowLayoutPanel { FlowDirection = FlowDirection.LeftToRight, Dock = DockStyle.Fill, AutoSize = true, Padding = new Padding(10, 0, 10, 10) };
            statusBar.Controls.Add(lblStatus);
            statusBar.Controls.Add(ledStatus);
            statusBar.Controls.Add(lblStatusText);
            ledStatus.Paint += (_, e) => PaintLed(e, ledStatus.Tag as bool? == true);
            root.Controls.Add(statusBar);

            // Events
            Load += (_, __) =>
            {
                cmbPorts.Items.Clear();
                cmbPorts.Items.AddRange(SerialPort.GetPortNames());
                if (cmbPorts.Items.Count > 0) cmbPorts.SelectedIndex = 0;

                _port.Encoding = Encoding.ASCII;
                _port.NewLine = "\r\n";          // matches Arduino Serial.println
                _port.DataReceived += Port_DataReceived;
                _port.ErrorReceived += (_, e) => SetStatus($"Serial error: {e.EventType}", false);
            };

            btnSend.Click += (_, __) => TrySend(txtSignal.Text);

            chkConnect.CheckedChanged += (_, __) =>
            {
                if (chkConnect.Checked)
                {
                    if (!EnsureOpen()) chkConnect.Checked = false;
                }
                else ClosePort();
                ledConn.Invalidate();
            };

            _t1.Tick += (_, __) => TrySend(txtPayload1.Text);
            _t2.Tick += (_, __) => TrySend(txtPayload2.Text);

            chkTask1.CheckedChanged += (_, __) =>
            {
                if (chkTask1.Checked)
                {
                    if (!TrySetInterval(txtPer1.Text, _t1)) { chkTask1.Checked = false; return; }
                    _t1.Start(); chkTask1.Text = "Running"; SetStatus("Task1 started");
                }
                else { _t1.Stop(); chkTask1.Text = "Start"; SetStatus("Task1 stopped"); }
            };

            chkTask2.CheckedChanged += (_, __) =>
            {
                if (chkTask2.Checked)
                {
                    if (!TrySetInterval(txtPer2.Text, _t2)) { chkTask2.Checked = false; return; }
                    _t2.Start(); chkTask2.Text = "Running"; SetStatus("Task2 started");
                }
                else { _t2.Stop(); chkTask2.Text = "Start"; SetStatus("Task2 stopped"); }
            };

            FormClosed += (_, __) =>
            {
                _t1.Stop(); _t2.Stop();
                ClosePort();
            };
        }

        // --- Layout helpers ---
        Label MakeHeader(string text) => new() { Text = text, AutoSize = true, Font = new Font(Font, FontStyle.Bold) };

        FlowLayoutPanel Row(params (string? label, Control control)[] cells)
        {
            var p = new FlowLayoutPanel { FlowDirection = FlowDirection.LeftToRight, AutoSize = true, WrapContents = false, Margin = new Padding(0, 4, 0, 4) };
            foreach (var (label, control) in cells)
            {
                if (label != null) p.Controls.Add(new Label { Text = label, Width = 70, TextAlign = ContentAlignment.MiddleLeft });
                control.Margin = new Padding(6, 0, 6, 0);
                p.Controls.Add(control);
            }
            return p;
        }

        void PaintLed(PaintEventArgs e, bool on)
        {
            e.Graphics.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.AntiAlias;
            var rect = new Rectangle(1, 1, e.ClipRectangle.Width - 3, e.ClipRectangle.Height - 3);
            using var bg = new SolidBrush(on ? Color.LimeGreen : Color.LightGray);
            using var pen = new Pen(on ? Color.Green : Color.Gray, 2);
            e.Graphics.FillEllipse(bg, rect);
            e.Graphics.DrawEllipse(pen, rect);
        }

        void SetLed(Panel panel, bool on)
        {
            panel.Tag = on;
            panel.Invalidate();
        }

        void Trace(string line)
        {
            txtTrace.AppendText($"{DateTime.Now:HH:mm:ss.fff}  {line}{Environment.NewLine}");
        }

        void SetStatus(string msg, bool ok = true)
        {
            if (InvokeRequired)
            {
                BeginInvoke(new Action(() => SetStatus(msg, ok)));
                return;
            }
            lblStatusText.Text = msg;
            SetLed(ledStatus, ok);
        }

        // --- Serial helpers ---
        bool EnsureOpen()
        {
            if (_port.IsOpen) return true;

            var name = cmbPorts.SelectedItem as string;
            if (string.IsNullOrWhiteSpace(name)) { SetStatus("Select a COM port", false); return false; }
            if (!int.TryParse(txtBaud.Text, out var baud)) { SetStatus("Bad baud", false); return false; }

            try
            {
                _port.PortName = name;
                _port.BaudRate = baud;
                _port.Handshake = Handshake.None;

                _port.Open();

                // مهم جدًا على Uno WiFi Rev2 وأي USB-CDC
                _port.DtrEnable = true;
                _port.RtsEnable = true;

                _port.ReadTimeout = 1000;         // لـ ReadLine()
                SetLed(ledConn, true);
                SetStatus($"Connected {name}@{baud}");
                return true;
            }
            catch (Exception ex)
            {
                SetStatus($"Open failed: {ex.Message}", false);
                SetLed(ledConn, false);
                return false;
            }
        }

        void ClosePort()
        {
            try { if (_port.IsOpen) _port.Close(); }
            catch { /* ignore */ }
            SetLed(ledConn, false);
            SetStatus("Disconnected");
        }

        void TrySend(string payload)
        {
            if (!EnsureOpen()) return;
            try
            {
                _port.WriteLine(payload);
                Trace($"-> {payload}");
                SetStatus("Sent");
            }
            catch (Exception ex)
            {
                SetStatus($"Send error: {ex.Message}", false);
            }
        }

        // --- Serial receive: يقرأ سطور كاملة باستخدام NewLine ---
        void Port_DataReceived(object? sender, SerialDataReceivedEventArgs e)
        {
            try
            {
                while (_port.IsOpen && _port.BytesToRead > 0)
                {
                    string line = _port.ReadLine();    // ينتظر \r\n
                    string message = line.Trim();

                    BeginInvoke(new Action(() =>
                    {
                        Trace($"<- {message}");

                        if (message.Equals("Button pressed!", StringComparison.OrdinalIgnoreCase))
                        {
                            lblStatusText.Text = "Microcontroller button was pushed!";
                            SetLed(ledStatus, true);
                        }
                    }));
                }
            }
            catch (TimeoutException)
            {
                // تجاهل الوقت المستقطع لجزء سطر بدون \r\n
            }
            catch (Exception ex)
            {
                BeginInvoke(new Action(() => SetStatus($"Read error: {ex.Message}", false)));
            }
        }

        bool TrySetInterval(string text, WinTimer t)
        {
            if (!int.TryParse(text, out var ms) || ms <= 0) { SetStatus("Bad period", false); return false; }
            t.Interval = ms;
            return true;
        }
    }
}
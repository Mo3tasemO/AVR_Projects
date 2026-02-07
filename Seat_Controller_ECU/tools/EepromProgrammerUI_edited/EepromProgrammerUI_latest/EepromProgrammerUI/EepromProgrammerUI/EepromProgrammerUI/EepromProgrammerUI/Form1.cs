using System;
using System.Drawing;
using System.IO.Ports;
using System.Windows.Forms;
using System.Drawing.Drawing2D;

namespace EepromProgrammerUI
{
    public partial class Form1 : Form
    {
        private EepromProgrammer _programmer;

        public Form1()
        {
            InitializeComponent();
            ApplyDarkTheme();
            InitializeControls();
        }

        private void ApplyDarkTheme()
        {
            // ----- Dark palette -----
            Color bgForm = Color.FromArgb(30, 30, 30);
            Color bgPanel = Color.FromArgb(37, 37, 38);
            Color bgGroup = Color.FromArgb(37, 37, 38);
            Color bgControl = Color.FromArgb(45, 45, 48);
            Color fgPrimary = Color.White;
            Color fgMuted = Color.Gainsboro;
            Color border = Color.FromArgb(80, 80, 85);

            // ----- Form / chrome -----
            this.BackColor = bgForm;
            this.ForeColor = fgPrimary;

            if (headerPanel != null) headerPanel.BackColor = bgPanel;

            if (statusStrip != null)
            {
                statusStrip.BackColor = bgPanel;
                statusStrip.ForeColor = fgPrimary;
                foreach (ToolStripItem it in statusStrip.Items) it.ForeColor = fgPrimary;
            }

            // ----- TabControl + pages (kill white gaps) -----
            if (tabMain != null)
            {
                tabMain.BackColor = bgForm;                   // background behind pages
                tabMain.Appearance = TabAppearance.Normal;
                tabMain.DrawMode = TabDrawMode.OwnerDrawFixed; // you're owner-drawing rounded tabs
                tabMain.SizeMode = TabSizeMode.Fixed;
                if (tabMain.ItemSize.Height < 36)             // keep a comfortable height
                    tabMain.ItemSize = new Size(tabMain.ItemSize.Width, 36);
                tabMain.Padding = new Point(12, 6);           // spacing around tab text

                foreach (TabPage page in tabMain.TabPages)
                {
                    page.BackColor = bgForm;                  // page surface
                    page.ForeColor = fgPrimary;
                    page.BorderStyle = BorderStyle.None;      // removes default light border
                }
            }

            // ----- Recursively style all controls -----
            void StyleControl(Control c)
            {
                if (c is GroupBox gb)
                {
                    gb.BackColor = bgGroup;
                    gb.ForeColor = fgMuted;
                }
                else if (c is Label lbl)
                {
                    lbl.BackColor = Color.Transparent;
                    lbl.ForeColor = fgMuted;
                }
                else if (c is TextBox tb)
                {
                    tb.BackColor = bgControl;
                    tb.ForeColor = fgPrimary;
                    tb.BorderStyle = BorderStyle.FixedSingle;
                }
                else if (c is ComboBox cb)
                {
                    cb.BackColor = bgControl;
                    cb.ForeColor = fgPrimary;
                    cb.FlatStyle = FlatStyle.Flat;
                }
                else if (c is Button btn)
                {
                    btn.FlatStyle = FlatStyle.Flat;
                    btn.BackColor = bgControl;
                    btn.ForeColor = fgPrimary;
                    btn.FlatAppearance.BorderColor = border;
                }
                else if (c is Panel p)
                {
                    // Header already set; make other panels dark too
                    if (!ReferenceEquals(p, headerPanel))
                        p.BackColor = bgPanel;
                }

                foreach (Control child in c.Controls)
                    StyleControl(child);
            }

            StyleControl(this);
        }

        private GraphicsPath RoundedRect(Rectangle bounds, int radius)
        {
            int d = radius * 2;
            var path = new GraphicsPath();
            path.AddArc(bounds.X, bounds.Y, d, d, 180, 90);
            path.AddArc(bounds.Right - d, bounds.Y, d, d, 270, 90);
            path.AddArc(bounds.Right - d, bounds.Bottom - d, d, d, 0, 90);
            path.AddArc(bounds.X, bounds.Bottom - d, d, d, 90, 90);
            path.CloseFigure();
            return path;
        }

        private void TabMain_DrawItem(object sender, DrawItemEventArgs e)
        {
            e.Graphics.SmoothingMode = SmoothingMode.AntiAlias;

            // Dark palette (matches dark mode below)
            Color tabBg = Color.FromArgb(45, 45, 48);
            Color tabBgSel = Color.FromArgb(62, 62, 66);
            Color tabBorder = Color.FromArgb(80, 80, 85);
            Color tabText = Color.White;

            bool selected = (e.State & DrawItemState.Selected) == DrawItemState.Selected;

            // Compute the tab rectangle (slightly inset for nicer look)
            Rectangle r = e.Bounds;
            r.Inflate(-6, -4);

            using (var path = RoundedRect(r, 8))
            using (var bg = new SolidBrush(selected ? tabBgSel : tabBg))
            using (var pen = new Pen(tabBorder))
            {
                e.Graphics.FillPath(bg, path);
                e.Graphics.DrawPath(pen, path);
            }

            // Draw the tab text centered
            string text = tabMain.TabPages[e.Index].Text;
            using (var sf = new StringFormat { Alignment = StringAlignment.Center, LineAlignment = StringAlignment.Center })
            using (var br = new SolidBrush(tabText))
            {
                e.Graphics.DrawString(text, this.Font, br, r, sf);
            }

            e.DrawFocusRectangle(); // optional
        }

        private void InitializeControls()
        {
            tabMain.DrawItem += TabMain_DrawItem;

            // Populate ports
            string[] ports = SerialPort.GetPortNames();
            comboBox_Port.Items.Clear();
            comboBox_Port.Items.AddRange(ports);
            if (ports.Length > 0) comboBox_Port.SelectedIndex = 0;

            // Wire events
            btnConnect.Click += BtnConnect_Click;
            btnDisconnect.Click += BtnDisconnect_Click;

            // Read
            btnReadByteDec.Click += BtnReadByteDec_Click;
            btnReadByteHex.Click += BtnReadByteHex_Click;
            btnReadAllDec.Click += BtnReadAllDec_Click;
            btnReadAllHex.Click += BtnReadAllHex_Click;

            // Write
            btnWriteByte.Click += BtnWriteByte_Click;
            btnWriteAll.Click += BtnWriteAll_Click;

            // Erase
            btnEraseAll.Click += BtnEraseAll_Click;
            btnEraseRange.Click += BtnEraseRange_Click;
        }

        // ------------------------------
        //  Connection handlers
        // ------------------------------
        private void BtnConnect_Click(object sender, EventArgs e)
        {
            try
            {
                string port = comboBox_Port.SelectedItem?.ToString();
                int baud = ParseIntFlexible(txtBaud.Text);
                if (string.IsNullOrWhiteSpace(port))
                {
                    AppendLog("PC> No COM port selected.");
                    return;
                }

                _programmer = new EepromProgrammer(port, baud);

                // Subscribe to logging events
                _programmer.OnLogMessage += AppendLog;

                _programmer.Connect();

                SetStatus($"Connected to {port} @ {baud}");
                AppendLog("PC> Connected.");
            }
            catch (Exception ex)
            {
                SetStatus("Connection failed.");
                AppendLog("PC> Connection error: " + ex.Message);
            }
        }

        private void BtnDisconnect_Click(object sender, EventArgs e)
        {
            try
            {
                _programmer?.Disconnect();
                SetStatus("Disconnected.");
                AppendLog("PC> Disconnected.");
            }
            catch (Exception ex)
            {
                SetStatus("Disconnect failed.");
                AppendLog("PC> Disconnect error: " + ex.Message);
            }
        }

        // ------------------------------
        //  Read handlers (Dec / Hex)
        // ------------------------------
        private void BtnReadByteDec_Click(object sender, EventArgs e)
        {
            if (!EnsureConnected()) return;
            try
            {
                int addr = ParseIntFlexible(txtReadAddr.Text);
                AppendLog($"PC> Read Byte (Dec) at address {addr}");

                string result = _programmer.ReadByte(addr);
                AppendLog($"DEVICE> {result}");
                SetStatus("Read Byte (Dec) done.");
            }
            catch (FormatException)
            {
                AppendLog("PC> Invalid address format.");
            }
        }

        private void BtnReadByteHex_Click(object sender, EventArgs e)
        {
            if (!EnsureConnected()) return;
            try
            {
                int addr = ParseIntFlexible(txtReadAddr.Text);
                AppendLog($"PC> Read Byte (Hex) at address 0x{addr:X}");

                // ReadByte returns decimal, we'll format as hex for display
                string result = _programmer.ReadByte(addr);
                AppendLog($"DEVICE> {result}");
                SetStatus("Read Byte (Hex) done.");
            }
            catch (FormatException)
            {
                AppendLog("PC> Invalid address format.");
            }
        }

        private void BtnReadAllDec_Click(object sender, EventArgs e)
        {
            if (!EnsureConnected()) return;
            try
            {
                // Check if user specified a size limit
                int size = -1;
                if (!string.IsNullOrWhiteSpace(txtReadAllSize.Text))
                {
                    size = ParseIntFlexible(txtReadAllSize.Text);
                    AppendLog($"PC> Read All (Dec), showing first {size} bytes");
                }
                else
                {
                    AppendLog("PC> Read All (Dec), full EEPROM");
                }

                string result = _programmer.ReadAll(size);
                AppendLog($"DEVICE> {result}");
                SetStatus("Read All (Dec) done.");
            }
            catch (FormatException)
            {
                AppendLog("PC> Invalid size format.");
            }
            catch (Exception ex)
            {
                AppendLog($"PC> Read error: {ex.Message}");
                SetStatus("Read failed.");
            }
        }

        private void BtnReadAllHex_Click(object sender, EventArgs e)
        {
            if (!EnsureConnected()) return;
            try
            {
                AppendLog("PC> Read All (Hex)");

                string result = _programmer.ReadAllHex();
                AppendLog($"DEVICE> {result}");
                SetStatus("Read All (Hex) done.");
            }
            catch (FormatException)
            {
                AppendLog("PC> Invalid size format.");
            }
        }

        // ------------------------------
        //  Write handlers
        // ------------------------------
        private void BtnWriteByte_Click(object sender, EventArgs e)
        {
            if (!EnsureConnected()) return;
            try
            {
                int addr = ParseIntFlexible(txtWriteAddr.Text);
                int val = ParseIntFlexible(txtWriteVal.Text);

                // Validate byte range
                if (val < 0 || val > 255)
                {
                    AppendLog("PC> Value must be between 0-255");
                    return;
                }

                // The EepromProgrammer class now handles logging internally
                string result = _programmer.WriteByte(addr, (byte)val);
                SetStatus("Write Byte done.");
            }
            catch (FormatException)
            {
                AppendLog("PC> Invalid address/value format.");
            }
            catch (Exception ex)
            {
                AppendLog($"PC> Write error: {ex.Message}");
                SetStatus("Write failed.");
            }
        }

        private void BtnWriteAll_Click(object sender, EventArgs e)
        {
            if (!EnsureConnected()) return;
            try
            {
                int size = ParseIntFlexible(txtWriteAllSize.Text);
                int val = ParseIntFlexible(txtWriteAllVal.Text);
                AppendLog($"PC> Write All, fill {size} bytes with {val} (0x{val:X2})");

                string result = _programmer.WriteAllFill(size, (byte)val);
                AppendLog($"DEVICE> {result}");
                SetStatus("Write All done.");
            }
            catch (FormatException)
            {
                AppendLog("PC> Invalid size/value format.");
            }
        }

        // ------------------------------
        //  Erase handlers
        // ------------------------------
        private void BtnEraseAll_Click(object sender, EventArgs e)
        {
            if (!EnsureConnected()) return;
            AppendLog("PC> Erase All");

            string result = _programmer.EraseAll();
            AppendLog($"DEVICE> {result}");
            SetStatus("Erase All done.");
        }

        private void BtnEraseRange_Click(object sender, EventArgs e)
        {
            if (!EnsureConnected()) return;
            try
            {
                int start = ParseIntFlexible(txtEraseStart.Text);
                int size = ParseIntFlexible(txtEraseSize.Text);
                AppendLog($"PC> Erase Range: start=0x{start:X}, size={size}");

                string result = _programmer.EraseRange(start, size);
                AppendLog($"DEVICE> {result}");
                SetStatus("Erase Range done.");
            }
            catch (FormatException)
            {
                AppendLog("PC> Invalid start/size format.");
            }
        }

        // ------------------------------
        //  Helper methods (FIXED - these were missing!)
        // ------------------------------
        private bool EnsureConnected()
        {
            if (_programmer == null || !_programmer.IsConnected())
            {
                AppendLog("PC> Not connected to device.");
                SetStatus("Not connected.");
                return false;
            }
            return true;
        }

        private void AppendLog(string message)
        {
            if (rtbLog.InvokeRequired)
            {
                rtbLog.Invoke(new Action(() => AppendLog(message)));
                return;
            }
            rtbLog.AppendText(message + Environment.NewLine);
            rtbLog.ScrollToCaret();
        }

        // FIXED: Added missing SetStatus method
        private void SetStatus(string message)
        {
            if (statusStrip?.Items.Count > 0 && statusStrip.Items[0] is ToolStripStatusLabel statusLabel)
            {
                if (statusStrip.InvokeRequired)
                {
                    statusStrip.Invoke(new Action(() => SetStatus(message)));
                    return;
                }
                statusLabel.Text = message;
            }
        }

        // FIXED: Added missing ParseIntFlexible method
        private int ParseIntFlexible(string input)
        {
            if (string.IsNullOrWhiteSpace(input))
                throw new FormatException("Input is null or empty");

            input = input.Trim();

            // Handle hex format (0x prefix or 0X prefix)
            if (input.StartsWith("0x", StringComparison.OrdinalIgnoreCase))
            {
                return Convert.ToInt32(input.Substring(2), 16);
            }

            // Handle decimal format
            if (int.TryParse(input, out int result))
            {
                return result;
            }

            // Try as hex without prefix (fallback)
            try
            {
                return Convert.ToInt32(input, 16);
            }
            catch
            {
                throw new FormatException($"Cannot parse '{input}' as integer (decimal or hex)");
            }
        }
    }
}
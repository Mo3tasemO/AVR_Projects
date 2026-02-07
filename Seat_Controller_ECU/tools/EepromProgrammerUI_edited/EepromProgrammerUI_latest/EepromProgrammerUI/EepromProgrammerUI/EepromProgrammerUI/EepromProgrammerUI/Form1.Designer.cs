using System;
using System.Drawing;
using System.Windows.Forms;

namespace EepromProgrammerUI
{
    partial class Form1
    {
        private System.ComponentModel.IContainer components = null;

        // Header
        private Panel headerPanel;
        private Label lblPort;
        private ComboBox comboBox_Port;
        private Label lblBaud;
        private TextBox txtBaud;
        private Button btnConnect;
        private Button btnDisconnect;

        // Main
        private TabControl tabMain;
        private TabPage tabRead;
        private TabPage tabWrite;
        private TabPage tabErase;
        private StatusStrip statusStrip;
        private ToolStripStatusLabel statusLabel;
        private ToolTip tips;

        // Read tab
        private GroupBox grpReadByte;
        private Label lblReadAddr;
        private TextBox txtReadAddr;
        private Button btnReadByteDec;
        private Button btnReadByteHex;

        private GroupBox grpReadAll;
        private Label lblReadAllSize;
        private TextBox txtReadAllSize;
        private Button btnReadAllDec;
        private Button btnReadAllHex;

        // Write tab
        private GroupBox grpWriteByte;
        private Label lblWriteAddr;
        private TextBox txtWriteAddr;
        private Label lblWriteVal;
        private TextBox txtWriteVal;
        private Button btnWriteByte;

        private GroupBox grpWriteAll;
        private Label lblWriteAllStart;   // NEW
        private TextBox txtWriteAllStart; // NEW
        private Label lblWriteAllSize;
        private TextBox txtWriteAllSize;
        private Label lblWriteAllVal;
        private TextBox txtWriteAllVal;
        private Button btnWriteAll;

        // Erase tab
        private GroupBox grpEraseAll;
        private Button btnEraseAll;

        private GroupBox grpEraseRange;
        private Label lblEraseStart;
        private TextBox txtEraseStart;
        private Label lblEraseSize;
        private TextBox txtEraseSize;
        private Button btnEraseRange;

        // === NEW: Log Console ===
        private RichTextBox rtbLog;

        /// <summary>Clean up any resources being used.</summary>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
                components.Dispose();
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        private void InitializeComponent()
        {
            components = new System.ComponentModel.Container();
            tips = new ToolTip(components);

            // === Form ===
            this.SuspendLayout();
            this.Font = new Font("Segoe UI", 9F, FontStyle.Regular, GraphicsUnit.Point);
            this.BackColor = Color.White;
            this.MinimumSize = new Size(860, 540);
            this.Text = "EEPROM Programmer";
            this.StartPosition = FormStartPosition.CenterScreen;

            // === Header Panel ===
            headerPanel = new Panel
            {
                Dock = DockStyle.Top,
                Height = 64,
                BackColor = Color.FromArgb(246, 248, 250),
                Padding = new Padding(16, 12, 16, 12)
            };

            lblPort = new Label { Text = "Port:", AutoSize = true, Location = new Point(8, 20) };
            comboBox_Port = new ComboBox
            {
                DropDownStyle = ComboBoxStyle.DropDownList,
                Location = new Point(48, 16),
                Width = 140
            };

            lblBaud = new Label { Text = "Baud:", AutoSize = true, Location = new Point(204, 20) };
            txtBaud = new TextBox { Location = new Point(252, 16), Width = 100, Text = "9600" };

            btnConnect = new Button { Text = "Connect", Location = new Point(370, 14), Size = new Size(100, 30) };
            btnDisconnect = new Button { Text = "Disconnect", Location = new Point(478, 14), Size = new Size(100, 30) };

            headerPanel.Controls.AddRange(new Control[] { lblPort, comboBox_Port, lblBaud, txtBaud, btnConnect, btnDisconnect });

            // === TabControl ===
            tabMain = new TabControl { Dock = DockStyle.Fill, Padding = new Point(12, 6) };
            tabMain.DrawMode = TabDrawMode.OwnerDrawFixed;
            tabMain.SizeMode = TabSizeMode.Fixed;
            tabMain.ItemSize = new Size(140, 36);
            tabRead = new TabPage("Read Operations");
            tabWrite = new TabPage("Write Operations");
            tabErase = new TabPage("Erase Operations");

            // === StatusStrip ===
            statusStrip = new StatusStrip();
            statusLabel = new ToolStripStatusLabel("Ready");
            statusStrip.Items.Add(statusLabel);

            // ---------- Read Tab ----------
            grpReadByte = new GroupBox
            {
                Text = "Read Byte",
                Location = new Point(16, 16),
                Size = new Size(380, 120),
                Anchor = AnchorStyles.Top | AnchorStyles.Left
            };
            lblReadAddr = new Label { Text = "Address:", Location = new Point(16, 32), AutoSize = true };
            txtReadAddr = new TextBox { Location = new Point(80, 28), Width = 120 };
            btnReadByteDec = new Button { Text = "Read Byte (Dec)", Location = new Point(210, 25), Size = new Size(150, 30) };
            btnReadByteHex = new Button { Text = "Read Byte (Hex)", Location = new Point(210, 65), Size = new Size(150, 30) };
            grpReadByte.Controls.AddRange(new Control[] { lblReadAddr, txtReadAddr, btnReadByteDec, btnReadByteHex });

            grpReadAll = new GroupBox
            {
                Text = "Read Block",
                Location = new Point(412, 16),
                Size = new Size(412, 120),
                Anchor = AnchorStyles.Top | AnchorStyles.Left | AnchorStyles.Right
            };
            lblReadAllSize = new Label { Text = "Size:", Location = new Point(16, 32), AutoSize = true };
            txtReadAllSize = new TextBox { Location = new Point(60, 28), Width = 110 };
            btnReadAllDec = new Button { Text = "Read All (Dec)", Location = new Point(184, 25), Size = new Size(110, 30) };
            btnReadAllHex = new Button { Text = "Read All (Hex)", Location = new Point(302, 25), Size = new Size(110, 30) };
            grpReadAll.Controls.AddRange(new Control[] { lblReadAllSize, txtReadAllSize, btnReadAllDec, btnReadAllHex });

            tabRead.Controls.AddRange(new Control[] { grpReadByte, grpReadAll });

            // ---------- Write Tab ----------
            grpWriteByte = new GroupBox
            {
                Text = "Write Byte",
                Location = new Point(16, 16),
                Size = new Size(420, 120),
                Anchor = AnchorStyles.Top | AnchorStyles.Left
            };
            lblWriteAddr = new Label { Text = "Address:", Location = new Point(16, 32), AutoSize = true };
            txtWriteAddr = new TextBox { Location = new Point(80, 28), Width = 100 };
            lblWriteVal = new Label { Text = "Value:", Location = new Point(190, 32), AutoSize = true };
            txtWriteVal = new TextBox { Location = new Point(238, 28), Width = 100 };
            btnWriteByte = new Button { Text = "Write Byte", Location = new Point(16, 70), Size = new Size(150, 30) };
            grpWriteByte.Controls.AddRange(new Control[] { lblWriteAddr, txtWriteAddr, lblWriteVal, txtWriteVal, btnWriteByte });

            grpWriteAll = new GroupBox
            {
                Text = "Write Block (fill)",
                Location = new Point(448, 16),
                Size = new Size(376, 120),
                Anchor = AnchorStyles.Top | AnchorStyles.Left | AnchorStyles.Right
            };
            lblWriteAllStart = new Label { Text = "Start:", Location = new Point(16, 32), AutoSize = true };
            txtWriteAllStart = new TextBox { Location = new Point(60, 28), Width = 90 };
            lblWriteAllSize = new Label { Text = "Size:", Location = new Point(160, 32), AutoSize = true };
            txtWriteAllSize = new TextBox { Location = new Point(200, 28), Width = 90 };
            lblWriteAllVal = new Label { Text = "Value:", Location = new Point(300, 32), AutoSize = true };
            txtWriteAllVal = new TextBox { Location = new Point(350, 28), Width = 90 };
            btnWriteAll = new Button { Text = "Write All", Location = new Point(16, 70), Size = new Size(140, 30) };
            grpWriteAll.Controls.AddRange(new Control[] { lblWriteAllStart, txtWriteAllStart, lblWriteAllSize, txtWriteAllSize, lblWriteAllVal, txtWriteAllVal, btnWriteAll });

            tabWrite.Controls.AddRange(new Control[] { grpWriteByte, grpWriteAll });

            // ---------- Erase Tab ----------
            grpEraseAll = new GroupBox { Text = "Erase Entire Chip", Location = new Point(16, 16), Size = new Size(300, 100) };
            btnEraseAll = new Button { Text = "Erase All", Location = new Point(16, 36), Size = new Size(120, 32) };
            grpEraseAll.Controls.Add(btnEraseAll);

            grpEraseRange = new GroupBox
            {
                Text = "Erase Range",
                Location = new Point(336, 16),
                Size = new Size(488, 100),
                Anchor = AnchorStyles.Top | AnchorStyles.Left | AnchorStyles.Right
            };
            lblEraseStart = new Label { Text = "Start:", Location = new Point(16, 32), AutoSize = true };
            txtEraseStart = new TextBox { Location = new Point(60, 28), Width = 90 };
            lblEraseSize = new Label { Text = "Size:", Location = new Point(160, 32), AutoSize = true };
            txtEraseSize = new TextBox { Location = new Point(200, 28), Width = 90 };
            btnEraseRange = new Button { Text = "Erase Range", Location = new Point(16, 60), Size = new Size(140, 32) };
            grpEraseRange.Controls.AddRange(new Control[] { lblEraseStart, txtEraseStart, lblEraseSize, txtEraseSize, btnEraseRange });

            tabErase.Controls.AddRange(new Control[] { grpEraseAll, grpEraseRange });

            // === Log Console ===
            rtbLog = new RichTextBox
            {
                Dock = DockStyle.Bottom,
                Height = 160,
                ReadOnly = true,
                BackColor = Color.Black,
                ForeColor = Color.Lime,
                Font = new Font("Consolas", 9F, FontStyle.Regular, GraphicsUnit.Point)
            };

            // Add controls to form
            tabMain.TabPages.AddRange(new TabPage[] { tabRead, tabWrite, tabErase });
            this.Controls.Add(tabMain);
            this.Controls.Add(headerPanel);
            this.Controls.Add(rtbLog);      // << NEW
            this.Controls.Add(statusStrip);

            // Tooltips
            tips.SetToolTip(btnConnect, "Open serial connection");
            tips.SetToolTip(btnDisconnect, "Close serial connection");

            this.ResumeLayout(false);
            this.PerformLayout();
        }

        #endregion
    }
}

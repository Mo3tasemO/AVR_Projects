namespace EepromProgrammerUI
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.tabPage_ReadByte = new System.Windows.Forms.TabPage();
            this.btnReadByte = new System.Windows.Forms.Button();
            this.txtAddress_Read = new System.Windows.Forms.TextBox();
            this.lblAddress_Read = new System.Windows.Forms.Label();
            this.tabPage_WriteByte = new System.Windows.Forms.TabPage();
            this.btnWriteByte = new System.Windows.Forms.Button();
            this.txtValue_Write = new System.Windows.Forms.TextBox();
            this.lblValue_Write = new System.Windows.Forms.Label();
            this.txtAddress_Write = new System.Windows.Forms.TextBox();
            this.lblAddress_Write = new System.Windows.Forms.Label();
            this.tabControl_Operations = new System.Windows.Forms.TabPage();
            this.txtSize_ReadAll = new System.Windows.Forms.TextBox();
            this.btnReadAll = new System.Windows.Forms.Button();
            this.lblSize_ReadAll = new System.Windows.Forms.Label();
            this.tabPage_WriteAll = new System.Windows.Forms.TabPage();
            this.rtbData_WriteAll = new System.Windows.Forms.RichTextBox();
            this.txtSize_WriteAll = new System.Windows.Forms.TextBox();
            this.lblData_WriteAll = new System.Windows.Forms.Label();
            this.lblSize_WriteAll = new System.Windows.Forms.Label();
            this.btnWriteAll = new System.Windows.Forms.Button();
            this.btnConnect = new System.Windows.Forms.Button();
            this.lblPort = new System.Windows.Forms.Label();
            this.comboBox_Port = new System.Windows.Forms.ComboBox();
            this.lblBaud = new System.Windows.Forms.Label();
            this.rtbLog = new System.Windows.Forms.RichTextBox();
            this.txtBaud = new System.Windows.Forms.TextBox();
            this.tabControl1.SuspendLayout();
            this.tabPage_ReadByte.SuspendLayout();
            this.tabPage_WriteByte.SuspendLayout();
            this.tabControl_Operations.SuspendLayout();
            this.tabPage_WriteAll.SuspendLayout();
            this.SuspendLayout();
            // 
            // tabControl1
            // 
            this.tabControl1.Controls.Add(this.tabPage_ReadByte);
            this.tabControl1.Controls.Add(this.tabPage_WriteByte);
            this.tabControl1.Controls.Add(this.tabControl_Operations);
            this.tabControl1.Controls.Add(this.tabPage_WriteAll);
            this.tabControl1.Location = new System.Drawing.Point(12, 54);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(784, 158);
            this.tabControl1.TabIndex = 0;
            // 
            // tabPage_ReadByte
            // 
            this.tabPage_ReadByte.Controls.Add(this.btnReadByte);
            this.tabPage_ReadByte.Controls.Add(this.txtAddress_Read);
            this.tabPage_ReadByte.Controls.Add(this.lblAddress_Read);
            this.tabPage_ReadByte.Location = new System.Drawing.Point(4, 25);
            this.tabPage_ReadByte.Name = "tabPage_ReadByte";
            this.tabPage_ReadByte.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage_ReadByte.Size = new System.Drawing.Size(776, 129);
            this.tabPage_ReadByte.TabIndex = 0;
            this.tabPage_ReadByte.Text = "Read Byte";
            this.tabPage_ReadByte.UseVisualStyleBackColor = true;
            // 
            // btnReadByte
            // 
            this.btnReadByte.Location = new System.Drawing.Point(239, 16);
            this.btnReadByte.Name = "btnReadByte";
            this.btnReadByte.Size = new System.Drawing.Size(75, 23);
            this.btnReadByte.TabIndex = 2;
            this.btnReadByte.Text = "Read";
            this.btnReadByte.UseVisualStyleBackColor = true;
            this.btnReadByte.Click += new System.EventHandler(this.btnReadByte_Click);
            // 
            // txtAddress_Read
            // 
            this.txtAddress_Read.Location = new System.Drawing.Point(116, 18);
            this.txtAddress_Read.Name = "txtAddress_Read";
            this.txtAddress_Read.Size = new System.Drawing.Size(100, 22);
            this.txtAddress_Read.TabIndex = 1;
            // 
            // lblAddress_Read
            // 
            this.lblAddress_Read.AutoSize = true;
            this.lblAddress_Read.Location = new System.Drawing.Point(29, 18);
            this.lblAddress_Read.Name = "lblAddress_Read";
            this.lblAddress_Read.Size = new System.Drawing.Size(61, 16);
            this.lblAddress_Read.TabIndex = 0;
            this.lblAddress_Read.Text = "Address:";
            // 
            // tabPage_WriteByte
            // 
            this.tabPage_WriteByte.Controls.Add(this.btnWriteByte);
            this.tabPage_WriteByte.Controls.Add(this.txtValue_Write);
            this.tabPage_WriteByte.Controls.Add(this.lblValue_Write);
            this.tabPage_WriteByte.Controls.Add(this.txtAddress_Write);
            this.tabPage_WriteByte.Controls.Add(this.lblAddress_Write);
            this.tabPage_WriteByte.Location = new System.Drawing.Point(4, 25);
            this.tabPage_WriteByte.Name = "tabPage_WriteByte";
            this.tabPage_WriteByte.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage_WriteByte.Size = new System.Drawing.Size(776, 129);
            this.tabPage_WriteByte.TabIndex = 1;
            this.tabPage_WriteByte.Text = "Write Byte";
            this.tabPage_WriteByte.UseVisualStyleBackColor = true;
            // 
            // btnWriteByte
            // 
            this.btnWriteByte.Location = new System.Drawing.Point(568, 46);
            this.btnWriteByte.Name = "btnWriteByte";
            this.btnWriteByte.Size = new System.Drawing.Size(75, 23);
            this.btnWriteByte.TabIndex = 4;
            this.btnWriteByte.Text = "Write";
            this.btnWriteByte.UseVisualStyleBackColor = true;
            // 
            // txtValue_Write
            // 
            this.txtValue_Write.Location = new System.Drawing.Point(459, 46);
            this.txtValue_Write.Name = "txtValue_Write";
            this.txtValue_Write.Size = new System.Drawing.Size(100, 22);
            this.txtValue_Write.TabIndex = 3;
            // 
            // lblValue_Write
            // 
            this.lblValue_Write.AutoSize = true;
            this.lblValue_Write.Location = new System.Drawing.Point(408, 46);
            this.lblValue_Write.Name = "lblValue_Write";
            this.lblValue_Write.Size = new System.Drawing.Size(45, 16);
            this.lblValue_Write.TabIndex = 2;
            this.lblValue_Write.Text = "Value:";
            // 
            // txtAddress_Write
            // 
            this.txtAddress_Write.Location = new System.Drawing.Point(144, 42);
            this.txtAddress_Write.Name = "txtAddress_Write";
            this.txtAddress_Write.Size = new System.Drawing.Size(100, 22);
            this.txtAddress_Write.TabIndex = 1;
            // 
            // lblAddress_Write
            // 
            this.lblAddress_Write.AutoSize = true;
            this.lblAddress_Write.Location = new System.Drawing.Point(64, 42);
            this.lblAddress_Write.Name = "lblAddress_Write";
            this.lblAddress_Write.Size = new System.Drawing.Size(61, 16);
            this.lblAddress_Write.TabIndex = 0;
            this.lblAddress_Write.Text = "Address:";
            // 
            // tabControl_Operations
            // 
            this.tabControl_Operations.Controls.Add(this.txtSize_ReadAll);
            this.tabControl_Operations.Controls.Add(this.btnReadAll);
            this.tabControl_Operations.Controls.Add(this.lblSize_ReadAll);
            this.tabControl_Operations.Location = new System.Drawing.Point(4, 25);
            this.tabControl_Operations.Name = "tabControl_Operations";
            this.tabControl_Operations.Padding = new System.Windows.Forms.Padding(3);
            this.tabControl_Operations.Size = new System.Drawing.Size(776, 129);
            this.tabControl_Operations.TabIndex = 2;
            this.tabControl_Operations.Text = "Read All";
            this.tabControl_Operations.UseVisualStyleBackColor = true;
            // 
            // txtSize_ReadAll
            // 
            this.txtSize_ReadAll.Location = new System.Drawing.Point(122, 35);
            this.txtSize_ReadAll.Name = "txtSize_ReadAll";
            this.txtSize_ReadAll.Size = new System.Drawing.Size(100, 22);
            this.txtSize_ReadAll.TabIndex = 6;
            // 
            // btnReadAll
            // 
            this.btnReadAll.Location = new System.Drawing.Point(252, 38);
            this.btnReadAll.Name = "btnReadAll";
            this.btnReadAll.Size = new System.Drawing.Size(75, 23);
            this.btnReadAll.TabIndex = 1;
            this.btnReadAll.Text = "Read All";
            this.btnReadAll.UseVisualStyleBackColor = true;
            this.btnReadAll.Click += new System.EventHandler(this.btnReadAll_Click_1);
            // 
            // lblSize_ReadAll
            // 
            this.lblSize_ReadAll.AutoSize = true;
            this.lblSize_ReadAll.Location = new System.Drawing.Point(80, 38);
            this.lblSize_ReadAll.Name = "lblSize_ReadAll";
            this.lblSize_ReadAll.Size = new System.Drawing.Size(36, 16);
            this.lblSize_ReadAll.TabIndex = 0;
            this.lblSize_ReadAll.Text = "Size:";
            // 
            // tabPage_WriteAll
            // 
            this.tabPage_WriteAll.Controls.Add(this.rtbData_WriteAll);
            this.tabPage_WriteAll.Controls.Add(this.txtSize_WriteAll);
            this.tabPage_WriteAll.Controls.Add(this.lblData_WriteAll);
            this.tabPage_WriteAll.Controls.Add(this.lblSize_WriteAll);
            this.tabPage_WriteAll.Controls.Add(this.btnWriteAll);
            this.tabPage_WriteAll.Location = new System.Drawing.Point(4, 25);
            this.tabPage_WriteAll.Name = "tabPage_WriteAll";
            this.tabPage_WriteAll.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage_WriteAll.Size = new System.Drawing.Size(776, 129);
            this.tabPage_WriteAll.TabIndex = 3;
            this.tabPage_WriteAll.Text = "Write All";
            this.tabPage_WriteAll.UseVisualStyleBackColor = true;
            // 
            // rtbData_WriteAll
            // 
            this.rtbData_WriteAll.Location = new System.Drawing.Point(320, 34);
            this.rtbData_WriteAll.Name = "rtbData_WriteAll";
            this.rtbData_WriteAll.Size = new System.Drawing.Size(125, 74);
            this.rtbData_WriteAll.TabIndex = 8;
            this.rtbData_WriteAll.Text = "";
            // 
            // txtSize_WriteAll
            // 
            this.txtSize_WriteAll.Location = new System.Drawing.Point(125, 52);
            this.txtSize_WriteAll.Name = "txtSize_WriteAll";
            this.txtSize_WriteAll.Size = new System.Drawing.Size(100, 22);
            this.txtSize_WriteAll.TabIndex = 7;
            // 
            // lblData_WriteAll
            // 
            this.lblData_WriteAll.AutoSize = true;
            this.lblData_WriteAll.Location = new System.Drawing.Point(275, 59);
            this.lblData_WriteAll.Name = "lblData_WriteAll";
            this.lblData_WriteAll.Size = new System.Drawing.Size(39, 16);
            this.lblData_WriteAll.TabIndex = 6;
            this.lblData_WriteAll.Text = "Data:";
            // 
            // lblSize_WriteAll
            // 
            this.lblSize_WriteAll.AutoSize = true;
            this.lblSize_WriteAll.Location = new System.Drawing.Point(59, 59);
            this.lblSize_WriteAll.Name = "lblSize_WriteAll";
            this.lblSize_WriteAll.Size = new System.Drawing.Size(36, 16);
            this.lblSize_WriteAll.TabIndex = 1;
            this.lblSize_WriteAll.Text = "Size:";
            // 
            // btnWriteAll
            // 
            this.btnWriteAll.Location = new System.Drawing.Point(461, 59);
            this.btnWriteAll.Name = "btnWriteAll";
            this.btnWriteAll.Size = new System.Drawing.Size(75, 23);
            this.btnWriteAll.TabIndex = 0;
            this.btnWriteAll.Text = "Write All";
            this.btnWriteAll.UseVisualStyleBackColor = true;
            // 
            // btnConnect
            // 
            this.btnConnect.Location = new System.Drawing.Point(701, 20);
            this.btnConnect.Name = "btnConnect";
            this.btnConnect.Size = new System.Drawing.Size(75, 23);
            this.btnConnect.TabIndex = 1;
            this.btnConnect.Text = "Connect";
            this.btnConnect.UseVisualStyleBackColor = true;
            // 
            // lblPort
            // 
            this.lblPort.AutoSize = true;
            this.lblPort.Location = new System.Drawing.Point(394, 20);
            this.lblPort.Name = "lblPort";
            this.lblPort.Size = new System.Drawing.Size(31, 16);
            this.lblPort.TabIndex = 2;
            this.lblPort.Text = "Port";
            // 
            // comboBox_Port
            // 
            this.comboBox_Port.FormattingEnabled = true;
            this.comboBox_Port.Location = new System.Drawing.Point(431, 17);
            this.comboBox_Port.Name = "comboBox_Port";
            this.comboBox_Port.Size = new System.Drawing.Size(121, 24);
            this.comboBox_Port.TabIndex = 3;
            // 
            // lblBaud
            // 
            this.lblBaud.AutoSize = true;
            this.lblBaud.Location = new System.Drawing.Point(581, 20);
            this.lblBaud.Name = "lblBaud";
            this.lblBaud.Size = new System.Drawing.Size(42, 16);
            this.lblBaud.TabIndex = 4;
            this.lblBaud.Text = "Baud:";
            // 
            // rtbLog
            // 
            this.rtbLog.Location = new System.Drawing.Point(10, 349);
            this.rtbLog.Name = "rtbLog";
            this.rtbLog.ReadOnly = true;
            this.rtbLog.Size = new System.Drawing.Size(782, 96);
            this.rtbLog.TabIndex = 6;
            this.rtbLog.Text = "";
            this.rtbLog.Click += new System.EventHandler(this.rtbLog_Click);
            // 
            // txtBaud
            // 
            this.txtBaud.Location = new System.Drawing.Point(620, 19);
            this.txtBaud.Name = "txtBaud";
            this.txtBaud.Size = new System.Drawing.Size(75, 22);
            this.txtBaud.TabIndex = 7;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.txtBaud);
            this.Controls.Add(this.rtbLog);
            this.Controls.Add(this.lblBaud);
            this.Controls.Add(this.comboBox_Port);
            this.Controls.Add(this.lblPort);
            this.Controls.Add(this.btnConnect);
            this.Controls.Add(this.tabControl1);
            this.Name = "Form1";
            this.Text = "Eeprom Control Panel";
            this.tabControl1.ResumeLayout(false);
            this.tabPage_ReadByte.ResumeLayout(false);
            this.tabPage_ReadByte.PerformLayout();
            this.tabPage_WriteByte.ResumeLayout(false);
            this.tabPage_WriteByte.PerformLayout();
            this.tabControl_Operations.ResumeLayout(false);
            this.tabControl_Operations.PerformLayout();
            this.tabPage_WriteAll.ResumeLayout(false);
            this.tabPage_WriteAll.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.TabPage tabPage_ReadByte;
        private System.Windows.Forms.TabPage tabPage_WriteByte;
        private System.Windows.Forms.TabPage tabControl_Operations;
        private System.Windows.Forms.TabPage tabPage_WriteAll;
        private System.Windows.Forms.Button btnConnect;
        private System.Windows.Forms.Label lblPort;
        private System.Windows.Forms.ComboBox comboBox_Port;
        private System.Windows.Forms.Label lblBaud;
        private System.Windows.Forms.Button btnReadByte;
        private System.Windows.Forms.TextBox txtAddress_Read;
        private System.Windows.Forms.Label lblAddress_Read;
        private System.Windows.Forms.TextBox txtAddress_Write;
        private System.Windows.Forms.Label lblAddress_Write;
        private System.Windows.Forms.Button btnWriteByte;
        private System.Windows.Forms.TextBox txtValue_Write;
        private System.Windows.Forms.Label lblValue_Write;
        private System.Windows.Forms.TextBox txtSize_ReadAll;
        private System.Windows.Forms.Button btnReadAll;
        private System.Windows.Forms.Label lblSize_ReadAll;
        private System.Windows.Forms.RichTextBox rtbData_WriteAll;
        private System.Windows.Forms.TextBox txtSize_WriteAll;
        private System.Windows.Forms.Label lblData_WriteAll;
        private System.Windows.Forms.Label lblSize_WriteAll;
        private System.Windows.Forms.Button btnWriteAll;
        private System.Windows.Forms.RichTextBox rtbLog;
        private System.Windows.Forms.TextBox txtBaud;
    }
}


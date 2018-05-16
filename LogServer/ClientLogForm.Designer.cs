namespace LogServer
{
    partial class ClientLogForm
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
            this.components = new System.ComponentModel.Container();
            this.fConsole1 = new WindowsForm.Console.FConsole();
            this.btnExcute = new System.Windows.Forms.Button();
            this.ccbCommand = new System.Windows.Forms.ComboBox();
            this.label1 = new System.Windows.Forms.Label();
            this.lbStatus = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.lbExceptionCount = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.lbTime = new System.Windows.Forms.Label();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.label2 = new System.Windows.Forms.Label();
            this.lbLogCount = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // fConsole1
            // 
            this.fConsole1.Arguments = new string[0];
            this.fConsole1.AutoScrollToEndLine = true;
            this.fConsole1.BackColor = System.Drawing.Color.Black;
            this.fConsole1.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.fConsole1.Font = new System.Drawing.Font("Consolas", 10F);
            this.fConsole1.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(223)))), ((int)(((byte)(216)))), ((int)(((byte)(194)))));
            this.fConsole1.HyperlinkColor = System.Drawing.Color.Empty;
            this.fConsole1.Location = new System.Drawing.Point(3, 26);
            this.fConsole1.MinimumSize = new System.Drawing.Size(470, 200);
            this.fConsole1.Name = "fConsole1";
            this.fConsole1.ReadOnly = true;
            this.fConsole1.ScrollBars = System.Windows.Forms.RichTextBoxScrollBars.Vertical;
            this.fConsole1.SecureReadLine = true;
            this.fConsole1.Size = new System.Drawing.Size(762, 453);
            this.fConsole1.State = WindowsForm.Console.Enums.ConsoleState.Writing;
            this.fConsole1.TabIndex = 0;
            this.fConsole1.Text = "";
            this.fConsole1.Title = "ClientLogForm";
            // 
            // btnExcute
            // 
            this.btnExcute.Location = new System.Drawing.Point(673, 485);
            this.btnExcute.Name = "btnExcute";
            this.btnExcute.Size = new System.Drawing.Size(92, 23);
            this.btnExcute.TabIndex = 2;
            this.btnExcute.Text = "Execute";
            this.btnExcute.UseVisualStyleBackColor = true;
            this.btnExcute.Click += new System.EventHandler(this.btnExcute_Click);
            // 
            // ccbCommand
            // 
            this.ccbCommand.BackColor = System.Drawing.Color.Black;
            this.ccbCommand.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(223)))), ((int)(((byte)(216)))), ((int)(((byte)(194)))));
            this.ccbCommand.FormattingEnabled = true;
            this.ccbCommand.Items.AddRange(new object[] {
            "clear"});
            this.ccbCommand.Location = new System.Drawing.Point(3, 487);
            this.ccbCommand.Name = "ccbCommand";
            this.ccbCommand.Size = new System.Drawing.Size(664, 20);
            this.ccbCommand.TabIndex = 3;
            this.ccbCommand.KeyDown += new System.Windows.Forms.KeyEventHandler(this.ccbCommand_KeyDown);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 8);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(47, 12);
            this.label1.TabIndex = 4;
            this.label1.Text = "Statue:";
            // 
            // lbStatus
            // 
            this.lbStatus.AutoSize = true;
            this.lbStatus.ForeColor = System.Drawing.SystemColors.WindowText;
            this.lbStatus.Location = new System.Drawing.Point(60, 8);
            this.lbStatus.Name = "lbStatus";
            this.lbStatus.Size = new System.Drawing.Size(59, 12);
            this.lbStatus.TabIndex = 5;
            this.lbStatus.Text = "Connected";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(337, 8);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(95, 12);
            this.label3.TabIndex = 6;
            this.label3.Text = "ExceptionCount:";
            // 
            // lbExceptionCount
            // 
            this.lbExceptionCount.AutoSize = true;
            this.lbExceptionCount.ForeColor = System.Drawing.Color.Red;
            this.lbExceptionCount.Location = new System.Drawing.Point(438, 8);
            this.lbExceptionCount.Name = "lbExceptionCount";
            this.lbExceptionCount.Size = new System.Drawing.Size(11, 12);
            this.lbExceptionCount.TabIndex = 7;
            this.lbExceptionCount.Text = "0";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(535, 8);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(77, 12);
            this.label5.TabIndex = 8;
            this.label5.Text = "Runing Time:";
            // 
            // lbTime
            // 
            this.lbTime.AutoSize = true;
            this.lbTime.Location = new System.Drawing.Point(618, 8);
            this.lbTime.Name = "lbTime";
            this.lbTime.Size = new System.Drawing.Size(47, 12);
            this.lbTime.TabIndex = 9;
            this.lbTime.Text = "0:00:00";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(174, 8);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(59, 12);
            this.label2.TabIndex = 10;
            this.label2.Text = "LogCount:";
            // 
            // lbLogCount
            // 
            this.lbLogCount.AutoSize = true;
            this.lbLogCount.Location = new System.Drawing.Point(239, 8);
            this.lbLogCount.Name = "lbLogCount";
            this.lbLogCount.Size = new System.Drawing.Size(11, 12);
            this.lbLogCount.TabIndex = 11;
            this.lbLogCount.Text = "0";
            // 
            // ClientLogForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(777, 509);
            this.Controls.Add(this.lbLogCount);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.lbTime);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.lbExceptionCount);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.lbStatus);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.ccbCommand);
            this.Controls.Add(this.btnExcute);
            this.Controls.Add(this.fConsole1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
            this.Name = "ClientLogForm";
            this.Text = "ClientLogForm";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.ClientLogForm_FormClosing);
            this.Load += new System.EventHandler(this.ClientLogForm_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private WindowsForm.Console.FConsole fConsole1;
        private System.Windows.Forms.Button btnExcute;
        private System.Windows.Forms.ComboBox ccbCommand;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label lbStatus;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label lbExceptionCount;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label lbTime;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label lbLogCount;
    }
}
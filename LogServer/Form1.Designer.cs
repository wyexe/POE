namespace LogServer
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
            this.components = new System.ComponentModel.Container();
            this.label1 = new System.Windows.Forms.Label();
            this.lbClient = new System.Windows.Forms.ListBox();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.panel1 = new System.Windows.Forms.Panel();
            this.cmsClientName = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.clearBrokeToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.cmsClientName.SuspendLayout();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 9);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(95, 12);
            this.label1.TabIndex = 0;
            this.label1.Text = "Current Client:";
            // 
            // lbClient
            // 
            this.lbClient.FormattingEnabled = true;
            this.lbClient.ItemHeight = 12;
            this.lbClient.Items.AddRange(new object[] {
            "AAA",
            "BBB",
            "CCC"});
            this.lbClient.Location = new System.Drawing.Point(14, 24);
            this.lbClient.Name = "lbClient";
            this.lbClient.Size = new System.Drawing.Size(110, 544);
            this.lbClient.TabIndex = 1;
            this.lbClient.SelectedIndexChanged += new System.EventHandler(this.lbClient_SelectedIndexChanged);
            // 
            // panel1
            // 
            this.panel1.Location = new System.Drawing.Point(130, 9);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(763, 563);
            this.panel1.TabIndex = 2;
            // 
            // cmsClientName
            // 
            this.cmsClientName.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.clearBrokeToolStripMenuItem});
            this.cmsClientName.Name = "cmsClientName";
            this.cmsClientName.Size = new System.Drawing.Size(181, 48);
            // 
            // clearBrokeToolStripMenuItem
            // 
            this.clearBrokeToolStripMenuItem.Name = "clearBrokeToolStripMenuItem";
            this.clearBrokeToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            this.clearBrokeToolStripMenuItem.Text = "ClearBroke";
            this.clearBrokeToolStripMenuItem.Click += new System.EventHandler(this.clearBrokeToolStripMenuItem_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(894, 573);
            this.Controls.Add(this.panel1);
            this.Controls.Add(this.lbClient);
            this.Controls.Add(this.label1);
            this.Name = "Form1";
            this.Text = "Form1";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Form1_FormClosing);
            this.Load += new System.EventHandler(this.Form1_Load);
            this.cmsClientName.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ListBox lbClient;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.ContextMenuStrip cmsClientName;
        private System.Windows.Forms.ToolStripMenuItem clearBrokeToolStripMenuItem;
    }
}


using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace LogServer
{
    public partial class ClientLogForm : Form
    {
        private String _ClientName = String.Empty;

        [DllImport("shell32.dll", SetLastError = true)]
        static extern IntPtr CommandLineToArgvW([MarshalAs(UnmanagedType.LPWStr)] string lpCmdLine, out int pNumArgs);

        private static String[] CommandLineToArgs(String Text)
        {
            int argc;
            var argv = CommandLineToArgvW(Text, out argc);
            if (argv == IntPtr.Zero)
                throw new System.ComponentModel.Win32Exception();
            try
            {
                var args = new string[argc];
                for (var i = 0; i < args.Length; i++)
                {
                    var p = Marshal.ReadIntPtr(argv, i * IntPtr.Size);
                    args[i] = Marshal.PtrToStringUni(p);
                }

                return args;
            }
            finally
            {
                Marshal.FreeHGlobal(argv);
            }
        }

        public ClientLogForm(String ClientName)
        {
            _ClientName = ClientName;
            CheckForIllegalCrossThreadCalls = false;
            InitializeComponent();
        }


        private DateTime RunTime = DateTime.Now;
        private void ClientLogForm_Load(object sender, EventArgs e)
        {
            RunTime = DateTime.Now;
            this.timer1.Interval = 1000;
            this.timer1.Tick += new EventHandler(timer1_Tick);
            this.timer1.Start();
            
        }


        public void HandleConsole(Action<WindowsForm.Console.FConsole> Ptr)
        {
            if (this.fConsole1.TextLength >= 50000)
            {
                this.fConsole1.Clear();
            }

            Ptr(fConsole1);
        }


        public void HandleExceptionCount(Action<Label> Ptr)
        {
            Ptr(this.lbExceptionCount);
        }


        public void HandleConnectedStatus(Action<Label> Ptr)
        {
            Ptr(this.lbStatus);
        }


        public void HandleLogCount(Action<Label> Ptr)
        {
            Ptr(this.lbLogCount);
        }


        private void timer1_Tick(object sender, EventArgs e)
        {
            var nTime = (DateTime.Now - RunTime).TotalSeconds;
            var Hour = nTime / 60 / 60;
            var Minute = (nTime - Hour * 60 * 60) / 60;
            var Second = nTime - Hour * 60 * 60 - Minute * 60;
            lbTime.Text = String.Format("{0}:{1:2D}:{2:2D}", Convert.ToInt32(Hour).ToString(), Convert.ToInt32(Minute), Convert.ToInt32(Second));
        }


        private void ClientLogForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            this.timer1.Stop();
            this.fConsole1.Dispose();
        }


        private void ExcuteCmd(String CmdText)
        {
            if (CmdText.Trim() == "")
            {
                this.fConsole1.WriteLine("Empty Command", Color.Red);
                return;
            }
            else if (CmdText.Trim() == "clear")
            {
                ccbCommand.Items.Clear();
                fConsole1.Clear();
                return;
            }

            var args = CommandLineToArgs(Text);
            if (args.Length == 0)
            {
                this.fConsole1.WriteLine("Empty Command", Color.Red);
                return;
            }


            //Code.API.SendCmdToClient(_ClientName, String.Join("\r\n", args));
            Code.API.SendCmdToClient(_ClientName, args.Aggregate((prev, curr) => { return prev + "\r\n" + curr; }));
        }


        private void btnExcute_Click(object sender, EventArgs e)
        {
            if (ccbCommand.SelectedIndex == -1)
            {
                this.fConsole1.WriteLine("ccbCommand.SelectedIndex = -1", Color.Red);
                return;
            }

            ExcuteCmd(ccbCommand.Items[ccbCommand.SelectedIndex].ToString());
        }


        private void ccbCommand_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
            {
                ExcuteCmd(ccbCommand.Items[ccbCommand.SelectedIndex].ToString());
            }
        }
    }
}

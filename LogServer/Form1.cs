using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace LogServer
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            CheckForIllegalCrossThreadCalls = false;
        }

        Thread _hWorker = null;
        bool _IsRun = true;
        Dictionary<String, ClientLogForm> _DictForm = new Dictionary<string, ClientLogForm>();


        private void Form1_Load(object sender, EventArgs e)
        {
            if (Code.API.Initialize() == 0)
            {
                MessageBox.Show("Initialize = FALSE!");
                Application.Exit();
            }

            _hWorker = new Thread(Worker);
            _hWorker.Start();
        }

        private List<String> GetVecClientName()
        {
            StringBuilder ClientArrayText = new StringBuilder(1024);
            Code.API.GetConnectedClient(ClientArrayText);

            return ClientArrayText.ToString().Split(new String[] { "\r\n" }, StringSplitOptions.RemoveEmptyEntries).ToList();
        }


        private List<String> _VecClientName = new List<String>();
        private void RefreshClientNameList()
        {
            var NewVecClientName = GetVecClientName();
            if (_VecClientName.Count != 0)
            {
                NewVecClientName.ForEach(ClientName => 
                {
                    if (!_DictForm.ContainsKey(ClientName))
                    {
                        _DictForm.Add(ClientName, new ClientLogForm(ClientName));
                        _VecClientName.Add(ClientName);
                        lbClient.Items.Add(ClientName);
                    }


                    _DictForm[ClientName].HandleConnectedStatus((Label lb) => 
                    {
                        lb.Text = NewVecClientName.Contains(ClientName) ? "Runing" : "Broke";
                    });
                });
            }
            else
            {
                _VecClientName = NewVecClientName;
                _VecClientName.ForEach(itm => lbClient.Items.Add(itm));
            }
        }

        private void Worker()
        {
            DateTime Tick = DateTime.Now;
            StringBuilder sbClientName = new StringBuilder(1024) , sbLogText = new StringBuilder(1024);
            while (_IsRun)
            {
                if (Code.API.GetClientLog(sbClientName, sbLogText) == 1)
                {
                    if (!_DictForm.ContainsKey(sbClientName.ToString()))
                    {
                        MessageBox.Show("UnExist Client[" + sbClientName.ToString() + "] in _DictForm");
                        continue;
                    }


                    _DictForm[sbClientName.ToString()].HandleConsole((CmdControl) => 
                    {
                        var LogTextArray = sbLogText.ToString().Split(new string[] { "\r\n" }, StringSplitOptions.None).ToList();
                        if (LogTextArray.Count < 6)
                            return;


                        var LogContent = new Code.CLogContent();
                        LogContent.emLogType = (Code.em_Log_Type)int.Parse(LogTextArray[0]);
                        LogContent.strFunName = LogTextArray[1];
                        LogContent.strFileName = LogTextArray[2];
                        LogContent.nLine = int.Parse(LogTextArray[3]);
                        LogContent.strLogContent = LogTextArray[4];
                        LogContent.strTime = DateTime.Now.ToString("HH:mm:ss ms");
                        LogContent.strClientName = LogTextArray[5];
                        CmdControl.WriteLine(String.Format("[{0:d2}:{1:d2}:{2:d2}] {3}", DateTime.Now.Hour, DateTime.Now.Minute, DateTime.Now.Second, LogContent.strLogContent), LogContent.emLogType == Code.em_Log_Type.em_Log_Type_Exception ? Color.Red : Color.White);
                    });

                    continue;
                }


                if ((DateTime.Now - Tick).TotalSeconds >= 1000)
                {
                    RefreshClientNameList();
                    Tick = DateTime.Now;
                }
                
                Thread.Sleep(100);
            }
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            _IsRun = false;
            _hWorker.Join();
        }


       
        private void lbClient_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (lbClient.SelectedIndex != -1)
            {
                String ClientName = lbClient.Items[lbClient.SelectedIndex].ToString();


                var InstanceForm = _DictForm[ClientName];
                InstanceForm.TopLevel = false;
                InstanceForm.FormBorderStyle = FormBorderStyle.None;
                InstanceForm.Dock = DockStyle.Fill;
                InstanceForm.Parent = this;

                this.panel1.Controls.Clear();
                this.panel1.Controls.Add(InstanceForm);
                InstanceForm.Show();
            }
        }

        private void clearBrokeToolStripMenuItem_Click(object sender, EventArgs e)
        {
            foreach (var itm in _DictForm)
            {
                bool bRuning = false;
                itm.Value.HandleConnectedStatus((Label lb) => { bRuning = lb.Text == "Runing"; });
                if (!bRuning)
                {
                    _DictForm.Remove(itm.Key);
                }
            }
        }
    }
}

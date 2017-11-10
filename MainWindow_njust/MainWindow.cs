using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;


namespace MainWindow_njust
{
    public partial class MainWindow : Form
    {
        public ClientSocket m_clientSocket = null;
        public bool m_bConnected = false;
        private ParameterWindow m_pw = null;

        public MainWindow()
        {
            InitializeComponent();
            this.button_parameter.Enabled = false;
            this.button_RunOnce.Enabled = false;
            this.button_restart.Enabled = false;
            this.radioButton_NormalLCD.Checked = true;
            this.button_EnvironmentSetting.Enabled = false;
            this.textBox_address.Text = "192.168.1.110";
            this.textBox_port.Text = "1400";
        }

        private void button_connect_Click(object sender, EventArgs e)
        {
            string strIP = this.textBox_address.Text.ToString();
            if (strIP.Trim().Equals(""))
            {
                MessageBox.Show("IP地址不能为空!");
                return;
            }
            string strPort = this.textBox_port.Text.ToString();
            if (strPort.Trim().Equals(""))
            {
                MessageBox.Show("端口号不能为空!");
                return;
            }

            int intPort = Convert.ToInt32(strPort);
            m_clientSocket = new ClientSocket(strIP, intPort);
            m_bConnected = m_clientSocket.ConnectServer();
            string strRecved = null;
            if (m_bConnected)
            {
                try
                {
                    m_clientSocket.ClientSend("?config.IsNetCamera\n");
                    strRecved = m_clientSocket.ClientRecv();
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.StackTrace.ToString());
                }
                this.button_parameter.Enabled = true;
                this.button_RunOnce.Enabled = true;
                this.button_restart.Enabled = true;
                if (strRecved.Equals("false\n"))
                {
                    this.button_EnvironmentSetting.Enabled = false;
                    MessageBox.Show("已成功连接至服务器, \n\n您正在使用Logitech摄像头!");
                    //SelfMessageBox smb = new SelfMessageBox(m_clientSocket);
                    //smb.ShowDialog(this);
                }
                else if (strRecved.Equals("true\n"))
                {
                    this.button_EnvironmentSetting.Enabled = true;
                    SelfMessageBox smb = new SelfMessageBox(m_clientSocket);
                    smb.ShowDialog(this);
                }
                InitializeTimer(5000);
            }
            else
            {
                this.button_parameter.Enabled = false;
                this.button_RunOnce.Enabled = false;
                this.button_restart.Enabled = false;
                m_clientSocket = null;
                MessageBox.Show("连接失败, 请正确配置服务器!");
            }
        }

        private void button_parameter_Click(object sender, EventArgs e)
        {
            try
            {
	            if (m_clientSocket != null && m_clientSocket.GetSocketState())
	            {
                    if (m_pw == null || m_pw.IsDisposed)
                    {
                        m_pw = new ParameterWindow(m_clientSocket);
                        m_pw.Show();
                    }
                    else
                    {
                        m_pw.Activate();
                    }
	            }
	            else
	            {
                    this.button_parameter.Enabled = false;
                    this.button_RunOnce.Enabled = false;
                    this.button_restart.Enabled = false;
	                MessageBox.Show("请先连接到服务器!");
	            }
            }
            catch (System.Exception)
            {
                this.button_parameter.Enabled = false;
                this.button_RunOnce.Enabled = false;
                this.button_restart.Enabled = false;
                MessageBox.Show("服务器异常退出, 请重新连接!");
            }
        }

        private void button_grasp_Click(object sender, EventArgs e)
        {
            try
            {
                ImageWindow iw = new ImageWindow(this.textBox_address.Text.ToString().Trim());
                iw.Show();
            }
            catch (System.Exception)
            {
                MessageBox.Show("请先打开HTTP服务器!");
            }
        }

        private void button_restart_Click(object sender, EventArgs e)
        {
            try
            {
	            if (m_clientSocket != null && m_clientSocket.GetSocketState())
	            {
	                m_clientSocket.ClientSend("os.exit()\n");
	                m_clientSocket.CloseSocket();
	                m_clientSocket = null;
	                this.button_parameter.Enabled = false;
                    this.button_RunOnce.Enabled = false;
                    this.button_restart.Enabled = false;
	            }
	            else
	            {
                    this.button_parameter.Enabled = false;
                    this.button_RunOnce.Enabled = false;
                    this.button_restart.Enabled = false;
	                MessageBox.Show("请先连接服务器!");
	            }
            }
            catch (System.Exception)
            {
                this.button_parameter.Enabled = false;
                this.button_RunOnce.Enabled = false;
                this.button_restart.Enabled = false;
                MessageBox.Show("服务器异常退出, 请重新连接!");
            }
        }

        private void button_exit_Click(object sender, EventArgs e)
        {
	        if (m_clientSocket != null && m_clientSocket.GetSocketState())
	        {
	            m_clientSocket.CloseSocket();
	            m_clientSocket = null; 
	        }
            this.Close();
        }

        private void InitializeTimer(int deltaTime)
        {
            System.Timers.Timer timer = new System.Timers.Timer(deltaTime);
            timer.Elapsed += new System.Timers.ElapsedEventHandler(OnTimer);
            timer.AutoReset = true;
            timer.Enabled = true;
            timer.SynchronizingObject = this;
        }

        public void OnTimer(object source, System.Timers.ElapsedEventArgs e)
        {
            try
            {
                m_clientSocket.ClientSend("?server.status\n");
                string strRecved = m_clientSocket.ClientRecv();
                this.textBox_status.Text = strRecved;
            }
            catch (System.Exception)
            {

            }
        }

        private void button__Click(object sender, EventArgs e)
        {
            try
            {
                if (m_clientSocket != null && m_clientSocket.GetSocketState())
                {
                    string strTemp = null;
                    if (this.radioButton_BlueScreen.Checked == true)
                    {
                        m_clientSocket.ClientSend("config.IsBlueScreen=true\n");
                        strTemp = m_clientSocket.ClientRecv();
                    }
                    else if (this.radioButton_NormalLCD.Checked == true)
                    {
                        m_clientSocket.ClientSend("config.IsBlueScreen=false\n");
                        strTemp = m_clientSocket.ClientRecv();
                    }
                    m_clientSocket.ClientSend("donce()\n");
                    strTemp = m_clientSocket.ClientRecv();
                    MessageBox.Show("已开始运行!");
                }
                else
                {
                    this.button_parameter.Enabled = false;
                    this.button_RunOnce.Enabled = false;
                    this.button_restart.Enabled = false;
                    MessageBox.Show("请先连接到服务器!");
                }
            }
            catch (System.Exception)
            {

            }
        }

        private void radioCheckChanged(object sender, EventArgs e)
        {
            if (m_clientSocket != null && m_clientSocket.GetSocketState())
            {
                string strTemp = "";
                if (this.radioButton_BlueScreen.Checked == true)
                {
                    m_clientSocket.ClientSend("config.IsBlueScreen=true\n");
                    strTemp = m_clientSocket.ClientRecv();
                    MessageBox.Show("已设置为使用蓝相屏!");
                }
                else if (this.radioButton_NormalLCD.Checked == true)
                {
                    m_clientSocket.ClientSend("config.IsBlueScreen=false\n");
                    strTemp = m_clientSocket.ClientRecv();
                    MessageBox.Show("已设置为使用工业屏!");
                }
            }
            else
            {
                this.button_parameter.Enabled = false;
                this.button_RunOnce.Enabled = false;
                this.button_restart.Enabled = false;
                MessageBox.Show("请先连接到服务器!");
            }
        }

        private void button_EnvironmentSetting_Click(object sender, EventArgs e)
        {
            EnviromentSelectionForm esf = new EnviromentSelectionForm(m_clientSocket);
            esf.ShowDialog(this);
        }

    }
}

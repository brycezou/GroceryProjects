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

        //主窗口的构造函数
        public MainWindow()
        {
            InitializeComponent();  //初始化组件,系统自动生成
            this.button_parameter.Enabled = false; //参数设置按钮无效
            this.button_RunOnce.Enabled = false; //运行一次按钮无效
            this.button_restart.Enabled = false;  //服务器重启按钮无效
            this.radioButton_NormalLCD.Checked = true; //选中工业屏
            this.button_EnvironmentSetting.Enabled = false; //环境设置无效
            this.textBox_address.Text = "192.168.1.110";    //设置IP地址
            this.textBox_port.Text = "1400";   //设置端口号
        }

        //系统连接按钮事件
        private void button_connect_Click(object sender, EventArgs e)
        {
            string strIP = this.textBox_address.Text.ToString();  //获取IP地址
            if (strIP.Trim().Equals("")) //如果IP地址为空
            {
                MessageBox.Show("IP地址不能为空!"); //弹出对话框
                return;
            }
            string strPort = this.textBox_port.Text.ToString(); //获取端口号
            if (strPort.Trim().Equals("")) //如果端口号为空
            {
                MessageBox.Show("端口号不能为空!");
                return;
            }

            int intPort = Convert.ToInt32(strPort); //得到端口号
            m_clientSocket = new ClientSocket(strIP, intPort); //创建套接字
            m_bConnected = m_clientSocket.ConnectServer(); //连接服务器
            string strRecved = null; //接收到的数据
            if (m_bConnected)   //如果服务器连接成功
            {
                try
                {
                    //向服务器发送状态查询指令
                    m_clientSocket.ClientSend("?config.IsNetCamera\n");
                    strRecved = m_clientSocket.ClientRecv(); //从服务器接收返回结果
                }
                catch (Exception ex)
                {
                    //如果通信异常, 给出错误信息
                    MessageBox.Show(ex.StackTrace.ToString());
                }
                this.button_parameter.Enabled = true; //参数设置按钮有效
                this.button_RunOnce.Enabled = true; //运行一次按钮有效
                this.button_restart.Enabled = true; //服务器重启按钮有效
                if (strRecved.Equals("false\n"))    //如果使用的是罗技摄像头
                {
                    this.button_EnvironmentSetting.Enabled = false; //环境设置按钮无效
                    MessageBox.Show("已成功连接至服务器, \n\n您正在使用Logitech摄像头!");
                    //SelfMessageBox smb = new SelfMessageBox(m_clientSocket);
                    //smb.ShowDialog(this);
                }
                else if (strRecved.Equals("true\n"))  //如果使用的是网口摄像头
                {
                    this.button_EnvironmentSetting.Enabled = true; //环境设置按钮有效
                    SelfMessageBox smb = new SelfMessageBox(m_clientSocket);
                    smb.ShowDialog(this); //创建并显示环境设置对话框
                }
                InitializeTimer(5000); //初始化定时器
            }
            else  //如果服务器连接失败
            {
                this.button_parameter.Enabled = false; //参数设置按钮无效
                this.button_RunOnce.Enabled = false; //运行一次按钮无效
                this.button_restart.Enabled = false; //服务器重启按钮无效
                m_clientSocket = null; //清理套接字
                MessageBox.Show("连接失败, 请正确配置服务器!");
            }
        }

        //参数设置按钮事件
        private void button_parameter_Click(object sender, EventArgs e)
        {
            try
            {
                //如果网络连接正常
	            if (m_clientSocket != null && m_clientSocket.GetSocketState())
	            {
                    if (m_pw == null || m_pw.IsDisposed) //如果还未打开参数设置对话框
                    {
                        m_pw = new ParameterWindow(m_clientSocket);
                        m_pw.Show(); //创建并显示参数设置对话框
                    }
                    else //如果已打开参数设置对话框
                    {
                        m_pw.Activate(); //激活参数设置对话框
                    }
	            }
                else //如果网络连接不正常
	            {
                    this.button_parameter.Enabled = false; //参数设置按钮无效
                    this.button_RunOnce.Enabled = false; //运行一次按钮无效
                    this.button_restart.Enabled = false; //服务器重启按钮无效
	                MessageBox.Show("请先连接到服务器!");
	            }
            }
            catch (System.Exception) //如果发生异常
            {
                this.button_parameter.Enabled = false; //参数设置按钮无效
                this.button_RunOnce.Enabled = false; //运行一次按钮无效
                this.button_restart.Enabled = false; //服务器重启按钮无效
                MessageBox.Show("服务器异常退出, 请重新连接!");
            }
        }

        //抓图按钮事件
        private void button_grasp_Click(object sender, EventArgs e)
        {
            try
            {
                //创建图像显示对话框并显示
                ImageWindow iw = new ImageWindow(this.textBox_address.Text.ToString().Trim());
                iw.Show();
            }
            catch (System.Exception) //如果抓图失败
            {
                MessageBox.Show("请先打开HTTP服务器!");
            }
        }

        //服务器重启按钮事件
        private void button_restart_Click(object sender, EventArgs e)
        {
            try
            {
                //如果网络连接正常
	            if (m_clientSocket != null && m_clientSocket.GetSocketState())
	            {
	                m_clientSocket.ClientSend("os.exit()\n"); //向服务器发送指令
	                m_clientSocket.CloseSocket(); //关闭套接字
	                m_clientSocket = null;
	                this.button_parameter.Enabled = false; //参数设置按钮无效
                    this.button_RunOnce.Enabled = false; //运行一次按钮无效
                    this.button_restart.Enabled = false; //服务器重启按钮无效
	            }
                else //如果网络连接不正常
	            {
                    this.button_parameter.Enabled = false; //参数设置按钮无效
                    this.button_RunOnce.Enabled = false; //运行一次按钮无效
                    this.button_restart.Enabled = false; //服务器重启按钮无效
	                MessageBox.Show("请先连接服务器!");
	            }
            }
            catch (System.Exception) //如果发生错误
            {
                this.button_parameter.Enabled = false; //参数设置按钮无效
                this.button_RunOnce.Enabled = false; //运行一次按钮无效
                this.button_restart.Enabled = false; //服务器重启按钮无效
                MessageBox.Show("服务器异常退出, 请重新连接!");
            }
        }

        //程序退出按钮事件
        private void button_exit_Click(object sender, EventArgs e)
        {
            //如果网络连接正常
	        if (m_clientSocket != null && m_clientSocket.GetSocketState())
	        {
	            m_clientSocket.CloseSocket(); //关闭套接字
	            m_clientSocket = null; 
	        }
            this.Close(); //关闭程序
        }

        //初始化定时器
        private void InitializeTimer(int deltaTime)
        {
            //创建定时器对象并绑定方法到事件
            System.Timers.Timer timer = new System.Timers.Timer(deltaTime);
            timer.Elapsed += new System.Timers.ElapsedEventHandler(OnTimer);
            timer.AutoReset = true; //设置定时器参数
            timer.Enabled = true; //开启定时器
            timer.SynchronizingObject = this;
        }

        //定时到达的事件响应函数
        public void OnTimer(object source, System.Timers.ElapsedEventArgs e)
        {
            try
            {
                m_clientSocket.ClientSend("?server.status\n");    //向服务器发送查询指令
                string strRecved = m_clientSocket.ClientRecv(); //接收数据
                this.textBox_status.Text = strRecved; //设置系统状态文本
            }
            catch (System.Exception) //如果发生错误
            {

            }
        }

        //运行一次按钮事件
        private void button__Click(object sender, EventArgs e)
        {
            try
            {
                //如果网络连接正常
                if (m_clientSocket != null && m_clientSocket.GetSocketState())
                {
                    string strTemp = null;
                    //设置显示器类型
                    if (this.radioButton_BlueScreen.Checked == true)
                    {
                        //如果是蓝相屏
                        m_clientSocket.ClientSend("config.IsBlueScreen=true\n");
                        strTemp = m_clientSocket.ClientRecv();//接收数据
                    }
                    else if (this.radioButton_NormalLCD.Checked == true)
                    {
                        //如果是工业屏
                        m_clientSocket.ClientSend("config.IsBlueScreen=false\n");
                        strTemp = m_clientSocket.ClientRecv();//接收数据
                    }
                    m_clientSocket.ClientSend("donce()\n"); //向服务器发送指令
                    strTemp = m_clientSocket.ClientRecv(); //接收数据
                    MessageBox.Show("已开始运行!");
                }
                else //如果网络连接不正常
                {
                    this.button_parameter.Enabled = false; //参数设置按钮无效
                    this.button_RunOnce.Enabled = false; //运行一次按钮无效
                    this.button_restart.Enabled = false; //服务器重启按钮无效
                    MessageBox.Show("请先连接到服务器!");
                }
            }
            catch (System.Exception) //如果发生错误
            {

            }
        }

        //单选框事件, 用来选择显示器类型
        private void radioCheckChanged(object sender, EventArgs e)
        {
            //如果网络连接正常
            if (m_clientSocket != null && m_clientSocket.GetSocketState())
            {
                string strTemp = "";
                //如果选择了蓝相屏
                if (this.radioButton_BlueScreen.Checked == true)
                {
                    //向服务器发送指令
                    m_clientSocket.ClientSend("config.IsBlueScreen=true\n");
                    strTemp = m_clientSocket.ClientRecv(); //接收数据
                    MessageBox.Show("已设置为使用蓝相屏!");
                }
                //如果选择了工业屏
                else if (this.radioButton_NormalLCD.Checked == true)
                {
                    //向服务器发送指令
                    m_clientSocket.ClientSend("config.IsBlueScreen=false\n");
                    strTemp = m_clientSocket.ClientRecv(); //接收数据
                    MessageBox.Show("已设置为使用工业屏!");
                }
            }
            else //如果网络连接不正常
            {
                this.button_parameter.Enabled = false; //参数设置按钮无效
                this.button_RunOnce.Enabled = false; //运行一次按钮无效
                this.button_restart.Enabled = false; //服务器重启按钮无效
                MessageBox.Show("请先连接到服务器!");
            }
        }

        //环境设置按钮事件
        private void button_EnvironmentSetting_Click(object sender, EventArgs e)
        {
            //创建并显示环境设置对话框
            EnviromentSelectionForm esf = new EnviromentSelectionForm(m_clientSocket);
            esf.ShowDialog(this);
        }

    }
}

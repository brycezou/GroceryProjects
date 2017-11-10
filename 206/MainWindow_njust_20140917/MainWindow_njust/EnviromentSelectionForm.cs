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
    public partial class EnviromentSelectionForm : Form
    {
        private double m_fR; //R的系数
        private double m_fG; //G的系数
        private double m_fB; //B的系数
        private string m_strText = null;
        public ClientSocket m_clientSocket = null; //通信套接字

        //环境选择对话框
        public EnviromentSelectionForm(ClientSocket clntSocket)
        {
            InitializeComponent(); //初始化组件, 系统自动生成
            m_clientSocket = clntSocket;
            
            //四种典型环境下的R通道系数
            this.textBox_r1.Text = "1.0";
            this.textBox_r2.Text = "1.0";
            this.textBox_r3.Text = "1.0";
            this.textBox_r4.Text = "1.0";

            //四种典型环境下的G通道系数
            this.textBox_g1.Text = "1.0";
            this.textBox_g2.Text = "1.0";
            this.textBox_g3.Text = "1.0";
            this.textBox_g4.Text = "1.0";

            //四种典型环境下的B通道系数
            this.textBox_b1.Text = "1.0";
            this.textBox_b2.Text = "1.0";
            this.textBox_b3.Text = "1.0";
            this.textBox_b4.Text = "1.0";
        }

        //点击确定按钮
        private void button_OKSet_Click(object sender, EventArgs e)
        {
            try
            {
                if (m_strText.Equals("草地")) //如果选择了草地
                {
                    //获取三个系数
                    this.m_fR = Convert.ToDouble(this.textBox_r1.Text.ToString());
                    this.m_fG = Convert.ToDouble(this.textBox_g1.Text.ToString());
                    this.m_fB = Convert.ToDouble(this.textBox_b1.Text.ToString());
                }
                else if (m_strText.Equals("沙土地")) //如果选择了沙土地
                {
                    //获取三个系数
                    this.m_fR = Convert.ToDouble(this.textBox_r2.Text.ToString());
                    this.m_fG = Convert.ToDouble(this.textBox_g2.Text.ToString());
                    this.m_fB = Convert.ToDouble(this.textBox_b2.Text.ToString());
                }
                else if (m_strText.Equals("水泥地")) //如果选择了水泥地
                {
                    //获取三个系数
                    this.m_fR = Convert.ToDouble(this.textBox_r3.Text.ToString());
                    this.m_fG = Convert.ToDouble(this.textBox_g3.Text.ToString());
                    this.m_fB = Convert.ToDouble(this.textBox_b3.Text.ToString());
                }
                else if (m_strText.Equals("林地")) //如果选择了林地
                {
                    //获取三个系数
                    this.m_fR = Convert.ToDouble(this.textBox_r4.Text.ToString());
                    this.m_fG = Convert.ToDouble(this.textBox_g4.Text.ToString());
                    this.m_fB = Convert.ToDouble(this.textBox_b4.Text.ToString());
                }
            }
            catch (System.Exception) //如果发生错误
            {
                MessageBox.Show("输入数据不合法!");
            }

            //如果网络连接正常
            if (m_clientSocket != null && m_clientSocket.GetSocketState())
            {
                //向服务器发送指令
                string strTemp = String.Format("AjustRgbs({0},{1},{2})\n", m_fR, m_fG, m_fB);
                m_clientSocket.ClientSend(strTemp);
                strTemp = m_clientSocket.ClientRecv(); //接收数据
            }
            else //如果网络连接不正常
            {
                MessageBox.Show("请先连接到服务器!");
            }
            this.Close(); //关闭对话框
        }

        //单选框选择内容改变事件
        private void button_EnvironmentChanged(object sender, EventArgs e)
        {
            RadioButton rb = (RadioButton)sender;   //获取发出事件的单选框
            m_strText = rb.Text.ToString(); //获取单选框文字
            if (m_strText.Equals("草地")) //如果选择了草地
            {
                //将其它选项下的控件置为无法使用
                this.textBox_r1.Enabled = true;
                this.textBox_g1.Enabled = true;
                this.textBox_b1.Enabled = true;
                this.textBox_r2.Enabled = false;
                this.textBox_g2.Enabled = false;
                this.textBox_b2.Enabled = false;
                this.textBox_r3.Enabled = false;
                this.textBox_g3.Enabled = false;
                this.textBox_b3.Enabled = false;
                this.textBox_r4.Enabled = false;
                this.textBox_g4.Enabled = false;
                this.textBox_b4.Enabled = false;
            }
            else if (m_strText.Equals("沙土地")) //如果选择了沙土地
            {
                //将其它选项下的控件置为无法使用
                this.textBox_r1.Enabled = false;
                this.textBox_g1.Enabled = false;
                this.textBox_b1.Enabled = false;
                this.textBox_r2.Enabled = true;
                this.textBox_g2.Enabled = true;
                this.textBox_b2.Enabled = true;
                this.textBox_r3.Enabled = false;
                this.textBox_g3.Enabled = false;
                this.textBox_b3.Enabled = false;
                this.textBox_r4.Enabled = false;
                this.textBox_g4.Enabled = false;
                this.textBox_b4.Enabled = false;
            }
            else if (m_strText.Equals("水泥地")) //如果选择了水泥地
            {
                //将其它选项下的控件置为无法使用
                this.textBox_r1.Enabled = false;
                this.textBox_g1.Enabled = false;
                this.textBox_b1.Enabled = false;
                this.textBox_r2.Enabled = false;
                this.textBox_g2.Enabled = false;
                this.textBox_b2.Enabled = false;
                this.textBox_r3.Enabled = true;
                this.textBox_g3.Enabled = true;
                this.textBox_b3.Enabled = true;
                this.textBox_r4.Enabled = false;
                this.textBox_g4.Enabled = false;
                this.textBox_b4.Enabled = false;
            }
            else if (m_strText.Equals("林地")) //如果选择了林地
            {
                //将其它选项下的控件置为无法使用
                this.textBox_r1.Enabled = false;
                this.textBox_g1.Enabled = false;
                this.textBox_b1.Enabled = false;
                this.textBox_r2.Enabled = false;
                this.textBox_g2.Enabled = false;
                this.textBox_b2.Enabled = false;
                this.textBox_r3.Enabled = false;
                this.textBox_g3.Enabled = false;
                this.textBox_b3.Enabled = false;
                this.textBox_r4.Enabled = true;
                this.textBox_g4.Enabled = true;
                this.textBox_b4.Enabled = true;
            }
        }
    }
}

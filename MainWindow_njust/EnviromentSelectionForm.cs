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
        private double m_fR;
        private double m_fG;
        private double m_fB;
        private string m_strText = null;
        public ClientSocket m_clientSocket = null;

        public EnviromentSelectionForm(ClientSocket clntSocket)
        {
            InitializeComponent();
            m_clientSocket = clntSocket;
            this.textBox_r1.Text = "1.0";
            this.textBox_r2.Text = "1.0";
            this.textBox_r3.Text = "1.0";
            this.textBox_r4.Text = "1.0";

            this.textBox_g1.Text = "1.0";
            this.textBox_g2.Text = "1.0";
            this.textBox_g3.Text = "1.0";
            this.textBox_g4.Text = "1.0";

            this.textBox_b1.Text = "1.0";
            this.textBox_b2.Text = "1.0";
            this.textBox_b3.Text = "1.0";
            this.textBox_b4.Text = "1.0";
        }

        private void button_OKSet_Click(object sender, EventArgs e)
        {
            try
            {
                if (m_strText.Equals("草地"))
                {
                    this.m_fR = Convert.ToDouble(this.textBox_r1.Text.ToString());
                    this.m_fG = Convert.ToDouble(this.textBox_g1.Text.ToString());
                    this.m_fB = Convert.ToDouble(this.textBox_b1.Text.ToString());
                }
                else if (m_strText.Equals("沙土地"))
                {
                    this.m_fR = Convert.ToDouble(this.textBox_r2.Text.ToString());
                    this.m_fG = Convert.ToDouble(this.textBox_g2.Text.ToString());
                    this.m_fB = Convert.ToDouble(this.textBox_b2.Text.ToString());
                }
                else if (m_strText.Equals("水泥地"))
                {
                    this.m_fR = Convert.ToDouble(this.textBox_r3.Text.ToString());
                    this.m_fG = Convert.ToDouble(this.textBox_g3.Text.ToString());
                    this.m_fB = Convert.ToDouble(this.textBox_b3.Text.ToString());
                }
                else if (m_strText.Equals("林地"))
                {
                    this.m_fR = Convert.ToDouble(this.textBox_r4.Text.ToString());
                    this.m_fG = Convert.ToDouble(this.textBox_g4.Text.ToString());
                    this.m_fB = Convert.ToDouble(this.textBox_b4.Text.ToString());
                }
            }
            catch (System.Exception)
            {
                MessageBox.Show("输入数据不合法!");
            }

            if (m_clientSocket != null && m_clientSocket.GetSocketState())
            {
                string strTemp = String.Format("AjustRgbs({0},{1},{2})\n", m_fR, m_fG, m_fB);
                m_clientSocket.ClientSend(strTemp);
                strTemp = m_clientSocket.ClientRecv();
            }
            else
            {
                MessageBox.Show("请先连接到服务器!");
            }
            this.Close();
        }

        private void button_EnvironmentChanged(object sender, EventArgs e)
        {
            RadioButton rb = (RadioButton)sender;
            m_strText = rb.Text.ToString();
            if (m_strText.Equals("草地"))
            {
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
            else if (m_strText.Equals("沙土地"))
            {
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
            else if (m_strText.Equals("水泥地"))
            {
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
            else if (m_strText.Equals("林地"))
            {
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

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;


namespace MainWindow_njust
{
    public partial class ParameterWindow : Form
    {
        public string m_strCamera = null;
        ClientSocket m_clientSocket = null;

        public ParameterWindow(ClientSocket clientSocket)
        {
            InitializeComponent();
            this.radioButton_640480.Select();
            this.checkBox_midresult.CheckState = CheckState.Checked;
            this.textBox_Step.Text = "5";
            m_clientSocket = clientSocket;
            RefreshVariableValues();
        }

        private void button_CamereSetOK_Click(object sender, EventArgs e)
        {
            string strTemp = "config.camera='" + this.m_strCamera + "'\n";
            m_clientSocket.ClientSend(strTemp);
            strTemp = m_clientSocket.ClientRecv();
            if (this.checkBox_midresult.Checked)
            {
                m_clientSocket.ClientSend("config.debug=true\n");
                strTemp = m_clientSocket.ClientRecv();
            }
            else
            {
                m_clientSocket.ClientSend("config.debug=false\n");
                strTemp = m_clientSocket.ClientRecv();
            }
        }

        private void button_RadioChanged(object sender, EventArgs e)
        {
            RadioButton rb = (RadioButton)sender;
            m_strCamera = rb.Text.ToString();
        }

        private void button_RgbSetOK_Click(object sender, EventArgs e)
        {
            int intR1 = Convert.ToInt32(this.textBox_r1.Text.ToString().Trim());
            int intG1 = Convert.ToInt32(this.textBox_g1.Text.ToString().Trim());
            int intB1 = Convert.ToInt32(this.textBox_b1.Text.ToString().Trim());
            int intR2 = Convert.ToInt32(this.textBox_r2.Text.ToString().Trim());
            int intG2 = Convert.ToInt32(this.textBox_g2.Text.ToString().Trim());
            int intB2 = Convert.ToInt32(this.textBox_b2.Text.ToString().Trim()); 
            int intR3 = Convert.ToInt32(this.textBox_r3.Text.ToString().Trim());
            int intG3 = Convert.ToInt32(this.textBox_g3.Text.ToString().Trim());
            int intB3 = Convert.ToInt32(this.textBox_b3.Text.ToString().Trim());
            int intDeltaTime = Convert.ToInt32(this.textBox_ShowDelta.Text.ToString().Trim());
            double dbBorder = Convert.ToDouble(this.textBox_PingGaoBi.Text.ToString().Trim());
            if ((intR1 > 255) || (intG1 > 255) || (intB1 > 255) || (intR2 > 255) || (intG2 > 255) || (intB2 > 255) || (intR3 > 255) || (intG3 > 255) || (intB3 > 255))
            {
                MessageBox.Show("RGB值范围为0~255，请重新输入!");
                return;
            }
            if (dbBorder > 0.5 || dbBorder < 0.01)
            {
                MessageBox.Show("屏高比范围0.01~0.5!");
                return;
            }
            if (intDeltaTime > 120 || intDeltaTime < 5)
            {
                intDeltaTime = intDeltaTime > 120 ? 120 : 5;
                this.textBox_ShowDelta.Text = intDeltaTime.ToString();
            }

            string strTemp = null;
            m_clientSocket.ClientSend("config.matting.RGB1.R=" + intR1 + "\n");
            strTemp = m_clientSocket.ClientRecv();
            m_clientSocket.ClientSend("config.matting.RGB1.G=" + intG1 + "\n");
            strTemp = m_clientSocket.ClientRecv();
            m_clientSocket.ClientSend("config.matting.RGB1.B=" + intB1 + "\n");
            strTemp = m_clientSocket.ClientRecv();
            m_clientSocket.ClientSend("config.matting.RGB2.R=" + intR2 + "\n");
            strTemp = m_clientSocket.ClientRecv();
            m_clientSocket.ClientSend("config.matting.RGB2.G=" + intG2 + "\n");
            strTemp = m_clientSocket.ClientRecv();
            m_clientSocket.ClientSend("config.matting.RGB2.B=" + intB2 + "\n");
            strTemp = m_clientSocket.ClientRecv();
            m_clientSocket.ClientSend("config.matting.RGB3.R=" + intR3 + "\n");
            strTemp = m_clientSocket.ClientRecv();
            m_clientSocket.ClientSend("config.matting.RGB3.G=" + intG3 + "\n");
            strTemp = m_clientSocket.ClientRecv();
            m_clientSocket.ClientSend("config.matting.RGB3.B=" + intB3 + "\n");
            strTemp = m_clientSocket.ClientRecv();
            m_clientSocket.ClientSend("config.matting.border=" + dbBorder + "\n");
            strTemp = m_clientSocket.ClientRecv();
            m_clientSocket.ClientSend("config.matting.deltaTime=" + intDeltaTime + "\n");
            strTemp = m_clientSocket.ClientRecv();
        }

        private void button_WenLiSetOK_Click(object sender, EventArgs e)
        {
            int intBlockSize = Convert.ToInt32(this.textBox_BlockSize.Text.ToString().Trim());
            int intBlockNum = Convert.ToInt32(this.textBox_BlockNumber.Text.ToString().Trim());
            double dbBorder = Convert.ToDouble(this.textBox_PingGaoBi2.Text.ToString().Trim());
            if ((intBlockSize > 1000) || (intBlockSize < 1))
            {
                MessageBox.Show("块大小范围1~1000!");
                return;
            }
            if ((intBlockNum > 480000))
            {
                MessageBox.Show("块个数范围0~480000!");
                return;
            }
            if (dbBorder > 0.5 || dbBorder < 0.01)
            {
                MessageBox.Show("屏高比范围0.01~0.5!");
                return;
            }
            string strTemp = null;
            m_clientSocket.ClientSend("config.filling.block.size=" + intBlockSize + "\n");
            strTemp = m_clientSocket.ClientRecv();
            m_clientSocket.ClientSend("config.filling.block.num=" + intBlockNum + "\n");
            strTemp = m_clientSocket.ClientRecv();
            m_clientSocket.ClientSend("config.filling.border=" + dbBorder + "\n");
            strTemp = m_clientSocket.ClientRecv();
        }

        private void button_AutoLabSetOK_Click(object sender, EventArgs e)
        {
            int intLabThreshold = Convert.ToInt32(this.textBox_LabThreshold.Text.ToString().Trim());
            int intIteration = Convert.ToInt32(this.textBox_iteration.Text.ToString().Trim());
            int intInterval = Convert.ToInt32(this.textBox_RunTime.Text.ToString().Trim());
            double dbBorder = Convert.ToDouble(this.textBox_PingGaoBi3.Text.ToString().Trim());
            if ((intInterval > 7200) || (intInterval < 1))
            {
                MessageBox.Show("运行间隔范围1~7200 秒!");
                return;
            }
            if ((intLabThreshold > 10) || (intLabThreshold < 1))
            {
                MessageBox.Show("区域相似性阈值范围1~10!");
                return;
            }
            if (intIteration > 20)
            {
                MessageBox.Show("最大纠正次数范围0~20!");
                return;
            }
            if (dbBorder > 0.5 || dbBorder < 0.01)
            {
                MessageBox.Show("屏高比范围0.01~0.5!");
                return;
            }

            string strTemp = null;
            m_clientSocket.ClientSend("config.evaluation.labThreshold=" + intLabThreshold + "\n");
            strTemp = m_clientSocket.ClientRecv();
            m_clientSocket.ClientSend("config.evaluation.iteration=" + intIteration + "\n");
            strTemp = m_clientSocket.ClientRecv();
            m_clientSocket.ClientSend("config.evaluation.interval=" + intInterval + "\n");
            strTemp = m_clientSocket.ClientRecv();
            m_clientSocket.ClientSend("config.evaluation.border=" + dbBorder + "\n");
            strTemp = m_clientSocket.ClientRecv();
        }

        private void button_AutoLabDone_Click(object sender, EventArgs e)
        {
            string strTemp = null;
            m_clientSocket.ClientSend("autimer()\n");
            strTemp = m_clientSocket.ClientRecv();
        }

        private void button_LPlus_Click(object sender, EventArgs e)
        {
            int intStep = Convert.ToInt32(this.textBox_Step.Text.ToString().Trim());
            int intL = Convert.ToInt32(this.textBox_L.Text.ToString().Trim()) + intStep;
            if (intL > 100) intL = 100;
            else if (intL < 0) intL = 0;
            this.textBox_L.Text = intL.ToString();
            string strTemp = String.Format("manual({0},{1},{2})\n", intL, this.textBox_a.Text.ToString().Trim(), this.textBox_b.Text.ToString().Trim());
            m_clientSocket.ClientSend(strTemp);
            strTemp = m_clientSocket.ClientRecv();
        }

        private void button_aPlus_Click(object sender, EventArgs e)
        {
            int intStep = Convert.ToInt32(this.textBox_Step.Text.ToString().Trim());
            int intA = Convert.ToInt32(this.textBox_a.Text.ToString().Trim()) + intStep;
            if (intA > 108) intA = 108;
            else if (intA < -94) intA = -94;
            this.textBox_a.Text = intA.ToString();
            string strTemp = String.Format("manual({0},{1},{2})\n", this.textBox_L.Text.ToString().Trim(), intA, this.textBox_b.Text.ToString().Trim());
            m_clientSocket.ClientSend(strTemp);
            strTemp = m_clientSocket.ClientRecv();
        }

        private void button_LMinus_Click(object sender, EventArgs e)
        {
            int intStep = Convert.ToInt32(this.textBox_Step.Text.ToString().Trim());
            int intL = Convert.ToInt32(this.textBox_L.Text.ToString().Trim()) - intStep;
            if (intL > 100) intL = 100;
            else if (intL < 0) intL = 0;
            this.textBox_L.Text = intL.ToString();
            string strTemp = String.Format("manual({0},{1},{2})\n", intL, this.textBox_a.Text.ToString().Trim(), this.textBox_b.Text.ToString().Trim());
            m_clientSocket.ClientSend(strTemp);
            strTemp = m_clientSocket.ClientRecv();
        }

        private void button_aMinus_Click(object sender, EventArgs e)
        {
            int intStep = Convert.ToInt32(this.textBox_Step.Text.ToString().Trim());
            int intA = Convert.ToInt32(this.textBox_a.Text.ToString().Trim()) - intStep;
            if (intA > 108) intA = 108;
            else if (intA < -94) intA = -94;
            this.textBox_a.Text = intA.ToString();
            string strTemp = String.Format("manual({0},{1},{2})\n", this.textBox_L.Text.ToString().Trim(), intA, this.textBox_b.Text.ToString().Trim());
            m_clientSocket.ClientSend(strTemp);
            strTemp = m_clientSocket.ClientRecv();
        }

        private void button_bPlus_Click(object sender, EventArgs e)
        {
            int intStep = Convert.ToInt32(this.textBox_Step.Text.ToString().Trim());
            int intB = Convert.ToInt32(this.textBox_b.Text.ToString().Trim()) + intStep;
            if (intB > 95) intB = 95;
            else if (intB < -108) intB = -108;
            this.textBox_b.Text = intB.ToString();
            string strTemp = String.Format("manual({0},{1},{2})\n", this.textBox_L.Text.ToString().Trim(), this.textBox_a.Text.ToString().Trim(), intB);
            m_clientSocket.ClientSend(strTemp);
            strTemp = m_clientSocket.ClientRecv();
        }

        private void button_bMinus_Click(object sender, EventArgs e)
        {
            int intStep = Convert.ToInt32(this.textBox_Step.Text.ToString().Trim());
            int intB = Convert.ToInt32(this.textBox_b.Text.ToString().Trim()) - intStep;
            if (intB > 95) intB = 95;
            else if (intB < -108) intB = -108;
            this.textBox_b.Text = intB.ToString();
            string strTemp = String.Format("manual({0},{1},{2})\n", this.textBox_L.Text.ToString().Trim(), this.textBox_a.Text.ToString().Trim(), intB);
            m_clientSocket.ClientSend(strTemp);
            strTemp = m_clientSocket.ClientRecv();
        }

        private void button_ManualOnce_Click(object sender, EventArgs e)
        {
            string strTemp = null;
            m_clientSocket.ClientSend("disautimer()\n");
            strTemp = m_clientSocket.ClientRecv();
            m_clientSocket.ClientSend("autonce()\n");
            strTemp = m_clientSocket.ClientRecv();
        }

        private void ControlTableIndexChanged(object sender, EventArgs e)
        {
            RefreshVariableValues();
        }

        private void RefreshVariableValues()
        {
            string strRecved = null;
            try
            {
                if (m_clientSocket != null && m_clientSocket.GetSocketState())
                {
                    m_clientSocket.ClientSend("?\n");
                    strRecved = m_clientSocket.ClientRecv();
                }
                else
                {
                    this.Close();
                    MessageBox.Show("请先连接到服务器!");
                    return;
                }
            }
            catch (System.Exception)
            {

            }

            JObject jObj=null;
            try
            {
                jObj = JObject.Parse(strRecved);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.StackTrace.ToString());
                return;
            }
            ParseJsonData(jObj);            
        }

        private void ParseJsonData(JObject jObj)
        {
            this.textBox_r1.Text = jObj[GlobalVariable.MATTING_RGB1_R].ToString().Replace("\"", "");
            this.textBox_r2.Text = jObj[GlobalVariable.MATTING_RGB2_R].ToString().Replace("\"", "");
            this.textBox_r3.Text = jObj[GlobalVariable.MATTING_RGB3_R].ToString().Replace("\"", "");
            this.textBox_g1.Text = jObj[GlobalVariable.MATTING_RGB1_G].ToString().Replace("\"", "");
            this.textBox_g2.Text = jObj[GlobalVariable.MATTING_RGB2_G].ToString().Replace("\"", "");
            this.textBox_g3.Text = jObj[GlobalVariable.MATTING_RGB3_G].ToString().Replace("\"", "");
            this.textBox_b1.Text = jObj[GlobalVariable.MATTING_RGB1_B].ToString().Replace("\"", "");
            this.textBox_b2.Text = jObj[GlobalVariable.MATTING_RGB2_B].ToString().Replace("\"", "");
            this.textBox_b3.Text = jObj[GlobalVariable.MATTING_RGB3_B].ToString().Replace("\"", "");
            this.textBox_PingGaoBi.Text = jObj[GlobalVariable.MATTING_BORDER].ToString().Replace("\"", "");
            this.textBox_ShowDelta.Text = jObj[GlobalVariable.MATTING_DTIME].ToString().Replace("\"", "");

            this.textBox_BlockSize.Text = jObj[GlobalVariable.FILLING_BLOCK_SIZE].ToString().Replace("\"", "");
            this.textBox_BlockNumber.Text = jObj[GlobalVariable.FILLING_BLOCK_NUM].ToString().Replace("\"", "");
            this.textBox_PingGaoBi2.Text = jObj[GlobalVariable.FILLING_BORDER].ToString().Replace("\"", "");

            this.textBox_LabThreshold.Text = jObj[GlobalVariable.EVALUATION_LAB_THREHOLD].ToString().Replace("\"", "");
            this.textBox_iteration.Text = jObj[GlobalVariable.EVALUATION_ITERATION].ToString().Replace("\"", "");
            this.textBox_RunTime.Text = jObj[GlobalVariable.EVALUATION_INTERVAL].ToString().Replace("\"", "");
            this.textBox_PingGaoBi3.Text = jObj[GlobalVariable.EVALUATION_BORDER].ToString().Replace("\"", "");
            this.textBox_L.Text = jObj[GlobalVariable.EVALUATION_CURRENT_L].ToString().Replace("\"", "");
            this.textBox_a.Text = jObj[GlobalVariable.EVALUATION_CURRENT_A].ToString().Replace("\"", "");
            this.textBox_b.Text = jObj[GlobalVariable.EVALUATION_CURRENT_B].ToString().Replace("\"", "");

            string strTemp = jObj[GlobalVariable.SYS_CAMER].ToString().Replace("\"", "");
            if (strTemp.Equals("320x240"))
            {
                this.radioButton_320240.Select();
            }
            else if (strTemp.Equals("640x480"))
            {
                this.radioButton_640480.Select();
            }
            else
            {
                this.radioButton_1280960.Select();
            }

            strTemp = jObj[GlobalVariable.SYS_DEBUG].ToString().Replace("\"", "");
            if (strTemp.Equals("true"))
            {
                this.checkBox_midresult.CheckState = CheckState.Checked;
            }
            else
            {
                this.checkBox_midresult.CheckState = CheckState.Unchecked;
            }
        }
    }
}

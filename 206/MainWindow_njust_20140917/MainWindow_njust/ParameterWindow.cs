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
    //参数设置窗口类
    public partial class ParameterWindow : Form
    {
        //相机参数字符串
        public string m_strCamera = null;
        //通信套接字
        ClientSocket m_clientSocket = null;

        //参数设置窗口类的构造函数
        public ParameterWindow(ClientSocket clientSocket)
        {
            InitializeComponent(); //初始化组件, 由系统自动生成
            this.radioButton_640480.Select(); //选择640X480的单选框
            //选中显示中间结果复选框
            this.checkBox_midresult.CheckState = CheckState.Checked;
            //设置手动Lab校正参数的步长
            this.textBox_Step.Text = "5";
            m_clientSocket = clientSocket; //初始化通信套接字
            RefreshVariableValues(); //更新控件变量的值
        }

        //基本参数设置按钮事件
        private void button_CamereSetOK_Click(object sender, EventArgs e)
        {
            //构造相机参数字符串
            string strTemp = "config.camera='" + this.m_strCamera + "'\n";
            m_clientSocket.ClientSend(strTemp); //发送指令
            strTemp = m_clientSocket.ClientRecv(); //接收数据
            //如果是否输出中间结果复选框被选中
            if (this.checkBox_midresult.Checked)
            {
                m_clientSocket.ClientSend("config.debug=true\n"); //发送指令
                strTemp = m_clientSocket.ClientRecv(); //接收数据
            }
            else  //如果是否输出中间结果复选框没被选中
            {
                m_clientSocket.ClientSend("config.debug=false\n"); //发送指令
                strTemp = m_clientSocket.ClientRecv(); //接收数据
            }
        }

        //单选框改变事件
        private void button_RadioChanged(object sender, EventArgs e)
        {
            RadioButton rb = (RadioButton)sender;
            m_strCamera = rb.Text.ToString(); //从控件中得到相机参数
        }

        //抠图参数设置按钮事件
        private void button_RgbSetOK_Click(object sender, EventArgs e)
        {
            //从控件中得到三种颜色的参数
            int intR1 = Convert.ToInt32(this.textBox_r1.Text.ToString().Trim());
            int intG1 = Convert.ToInt32(this.textBox_g1.Text.ToString().Trim());
            int intB1 = Convert.ToInt32(this.textBox_b1.Text.ToString().Trim());
            int intR2 = Convert.ToInt32(this.textBox_r2.Text.ToString().Trim());
            int intG2 = Convert.ToInt32(this.textBox_g2.Text.ToString().Trim());
            int intB2 = Convert.ToInt32(this.textBox_b2.Text.ToString().Trim()); 
            int intR3 = Convert.ToInt32(this.textBox_r3.Text.ToString().Trim());
            int intG3 = Convert.ToInt32(this.textBox_g3.Text.ToString().Trim());
            int intB3 = Convert.ToInt32(this.textBox_b3.Text.ToString().Trim());
            //得到三种颜色的显示间隔时间
            int intDeltaTime = Convert.ToInt32(this.textBox_ShowDelta.Text.ToString().Trim());
            //得到抠图参数屏高比
            double dbBorder = Convert.ToDouble(this.textBox_PingGaoBi.Text.ToString().Trim());
            //判断输入的颜色值是否合法
            if ((intR1 > 255) || (intG1 > 255) || (intB1 > 255) || (intR2 > 255) || (intG2 > 255) || (intB2 > 255) || (intR3 > 255) || (intG3 > 255) || (intB3 > 255))
            {
                MessageBox.Show("RGB值范围为0~255，请重新输入!");
                return;
            }
            //判断输入的屏高比是否合法
            if (dbBorder > 0.5 || dbBorder < 0.01)
            {
                MessageBox.Show("屏高比范围0.01~0.5!");
                return;
            }
            //判断输入的显示间隔时间是否合法
            if (intDeltaTime > 120 || intDeltaTime < 5)
            {
                //如果不合法, 将其限定在合法范围内，并显示出来
                intDeltaTime = intDeltaTime > 120 ? 120 : 5;
                this.textBox_ShowDelta.Text = intDeltaTime.ToString();
            }

            //依次发送所有参数, 对返回数据不作处理
            string strTemp = null;
            //发送第一种颜色的参数
            m_clientSocket.ClientSend("config.matting.RGB1.R=" + intR1 + "\n");
            strTemp = m_clientSocket.ClientRecv();
            m_clientSocket.ClientSend("config.matting.RGB1.G=" + intG1 + "\n");
            strTemp = m_clientSocket.ClientRecv();
            m_clientSocket.ClientSend("config.matting.RGB1.B=" + intB1 + "\n");
            strTemp = m_clientSocket.ClientRecv();
            //发送第二种颜色参数
            m_clientSocket.ClientSend("config.matting.RGB2.R=" + intR2 + "\n");
            strTemp = m_clientSocket.ClientRecv();
            m_clientSocket.ClientSend("config.matting.RGB2.G=" + intG2 + "\n");
            strTemp = m_clientSocket.ClientRecv();
            m_clientSocket.ClientSend("config.matting.RGB2.B=" + intB2 + "\n");
            strTemp = m_clientSocket.ClientRecv();
            //发送第三种颜色参数
            m_clientSocket.ClientSend("config.matting.RGB3.R=" + intR3 + "\n");
            strTemp = m_clientSocket.ClientRecv();
            m_clientSocket.ClientSend("config.matting.RGB3.G=" + intG3 + "\n");
            strTemp = m_clientSocket.ClientRecv();
            m_clientSocket.ClientSend("config.matting.RGB3.B=" + intB3 + "\n");
            strTemp = m_clientSocket.ClientRecv();
            //发送抠图参数屏高比
            m_clientSocket.ClientSend("config.matting.border=" + dbBorder + "\n");
            strTemp = m_clientSocket.ClientRecv();
            //发送抠图参数显示间隔
            m_clientSocket.ClientSend("config.matting.deltaTime=" + intDeltaTime + "\n");
            strTemp = m_clientSocket.ClientRecv();
        }

        //纹理合成参数设置事件
        private void button_WenLiSetOK_Click(object sender, EventArgs e)
        {
            //从控件中获取块大小参数
            int intBlockSize = Convert.ToInt32(this.textBox_BlockSize.Text.ToString().Trim());
            //从控件中获取块个数参数
            int intBlockNum = Convert.ToInt32(this.textBox_BlockNumber.Text.ToString().Trim());
            double dbBorder = Convert.ToDouble(this.textBox_PingGaoBi2.Text.ToString().Trim());
            //判断块大小参数是否合法
            if ((intBlockSize > 1000) || (intBlockSize < 1))
            {
                MessageBox.Show("块大小范围1~1000!");
                return;
            }
            //判断块个数参数是否合法
            if ((intBlockNum > 480000))
            {
                MessageBox.Show("块个数范围0~480000!");
                return;
            }
            //判断纹理合成参数屏高比是否合法
            if (dbBorder > 0.5 || dbBorder < 0.01)
            {
                MessageBox.Show("屏高比范围0.01~0.5!");
                return;
            }
            string strTemp = null;
            //发送纹理合成参数块大小
            m_clientSocket.ClientSend("config.filling.block.size=" + intBlockSize + "\n");
            strTemp = m_clientSocket.ClientRecv();
            //发送纹理合成参数块个数
            m_clientSocket.ClientSend("config.filling.block.num=" + intBlockNum + "\n");
            strTemp = m_clientSocket.ClientRecv();
            //发送纹理合成参数屏高比
            m_clientSocket.ClientSend("config.filling.border=" + dbBorder + "\n");
            strTemp = m_clientSocket.ClientRecv();
        }

        //定时Lab校正参数设置事件
        private void button_AutoLabSetOK_Click(object sender, EventArgs e)
        {
            //从控件中获取Lab阈值
            int intLabThreshold = Convert.ToInt32(this.textBox_LabThreshold.Text.ToString().Trim());
            //从控件中获取最大迭代次数
            int intIteration = Convert.ToInt32(this.textBox_iteration.Text.ToString().Trim());
            //从控件中获取定时间隔
            int intInterval = Convert.ToInt32(this.textBox_RunTime.Text.ToString().Trim());
            double dbBorder = Convert.ToDouble(this.textBox_PingGaoBi3.Text.ToString().Trim());
            //判断定时间隔是否合法
            if ((intInterval > 7200) || (intInterval < 1))
            {
                MessageBox.Show("运行间隔范围1~7200 秒!");
                return;
            }
            //判断Lab相似性阈值是否合法
            if ((intLabThreshold > 10) || (intLabThreshold < 1))
            {
                MessageBox.Show("区域相似性阈值范围1~10!");
                return;
            }
            //判断最大迭代次数是否合法
            if (intIteration > 20)
            {
                MessageBox.Show("最大纠正次数范围0~20!");
                return;
            }
            //判断自动颜色校正算法屏高比是否合法
            if (dbBorder > 0.5 || dbBorder < 0.01)
            {
                MessageBox.Show("屏高比范围0.01~0.5!");
                return;
            }

            string strTemp = null;
            //发送lab相似性阈值
            m_clientSocket.ClientSend("config.evaluation.labThreshold=" + intLabThreshold + "\n");
            strTemp = m_clientSocket.ClientRecv();
            //发送最大迭代次数
            m_clientSocket.ClientSend("config.evaluation.iteration=" + intIteration + "\n");
            strTemp = m_clientSocket.ClientRecv();
            //发送定时间隔参数
            m_clientSocket.ClientSend("config.evaluation.interval=" + intInterval + "\n");
            strTemp = m_clientSocket.ClientRecv();
            //发送屏高比参数
            m_clientSocket.ClientSend("config.evaluation.border=" + dbBorder + "\n");
            strTemp = m_clientSocket.ClientRecv();
        }

        //定时执行按钮事件
        private void button_AutoLabDone_Click(object sender, EventArgs e)
        {
            string strTemp = null;
            m_clientSocket.ClientSend("autimer()\n"); //发送指令
            strTemp = m_clientSocket.ClientRecv(); //接收数据
        }

        //手动Lab校正参数, L加事件, 下同
        private void button_LPlus_Click(object sender, EventArgs e)
        {
            //获得L, a, b增加的步长
            int intStep = Convert.ToInt32(this.textBox_Step.Text.ToString().Trim());
            //从控件中获取L的值
            int intL = Convert.ToInt32(this.textBox_L.Text.ToString().Trim()) + intStep;
            if (intL > 100) intL = 100; //判断L是否合法
            else if (intL < 0) intL = 0;
            this.textBox_L.Text = intL.ToString(); //从控件中获取L的值
            string strTemp = String.Format("manual({0},{1},{2})\n", intL, this.textBox_a.Text.ToString().Trim(), this.textBox_b.Text.ToString().Trim());
            m_clientSocket.ClientSend(strTemp); //发送指令
            strTemp = m_clientSocket.ClientRecv(); //接收数据
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

        //手动Lab校正：执行一次按钮事件
        private void button_ManualOnce_Click(object sender, EventArgs e)
        {
            string strTemp = null;
            m_clientSocket.ClientSend("disautimer()\n"); //发送指令
            strTemp = m_clientSocket.ClientRecv(); //接收数据
            m_clientSocket.ClientSend("autonce()\n"); //发送指令
            strTemp = m_clientSocket.ClientRecv();  //接收数据
        }

        //Table页切换事件
        private void ControlTableIndexChanged(object sender, EventArgs e)
        {
            RefreshVariableValues(); //更新所有控件变量的值
        }

        //更新所有控件变量的值
        private void RefreshVariableValues()
        {
            string strRecved = null;
            try
            {
                //如果网络连接正常
                if (m_clientSocket != null && m_clientSocket.GetSocketState())
                {
                    m_clientSocket.ClientSend("?\n"); //发送指令
                    strRecved = m_clientSocket.ClientRecv(); //接收数据
                }
                else  //如果网络连接不正常
                {
                    this.Close(); //关闭对话框
                    MessageBox.Show("请先连接到服务器!");
                    return;
                }
            } 
            catch (System.Exception)  //如果发生错误
            {

            }

            JObject jObj=null;
            try
            {
                jObj = JObject.Parse(strRecved);  //解析Json
            }
            catch (Exception ex) //如果发生错误
            {
                MessageBox.Show(ex.StackTrace.ToString());
                return;
            }
            ParseJsonData(jObj);  //处理已解析的Json对象          
        }

        //处理已解析的Json对象
        private void ParseJsonData(JObject jObj)
        {
            //得到三幅图像的R通道
            this.textBox_r1.Text = jObj[GlobalVariable.MATTING_RGB1_R].ToString().Replace("\"", "");
            this.textBox_r2.Text = jObj[GlobalVariable.MATTING_RGB2_R].ToString().Replace("\"", "");
            this.textBox_r3.Text = jObj[GlobalVariable.MATTING_RGB3_R].ToString().Replace("\"", "");
            //得到三幅图像的G通道
            this.textBox_g1.Text = jObj[GlobalVariable.MATTING_RGB1_G].ToString().Replace("\"", "");
            this.textBox_g2.Text = jObj[GlobalVariable.MATTING_RGB2_G].ToString().Replace("\"", "");
            this.textBox_g3.Text = jObj[GlobalVariable.MATTING_RGB3_G].ToString().Replace("\"", "");
            //得到三幅图像的B通道
            this.textBox_b1.Text = jObj[GlobalVariable.MATTING_RGB1_B].ToString().Replace("\"", "");
            this.textBox_b2.Text = jObj[GlobalVariable.MATTING_RGB2_B].ToString().Replace("\"", "");
            this.textBox_b3.Text = jObj[GlobalVariable.MATTING_RGB3_B].ToString().Replace("\"", "");
            //得到抠图参数屏高比
            this.textBox_PingGaoBi.Text = jObj[GlobalVariable.MATTING_BORDER].ToString().Replace("\"", "");
            //得到抠图参数显示时间间隔
            this.textBox_ShowDelta.Text = jObj[GlobalVariable.MATTING_DTIME].ToString().Replace("\"", "");
            //得到纹理合成参数块大小
            this.textBox_BlockSize.Text = jObj[GlobalVariable.FILLING_BLOCK_SIZE].ToString().Replace("\"", "");
            //得到纹理合成参数块个数
            this.textBox_BlockNumber.Text = jObj[GlobalVariable.FILLING_BLOCK_NUM].ToString().Replace("\"", "");
            //得到纹理合成参数屏高比
            this.textBox_PingGaoBi2.Text = jObj[GlobalVariable.FILLING_BORDER].ToString().Replace("\"", "");
            //得到Lab相似性阈值
            this.textBox_LabThreshold.Text = jObj[GlobalVariable.EVALUATION_LAB_THREHOLD].ToString().Replace("\"", "");
            //得到最大迭代次数
            this.textBox_iteration.Text = jObj[GlobalVariable.EVALUATION_ITERATION].ToString().Replace("\"", "");
            //得到定时间隔
            this.textBox_RunTime.Text = jObj[GlobalVariable.EVALUATION_INTERVAL].ToString().Replace("\"", "");
            //得到颜色校正参数屏高比
            this.textBox_PingGaoBi3.Text = jObj[GlobalVariable.EVALUATION_BORDER].ToString().Replace("\"", "");
            //得到L, a, b值
            this.textBox_L.Text = jObj[GlobalVariable.EVALUATION_CURRENT_L].ToString().Replace("\"", "");
            this.textBox_a.Text = jObj[GlobalVariable.EVALUATION_CURRENT_A].ToString().Replace("\"", "");
            this.textBox_b.Text = jObj[GlobalVariable.EVALUATION_CURRENT_B].ToString().Replace("\"", "");
            //得到相机参数
            string strTemp = jObj[GlobalVariable.SYS_CAMER].ToString().Replace("\"", "");
            if (strTemp.Equals("320x240")) //如果相机参数是320x240
            {
                this.radioButton_320240.Select(); //设置单选框选择内容
            }
            else if (strTemp.Equals("640x480")) //如果相机参数是640x480
            {
                this.radioButton_640480.Select(); //设置单选框选择内容
            }
            else
            {
                this.radioButton_1280960.Select(); //设置单选框选择内容
            }
            //系统调试状态
            strTemp = jObj[GlobalVariable.SYS_DEBUG].ToString().Replace("\"", "");
            if (strTemp.Equals("true")) //如果状态为调试
            {
                //设置复选框是否输出中间结果
                this.checkBox_midresult.CheckState = CheckState.Checked;
            }
            else //如果状态为非调试
            {
                //设置复选框是否输出中间结果
                this.checkBox_midresult.CheckState = CheckState.Unchecked;
            }
        }
    }
}

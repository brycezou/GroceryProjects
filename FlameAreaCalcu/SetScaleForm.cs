using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;

namespace FlameAreaCalcu
{
    public partial class SetScaleForm : Form
    {
        private bool m_bImageLoaded = false;
        private bool m_bLButtonDown = false;
        private Point m_StartPoint;
        private Point m_EndPoint;
        private Graphics mGraph = null;
        private Pen mPen = new Pen(Color.Green, 1);
        private int m_PicWidth;
        private int m_PicHeight;
        private double m_TempRatio;
        private MainForm m_mainForm;

        public SetScaleForm(MainForm mf)
        {
            InitializeComponent();
            m_mainForm = mf;
        }

        private void SetScaleForm_Load(object sender, EventArgs e)
        {
            this.mGraph = pictureBox.CreateGraphics();
            m_TempRatio = -1;
            SetLanguage();
        }

        private void button_createFile_Click(object sender, EventArgs e)
        {
            if (m_TempRatio < 0)
            {
                //MessageBox.Show("请先进行标定!");
                MessageBox.Show(LanguageControl.MSG_CALIBRATE_FIRST);
                return;
            }
            SaveFileDialog sfd = new SaveFileDialog();
            sfd.Filter = "标定文件|*.std";
            if (sfd.ShowDialog() == DialogResult.OK)
            {
                    string fileName = sfd.FileName;
                    SaveFile(fileName); 
            }
        }

        protected void SaveFile(string fileName)  
        {   
            try   
            {    
                Stream stream = File.OpenWrite(fileName); 
                using(StreamWriter writer = new StreamWriter(stream))    
                {
                    writer.WriteLine(m_TempRatio);
                    writer.Close();
                }
                stream.Close();
                //MessageBox.Show("保存成功!");
                MessageBox.Show(LanguageControl.MSG_SAVE_SUCCESSFULLY);
            } 
            catch(IOException)   
            {  
                //MessageBox.Show("保存文件失败!");
                MessageBox.Show(LanguageControl.MSG_SAVE_FILE_FAILED); 
            } 
        }

        private void button_readFile_Click(object sender, EventArgs e)
        {
            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                string fielName = openFileDialog1.FileName;
                FileInfo fi = new FileInfo(fielName);
                StreamReader sr = fi.OpenText();
                if(sr.Peek() > 0)
                {
                    string strRatio = sr.ReadLine();
                    m_TempRatio = Convert.ToDouble(strRatio);
                    this.label_scaleValue.Text = String.Format("<{0}>", m_TempRatio.ToString("f2"));
                    //MessageBox.Show("导入成功!");
                    MessageBox.Show(LanguageControl.MSG_LOAD_SUCCESSFULLY);
                }
                sr.Close();
            }
        }

        private void button_LoadImage_Click(object sender, EventArgs e)
        {
            if (openFileDialog.ShowDialog() == DialogResult.OK)
            {
                string fielName = openFileDialog.FileName;
                Bitmap srcImg = new Bitmap(fielName);
                m_PicHeight = srcImg.Height;
                m_PicWidth = srcImg.Width;
                pictureBox.Image = srcImg;
                //if (m_PicWidth > this.pictureBox.Width && m_PicHeight > this.pictureBox.Height)
                //    this.pictureBox.SizeMode = PictureBoxSizeMode.StretchImage;
                //else
                //    this.pictureBox.SizeMode = PictureBoxSizeMode.CenterImage;
                //this.Refresh();
                m_bImageLoaded = true;
            }
        }

        private void pictureBox_MouseDown(object sender, MouseEventArgs e)
        {
            if (m_bImageLoaded)
            {
                switch (e.Button)
                {
                    case MouseButtons.Left:
                        this.Refresh();
                        m_bLButtonDown = true;
                        m_StartPoint = e.Location;
                        mPen.Color = Color.Red;
                        mGraph.DrawEllipse(mPen, m_StartPoint.X - 15, m_StartPoint.Y - 15, 30, 30);
                        break;
                    default:
                        break;
                }
            }
        }

        private void pictureBox_MouseMove(object sender, MouseEventArgs e)
        {
            if (m_bLButtonDown)
            {
                mPen.Color = Color.Red;
                mGraph.DrawEllipse(mPen, m_StartPoint.X - 15, m_StartPoint.Y - 15, 30, 30);
                mPen.Color = Color.Green;
                mGraph.DrawLine(mPen, m_StartPoint, e.Location);
                //string strText = String.Format("{0}: {1:N2}", "线段长度", GetPixelDistance(m_StartPoint, e.Location));
                string strText = String.Format("{0}: {1:N2}", LanguageControl.MSG_LINE_LENGTH1, GetPixelDistance(m_StartPoint, e.Location));
                mGraph.DrawString(strText, new Font("宋体", 18f), Brushes.Pink, new Point(25, this.pictureBox.Height - 65));
                this.Refresh();
                mPen.Color = Color.Red;
                mGraph.DrawEllipse(mPen, m_StartPoint.X - 15, m_StartPoint.Y - 15, 30, 30);
                mPen.Color = Color.Green;
                mGraph.DrawLine(mPen, m_StartPoint, e.Location);
                mGraph.DrawString(strText, new Font("宋体", 18f), Brushes.Pink, new Point(25, this.pictureBox.Height - 65));
            }
        }

        private void pictureBox_MouseUp(object sender, MouseEventArgs e)
        {
            if (m_bImageLoaded)
            {
                switch (e.Button)
                {
                    case MouseButtons.Left:
                        if (m_bLButtonDown)
                        {
                            m_EndPoint = e.Location;
                            mPen.Color = Color.Red;
                            mGraph.DrawEllipse(mPen, m_StartPoint.X - 15, m_StartPoint.Y - 15, 30, 30);
                            mPen.Color = Color.Green;
                            mGraph.DrawLine(mPen, m_StartPoint, e.Location);
                            mPen.Color = Color.Red;
                            mGraph.DrawEllipse(mPen, m_EndPoint.X - 15, m_EndPoint.Y - 15, 30, 30);
                            if (!m_EndPoint.Equals(m_StartPoint))
                            {
                                int dist = (int)Math.Ceiling(GetPixelDistance(m_StartPoint, m_EndPoint));
                                this.textBox_DIP.Text = dist + "";
                                this.textBox_KD.Text = dist + "";
                                this.textBox_UOL.Text = "pixel";
                            }
                        }
                        m_bLButtonDown = false;
                        break;
                    default:
                        break;
                }
            }
        }

        private double GetPixelDistance(Point sp, Point ep)
        {
            int boxWidth = this.pictureBox.Width;
            int boxHeight = this.pictureBox.Height;
            int picWidth = m_PicWidth;
            int picHeight = m_PicHeight;
            double pbRatioW = picWidth / 1.0 / boxWidth;
            double pbRatioH = picHeight / 1.0 / boxHeight;
            double realStartX = pbRatioW * sp.X;
            double realStartY = pbRatioH * sp.Y;
            double realEndX = pbRatioW * ep.X;
            double realEndY = pbRatioH * ep.Y;
            double dx = realEndX - realStartX;
            double dy = realEndY - realStartY;
            double dist = Math.Sqrt(dx * dx + dy * dy);
            return dist;
        }

        private void textBox_KD_TextChanged(object sender, EventArgs e)
        {
            if (!this.textBox_DIP.Text.Trim().Equals("") && !this.textBox_KD.Text.Trim().Equals(""))
            {
                try
                {
                    double pix_dis = Convert.ToDouble(this.textBox_DIP.Text.Trim());
                    double real_dis = Convert.ToDouble(this.textBox_KD.Text.Trim());
                    m_TempRatio = real_dis / pix_dis;
                    this.label_scaleValue.Text = String.Format("<{0}>", m_TempRatio.ToString("f2"));
                }
                catch (System.Exception)
                {
                    //MessageBox.Show("输入数据不合法!");
                    MessageBox.Show(LanguageControl.MSG_ILLEGAL_INPUT);
                }
            }
        }

        private void button_Cancel_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void button_OK_Click(object sender, EventArgs e)
        {
            if (m_TempRatio != -1)
            {
                CalcuAeras.PIX_DIS_RATIO = m_TempRatio;
                m_mainForm.toolStrip_StatusLabel.Text = LanguageControl.MSG_STATUS_LABEL2 + m_TempRatio.ToString("f2");
                if (!this.textBox_UOL.Text.Trim().Equals("") && !this.textBox_UOL.Text.Trim().Equals("pixel"))
                {
                    CalcuAeras.AERA_UNIT = this.textBox_UOL.Text.Trim() + "^2";
                    m_mainForm.CallCalcuAeras();
                }
                else
                {
                    CalcuAeras.AERA_UNIT = "pixel";
                    m_mainForm.CallCalcuAeras();
                }
            }
            this.Close();
        }

        private void button_Help_Click(object sender, EventArgs e)
        {

        }

        private void SetLanguage()
        {
            LanguageControl.SetLanguage();
            this.Text = LanguageControl.STR_CALIBRATE_FORM_NAME;
            this.label_DIP.Text = LanguageControl.STR_CALIBRATE_DIP;
            this.label_KD.Text = LanguageControl.STR_CALIBRATE_KD;
            this.label_UOL.Text = LanguageControl.STR_CALIBRATE_UOL;
            this.label_perPixelDis.Text = LanguageControl.STR_CALIBRATE_PERPIXEL_LENGTH;
            this.label_scaleValue.Text = LanguageControl.STR_CALIBRATE_SCALE_VALUE;
            this.button_LoadImage.Text = LanguageControl.STR_CALIBRATE_READ_IMAGE;
            this.button_createFile.Text = LanguageControl.STR_CALIBRATE_CREATE_FILE;
            this.button_readFile.Text = LanguageControl.STR_CALIBRATE_LOAD_FILE;
            this.button_Cancel.Text = LanguageControl.STR_CALIBRATE_CANCEL;
            this.button_Help.Text = LanguageControl.STR_CALIBRATE_HELP;
            this.button_OK.Text = LanguageControl.STR_CALIBRATE_OK;
        }

    }
}

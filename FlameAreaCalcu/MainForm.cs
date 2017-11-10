using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;
using System.Threading;
using System.Drawing.Printing;


namespace FlameAreaCalcu
{
    public partial class MainForm : Form
    {
        private CalcuAeras mCalcuAera = new CalcuAeras();
        private bool m_bCalculatingAera = false;
        //left button
        private bool m_bLButtonDown = false;
        private Point m_LStartPoint;
        private Point m_LEndPoint;
        private Graphics mGraph = null;
        private Pen mLPen = new Pen(Color.Green, 1);
        //right button
        private bool m_bRButtonDown = false;
        private Point m_RStartPoint;
        private Point m_REndPoint;
        private Pen mRPen = new Pen(Color.Green, 1);

        private string m_fileName = null;
        private bool m_bMeasureDistance = false;

        private bool m_bLlined = false;
        private bool m_bRlined = false;

        private double m_pbRatioW;
        private double m_pbRatioH;

        public MainForm()
        {
            InitializeComponent();
            CalcuAeras.PIX_DIS_RATIO = -100;
            CalcuAeras.AERA_UNIT = "pixel";
            CalcuAeras.HIST_LOW_VALUE = -1;
            CalcuAeras.HIST_HIGH_VALUE = -1;
        }

        private void MainForm_Load(object sender, EventArgs e)
        {
            this.另存为ToolStripMenuItem.Enabled = false;
            this.保存数据ToolStripMenuItem.Enabled = false;
            this.关闭ToolStripMenuItem.Enabled = false;
            this.测量距离ToolStripMenuItem.Enabled = false;
            this.测量面积ToolStripMenuItem.Enabled = false;
            this.打印ToolStripMenuItem.Enabled = false;

            this.toolStripButton_saveAs.Enabled = false;
            this.toolStripButton_saveData.Enabled = false;
            this.toolStripButton_closeFile.Enabled = false;
            this.toolStripButton_measureDistance.Enabled = false;
            this.toolStripButton_measureAera.Enabled = false;

            this.mGraph = pictureBox.CreateGraphics();
            LanguageControl.m_bChinese = true;
            LanguageControl.SetLanguage();
            //this.toolStrip_StatusLabel.Text = "未标定，比例尺为：1.00";
            this.toolStrip_StatusLabel.Text = LanguageControl.MSG_STATUS_LABEL;
        }

        private void ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            ToolStripMenuItem tsmi = (ToolStripMenuItem)sender;
            if (tsmi.Text.Equals(LanguageControl.STR_MENU_OPEN))    //打开文件
                OpenNewImageFile();
            else if (tsmi.Text.Equals(LanguageControl.STR_MENU_SAVE_AS))    //另存为
            {
                SaveFileDialog sfd = new SaveFileDialog();
                sfd.Filter = "位图|*.bmp";
                sfd.FileName = m_fileName;
                if (sfd.ShowDialog() == DialogResult.OK)
                {
                    SaveAsNewImage(sfd.FileName);
                    MessageBox.Show(LanguageControl.MSG_SAVE_SUCCESSFULLY);
                    CloseCurrentImageFile();
                }
            }
            else if (tsmi.Text.Equals(LanguageControl.STR_MENU_SAVE_DATA))  //保存数据
            {
                SaveFileDialog sfd = new SaveFileDialog();
                sfd.Filter = "文本文件|*.txt";
                sfd.OverwritePrompt = false;
                if (sfd.ShowDialog() == DialogResult.OK)
                    SaveDataFile(sfd.FileName);
            }
            else if (tsmi.Text.Equals(LanguageControl.STR_MENU_CLOSE)) //关闭
                CloseCurrentImageFile();
            else if (tsmi.Text.Equals(LanguageControl.STR_MENU_EXIT))   //退出
                this.Close();
            else if (tsmi.Text.Equals(LanguageControl.STR_MENU_MEASURE_DISTANCE))   //测量距离
            {
                this.测量距离ToolStripMenuItem.CheckState = CheckState.Checked;
                this.测量面积ToolStripMenuItem.CheckState = CheckState.Unchecked;
                m_bMeasureDistance = true;
                this.Refresh();
            }
            else if (tsmi.Text.Equals(LanguageControl.STR_MENU_MEASURE_AREA))   //测量面积
            {
                this.测量距离ToolStripMenuItem.CheckState = CheckState.Unchecked;
                this.测量面积ToolStripMenuItem.CheckState = CheckState.Checked;
                m_bMeasureDistance = false;
                HistogramForm hf = new HistogramForm(this, mCalcuAera);
                hf.ShowDialog();
                this.Refresh();
            }
            else if (tsmi.Text.Equals(LanguageControl.STR_MENU_CALIBRATE))    //标定
            {
                SetScaleForm ssf = new SetScaleForm(this);
                ssf.ShowDialog();
            }
            else if (tsmi.Text.Equals("中文"))
            {
                LanguageControl.m_bChinese = true;
                SetLanguage();
                CallCalcuAeras();
                this.中文ToolStripMenuItem.CheckState = CheckState.Checked;
                this.englishToolStripMenuItem.CheckState = CheckState.Unchecked;
                if (CalcuAeras.PIX_DIS_RATIO < 0)
                    this.toolStrip_StatusLabel.Text = LanguageControl.MSG_STATUS_LABEL;
                else
                    this.toolStrip_StatusLabel.Text = LanguageControl.MSG_STATUS_LABEL2 + CalcuAeras.PIX_DIS_RATIO.ToString("f2");
            }
            else if (tsmi.Text.Equals("Français"))       //English
            {
                LanguageControl.m_bChinese = false;
                SetLanguage();
                CallCalcuAeras();
                this.中文ToolStripMenuItem.CheckState = CheckState.Unchecked;
                this.englishToolStripMenuItem.CheckState = CheckState.Checked;
                if (CalcuAeras.PIX_DIS_RATIO < 0)
                    this.toolStrip_StatusLabel.Text = LanguageControl.MSG_STATUS_LABEL;
                else
                    this.toolStrip_StatusLabel.Text = LanguageControl.MSG_STATUS_LABEL2 + CalcuAeras.PIX_DIS_RATIO.ToString("f2");
            }
            else if (tsmi.Text.Equals(LanguageControl.STR_MENU_ABOUT))
            {
                AboutForm af = new AboutForm();
                af.ShowDialog();
            }
            else if (tsmi.Text.Equals(LanguageControl.STR_MENU_PRINT_IMAGE))
            {
                if (this.pictureBox.Image == null)
                    return;
                this.printDocument.PrintPage += new PrintPageEventHandler(PrintPage);
                //初始化要显示的设置窗口
                PageSetupDialog objPageSetupDialog = new PageSetupDialog();
                objPageSetupDialog.Document = this.printDocument;       //获取文档
                if (objPageSetupDialog.ShowDialog() == DialogResult.OK)
                {
                    //初始化要预览窗口
                    PrintPreviewDialog objPrintPreviewDialog = new PrintPreviewDialog();
                    objPrintPreviewDialog.Document = this.printDocument;  //获取要预览的文档
                    if (objPrintPreviewDialog.ShowDialog() == DialogResult.OK)
                        objPrintPreviewDialog.ShowDialog();
                }
                this.printDocument.PrintPage -= new PrintPageEventHandler(PrintPage);
                CloseCurrentImageFile();
            }
        }

        private void PrintPage(object sender, PrintPageEventArgs e)
        {
            if (m_bLlined)
            {
                if (CalcuAeras.PIX_DIS_RATIO < 0)
                    mCalcuAera.NSetText_2Threshold(LanguageControl.MSG_LINE_LENGTH1, (float)GetPixelDistance(m_LStartPoint, m_LEndPoint), true,
                        (int)(m_pbRatioW * m_LStartPoint.X), (int)(m_pbRatioH * m_LStartPoint.Y), (int)(m_pbRatioW * m_LEndPoint.X), (int)(m_pbRatioH * m_LEndPoint.Y));
                else
                    mCalcuAera.NSetText_2Threshold(LanguageControl.MSG_LINE_LENGTH1, (float)(CalcuAeras.PIX_DIS_RATIO * GetPixelDistance(m_LStartPoint, m_LEndPoint)), true,
                        (int)(m_pbRatioW * m_LStartPoint.X), (int)(m_pbRatioH * m_LStartPoint.Y), (int)(m_pbRatioW * m_LEndPoint.X), (int)(m_pbRatioH * m_LEndPoint.Y));
            }
            if (m_bRlined)
            {
                if (CalcuAeras.PIX_DIS_RATIO < 0)
                    mCalcuAera.NSetText_2Threshold(LanguageControl.MSG_LINE_LENGTH2, (float)GetPixelDistance(m_RStartPoint, m_REndPoint), false,
                        (int)(m_pbRatioW * m_RStartPoint.X), (int)(m_pbRatioH * m_RStartPoint.Y), (int)(m_pbRatioW * m_REndPoint.X), (int)(m_pbRatioH * m_REndPoint.Y));
                else
                    mCalcuAera.NSetText_2Threshold(LanguageControl.MSG_LINE_LENGTH2, (float)(CalcuAeras.PIX_DIS_RATIO * GetPixelDistance(m_RStartPoint, m_REndPoint)), false,
                        (int)(m_pbRatioW * m_RStartPoint.X), (int)(m_pbRatioH * m_RStartPoint.Y), (int)(m_pbRatioW * m_REndPoint.X), (int)(m_pbRatioH * m_REndPoint.Y));
            }
            Graphics g = e.Graphics;    //获取用于绘制页面的Graphics的对象
            g.DrawImage(mCalcuAera.NGetDstImage2(), 0, 0);
            g.Dispose();
        }

        public void ShowDstImage()
        {
            Bitmap bmp = mCalcuAera.NGetDstImage2();
            this.pictureBox.Image = bmp;
            this.Refresh();
        }

        private void pictureBox_MouseDown(object sender, MouseEventArgs e)
        {
            if (!m_bMeasureDistance)
                return;

            if (mCalcuAera.bSuccessful)
            {
                switch (e.Button)
                {
                    case MouseButtons.Left:
                        m_bLlined = false;
                        m_bRlined = false;
                        this.Refresh();
                        m_bLButtonDown = true;
                        m_LStartPoint = e.Location;
                        mLPen.Color = Color.Red;
                        mGraph.DrawEllipse(mLPen, m_LStartPoint.X - 15, m_LStartPoint.Y - 15, 30, 30);
                        break;
                    case MouseButtons.Right:
                        m_bRlined = false;
                        if(m_bLButtonDown)
                            return;
                        this.Refresh();
                        m_bRButtonDown = true;
                        m_RStartPoint = e.Location;
                        mRPen.Color = Color.Red;
                        mGraph.DrawEllipse(mRPen, m_RStartPoint.X - 15, m_RStartPoint.Y - 15, 30, 30);
                        ///////////////////////////////////////////////////////////////////////////////////加载第一条线
                        if (m_bLlined)
                        {
                            mLPen.Color = Color.Red;
                            mGraph.DrawEllipse(mLPen, m_LStartPoint.X - 15, m_LStartPoint.Y - 15, 30, 30);
                            mGraph.DrawEllipse(mLPen, m_LEndPoint.X - 15, m_LEndPoint.Y - 15, 30, 30);
                            mLPen.Color = Color.Green;
                            mGraph.DrawLine(mLPen, m_LStartPoint, m_LEndPoint);
                            string strText;
                            if (CalcuAeras.PIX_DIS_RATIO < 0)
                                strText = String.Format("{0}: {1:N2}", LanguageControl.MSG_LINE_LENGTH1, GetPixelDistance(m_LStartPoint, m_LEndPoint));
                            else
                                strText = String.Format("{0}: {1:N2}", LanguageControl.MSG_LINE_LENGTH1, CalcuAeras.PIX_DIS_RATIO * GetPixelDistance(m_LStartPoint, m_LEndPoint));
                            mGraph.DrawString(strText, new Font("宋体", 18f), Brushes.Pink, new Point(25, this.pictureBox.Height - 105));
                        }
                        ///////////////////////////////////////////////////////////////////////////////////
                        break;
                    default:
                        break;
                }
            }
        }
        private void pictureBox_MouseUp(object sender, MouseEventArgs e)
        {
            if (!m_bMeasureDistance)
                return;

            if (mCalcuAera.bSuccessful)
            {
                switch (e.Button)
                {
                    case MouseButtons.Left:
                        if (m_bLButtonDown)
                        {
                            m_LEndPoint = e.Location;
                            mLPen.Color = Color.Red;
                            mGraph.DrawEllipse(mLPen, m_LStartPoint.X - 15, m_LStartPoint.Y - 15, 30, 30);
                            mLPen.Color = Color.Green;
                            mGraph.DrawLine(mLPen, m_LStartPoint, e.Location);
                            mLPen.Color = Color.Red;
                            mGraph.DrawEllipse(mLPen, m_LEndPoint.X - 15, m_LEndPoint.Y - 15, 30, 30);
                            if (!m_LEndPoint.Equals(m_LStartPoint))
                            {
                                //int dist = (int)Math.Ceiling(GetPixelDistance(m_LStartPoint, m_LEndPoint));
                                mGraph.DrawString("1", new Font("宋体", 10f), Brushes.Yellow, new Point(m_LStartPoint.X, m_LStartPoint.Y));
                                mGraph.DrawString("1", new Font("宋体", 10f), Brushes.Yellow, new Point(m_LEndPoint.X, m_LEndPoint.Y));
                                m_bLlined = true;
                            }
                        }
                        m_bLButtonDown = false;
                        break;
                    case MouseButtons.Right:
                        if (m_bLButtonDown)
                            return;
                        if (m_bRButtonDown)
                        {
                            m_REndPoint = e.Location;
                            mRPen.Color = Color.Red;
                            mGraph.DrawEllipse(mRPen, m_RStartPoint.X - 15, m_RStartPoint.Y - 15, 30, 30);
                            mRPen.Color = Color.Green;
                            mGraph.DrawLine(mRPen, m_RStartPoint, e.Location);
                            mRPen.Color = Color.Red;
                            mGraph.DrawEllipse(mRPen, m_REndPoint.X - 15, m_REndPoint.Y - 15, 30, 30);
                            if (!m_REndPoint.Equals(m_RStartPoint))
                            {
                                mGraph.DrawString("2", new Font("宋体", 10f), Brushes.Yellow, new Point(m_RStartPoint.X, m_RStartPoint.Y));
                                mGraph.DrawString("2", new Font("宋体", 10f), Brushes.Yellow, new Point(m_REndPoint.X, m_REndPoint.Y));
                                m_bRlined = true;
                            }
                        }
                        m_bRButtonDown = false;
                        break;
                    default:
                        break;
                }
            }
        }
        private void pictureBox_MouseMove(object sender, MouseEventArgs e)
        {
            if (!m_bMeasureDistance)
                return;

            if (m_bLButtonDown)
            {
                mLPen.Color = Color.Red;
                mGraph.DrawEllipse(mLPen, m_LStartPoint.X - 15, m_LStartPoint.Y - 15, 30, 30);
                mLPen.Color = Color.Green;
                mGraph.DrawLine(mLPen, m_LStartPoint, e.Location);
                string strText;
                if (CalcuAeras.PIX_DIS_RATIO < 0)
                    strText = String.Format("{0}: {1:N2}", LanguageControl.MSG_LINE_LENGTH1,  GetPixelDistance(m_LStartPoint, e.Location));
                else
                    strText = String.Format("{0}: {1:N2}", LanguageControl.MSG_LINE_LENGTH1, CalcuAeras.PIX_DIS_RATIO * GetPixelDistance(m_LStartPoint, e.Location));
                mGraph.DrawString(strText, new Font("宋体", 18f), Brushes.Pink, new Point(25, this.pictureBox.Height-105));
                this.Refresh();
                mLPen.Color = Color.Red;
                mGraph.DrawEllipse(mLPen, m_LStartPoint.X - 15, m_LStartPoint.Y - 15, 30, 30);
                mLPen.Color = Color.Green;
                mGraph.DrawLine(mLPen, m_LStartPoint, e.Location);
                mGraph.DrawString(strText, new Font("宋体", 18f), Brushes.Pink, new Point(25, this.pictureBox.Height-105));
            }
            if (m_bRButtonDown)
            {
                if (m_bLButtonDown)
                    return;
                mRPen.Color = Color.Red;
                mGraph.DrawEllipse(mRPen, m_RStartPoint.X - 15, m_RStartPoint.Y - 15, 30, 30);
                mRPen.Color = Color.Green;
                mGraph.DrawLine(mRPen, m_RStartPoint, e.Location);
                string strText;
                if (CalcuAeras.PIX_DIS_RATIO < 0)
                    strText = String.Format("{0}: {1:N2}", LanguageControl.MSG_LINE_LENGTH2, GetPixelDistance(m_RStartPoint, e.Location));
                else
                    strText = String.Format("{0}: {1:N2}", LanguageControl.MSG_LINE_LENGTH2, CalcuAeras.PIX_DIS_RATIO * GetPixelDistance(m_RStartPoint, e.Location));
                mGraph.DrawString(strText, new Font("宋体", 18f), Brushes.Pink, new Point(25, this.pictureBox.Height - 65));
                this.Refresh();
                mRPen.Color = Color.Red;
                mGraph.DrawEllipse(mRPen, m_RStartPoint.X - 15, m_RStartPoint.Y - 15, 30, 30);
                mRPen.Color = Color.Green;
                mGraph.DrawLine(mRPen, m_RStartPoint, e.Location);
                mGraph.DrawString(strText, new Font("宋体", 18f), Brushes.Pink, new Point(25, this.pictureBox.Height - 65));
                ///////////////////////////////////////////////////////////////////////////////////加载第一条线
                if (m_bLlined)
                {
                    mLPen.Color = Color.Red;
                    mGraph.DrawEllipse(mLPen, m_LStartPoint.X - 15, m_LStartPoint.Y - 15, 30, 30);
                    mGraph.DrawEllipse(mLPen, m_LEndPoint.X - 15, m_LEndPoint.Y - 15, 30, 30);
                    mLPen.Color = Color.Green;
                    mGraph.DrawLine(mLPen, m_LStartPoint, m_LEndPoint);
                    if (CalcuAeras.PIX_DIS_RATIO < 0)
                        strText = String.Format("{0}: {1:N2}", LanguageControl.MSG_LINE_LENGTH1, GetPixelDistance(m_LStartPoint, m_LEndPoint));
                    else
                        strText = String.Format("{0}: {1:N2}", LanguageControl.MSG_LINE_LENGTH1, CalcuAeras.PIX_DIS_RATIO * GetPixelDistance(m_LStartPoint, m_LEndPoint));
                    mGraph.DrawString(strText, new Font("宋体", 18f), Brushes.Pink, new Point(25, this.pictureBox.Height - 105));
                    mGraph.DrawString("1", new Font("宋体", 10f), Brushes.Yellow, new Point(m_LStartPoint.X, m_LStartPoint.Y));
                    mGraph.DrawString("1", new Font("宋体", 10f), Brushes.Yellow, new Point(m_LEndPoint.X, m_LEndPoint.Y));
                }
                ///////////////////////////////////////////////////////////////////////////////////
            }
        }

        private void OpenNewImageFile()
        {
            if (openFileDialog.ShowDialog() == DialogResult.OK)
            {
                string fielName = openFileDialog.FileName;
                m_fileName = fielName.Substring(fielName.LastIndexOf('\\') + 1);
                mCalcuAera.NLoadImage_2Threshold(fielName);
                if (mCalcuAera.bSuccessful)
                {
                    this.打开ToolStripMenuItem.Enabled = false;
                    this.另存为ToolStripMenuItem.Enabled = true;
                    this.保存数据ToolStripMenuItem.Enabled = true;
                    this.关闭ToolStripMenuItem.Enabled = true;
                    this.测量距离ToolStripMenuItem.Enabled = true;
                    this.测量面积ToolStripMenuItem.Enabled = true;
                    this.打印ToolStripMenuItem.Enabled = true;

                    this.toolStripButton_openFile.Enabled = false;
                    this.toolStripButton_saveAs.Enabled = true;
                    this.toolStripButton_saveData.Enabled = true;
                    this.toolStripButton_closeFile.Enabled = true;
                    this.toolStripButton_measureDistance.Enabled = true;
                    this.toolStripButton_measureAera.Enabled = true;

                    m_bLlined = false;
                    m_bRlined = false;

                    Bitmap bmp = mCalcuAera.NGetSrcImage();
                    this.pictureBox.Image = bmp;
                    mCalcuAera.NGetHistImage(bmp);
                    CalcuAeras.HIST_LOW_VALUE = -1;
                    CalcuAeras.HIST_HIGH_VALUE = -1;
                    HistogramForm hf = new HistogramForm(this, mCalcuAera);
                    hf.ShowDialog();
                }
                else
                    //MessageBox.Show("读取图像失败!");
                    MessageBox.Show(LanguageControl.MSG_READ_IMAGE_FAILED);
            }
        }

        private void CloseCurrentImageFile()
        {
            if (mCalcuAera.bSuccessful)
            {
                mCalcuAera.NReleaseImage();
                mCalcuAera.bSuccessful = false;
                this.打开ToolStripMenuItem.Enabled = true;
                this.另存为ToolStripMenuItem.Enabled = false;
                this.保存数据ToolStripMenuItem.Enabled = false;
                this.关闭ToolStripMenuItem.Enabled = false;
                this.测量距离ToolStripMenuItem.Enabled = false;
                this.测量面积ToolStripMenuItem.Enabled = false;
                this.打印ToolStripMenuItem.Enabled = false;

                this.toolStripButton_openFile.Enabled = true;
                this.toolStripButton_saveAs.Enabled = false;
                this.toolStripButton_saveData.Enabled = false;
                this.toolStripButton_closeFile.Enabled = false;
                this.toolStripButton_measureDistance.Enabled = false;
                this.toolStripButton_measureAera.Enabled = false;
                this.pictureBox.Image = null;
                this.Refresh();
            }
        }

        private void SaveAsNewImage(string strBmpName)
        {
            if (mCalcuAera.bSuccessful && (m_bCalculatingAera == false))
            {
                if (m_bLlined)
                {
                    if (CalcuAeras.PIX_DIS_RATIO < 0)
                        mCalcuAera.NSetText_2Threshold(LanguageControl.MSG_LINE_LENGTH1, (float)GetPixelDistance(m_LStartPoint, m_LEndPoint), true,
                            (int)(m_pbRatioW * m_LStartPoint.X), (int)(m_pbRatioH * m_LStartPoint.Y), (int)(m_pbRatioW * m_LEndPoint.X), (int)(m_pbRatioH * m_LEndPoint.Y));
                    else
                        mCalcuAera.NSetText_2Threshold(LanguageControl.MSG_LINE_LENGTH1, (float)(CalcuAeras.PIX_DIS_RATIO * GetPixelDistance(m_LStartPoint, m_LEndPoint)), true,
                            (int)(m_pbRatioW * m_LStartPoint.X), (int)(m_pbRatioH * m_LStartPoint.Y), (int)(m_pbRatioW * m_LEndPoint.X), (int)(m_pbRatioH * m_LEndPoint.Y));
                }
                if (m_bRlined)
                {
                    if (CalcuAeras.PIX_DIS_RATIO < 0)
                        mCalcuAera.NSetText_2Threshold(LanguageControl.MSG_LINE_LENGTH2, (float)GetPixelDistance(m_RStartPoint, m_REndPoint), false,
                            (int)(m_pbRatioW * m_RStartPoint.X), (int)(m_pbRatioH * m_RStartPoint.Y), (int)(m_pbRatioW * m_REndPoint.X), (int)(m_pbRatioH * m_REndPoint.Y));
                    else
                        mCalcuAera.NSetText_2Threshold(LanguageControl.MSG_LINE_LENGTH2, (float)(CalcuAeras.PIX_DIS_RATIO * GetPixelDistance(m_RStartPoint, m_REndPoint)), false,
                            (int)(m_pbRatioW * m_RStartPoint.X), (int)(m_pbRatioH * m_RStartPoint.Y), (int)(m_pbRatioW * m_REndPoint.X), (int)(m_pbRatioH * m_REndPoint.Y));
                }
                Bitmap bmp = mCalcuAera.NGetDstImage2();
                bmp.Save(strBmpName);
            }
        }

        private double GetPixelDistance(Point sp, Point ep)
        {
            int boxWidth = this.pictureBox.Width;
            int boxHeight = this.pictureBox.Height;
            int picWidth = mCalcuAera.NGetWidth();
            int picHeight = mCalcuAera.NGetHeight();
            m_pbRatioW = picWidth / 1.0 / boxWidth;
            m_pbRatioH = picHeight / 1.0 / boxHeight;
            double realStartX = m_pbRatioW * sp.X;
            double realStartY = m_pbRatioH * sp.Y;
            double realEndX = m_pbRatioW * ep.X;
            double realEndY = m_pbRatioH * ep.Y;
            double dx = realEndX - realStartX;
            double dy = realEndY - realStartY;
            double dist = Math.Sqrt(dx * dx + dy * dy);
            return dist;
        }

        private void SetLanguage()
        {
            LanguageControl.SetLanguage();
            this.Text = LanguageControl.STR_MAIN_FORM_NAME;
            this.文件ToolStripMenuItem.Text = LanguageControl.STR_MENU_FILE;
            this.分析ToolStripMenuItem.Text = LanguageControl.STR_MENU_ANALYZE;
            this.语言ToolStripMenuItem.Text = LanguageControl.STR_MENU_LANGUAGE;
            this.关于ToolStripMenuItem.Text = LanguageControl.STR_MENU_ABOUT;

            this.打开ToolStripMenuItem.Text = LanguageControl.STR_MENU_OPEN;
            this.另存为ToolStripMenuItem.Text = LanguageControl.STR_MENU_SAVE_AS;
            this.保存数据ToolStripMenuItem.Text = LanguageControl.STR_MENU_SAVE_DATA;
            this.打印ToolStripMenuItem.Text = LanguageControl.STR_MENU_PRINT_IMAGE;
            this.关闭ToolStripMenuItem.Text = LanguageControl.STR_MENU_CLOSE;
            this.退出ToolStripMenuItem.Text = LanguageControl.STR_MENU_EXIT;

            this.测量距离ToolStripMenuItem.Text = LanguageControl.STR_MENU_MEASURE_DISTANCE;
            this.测量面积ToolStripMenuItem.Text = LanguageControl.STR_MENU_MEASURE_AREA;
            this.标定ToolStripMenuItem.Text = LanguageControl.STR_MENU_CALIBRATE;

            this.toolStripButton_openFile.Text = LanguageControl.STR_MENU_OPEN;
            this.toolStripButton_saveAs.Text = LanguageControl.STR_MENU_SAVE_AS;
            this.toolStripButton_saveData.Text = LanguageControl.STR_MENU_SAVE_DATA;
            this.toolStripButton_closeFile.Text = LanguageControl.STR_MENU_CLOSE;
            this.toolStripButton_exit.Text = LanguageControl.STR_MENU_EXIT;

            this.toolStripButton_measureDistance.Text = LanguageControl.STR_MENU_MEASURE_DISTANCE;
            this.toolStripButton_measureAera.Text = LanguageControl.STR_MENU_MEASURE_AREA;
            this.toolStripButton_correct.Text = LanguageControl.STR_MENU_CALIBRATE;
        }

        private void MainForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            //if (MessageBox.Show("确定退出吗?", "提示", MessageBoxButtons.YesNo, MessageBoxIcon.Warning) == DialogResult.Yes)
            if (MessageBox.Show(LanguageControl.MSG_IF_EXIT, LanguageControl.MSG_NOTICE, MessageBoxButtons.YesNo,  MessageBoxIcon.Warning) == DialogResult.Yes)
            {
         
            }
            else
            {
                e.Cancel = true;
            }
        }

        private void toolStripButton_Click(object sender, EventArgs e)
        {
            ToolStripButton tsb = (ToolStripButton)sender;
            if (tsb.Text.Equals(LanguageControl.STR_MENU_OPEN))    //打开文件
                OpenNewImageFile();
            else if (tsb.Text.Equals(LanguageControl.STR_MENU_SAVE_AS))    //另存为
            {
                SaveFileDialog sfd = new SaveFileDialog();
                sfd.Filter = "位图|*.bmp";
                sfd.FileName = m_fileName;
                if (sfd.ShowDialog() == DialogResult.OK)
                {
                    SaveAsNewImage(sfd.FileName);
                    MessageBox.Show(LanguageControl.MSG_SAVE_SUCCESSFULLY);
                    CloseCurrentImageFile();
                }
            }
            else if (tsb.Text.Equals(LanguageControl.STR_MENU_SAVE_DATA))  //保存数据
            {
                SaveFileDialog sfd = new SaveFileDialog();
                sfd.Filter = "文本文件|*.txt";
                sfd.OverwritePrompt = false;
                if (sfd.ShowDialog() == DialogResult.OK)
                    SaveDataFile(sfd.FileName);
            }
            else if (tsb.Text.Equals(LanguageControl.STR_MENU_CLOSE)) //关闭
                CloseCurrentImageFile();
            else if (tsb.Text.Equals(LanguageControl.STR_MENU_EXIT))   //退出
                this.Close();
            else if (tsb.Text.Equals(LanguageControl.STR_MENU_MEASURE_DISTANCE))   //测量距离
            {
                this.测量距离ToolStripMenuItem.CheckState = CheckState.Checked;
                this.测量面积ToolStripMenuItem.CheckState = CheckState.Unchecked;
                m_bMeasureDistance = true;
                this.Refresh();
            }
            else if (tsb.Text.Equals(LanguageControl.STR_MENU_MEASURE_AREA))   //测量面积
            {
                this.测量距离ToolStripMenuItem.CheckState = CheckState.Unchecked;
                this.测量面积ToolStripMenuItem.CheckState = CheckState.Checked;
                m_bMeasureDistance = false;
                HistogramForm hf = new HistogramForm(this, mCalcuAera);
                hf.ShowDialog();
                this.Refresh();
            }
            else if (tsb.Text.Equals(LanguageControl.STR_MENU_CALIBRATE))    //标定
            {
                SetScaleForm ssf = new SetScaleForm(this);
                ssf.ShowDialog();
            }
        }

        private void SaveDataFile(string fileName)
        {
            try
            {
                using (StreamWriter writer = File.AppendText(fileName))
                {
                    double ratiOut = CalcuAeras.PIX_DIS_RATIO < 0 ? 1 : CalcuAeras.PIX_DIS_RATIO;
                    writer.WriteLine(m_fileName + ":\t" + ratiOut + "\t" + mCalcuAera.NGetAera());
                    writer.Close();
                }
                //MessageBox.Show("保存成功!");
                MessageBox.Show(LanguageControl.MSG_SAVE_SUCCESSFULLY);
            }
            catch (IOException)
            {
                //MessageBox.Show("保存文件失败!");
                MessageBox.Show(LanguageControl.MSG_SAVE_FILE_FAILED);
            }
        }

        public void CallCalcuAeras()
        {
            int highVal = CalcuAeras.HIST_HIGH_VALUE;
            int lowVal = CalcuAeras.HIST_LOW_VALUE;
            if (highVal < 0)
                return;
            if (CalcuAeras.PIX_DIS_RATIO < 0)
                mCalcuAera.NBinaryImage_2Threshold((float)1.0, "pixel", LanguageControl.PIC_AREA, lowVal, highVal);
            else
                mCalcuAera.NBinaryImage_2Threshold((float)(CalcuAeras.PIX_DIS_RATIO * CalcuAeras.PIX_DIS_RATIO), CalcuAeras.AERA_UNIT, LanguageControl.PIC_AREA, lowVal, highVal);
            ShowDstImage();
        }

    }
}

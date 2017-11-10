using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Threading;


namespace FlameAreaCalcu
{
    public partial class HistogramForm : Form
    {
        private Graphics mGraph = null;
        private Pen mPen = new Pen(Color.Green, 2);
        private MainForm mMainForm = null;
        private CalcuAeras mCal = null;
        private static bool mProcessing = false;

        public HistogramForm(MainForm mf, CalcuAeras cal)
        {
            mMainForm = mf;
            mCal = cal;
            InitializeComponent();
            this.mGraph = this.pictureBox_histogram.CreateGraphics();
            this.pictureBox_histogram.Image = mCal.mHistImg;
            SetLanguage();
        }

        private void HistogramForm_Load(object sender, EventArgs e)
        {
            if (CalcuAeras.HIST_LOW_VALUE > 0 && CalcuAeras.HIST_HIGH_VALUE > 0)
            {
                this.hScrollBar_low.ValueChanged -= new System.EventHandler(this.hScrollBar_ValueChanged);
                this.hScrollBar_low.Value = CalcuAeras.HIST_LOW_VALUE;
                this.hScrollBar_low.ValueChanged += new System.EventHandler(this.hScrollBar_ValueChanged);
                this.hScrollBar_high.Value = CalcuAeras.HIST_HIGH_VALUE;
            }
        }

        private void hScrollBar_ValueChanged(object sender, EventArgs e)
        {
            if (mProcessing)
                return;
            mProcessing = true;
            int width = this.pictureBox_histogram.Width;
            int height = this.pictureBox_histogram.Height;
            if (this.hScrollBar_high.Value <= this.hScrollBar_low.Value)
                this.hScrollBar_high.Value = this.hScrollBar_low.Value + 1;
            int low_pos = width * this.hScrollBar_low.Value / this.hScrollBar_low.Maximum;
            int high_pos = width * this.hScrollBar_high.Value / this.hScrollBar_high.Maximum;
            this.Refresh();
            mPen.Color = Color.GreenYellow;
            mGraph.DrawLine(mPen, new Point(low_pos, 0), new Point(low_pos, height));
            mGraph.DrawString(this.hScrollBar_low.Value.ToString(), new Font("宋体", 10f), Brushes.Yellow, new Point((low_pos>15?low_pos-15:low_pos), height/3));
            mPen.Color = Color.Red;
            mGraph.DrawLine(mPen, new Point(high_pos, 0), new Point(high_pos, height));
            mGraph.DrawString(this.hScrollBar_high.Value.ToString(), new Font("宋体", 10f), Brushes.Yellow, new Point((high_pos>10?high_pos-10:high_pos), height/5));
            //MessageBox.Show(low_pos + " " + high_pos);
            if (CalcuAeras.PIX_DIS_RATIO < 0)
                mCal.NBinaryImage_2Threshold((float)1.0, "pixel", LanguageControl.PIC_AREA, this.hScrollBar_low.Value, this.hScrollBar_high.Value);
            else
                mCal.NBinaryImage_2Threshold((float)(CalcuAeras.PIX_DIS_RATIO * CalcuAeras.PIX_DIS_RATIO), CalcuAeras.AERA_UNIT, LanguageControl.PIC_AREA, this.hScrollBar_low.Value, this.hScrollBar_high.Value);
            mMainForm.ShowDstImage();
            CalcuAeras.HIST_LOW_VALUE = this.hScrollBar_low.Value;
            CalcuAeras.HIST_HIGH_VALUE = this.hScrollBar_high.Value;
            mProcessing = false;
        }

        private void SetLanguage()
        {
            LanguageControl.SetLanguage();
            this.Text = LanguageControl.STR_HISOGRAM_FORM_NAME;
        }

    }
}

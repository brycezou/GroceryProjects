using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Imaging;
using System.Linq;
using System.Text;
using System.Windows.Forms;
//using Emgu.CV;
//using Emgu.CV.Structure;
//using Emgu.Util;


namespace MakeColorImage
{
    public partial class MainForm : Form
    {
        private DataGridViewCell m_Cell = null;

        public MainForm()
        {
            InitializeComponent();
        }

        private void MainForm_Load(object sender, EventArgs e)
        {
            this.textBox.Text = "255,0,0";
            this.dataGridView.ColumnCount = 90;
            this.dataGridView.RowCount = 72;
            for (int i = 0; i < 90; i++ )
            {
                this.dataGridView.Columns[i].HeaderText = Convert.ToString(i+1);
            }
            for (int i = 0; i < 72; i++)
            {
                this.dataGridView.Rows[i].HeaderCell.Value = Convert.ToString(i + 1);
            }

            dataGridView.MultiSelect = true;
            dataGridView.CellValueChanged += new DataGridViewCellEventHandler(Zc_CellValueChanged);
        }

        private void button_SetZero_Click(object sender, EventArgs e)
        {
            string strRgb = this.textBox.Text.ToString().Trim();
            if (strRgb.Equals(""))
            {
                MessageBox.Show("请输入正确的RGB值!  格式如: 255,0,128");
                return;
            }
            else
            {
                for (int row = 0; row < dataGridView.Rows.Count; row++)
                {
                    for (int col = 0; col < dataGridView.ColumnCount; col++)
                    {
                        this.dataGridView.Rows[row].Cells[col].Value = strRgb;
                    }
                }
            }
        }

        private void button_CreateImage_Click(object sender, EventArgs e)
        {
            //CreateColorImage_Emgu();
            CreateColorImage_NoEmgu();
        }

        private void CreateColorImage_Emgu()
        {
            //Image<Bgr, byte> srcImg = new Image<Bgr, byte>(90, 72);
            //string[] sArray = null;
            //for (int row = 0; row < 72; row++)
            //{
            //    for (int col = 0; col < 90; col++)
            //    {
            //        try
            //        {
            //            sArray = dataGridView.Rows[row].Cells[col].Value.ToString().Split(new char[] { ',' });
            //            if (sArray.Length != 3 || sArray[0].Equals("") || sArray[1].Equals("") || sArray[2].Equals(""))
            //            {
            //                srcImg.Dispose();
            //                sArray = null;
            //                srcImg = null;
            //                string strOut = String.Format("({0}, {1})处的数据格式不正确! 格式如: 255,0,128", row + 1, col + 1);
            //                MessageBox.Show(strOut);
            //                return;
            //            }
            //        }
            //        catch (System.Exception ex)
            //        {
            //            srcImg.Dispose();
            //            sArray = null;
            //            srcImg = null;
            //            string strOut = String.Format("({0}, {1})处的数据格式不正确! 格式如: 255,0,128", row + 1, col + 1);
            //            MessageBox.Show(strOut);
            //            return;
            //        }

            //        Bgr pColor = new Bgr(Convert.ToInt32(sArray[2]), Convert.ToInt32(sArray[1]), Convert.ToInt32(sArray[0]));
            //        srcImg[row, col] = pColor;
            //    }
            //}

            //srcImg.Save("saved.jpg");
            //srcImg.Dispose();
            //sArray = null;
            //srcImg = null;
            //MessageBox.Show("已生成图像 saved.jpg");
        }

        private void CreateColorImage_NoEmgu()
        {
            Bitmap srcImg = new Bitmap(90, 72, PixelFormat.Format24bppRgb);
            string[] sArray = null;
            for (int row = 0; row < 72; row++)
            {
                for (int col = 0; col < 90; col++)
                {
                    try
                    {
                        sArray = dataGridView.Rows[row].Cells[col].Value.ToString().Split(new char[] { ',' });
                        if (sArray.Length != 3 || sArray[0].Equals("") || sArray[1].Equals("") || sArray[2].Equals(""))
                        {
                            srcImg.Dispose();
                            sArray = null;
                            srcImg = null;
                            string strOut = String.Format("({0}, {1})处的数据格式不正确! 格式如: 255,0,128", row + 1, col + 1);
                            MessageBox.Show(strOut);
                            return;
                        }
                    }
                    catch (System.Exception ex)
                    {
                        srcImg.Dispose();
                        sArray = null;
                        srcImg = null;
                        string strOut = String.Format("({0}, {1})处的数据格式不正确! 格式如: 255,0,128", row + 1, col + 1);
                        MessageBox.Show(strOut);
                        return;
                    }
                    srcImg.SetPixel(col, row, Color.FromArgb(Convert.ToInt32(sArray[0]), Convert.ToInt32(sArray[1]), Convert.ToInt32(sArray[2])));
                }
            }

            srcImg.Save("saved.bmp", ImageFormat.Bmp);
            srcImg.Dispose();
            sArray = null;
            srcImg = null;
            MessageBox.Show("已生成图像 saved.bmp");
        }

        void Zc_CellValueChanged(object sender, DataGridViewCellEventArgs e)
        {
            var cell = this.dataGridView[e.ColumnIndex, e.RowIndex];

            foreach (DataGridViewCell item in dataGridView.SelectedCells)
            {
                if (!(cell.ColumnIndex == item.ColumnIndex || cell.RowIndex == item.RowIndex))
                    continue;

                item.Value = cell.Value;
            }
        }

        private void MainForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            DialogResult response = MessageBox.Show("表格中的数据将丢失!       \n您确定要退出吗?", "警告", 
                                                                                MessageBoxButtons.YesNo, MessageBoxIcon.Question, MessageBoxDefaultButton.Button2);
            if (response == System.Windows.Forms.DialogResult.No)
            {
                e.Cancel = true;
            }
        }

        private void button_OpenExistImage_Click(object sender, EventArgs e)
        {
            if (openFileDialog.ShowDialog() == DialogResult.OK)
            {
                string fielName = openFileDialog.FileName;
                Bitmap srcImg = new Bitmap(fielName);
                if (srcImg.Width == 90 && srcImg.Height == 72 && srcImg.PixelFormat == PixelFormat.Format24bppRgb)
                {
                    for (int row = 0; row < 72; row++)
                    {
                        for (int col = 0; col < 90; col++)
                        {
                            Color pColor = srcImg.GetPixel(col, row);
                            dataGridView.Rows[row].Cells[col].Value = String.Format("{0},{1},{2}", pColor.R, pColor.G, pColor.B);
                        }
                    }
                }
                else
                {
                    MessageBox.Show("图像文件格式不正确! \n正确格式为: 90x72像素, RGB三通道");
                }
            }
        }

        private void dataGridView_CellClick(object sender, DataGridViewCellEventArgs e)
        {
            var cell = this.dataGridView[e.ColumnIndex, e.RowIndex];
            try
            {
                this.textBox_realPixel.Text = cell.Value.ToString().Trim();
                m_Cell = cell;
            }
            catch (System.Exception)
            {
            	
            }
        }

        private void button_calcuDelta_Click(object sender, EventArgs e)
        {
            string strTemp = this.textBox_measuredPixel.Text.ToString().Trim();
            string[] sArray = strTemp.Split(new char[] { ',' });
            if (sArray.Length != 3 || sArray[0].Equals("") || sArray[1].Equals("") || sArray[2].Equals(""))
            {
                sArray = null;
                string strOut = String.Format("仪器测量值 数据格式不正确! 格式如: 255,0,128");
                MessageBox.Show(strOut);
                return;
            }
            strTemp = this.textBox_realPixel.Text.ToString().Trim();
            string[] sArray2 = strTemp.Split(new char[] { ',' });
             if (sArray2.Length != 3 || sArray2[0].Equals("") || sArray2[1].Equals("") || sArray2[2].Equals(""))
            {
                sArray2 = null;
                string strOut = String.Format("实际像素值  数据格式不正确! 格式如: 255,0,128");
                MessageBox.Show(strOut);
                return;
            }
            int deltaR = Convert.ToInt32(sArray2[0]) - Convert.ToInt32(sArray[0]);
            int deltaG = Convert.ToInt32(sArray2[1]) - Convert.ToInt32(sArray[1]);
            int deltaB = Convert.ToInt32(sArray2[2]) - Convert.ToInt32(sArray[2]);
            deltaR = deltaR > 255 ? 255 : deltaR;
            deltaG = deltaG > 255 ? 255 : deltaG;
            deltaB = deltaB > 255 ? 255 : deltaB;
            this.textBox_deltaPixel.Text = String.Format("{0},{1},{2}", deltaR, deltaG, deltaB);
        }

        private void button_changeCurrPixel_Click(object sender, EventArgs e)
        {
            string strTemp = this.textBox_realPixel.Text.ToString().Trim();
            //string strTemp = this.m_Cell.Value.ToString().Trim();
            string[] sArray1 = strTemp.Split(new char[] { ',' });
            strTemp = this.textBox_deltaPixel.Text.ToString().Trim();
            string[] sArray2 = strTemp.Split(new char[] { ',' });
            int dstR = Convert.ToInt32(sArray1[0]) - Convert.ToInt32(sArray2[0]);
            int dstG = Convert.ToInt32(sArray1[1]) - Convert.ToInt32(sArray2[1]);
            int dstB = Convert.ToInt32(sArray1[2]) - Convert.ToInt32(sArray2[2]);
            dstR = dstR > 255 ? 255 : dstR;
            dstG = dstG > 255 ? 255 : dstG;
            dstB = dstB > 255 ? 255 : dstB;
            dstR = dstR < 0 ? 0 : dstR;
            dstG = dstG < 0 ? 0 : dstG;
            dstB = dstB < 0 ? 0 : dstB;
            this.m_Cell.Value = String.Format("{0},{1},{2}", dstR, dstG, dstB);
        }

        private void button_changeAllPixel_Click(object sender, EventArgs e)
        {
            string strTemp = this.textBox_deltaPixel.Text.ToString().Trim();
            string[] sArray = strTemp.Split(new char[] { ',' });
            int deltaR = Convert.ToInt32(sArray[0]);
            int deltaG = Convert.ToInt32(sArray[1]);
            int deltaB = Convert.ToInt32(sArray[2]);
            for (int row = 0; row < dataGridView.Rows.Count; row++)
            {
                for (int col = 0; col < dataGridView.ColumnCount; col++)
                {
                    strTemp = this.dataGridView.Rows[row].Cells[col].Value.ToString().Trim();
                    sArray = strTemp.Split(new char[] { ',' });
                    int dstR = Convert.ToInt32(sArray[0]) - deltaR;
                    int dstG = Convert.ToInt32(sArray[1]) - deltaG;
                    int dstB = Convert.ToInt32(sArray[2]) - deltaB;
                    dstR = dstR > 255 ? 255 : dstR;
                    dstG = dstG > 255 ? 255 : dstG;
                    dstB = dstB > 255 ? 255 : dstB;
                    dstR = dstR < 0 ? 0 : dstR;
                    dstG = dstG < 0 ? 0 : dstG;
                    dstB = dstB < 0 ? 0 : dstB;
                    this.dataGridView.Rows[row].Cells[col].Value = String.Format("{0},{1},{2}", dstR, dstG, dstB);
                }
            }
        }
    }
}

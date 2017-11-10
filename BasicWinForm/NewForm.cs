using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;
using System.Drawing.Drawing2D;

namespace BasicWinForm
{
    public partial class NewForm : Form
    {
        public NewForm()
        {
            InitializeComponent();
            InitializeTreeView();
        }

        private void NewForm_Load(object sender, EventArgs e)
        {
            this.listBox.Items.Add("ListBox");
            this.listBox.Items.Add("Test !");

            this.comboBox.Items.Add("ComboBox");
            this.comboBox.Items.Add("Test !");
        }

        private void btnOKList_Click(object sender, EventArgs e)
        {
            if (this.listBox.SelectedIndex != -1)
            {
                MessageBox.Show("您当前选择的是：" + this.listBox.SelectedItem.ToString());
            }
            else
            {
                MessageBox.Show("请选中一项！");
            }
        }

        private void comboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            MessageBox.Show("您当前选择的是："+this.comboBox.SelectedItem.ToString());
        }

        private void checkBox_LiHua_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBox_LiHua.Checked && !listBox.Items.Contains(checkBox_LiHua.Text))
            {
                listBox.Items.Add(checkBox_LiHua.Text);
            }
            else
            {
                listBox.Items.Remove(checkBox_LiHua.Text);
            }
        }

        private void checkBox_LiuYu_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBox_LiuYu.Checked && !listBox.Items.Contains(checkBox_LiuYu.Text))
            {
                listBox.Items.Add(checkBox_LiuYu.Text);
            }
            else
            {
                listBox.Items.Remove(checkBox_LiuYu.Text);
            }
        }

        private void checkBox_LiHua_Click(object sender, EventArgs e)
        {
            checkBox_All.ThreeState = true;
            SetListBox_AllCheckState();
        }

        private void checkBox_LiuYu_Click(object sender, EventArgs e)
        {
            checkBox_All.ThreeState = true;
            SetListBox_AllCheckState();
        }

        private void checkBox_All_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBox_All.CheckState == CheckState.Checked)
            {
                checkBox_LiHua.Checked = true;
                checkBox_LiuYu.Checked = true;
            }
            else if (checkBox_All.CheckState == CheckState.Unchecked)
            {
                checkBox_LiHua.Checked = false;
                checkBox_LiuYu.Checked = false;
            }
        }

        private void SetListBox_AllCheckState()
        {
            if (checkBox_LiHua.Checked && checkBox_LiuYu.Checked)
            {
                checkBox_All.ThreeState = false;
                checkBox_All.CheckState = CheckState.Checked;
            }
            else if (!checkBox_LiHua.Checked && !checkBox_LiuYu.Checked)
            {
                checkBox_All.ThreeState = false;
                checkBox_All.CheckState = CheckState.Unchecked;
            }
            else
            {
                checkBox_All.CheckState = CheckState.Indeterminate;
            }
        }

        private void radioButton_CheckedChanged(object sender, EventArgs e) //在NewForm.Designer.cs中手动修改映射关系就好了！
        {
            RadioButton rb = (RadioButton)sender;
            textBox.Text = rb.Text;
        }

        private void treeView_AfterSelect(object sender, TreeViewEventArgs e)
        {
            TreeNode tn = treeView.SelectedNode;
            if (tn.Name != "0")
                MessageBox.Show("你选择了:" + tn.Parent.Text + "的" + tn.Text+"!");
        }

        private void InitializeTreeView()
        {
            TreeNode tn = new TreeNode("学校");
            tn.Name = "0";
            treeView.Nodes.Add(tn);
            tn = new TreeNode("家庭");
            tn.Name = "0";
            treeView.Nodes.Add(tn);
            tn = new TreeNode("同学");
            treeView.Nodes[0].Nodes.Add(tn);
            tn = new TreeNode("老师");
            treeView.Nodes[0].Nodes.Add(tn);
            tn = new TreeNode("爸妈");
            treeView.Nodes[1].Nodes.Add(tn);
        }

        private void btnSelectColor_Click(object sender, EventArgs e)
        {
            if (colorDialog.ShowDialog() == DialogResult.OK)
            {
                btnSelectColor.BackColor = colorDialog.Color;
            }
        }

        private void btnSelectFont_Click(object sender, EventArgs e)
        {
            if (fontDialog.ShowDialog() != DialogResult.Cancel)
            {
                textBox.Font = fontDialog.Font;
                textBox.ForeColor = fontDialog.Color;
            }
        }

        private void btnOpenFile_Click(object sender, EventArgs e)
        {
            if (openFileDialog.ShowDialog() == DialogResult.OK)
            {
                string[] fielNames = openFileDialog.FileNames;
                string strOut = "您选择的文件有:\n\n";
                foreach (string filename in fielNames)
                {
                    strOut = strOut + filename + '\n';
                }
                MessageBox.Show(strOut);
            }
        }

        private void btnSaveFile_Click(object sender, EventArgs e)
        {
            Stream myStream;
            if (saveFileDialog.ShowDialog() == DialogResult.OK)
            {
                if ((myStream = saveFileDialog.OpenFile()) != null)
                {
                    myStream.Close();
                }
            }
        }

        private void 同学ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            MessageBox.Show("您选择了快捷键中的\"学校—>同学\"\n创建菜单后在相关的Designer.cs文件中与窗体关联!!");
        }

        private void 附件ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            MessageBox.Show("您选择了快捷键中的\"开始—>程序—>附件\" !");
        }

        private void btnDrawTriangle_Click(object sender, EventArgs e)
        {
            Graphics g = this.CreateGraphics();
            PointF[] points = new PointF[]
           {
                new Point(300,30),
                new Point(450,50),
                new Point(400,280),
                new Point(300,30),
           };
            byte[] lines = new byte[]
            {
                (byte)PathPointType.Line,
                (byte)PathPointType.Line,
                (byte)PathPointType.Line,
                (byte)PathPointType.Line,
            };
            GraphicsPath path = new GraphicsPath(points, lines);
            Pen pen = new Pen(Color.Red);
            g.DrawPath(pen, path);
        }

        private void btnDrawEllipse_Click(object sender, EventArgs e)
        {
            Graphics g = this.CreateGraphics();
            Pen greenPen = new Pen(Color.Green, 3);
            g.DrawEllipse(greenPen, 300, 30, 100, 200);
        }

        private void btnCreateRegion_Click(object sender, EventArgs e)
        {
            Graphics g = this.CreateGraphics();
            GraphicsPath path = new GraphicsPath();
            path.AddEllipse(300, 30, 150, 150);
            Region region = new Region(path);
            SolidBrush brush = new SolidBrush(Color.Yellow);
            g.FillRegion(brush, region);
        }

        private void btnChangeBrush_Click(object sender, EventArgs e)
        {
            Graphics g = this.CreateGraphics();
            Rectangle rect = new Rectangle(350, 40, 100, 200);
            GraphicsPath path = new GraphicsPath();
            path.AddEllipse(rect);
            PathGradientBrush pgBrush = new PathGradientBrush(path);
            pgBrush.CenterColor = Color.White;
            pgBrush.SurroundColors = new Color[] { Color.Pink };
            g.FillEllipse(pgBrush, rect);
        }

        private void btnTextureFill_Click(object sender, EventArgs e)
        {
            Graphics g = this.CreateGraphics();
            Bitmap image = new Bitmap("Texture.png");
            TextureBrush brush = new TextureBrush(image);
            RectangleF rect = new RectangleF(300, 50, 150, 150);
            g.FillEllipse(brush, rect);
        }

        private void btnLinearChange_Click(object sender, EventArgs e)
        {
            Graphics g = this.CreateGraphics();
            Rectangle rect1 = new Rectangle(20, 0, 10, 10);
            LinearGradientBrush brush = new LinearGradientBrush(rect1, Color.White, Color.Red, LinearGradientMode.ForwardDiagonal);
            RectangleF rect2 = new RectangleF(300, 30, 100, 200);
            g.FillEllipse(brush, rect2);
        }

        private void btnShadowBrush_Click(object sender, EventArgs e)
        {
            Graphics g = this.CreateGraphics();
            HatchBrush brush = new HatchBrush(HatchStyle.Horizontal, Color.Black, Color.White);
            RectangleF rect = new RectangleF(350, 30, 120, 230);
            g.FillEllipse(brush, rect);
        }
    }
}

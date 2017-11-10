using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace BasicWinForm
{
    public partial class MainForm : Form
    {
        public MainForm()
        {
            InitializeComponent();
        }

        private void btnShowNewDlg_Click(object sender, EventArgs e)
        {
            NewForm nf = new NewForm();
            //this.Hide();
            nf.Show();

            progressBar.Visible = true;
            progressBar.Minimum = 0;
            progressBar.Maximum = 50000;
            for (int i = 0; i < 50000; i++)
            {
                progressBar.Value = i;
            }
        }

        private void MainForm_Load(object sender, EventArgs e)
        {
            this.Controls.Add(dataGridView);
            dataGridView.ColumnCount = 4;
            DataGridViewCellStyle style = dataGridView.ColumnHeadersDefaultCellStyle;
            style.BackColor = Color.Navy;
            style.ForeColor = Color.White;
            style.Font = new Font(dataGridView.Font, FontStyle.Bold);
            dataGridView.EditMode = DataGridViewEditMode.EditOnEnter;
            dataGridView.Name = "dataGridView";
            dataGridView.Location = new Point(15, 15);
            dataGridView.Size = new Size(450, 200);
            dataGridView.AutoSizeRowsMode = DataGridViewAutoSizeRowsMode.DisplayedCellsExceptHeaders;
            dataGridView.ColumnHeadersBorderStyle = DataGridViewHeaderBorderStyle.Raised;
            dataGridView.CellBorderStyle = DataGridViewCellBorderStyle.Single;
            dataGridView.GridColor = SystemColors.ActiveBorder;
            dataGridView.RowHeadersVisible = false;
            dataGridView.Columns[0].Name = "学号";
            dataGridView.Columns[1].Name = "姓名";
            dataGridView.Columns[2].Name = "性别";
            dataGridView.Columns[3].Name = "成绩";
            //把第四列文字为斜体
            dataGridView.Columns[3].DefaultCellStyle.Font = new Font(DataGridView.DefaultFont, FontStyle.Italic);
            dataGridView.SelectionMode = DataGridViewSelectionMode.FullRowSelect;
            dataGridView.MultiSelect = false;
            dataGridView.BackgroundColor = Color.Honeydew;
            dataGridView.Dock = DockStyle.Fill;

            number = 0;            
        }

        private void hScrollBar_Scroll(object sender, ScrollEventArgs e)
        {
            label.ForeColor = Color.FromArgb(255, hScrollBar.Value, 0, 0);
        }

        private void btnInsertRow_Click(object sender, EventArgs e)
        {
            DataGridViewRowCollection rows = this.dataGridView.Rows;
            switch (number)
            {
                case 0: rows.Add(row0); number++; break;
                case 1: rows.Add(row1); number++; break;
                case 2: rows.Add(row2); number++; break;
                default: break;
            }
        }

        private void btnDeleteRow_Click(object sender, EventArgs e)
        {
            DataGridViewRowCollection rows = this.dataGridView.Rows;
            number--;
            if(number>=0)
                rows.Remove(this.dataGridView.Rows[number]);      
        }

        private void btnChangeAppearance_Click(object sender, EventArgs e)
        {
            DataGridViewCellStyle style = new DataGridViewCellStyle();
            style.BackColor = Color.Beige;
            style.ForeColor = Color.Brown;
            style.Font = new Font("Verdana", 8);
            dataGridView.AlternatingRowsDefaultCellStyle = style;
            btnChangeAppearance.Enabled = false;
        }
    }
}

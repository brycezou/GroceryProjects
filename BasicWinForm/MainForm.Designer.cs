namespace BasicWinForm
{
    partial class MainForm
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.btnShowNewDlg = new System.Windows.Forms.Button();
            this.progressBar = new System.Windows.Forms.ProgressBar();
            this.hScrollBar = new System.Windows.Forms.HScrollBar();
            this.label = new System.Windows.Forms.Label();
            this.dataGridView = new System.Windows.Forms.DataGridView();
            this.btnInsertRow = new System.Windows.Forms.Button();
            this.btnDeleteRow = new System.Windows.Forms.Button();
            this.btnChangeAppearance = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView)).BeginInit();
            this.SuspendLayout();
            // 
            // btnShowNewDlg
            // 
            this.btnShowNewDlg.Location = new System.Drawing.Point(1, 81);
            this.btnShowNewDlg.Name = "btnShowNewDlg";
            this.btnShowNewDlg.Size = new System.Drawing.Size(149, 23);
            this.btnShowNewDlg.TabIndex = 0;
            this.btnShowNewDlg.Text = "显示新对话框";
            this.btnShowNewDlg.UseVisualStyleBackColor = true;
            this.btnShowNewDlg.Click += new System.EventHandler(this.btnShowNewDlg_Click);
            // 
            // progressBar
            // 
            this.progressBar.Location = new System.Drawing.Point(1, 155);
            this.progressBar.Name = "progressBar";
            this.progressBar.Size = new System.Drawing.Size(230, 23);
            this.progressBar.TabIndex = 1;
            // 
            // hScrollBar
            // 
            this.hScrollBar.Location = new System.Drawing.Point(1, 107);
            this.hScrollBar.Maximum = 255;
            this.hScrollBar.Name = "hScrollBar";
            this.hScrollBar.Size = new System.Drawing.Size(149, 23);
            this.hScrollBar.TabIndex = 2;
            this.hScrollBar.Scroll += new System.Windows.Forms.ScrollEventHandler(this.hScrollBar_Scroll);
            // 
            // label
            // 
            this.label.AutoSize = true;
            this.label.Font = new System.Drawing.Font("隶书", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label.Location = new System.Drawing.Point(1, 133);
            this.label.Name = "label";
            this.label.Size = new System.Drawing.Size(149, 19);
            this.label.TabIndex = 3;
            this.label.Text = "滚动条效果显示";
            // 
            // dataGridView
            // 
            this.dataGridView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridView.Location = new System.Drawing.Point(1, 1);
            this.dataGridView.Name = "dataGridView";
            this.dataGridView.RowTemplate.Height = 23;
            this.dataGridView.Size = new System.Drawing.Size(230, 30);
            this.dataGridView.TabIndex = 4;
            // 
            // btnInsertRow
            // 
            this.btnInsertRow.Location = new System.Drawing.Point(156, 81);
            this.btnInsertRow.Name = "btnInsertRow";
            this.btnInsertRow.Size = new System.Drawing.Size(75, 23);
            this.btnInsertRow.TabIndex = 5;
            this.btnInsertRow.Text = "插入行";
            this.btnInsertRow.UseVisualStyleBackColor = true;
            this.btnInsertRow.Click += new System.EventHandler(this.btnInsertRow_Click);
            // 
            // btnDeleteRow
            // 
            this.btnDeleteRow.Location = new System.Drawing.Point(156, 104);
            this.btnDeleteRow.Name = "btnDeleteRow";
            this.btnDeleteRow.Size = new System.Drawing.Size(75, 23);
            this.btnDeleteRow.TabIndex = 6;
            this.btnDeleteRow.Text = "删除行";
            this.btnDeleteRow.UseVisualStyleBackColor = true;
            this.btnDeleteRow.Click += new System.EventHandler(this.btnDeleteRow_Click);
            // 
            // btnChangeAppearance
            // 
            this.btnChangeAppearance.Location = new System.Drawing.Point(156, 127);
            this.btnChangeAppearance.Name = "btnChangeAppearance";
            this.btnChangeAppearance.Size = new System.Drawing.Size(75, 23);
            this.btnChangeAppearance.TabIndex = 7;
            this.btnChangeAppearance.Text = "改变外观";
            this.btnChangeAppearance.UseVisualStyleBackColor = true;
            this.btnChangeAppearance.Click += new System.EventHandler(this.btnChangeAppearance_Click);
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(522, 348);
            this.Controls.Add(this.btnChangeAppearance);
            this.Controls.Add(this.btnDeleteRow);
            this.Controls.Add(this.btnInsertRow);
            this.Controls.Add(this.dataGridView);
            this.Controls.Add(this.label);
            this.Controls.Add(this.hScrollBar);
            this.Controls.Add(this.progressBar);
            this.Controls.Add(this.btnShowNewDlg);
            this.Name = "MainForm";
            this.Text = "MainForm";
            this.Load += new System.EventHandler(this.MainForm_Load);
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btnShowNewDlg;
        private System.Windows.Forms.ProgressBar progressBar;
        private System.Windows.Forms.HScrollBar hScrollBar;
        private System.Windows.Forms.Label label;
        private System.Windows.Forms.DataGridView dataGridView;

        private string[] row0 = { "0910200124", "放细化", "女", "90" };
        private string[] row1 = { "0910200130", "李荣庆", "女", "91" };
        private string[] row2 = { "0910200132", "刘杨阳", "女", "92" };
        private int number;
        private System.Windows.Forms.Button btnInsertRow;
        private System.Windows.Forms.Button btnDeleteRow;
        private System.Windows.Forms.Button btnChangeAppearance;
    }
}


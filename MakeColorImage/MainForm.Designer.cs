namespace MakeColorImage
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
            this.dataGridView = new System.Windows.Forms.DataGridView();
            this.button_SetZero = new System.Windows.Forms.Button();
            this.button_CreateImage = new System.Windows.Forms.Button();
            this.textBox = new System.Windows.Forms.TextBox();
            this.button_OpenExistImage = new System.Windows.Forms.Button();
            this.openFileDialog = new System.Windows.Forms.OpenFileDialog();
            this.textBox_realPixel = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.textBox_measuredPixel = new System.Windows.Forms.TextBox();
            this.textBox_deltaPixel = new System.Windows.Forms.TextBox();
            this.button_changeCurrPixel = new System.Windows.Forms.Button();
            this.button_changeAllPixel = new System.Windows.Forms.Button();
            this.button_calcuDelta = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView)).BeginInit();
            this.SuspendLayout();
            // 
            // dataGridView
            // 
            this.dataGridView.AllowUserToAddRows = false;
            this.dataGridView.AllowUserToDeleteRows = false;
            this.dataGridView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridView.Location = new System.Drawing.Point(0, -4);
            this.dataGridView.Margin = new System.Windows.Forms.Padding(4);
            this.dataGridView.Name = "dataGridView";
            this.dataGridView.RowHeadersWidth = 60;
            this.dataGridView.RowTemplate.Height = 23;
            this.dataGridView.Size = new System.Drawing.Size(1061, 459);
            this.dataGridView.TabIndex = 0;
            this.dataGridView.CellClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.dataGridView_CellClick);
            // 
            // button_SetZero
            // 
            this.button_SetZero.Location = new System.Drawing.Point(224, 462);
            this.button_SetZero.Margin = new System.Windows.Forms.Padding(4);
            this.button_SetZero.Name = "button_SetZero";
            this.button_SetZero.Size = new System.Drawing.Size(208, 29);
            this.button_SetZero.TabIndex = 1;
            this.button_SetZero.Text = "全部设置为:";
            this.button_SetZero.UseVisualStyleBackColor = true;
            this.button_SetZero.Click += new System.EventHandler(this.button_SetZero_Click);
            // 
            // button_CreateImage
            // 
            this.button_CreateImage.Location = new System.Drawing.Point(640, 462);
            this.button_CreateImage.Margin = new System.Windows.Forms.Padding(4);
            this.button_CreateImage.Name = "button_CreateImage";
            this.button_CreateImage.Size = new System.Drawing.Size(412, 29);
            this.button_CreateImage.TabIndex = 2;
            this.button_CreateImage.Text = "生 成 图 像";
            this.button_CreateImage.UseVisualStyleBackColor = true;
            this.button_CreateImage.Click += new System.EventHandler(this.button_CreateImage_Click);
            // 
            // textBox
            // 
            this.textBox.Location = new System.Drawing.Point(448, 464);
            this.textBox.Margin = new System.Windows.Forms.Padding(4);
            this.textBox.Name = "textBox";
            this.textBox.Size = new System.Drawing.Size(171, 25);
            this.textBox.TabIndex = 3;
            // 
            // button_OpenExistImage
            // 
            this.button_OpenExistImage.Location = new System.Drawing.Point(3, 461);
            this.button_OpenExistImage.Margin = new System.Windows.Forms.Padding(4);
            this.button_OpenExistImage.Name = "button_OpenExistImage";
            this.button_OpenExistImage.Size = new System.Drawing.Size(208, 29);
            this.button_OpenExistImage.TabIndex = 4;
            this.button_OpenExistImage.Text = "打开图像";
            this.button_OpenExistImage.UseVisualStyleBackColor = true;
            this.button_OpenExistImage.Click += new System.EventHandler(this.button_OpenExistImage_Click);
            // 
            // openFileDialog
            // 
            this.openFileDialog.FileName = "saved.jpg";
            this.openFileDialog.Filter = "JPG图像|*.jpg|BMP图像|*.bmp";
            this.openFileDialog.InitialDirectory = "..\\";
            // 
            // textBox_realPixel
            // 
            this.textBox_realPixel.Enabled = false;
            this.textBox_realPixel.Location = new System.Drawing.Point(98, 505);
            this.textBox_realPixel.Name = "textBox_realPixel";
            this.textBox_realPixel.ReadOnly = true;
            this.textBox_realPixel.Size = new System.Drawing.Size(113, 25);
            this.textBox_realPixel.TabIndex = 5;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(1, 510);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(97, 15);
            this.label1.TabIndex = 6;
            this.label1.Text = "实际像素值：";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(222, 510);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(97, 15);
            this.label2.TabIndex = 8;
            this.label2.Text = "仪器测量值：";
            // 
            // textBox_measuredPixel
            // 
            this.textBox_measuredPixel.Location = new System.Drawing.Point(318, 505);
            this.textBox_measuredPixel.Name = "textBox_measuredPixel";
            this.textBox_measuredPixel.Size = new System.Drawing.Size(113, 25);
            this.textBox_measuredPixel.TabIndex = 7;
            // 
            // textBox_deltaPixel
            // 
            this.textBox_deltaPixel.Enabled = false;
            this.textBox_deltaPixel.Location = new System.Drawing.Point(506, 505);
            this.textBox_deltaPixel.Name = "textBox_deltaPixel";
            this.textBox_deltaPixel.ReadOnly = true;
            this.textBox_deltaPixel.Size = new System.Drawing.Size(113, 25);
            this.textBox_deltaPixel.TabIndex = 9;
            // 
            // button_changeCurrPixel
            // 
            this.button_changeCurrPixel.Location = new System.Drawing.Point(640, 503);
            this.button_changeCurrPixel.Name = "button_changeCurrPixel";
            this.button_changeCurrPixel.Size = new System.Drawing.Size(194, 29);
            this.button_changeCurrPixel.TabIndex = 11;
            this.button_changeCurrPixel.Text = "根据差值仅改变当前像素值";
            this.button_changeCurrPixel.UseVisualStyleBackColor = true;
            this.button_changeCurrPixel.Click += new System.EventHandler(this.button_changeCurrPixel_Click);
            // 
            // button_changeAllPixel
            // 
            this.button_changeAllPixel.Location = new System.Drawing.Point(840, 503);
            this.button_changeAllPixel.Name = "button_changeAllPixel";
            this.button_changeAllPixel.Size = new System.Drawing.Size(212, 29);
            this.button_changeAllPixel.TabIndex = 12;
            this.button_changeAllPixel.Text = "根据差值改变所有像素值";
            this.button_changeAllPixel.UseVisualStyleBackColor = true;
            this.button_changeAllPixel.Click += new System.EventHandler(this.button_changeAllPixel_Click);
            // 
            // button_calcuDelta
            // 
            this.button_calcuDelta.Location = new System.Drawing.Point(448, 503);
            this.button_calcuDelta.Name = "button_calcuDelta";
            this.button_calcuDelta.Size = new System.Drawing.Size(52, 29);
            this.button_calcuDelta.TabIndex = 13;
            this.button_calcuDelta.Text = "差值";
            this.button_calcuDelta.UseVisualStyleBackColor = true;
            this.button_calcuDelta.Click += new System.EventHandler(this.button_calcuDelta_Click);
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1055, 545);
            this.Controls.Add(this.button_calcuDelta);
            this.Controls.Add(this.button_changeAllPixel);
            this.Controls.Add(this.button_changeCurrPixel);
            this.Controls.Add(this.textBox_deltaPixel);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.textBox_measuredPixel);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.textBox_realPixel);
            this.Controls.Add(this.button_OpenExistImage);
            this.Controls.Add(this.textBox);
            this.Controls.Add(this.button_CreateImage);
            this.Controls.Add(this.button_SetZero);
            this.Controls.Add(this.dataGridView);
            this.Margin = new System.Windows.Forms.Padding(4);
            this.MaximumSize = new System.Drawing.Size(1073, 590);
            this.MinimumSize = new System.Drawing.Size(1073, 590);
            this.Name = "MainForm";
            this.Text = "制作彩色图像";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.MainForm_FormClosing);
            this.Load += new System.EventHandler(this.MainForm_Load);
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.DataGridView dataGridView;
        private System.Windows.Forms.Button button_SetZero;
        private System.Windows.Forms.Button button_CreateImage;
        private System.Windows.Forms.TextBox textBox;
        private System.Windows.Forms.Button button_OpenExistImage;
        private System.Windows.Forms.OpenFileDialog openFileDialog;
        private System.Windows.Forms.TextBox textBox_realPixel;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox textBox_measuredPixel;
        private System.Windows.Forms.TextBox textBox_deltaPixel;
        private System.Windows.Forms.Button button_changeCurrPixel;
        private System.Windows.Forms.Button button_changeAllPixel;
        private System.Windows.Forms.Button button_calcuDelta;
    }
}


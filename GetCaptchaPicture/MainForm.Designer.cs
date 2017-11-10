namespace GetCaptchaPicture
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
            this.label1 = new System.Windows.Forms.Label();
            this.textBox_url = new System.Windows.Forms.TextBox();
            this.pictureBox = new System.Windows.Forms.PictureBox();
            this.button_get = new System.Windows.Forms.Button();
            this.label2 = new System.Windows.Forms.Label();
            this.textBox_prefix = new System.Windows.Forms.TextBox();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox)).BeginInit();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(21, 27);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(47, 15);
            this.label1.TabIndex = 0;
            this.label1.Text = "URL: ";
            // 
            // textBox_url
            // 
            this.textBox_url.Location = new System.Drawing.Point(74, 22);
            this.textBox_url.Name = "textBox_url";
            this.textBox_url.Size = new System.Drawing.Size(501, 25);
            this.textBox_url.TabIndex = 1;
            // 
            // pictureBox
            // 
            this.pictureBox.BackColor = System.Drawing.SystemColors.ControlLight;
            this.pictureBox.Location = new System.Drawing.Point(24, 71);
            this.pictureBox.Name = "pictureBox";
            this.pictureBox.Size = new System.Drawing.Size(282, 161);
            this.pictureBox.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.pictureBox.TabIndex = 2;
            this.pictureBox.TabStop = false;
            // 
            // button_get
            // 
            this.button_get.Location = new System.Drawing.Point(344, 174);
            this.button_get.Name = "button_get";
            this.button_get.Size = new System.Drawing.Size(231, 58);
            this.button_get.TabIndex = 3;
            this.button_get.Text = "获 取";
            this.button_get.UseVisualStyleBackColor = true;
            this.button_get.Click += new System.EventHandler(this.button_get_Click);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(341, 76);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(105, 15);
            this.label2.TabIndex = 4;
            this.label2.Text = "图片名称前缀:";
            // 
            // textBox_prefix
            // 
            this.textBox_prefix.Location = new System.Drawing.Point(452, 71);
            this.textBox_prefix.Name = "textBox_prefix";
            this.textBox_prefix.Size = new System.Drawing.Size(123, 25);
            this.textBox_prefix.TabIndex = 5;
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(604, 259);
            this.Controls.Add(this.textBox_prefix);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.button_get);
            this.Controls.Add(this.pictureBox);
            this.Controls.Add(this.textBox_url);
            this.Controls.Add(this.label1);
            this.Name = "MainForm";
            this.Text = "获取验证码";
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox textBox_url;
        private System.Windows.Forms.PictureBox pictureBox;
        private System.Windows.Forms.Button button_get;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox textBox_prefix;
    }
}


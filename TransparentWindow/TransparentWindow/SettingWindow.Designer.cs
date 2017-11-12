namespace TransparentWindow
{
    partial class SettingWindow
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.colorDialog = new System.Windows.Forms.ColorDialog();
            this.button_setColor = new System.Windows.Forms.Button();
            this.trackBar = new System.Windows.Forms.TrackBar();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label_alpha = new System.Windows.Forms.Label();
            this.button_ok = new System.Windows.Forms.Button();
            this.button_cancel = new System.Windows.Forms.Button();
            this.pictureBox = new System.Windows.Forms.PictureBox();
            ((System.ComponentModel.ISupportInitialize)(this.trackBar)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox)).BeginInit();
            this.SuspendLayout();
            // 
            // button_setColor
            // 
            this.button_setColor.Location = new System.Drawing.Point(17, 19);
            this.button_setColor.Name = "button_setColor";
            this.button_setColor.Size = new System.Drawing.Size(100, 45);
            this.button_setColor.TabIndex = 0;
            this.button_setColor.Text = "设置前景色";
            this.button_setColor.UseVisualStyleBackColor = true;
            this.button_setColor.Click += new System.EventHandler(this.button_setColor_Click);
            // 
            // trackBar
            // 
            this.trackBar.Location = new System.Drawing.Point(137, 19);
            this.trackBar.Maximum = 50;
            this.trackBar.Name = "trackBar";
            this.trackBar.Size = new System.Drawing.Size(338, 45);
            this.trackBar.TabIndex = 1;
            this.trackBar.ValueChanged += new System.EventHandler(this.trackBar_ValueChanged);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(265, 52);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(53, 12);
            this.label1.TabIndex = 2;
            this.label1.Text = "透明度：";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(140, 52);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(17, 12);
            this.label2.TabIndex = 3;
            this.label2.Text = "0%";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(452, 52);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(23, 12);
            this.label3.TabIndex = 4;
            this.label3.Text = "50%";
            // 
            // label_alpha
            // 
            this.label_alpha.AutoSize = true;
            this.label_alpha.Location = new System.Drawing.Point(320, 52);
            this.label_alpha.Name = "label_alpha";
            this.label_alpha.Size = new System.Drawing.Size(17, 12);
            this.label_alpha.TabIndex = 5;
            this.label_alpha.Text = "0%";
            // 
            // button_ok
            // 
            this.button_ok.Location = new System.Drawing.Point(346, 83);
            this.button_ok.Name = "button_ok";
            this.button_ok.Size = new System.Drawing.Size(129, 47);
            this.button_ok.TabIndex = 7;
            this.button_ok.Text = "确 定";
            this.button_ok.UseVisualStyleBackColor = true;
            this.button_ok.Click += new System.EventHandler(this.button_ok_Click);
            // 
            // button_cancel
            // 
            this.button_cancel.Location = new System.Drawing.Point(346, 144);
            this.button_cancel.Name = "button_cancel";
            this.button_cancel.Size = new System.Drawing.Size(129, 47);
            this.button_cancel.TabIndex = 8;
            this.button_cancel.Text = "取 消";
            this.button_cancel.UseVisualStyleBackColor = true;
            this.button_cancel.Click += new System.EventHandler(this.button_cancel_Click);
            // 
            // pictureBox
            // 
            this.pictureBox.Location = new System.Drawing.Point(17, 83);
            this.pictureBox.Name = "pictureBox";
            this.pictureBox.Size = new System.Drawing.Size(317, 108);
            this.pictureBox.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.pictureBox.TabIndex = 6;
            this.pictureBox.TabStop = false;
            // 
            // SettingWindow
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(490, 209);
            this.Controls.Add(this.button_cancel);
            this.Controls.Add(this.button_ok);
            this.Controls.Add(this.label_alpha);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.trackBar);
            this.Controls.Add(this.button_setColor);
            this.Controls.Add(this.pictureBox);
            this.MaximumSize = new System.Drawing.Size(506, 247);
            this.MinimumSize = new System.Drawing.Size(506, 247);
            this.Name = "SettingWindow";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "设置背景";
            this.TopMost = true;
            this.Load += new System.EventHandler(this.SettingWindow_Load);
            ((System.ComponentModel.ISupportInitialize)(this.trackBar)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ColorDialog colorDialog;
        private System.Windows.Forms.Button button_setColor;
        private System.Windows.Forms.TrackBar trackBar;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label_alpha;
        private System.Windows.Forms.PictureBox pictureBox;
        private System.Windows.Forms.Button button_ok;
        private System.Windows.Forms.Button button_cancel;
    }
}
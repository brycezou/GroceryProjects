namespace FlameAreaCalcu
{
    partial class SetScaleForm
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
            this.label_DIP = new System.Windows.Forms.Label();
            this.textBox_DIP = new System.Windows.Forms.TextBox();
            this.textBox_KD = new System.Windows.Forms.TextBox();
            this.label_KD = new System.Windows.Forms.Label();
            this.textBox_UOL = new System.Windows.Forms.TextBox();
            this.label_UOL = new System.Windows.Forms.Label();
            this.label_perPixelDis = new System.Windows.Forms.Label();
            this.label_scaleValue = new System.Windows.Forms.Label();
            this.button_OK = new System.Windows.Forms.Button();
            this.button_Cancel = new System.Windows.Forms.Button();
            this.button_Help = new System.Windows.Forms.Button();
            this.button_LoadImage = new System.Windows.Forms.Button();
            this.button_createFile = new System.Windows.Forms.Button();
            this.button_readFile = new System.Windows.Forms.Button();
            this.pictureBox = new System.Windows.Forms.PictureBox();
            this.openFileDialog = new System.Windows.Forms.OpenFileDialog();
            this.openFileDialog1 = new System.Windows.Forms.OpenFileDialog();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox)).BeginInit();
            this.SuspendLayout();
            // 
            // label_DIP
            // 
            this.label_DIP.AutoSize = true;
            this.label_DIP.Font = new System.Drawing.Font("Times New Roman", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label_DIP.Location = new System.Drawing.Point(20, 13);
            this.label_DIP.Name = "label_DIP";
            this.label_DIP.Size = new System.Drawing.Size(72, 17);
            this.label_DIP.TabIndex = 0;
            this.label_DIP.Text = "像素距离";
            // 
            // textBox_DIP
            // 
            this.textBox_DIP.Location = new System.Drawing.Point(20, 39);
            this.textBox_DIP.Name = "textBox_DIP";
            this.textBox_DIP.Size = new System.Drawing.Size(255, 25);
            this.textBox_DIP.TabIndex = 1;
            // 
            // textBox_KD
            // 
            this.textBox_KD.Location = new System.Drawing.Point(20, 108);
            this.textBox_KD.Name = "textBox_KD";
            this.textBox_KD.Size = new System.Drawing.Size(255, 25);
            this.textBox_KD.TabIndex = 3;
            this.textBox_KD.TextChanged += new System.EventHandler(this.textBox_KD_TextChanged);
            // 
            // label_KD
            // 
            this.label_KD.AutoSize = true;
            this.label_KD.Font = new System.Drawing.Font("Times New Roman", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label_KD.Location = new System.Drawing.Point(20, 84);
            this.label_KD.Name = "label_KD";
            this.label_KD.Size = new System.Drawing.Size(72, 17);
            this.label_KD.TabIndex = 2;
            this.label_KD.Text = "实际距离";
            // 
            // textBox_UOL
            // 
            this.textBox_UOL.Location = new System.Drawing.Point(20, 174);
            this.textBox_UOL.Name = "textBox_UOL";
            this.textBox_UOL.Size = new System.Drawing.Size(255, 25);
            this.textBox_UOL.TabIndex = 7;
            // 
            // label_UOL
            // 
            this.label_UOL.AutoSize = true;
            this.label_UOL.Font = new System.Drawing.Font("Times New Roman", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label_UOL.Location = new System.Drawing.Point(20, 151);
            this.label_UOL.Name = "label_UOL";
            this.label_UOL.Size = new System.Drawing.Size(72, 17);
            this.label_UOL.TabIndex = 6;
            this.label_UOL.Text = "长度单位";
            // 
            // label_perPixelDis
            // 
            this.label_perPixelDis.AutoSize = true;
            this.label_perPixelDis.Font = new System.Drawing.Font("Times New Roman", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label_perPixelDis.Location = new System.Drawing.Point(23, 433);
            this.label_perPixelDis.Name = "label_perPixelDis";
            this.label_perPixelDis.Size = new System.Drawing.Size(120, 17);
            this.label_perPixelDis.TabIndex = 10;
            this.label_perPixelDis.Text = "单位像素长度：";
            // 
            // label_scaleValue
            // 
            this.label_scaleValue.AutoSize = true;
            this.label_scaleValue.Font = new System.Drawing.Font("Times New Roman", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label_scaleValue.Location = new System.Drawing.Point(199, 433);
            this.label_scaleValue.Name = "label_scaleValue";
            this.label_scaleValue.Size = new System.Drawing.Size(40, 17);
            this.label_scaleValue.TabIndex = 11;
            this.label_scaleValue.Text = "<无>";
            // 
            // button_OK
            // 
            this.button_OK.Font = new System.Drawing.Font("Times New Roman", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.button_OK.Location = new System.Drawing.Point(23, 537);
            this.button_OK.Name = "button_OK";
            this.button_OK.Size = new System.Drawing.Size(255, 39);
            this.button_OK.TabIndex = 12;
            this.button_OK.Text = "确定";
            this.button_OK.UseVisualStyleBackColor = true;
            this.button_OK.Click += new System.EventHandler(this.button_OK_Click);
            // 
            // button_Cancel
            // 
            this.button_Cancel.Font = new System.Drawing.Font("Times New Roman", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.button_Cancel.Location = new System.Drawing.Point(23, 488);
            this.button_Cancel.Name = "button_Cancel";
            this.button_Cancel.Size = new System.Drawing.Size(119, 30);
            this.button_Cancel.TabIndex = 13;
            this.button_Cancel.Text = "取消";
            this.button_Cancel.UseVisualStyleBackColor = true;
            this.button_Cancel.Click += new System.EventHandler(this.button_Cancel_Click);
            // 
            // button_Help
            // 
            this.button_Help.Font = new System.Drawing.Font("Times New Roman", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.button_Help.Location = new System.Drawing.Point(159, 488);
            this.button_Help.Name = "button_Help";
            this.button_Help.Size = new System.Drawing.Size(119, 30);
            this.button_Help.TabIndex = 14;
            this.button_Help.Text = "帮助";
            this.button_Help.UseVisualStyleBackColor = true;
            this.button_Help.Click += new System.EventHandler(this.button_Help_Click);
            // 
            // button_LoadImage
            // 
            this.button_LoadImage.Font = new System.Drawing.Font("Times New Roman", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.button_LoadImage.Location = new System.Drawing.Point(23, 236);
            this.button_LoadImage.Name = "button_LoadImage";
            this.button_LoadImage.Size = new System.Drawing.Size(255, 34);
            this.button_LoadImage.TabIndex = 15;
            this.button_LoadImage.Text = "读入标定图像";
            this.button_LoadImage.UseVisualStyleBackColor = true;
            this.button_LoadImage.Click += new System.EventHandler(this.button_LoadImage_Click);
            // 
            // button_createFile
            // 
            this.button_createFile.Font = new System.Drawing.Font("Times New Roman", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.button_createFile.Location = new System.Drawing.Point(23, 296);
            this.button_createFile.Name = "button_createFile";
            this.button_createFile.Size = new System.Drawing.Size(255, 34);
            this.button_createFile.TabIndex = 16;
            this.button_createFile.Text = "生成标定文件";
            this.button_createFile.UseVisualStyleBackColor = true;
            this.button_createFile.Click += new System.EventHandler(this.button_createFile_Click);
            // 
            // button_readFile
            // 
            this.button_readFile.Font = new System.Drawing.Font("Times New Roman", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.button_readFile.Location = new System.Drawing.Point(23, 356);
            this.button_readFile.Name = "button_readFile";
            this.button_readFile.Size = new System.Drawing.Size(255, 34);
            this.button_readFile.TabIndex = 17;
            this.button_readFile.Text = "导入标定文件";
            this.button_readFile.UseVisualStyleBackColor = true;
            this.button_readFile.Click += new System.EventHandler(this.button_readFile_Click);
            // 
            // pictureBox
            // 
            this.pictureBox.Cursor = System.Windows.Forms.Cursors.Cross;
            this.pictureBox.Location = new System.Drawing.Point(298, 12);
            this.pictureBox.Name = "pictureBox";
            this.pictureBox.Size = new System.Drawing.Size(760, 588);
            this.pictureBox.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.pictureBox.TabIndex = 18;
            this.pictureBox.TabStop = false;
            this.pictureBox.MouseDown += new System.Windows.Forms.MouseEventHandler(this.pictureBox_MouseDown);
            this.pictureBox.MouseMove += new System.Windows.Forms.MouseEventHandler(this.pictureBox_MouseMove);
            this.pictureBox.MouseUp += new System.Windows.Forms.MouseEventHandler(this.pictureBox_MouseUp);
            // 
            // openFileDialog
            // 
            this.openFileDialog.FileName = "openFileDialog";
            this.openFileDialog.Filter = "位图|*.bmp|JPG|*.jpg";
            // 
            // openFileDialog1
            // 
            this.openFileDialog1.Filter = "标定文件|*.std";
            // 
            // SetScaleForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1070, 612);
            this.Controls.Add(this.pictureBox);
            this.Controls.Add(this.button_readFile);
            this.Controls.Add(this.button_createFile);
            this.Controls.Add(this.button_LoadImage);
            this.Controls.Add(this.button_Help);
            this.Controls.Add(this.button_Cancel);
            this.Controls.Add(this.button_OK);
            this.Controls.Add(this.label_scaleValue);
            this.Controls.Add(this.label_perPixelDis);
            this.Controls.Add(this.textBox_UOL);
            this.Controls.Add(this.label_UOL);
            this.Controls.Add(this.textBox_KD);
            this.Controls.Add(this.label_KD);
            this.Controls.Add(this.textBox_DIP);
            this.Controls.Add(this.label_DIP);
            this.MaximizeBox = false;
            this.MaximumSize = new System.Drawing.Size(1088, 657);
            this.MinimizeBox = false;
            this.MinimumSize = new System.Drawing.Size(1088, 657);
            this.Name = "SetScaleForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "标定窗口";
            this.Load += new System.EventHandler(this.SetScaleForm_Load);
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label_DIP;
        private System.Windows.Forms.TextBox textBox_DIP;
        private System.Windows.Forms.TextBox textBox_KD;
        private System.Windows.Forms.Label label_KD;
        private System.Windows.Forms.TextBox textBox_UOL;
        private System.Windows.Forms.Label label_UOL;
        private System.Windows.Forms.Label label_perPixelDis;
        private System.Windows.Forms.Label label_scaleValue;
        private System.Windows.Forms.Button button_OK;
        private System.Windows.Forms.Button button_Cancel;
        private System.Windows.Forms.Button button_Help;
        private System.Windows.Forms.Button button_LoadImage;
        private System.Windows.Forms.Button button_createFile;
        private System.Windows.Forms.Button button_readFile;
        private System.Windows.Forms.PictureBox pictureBox;
        private System.Windows.Forms.OpenFileDialog openFileDialog;
        private System.Windows.Forms.OpenFileDialog openFileDialog1;
    }
}
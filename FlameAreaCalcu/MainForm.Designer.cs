namespace FlameAreaCalcu
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
            this.menuStrip = new System.Windows.Forms.MenuStrip();
            this.文件ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.打开ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.另存为ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.保存数据ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.打印ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.关闭ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.退出ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.分析ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.测量距离ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.测量面积ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.标定ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.语言ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.中文ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.englishToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.关于ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStrip = new System.Windows.Forms.ToolStrip();
            this.toolStripButton_openFile = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton_saveAs = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton_saveData = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton_closeFile = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton_exit = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripButton_measureDistance = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton_measureAera = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton_correct = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator2 = new System.Windows.Forms.ToolStripSeparator();
            this.openFileDialog = new System.Windows.Forms.OpenFileDialog();
            this.pictureBox = new System.Windows.Forms.PictureBox();
            this.statusStrip = new System.Windows.Forms.StatusStrip();
            this.toolStrip_StatusLabel = new System.Windows.Forms.ToolStripStatusLabel();
            this.toolStripStatusLabel = new System.Windows.Forms.ToolStripStatusLabel();
            this.printDocument = new System.Drawing.Printing.PrintDocument();
            this.menuStrip.SuspendLayout();
            this.toolStrip.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox)).BeginInit();
            this.statusStrip.SuspendLayout();
            this.SuspendLayout();
            // 
            // menuStrip
            // 
            this.menuStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.文件ToolStripMenuItem,
            this.分析ToolStripMenuItem,
            this.语言ToolStripMenuItem,
            this.关于ToolStripMenuItem});
            this.menuStrip.Location = new System.Drawing.Point(0, 0);
            this.menuStrip.Name = "menuStrip";
            this.menuStrip.Size = new System.Drawing.Size(1128, 25);
            this.menuStrip.TabIndex = 0;
            this.menuStrip.Text = "菜单栏";
            // 
            // 文件ToolStripMenuItem
            // 
            this.文件ToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.打开ToolStripMenuItem,
            this.另存为ToolStripMenuItem,
            this.保存数据ToolStripMenuItem,
            this.打印ToolStripMenuItem,
            this.关闭ToolStripMenuItem,
            this.退出ToolStripMenuItem});
            this.文件ToolStripMenuItem.Font = new System.Drawing.Font("Times New Roman", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.文件ToolStripMenuItem.Name = "文件ToolStripMenuItem";
            this.文件ToolStripMenuItem.Size = new System.Drawing.Size(52, 21);
            this.文件ToolStripMenuItem.Text = "文件";
            // 
            // 打开ToolStripMenuItem
            // 
            this.打开ToolStripMenuItem.Name = "打开ToolStripMenuItem";
            this.打开ToolStripMenuItem.Size = new System.Drawing.Size(140, 22);
            this.打开ToolStripMenuItem.Text = "打开";
            this.打开ToolStripMenuItem.Click += new System.EventHandler(this.ToolStripMenuItem_Click);
            // 
            // 另存为ToolStripMenuItem
            // 
            this.另存为ToolStripMenuItem.Name = "另存为ToolStripMenuItem";
            this.另存为ToolStripMenuItem.Size = new System.Drawing.Size(140, 22);
            this.另存为ToolStripMenuItem.Text = "另存为";
            this.另存为ToolStripMenuItem.Click += new System.EventHandler(this.ToolStripMenuItem_Click);
            // 
            // 保存数据ToolStripMenuItem
            // 
            this.保存数据ToolStripMenuItem.Name = "保存数据ToolStripMenuItem";
            this.保存数据ToolStripMenuItem.Size = new System.Drawing.Size(140, 22);
            this.保存数据ToolStripMenuItem.Text = "保存数据";
            this.保存数据ToolStripMenuItem.Click += new System.EventHandler(this.ToolStripMenuItem_Click);
            // 
            // 打印ToolStripMenuItem
            // 
            this.打印ToolStripMenuItem.Name = "打印ToolStripMenuItem";
            this.打印ToolStripMenuItem.Size = new System.Drawing.Size(140, 22);
            this.打印ToolStripMenuItem.Text = "打印图像";
            this.打印ToolStripMenuItem.Click += new System.EventHandler(this.ToolStripMenuItem_Click);
            // 
            // 关闭ToolStripMenuItem
            // 
            this.关闭ToolStripMenuItem.Name = "关闭ToolStripMenuItem";
            this.关闭ToolStripMenuItem.Size = new System.Drawing.Size(140, 22);
            this.关闭ToolStripMenuItem.Text = "关闭";
            this.关闭ToolStripMenuItem.Click += new System.EventHandler(this.ToolStripMenuItem_Click);
            // 
            // 退出ToolStripMenuItem
            // 
            this.退出ToolStripMenuItem.Name = "退出ToolStripMenuItem";
            this.退出ToolStripMenuItem.Size = new System.Drawing.Size(140, 22);
            this.退出ToolStripMenuItem.Text = "退出";
            this.退出ToolStripMenuItem.Click += new System.EventHandler(this.ToolStripMenuItem_Click);
            // 
            // 分析ToolStripMenuItem
            // 
            this.分析ToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.测量距离ToolStripMenuItem,
            this.测量面积ToolStripMenuItem,
            this.标定ToolStripMenuItem});
            this.分析ToolStripMenuItem.Font = new System.Drawing.Font("Times New Roman", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.分析ToolStripMenuItem.Name = "分析ToolStripMenuItem";
            this.分析ToolStripMenuItem.Size = new System.Drawing.Size(52, 21);
            this.分析ToolStripMenuItem.Text = "分析";
            // 
            // 测量距离ToolStripMenuItem
            // 
            this.测量距离ToolStripMenuItem.Name = "测量距离ToolStripMenuItem";
            this.测量距离ToolStripMenuItem.Size = new System.Drawing.Size(140, 22);
            this.测量距离ToolStripMenuItem.Text = "测量距离";
            this.测量距离ToolStripMenuItem.Click += new System.EventHandler(this.ToolStripMenuItem_Click);
            // 
            // 测量面积ToolStripMenuItem
            // 
            this.测量面积ToolStripMenuItem.Checked = true;
            this.测量面积ToolStripMenuItem.CheckState = System.Windows.Forms.CheckState.Checked;
            this.测量面积ToolStripMenuItem.Name = "测量面积ToolStripMenuItem";
            this.测量面积ToolStripMenuItem.Size = new System.Drawing.Size(140, 22);
            this.测量面积ToolStripMenuItem.Text = "测量面积";
            this.测量面积ToolStripMenuItem.Click += new System.EventHandler(this.ToolStripMenuItem_Click);
            // 
            // 标定ToolStripMenuItem
            // 
            this.标定ToolStripMenuItem.Name = "标定ToolStripMenuItem";
            this.标定ToolStripMenuItem.Size = new System.Drawing.Size(140, 22);
            this.标定ToolStripMenuItem.Text = "标定";
            this.标定ToolStripMenuItem.Click += new System.EventHandler(this.ToolStripMenuItem_Click);
            // 
            // 语言ToolStripMenuItem
            // 
            this.语言ToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.中文ToolStripMenuItem,
            this.englishToolStripMenuItem});
            this.语言ToolStripMenuItem.Font = new System.Drawing.Font("Times New Roman", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.语言ToolStripMenuItem.Name = "语言ToolStripMenuItem";
            this.语言ToolStripMenuItem.Size = new System.Drawing.Size(52, 21);
            this.语言ToolStripMenuItem.Text = "语言";
            // 
            // 中文ToolStripMenuItem
            // 
            this.中文ToolStripMenuItem.Checked = true;
            this.中文ToolStripMenuItem.CheckState = System.Windows.Forms.CheckState.Checked;
            this.中文ToolStripMenuItem.Name = "中文ToolStripMenuItem";
            this.中文ToolStripMenuItem.Size = new System.Drawing.Size(126, 22);
            this.中文ToolStripMenuItem.Text = "中文";
            this.中文ToolStripMenuItem.Click += new System.EventHandler(this.ToolStripMenuItem_Click);
            // 
            // englishToolStripMenuItem
            // 
            this.englishToolStripMenuItem.Name = "englishToolStripMenuItem";
            this.englishToolStripMenuItem.Size = new System.Drawing.Size(126, 22);
            this.englishToolStripMenuItem.Text = "Français";
            this.englishToolStripMenuItem.Click += new System.EventHandler(this.ToolStripMenuItem_Click);
            // 
            // 关于ToolStripMenuItem
            // 
            this.关于ToolStripMenuItem.Font = new System.Drawing.Font("Times New Roman", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.关于ToolStripMenuItem.Name = "关于ToolStripMenuItem";
            this.关于ToolStripMenuItem.Size = new System.Drawing.Size(52, 21);
            this.关于ToolStripMenuItem.Text = "关于";
            this.关于ToolStripMenuItem.Click += new System.EventHandler(this.ToolStripMenuItem_Click);
            // 
            // toolStrip
            // 
            this.toolStrip.AutoSize = false;
            this.toolStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripButton_openFile,
            this.toolStripButton_saveAs,
            this.toolStripButton_saveData,
            this.toolStripButton_closeFile,
            this.toolStripButton_exit,
            this.toolStripSeparator1,
            this.toolStripButton_measureDistance,
            this.toolStripButton_measureAera,
            this.toolStripButton_correct,
            this.toolStripSeparator2});
            this.toolStrip.Location = new System.Drawing.Point(0, 25);
            this.toolStrip.Name = "toolStrip";
            this.toolStrip.Size = new System.Drawing.Size(1128, 34);
            this.toolStrip.Stretch = true;
            this.toolStrip.TabIndex = 1;
            this.toolStrip.Text = "工具栏";
            // 
            // toolStripButton_openFile
            // 
            this.toolStripButton_openFile.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton_openFile.Image = global::FlameAreaCalcu.Properties.Resources.open;
            this.toolStripButton_openFile.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripButton_openFile.Name = "toolStripButton_openFile";
            this.toolStripButton_openFile.Size = new System.Drawing.Size(23, 31);
            this.toolStripButton_openFile.Text = "打开";
            this.toolStripButton_openFile.Click += new System.EventHandler(this.toolStripButton_Click);
            // 
            // toolStripButton_saveAs
            // 
            this.toolStripButton_saveAs.AutoSize = false;
            this.toolStripButton_saveAs.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton_saveAs.Image = global::FlameAreaCalcu.Properties.Resources.saveas;
            this.toolStripButton_saveAs.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripButton_saveAs.Name = "toolStripButton_saveAs";
            this.toolStripButton_saveAs.Size = new System.Drawing.Size(23, 27);
            this.toolStripButton_saveAs.Text = "另存为";
            this.toolStripButton_saveAs.Click += new System.EventHandler(this.toolStripButton_Click);
            // 
            // toolStripButton_saveData
            // 
            this.toolStripButton_saveData.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton_saveData.Image = global::FlameAreaCalcu.Properties.Resources.save;
            this.toolStripButton_saveData.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripButton_saveData.Name = "toolStripButton_saveData";
            this.toolStripButton_saveData.Size = new System.Drawing.Size(23, 31);
            this.toolStripButton_saveData.Text = "保存数据";
            this.toolStripButton_saveData.Click += new System.EventHandler(this.toolStripButton_Click);
            // 
            // toolStripButton_closeFile
            // 
            this.toolStripButton_closeFile.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton_closeFile.Image = global::FlameAreaCalcu.Properties.Resources.close;
            this.toolStripButton_closeFile.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripButton_closeFile.Name = "toolStripButton_closeFile";
            this.toolStripButton_closeFile.Size = new System.Drawing.Size(23, 31);
            this.toolStripButton_closeFile.Text = "关闭";
            this.toolStripButton_closeFile.Click += new System.EventHandler(this.toolStripButton_Click);
            // 
            // toolStripButton_exit
            // 
            this.toolStripButton_exit.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton_exit.Image = global::FlameAreaCalcu.Properties.Resources.exit;
            this.toolStripButton_exit.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripButton_exit.Name = "toolStripButton_exit";
            this.toolStripButton_exit.Size = new System.Drawing.Size(23, 31);
            this.toolStripButton_exit.Text = "退出";
            this.toolStripButton_exit.Click += new System.EventHandler(this.toolStripButton_Click);
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(6, 34);
            // 
            // toolStripButton_measureDistance
            // 
            this.toolStripButton_measureDistance.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton_measureDistance.Image = global::FlameAreaCalcu.Properties.Resources.mdist;
            this.toolStripButton_measureDistance.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripButton_measureDistance.Name = "toolStripButton_measureDistance";
            this.toolStripButton_measureDistance.Size = new System.Drawing.Size(23, 31);
            this.toolStripButton_measureDistance.Text = "测量距离";
            this.toolStripButton_measureDistance.Click += new System.EventHandler(this.toolStripButton_Click);
            // 
            // toolStripButton_measureAera
            // 
            this.toolStripButton_measureAera.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton_measureAera.Image = global::FlameAreaCalcu.Properties.Resources.marea;
            this.toolStripButton_measureAera.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripButton_measureAera.Name = "toolStripButton_measureAera";
            this.toolStripButton_measureAera.Size = new System.Drawing.Size(23, 31);
            this.toolStripButton_measureAera.Text = "测量面积";
            this.toolStripButton_measureAera.Click += new System.EventHandler(this.toolStripButton_Click);
            // 
            // toolStripButton_correct
            // 
            this.toolStripButton_correct.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton_correct.Image = global::FlameAreaCalcu.Properties.Resources.calibrate;
            this.toolStripButton_correct.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripButton_correct.Name = "toolStripButton_correct";
            this.toolStripButton_correct.Size = new System.Drawing.Size(23, 31);
            this.toolStripButton_correct.Text = "标定";
            this.toolStripButton_correct.Click += new System.EventHandler(this.toolStripButton_Click);
            // 
            // toolStripSeparator2
            // 
            this.toolStripSeparator2.Name = "toolStripSeparator2";
            this.toolStripSeparator2.Size = new System.Drawing.Size(6, 34);
            // 
            // openFileDialog
            // 
            this.openFileDialog.Filter = "位图|*.bmp|JPG|*.jpg";
            // 
            // pictureBox
            // 
            this.pictureBox.Cursor = System.Windows.Forms.Cursors.Cross;
            this.pictureBox.Location = new System.Drawing.Point(12, 83);
            this.pictureBox.Name = "pictureBox";
            this.pictureBox.Size = new System.Drawing.Size(1104, 711);
            this.pictureBox.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.pictureBox.TabIndex = 8;
            this.pictureBox.TabStop = false;
            this.pictureBox.MouseDown += new System.Windows.Forms.MouseEventHandler(this.pictureBox_MouseDown);
            this.pictureBox.MouseMove += new System.Windows.Forms.MouseEventHandler(this.pictureBox_MouseMove);
            this.pictureBox.MouseUp += new System.Windows.Forms.MouseEventHandler(this.pictureBox_MouseUp);
            // 
            // statusStrip
            // 
            this.statusStrip.Font = new System.Drawing.Font("Times New Roman", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.statusStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStrip_StatusLabel,
            this.toolStripStatusLabel});
            this.statusStrip.Location = new System.Drawing.Point(0, 809);
            this.statusStrip.Name = "statusStrip";
            this.statusStrip.Size = new System.Drawing.Size(1128, 22);
            this.statusStrip.TabIndex = 12;
            this.statusStrip.Text = "statusStrip";
            // 
            // toolStrip_StatusLabel
            // 
            this.toolStrip_StatusLabel.Name = "toolStrip_StatusLabel";
            this.toolStrip_StatusLabel.Size = new System.Drawing.Size(0, 17);
            // 
            // toolStripStatusLabel
            // 
            this.toolStripStatusLabel.Name = "toolStripStatusLabel";
            this.toolStripStatusLabel.Size = new System.Drawing.Size(0, 17);
            // 
            // printDocument
            // 
            this.printDocument.OriginAtMargins = true;
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 17F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1128, 831);
            this.Controls.Add(this.statusStrip);
            this.Controls.Add(this.pictureBox);
            this.Controls.Add(this.toolStrip);
            this.Controls.Add(this.menuStrip);
            this.Font = new System.Drawing.Font("Times New Roman", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.MainMenuStrip = this.menuStrip;
            this.MaximizeBox = false;
            this.MaximumSize = new System.Drawing.Size(1146, 876);
            this.MinimumSize = new System.Drawing.Size(1146, 876);
            this.Name = "MainForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "膛口火焰面积计算分析软件";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.MainForm_FormClosing);
            this.Load += new System.EventHandler(this.MainForm_Load);
            this.menuStrip.ResumeLayout(false);
            this.menuStrip.PerformLayout();
            this.toolStrip.ResumeLayout(false);
            this.toolStrip.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox)).EndInit();
            this.statusStrip.ResumeLayout(false);
            this.statusStrip.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip;
        private System.Windows.Forms.ToolStripMenuItem 文件ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 打开ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 另存为ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 保存数据ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 关闭ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 退出ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 分析ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 测量距离ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 测量面积ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 标定ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 语言ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 中文ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem englishToolStripMenuItem;
        private System.Windows.Forms.ToolStrip toolStrip;
        private System.Windows.Forms.ToolStripButton toolStripButton_openFile;
        private System.Windows.Forms.ToolStripButton toolStripButton_saveAs;
        private System.Windows.Forms.ToolStripButton toolStripButton_saveData;
        private System.Windows.Forms.ToolStripButton toolStripButton_closeFile;
        private System.Windows.Forms.ToolStripButton toolStripButton_exit;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        private System.Windows.Forms.ToolStripButton toolStripButton_measureDistance;
        private System.Windows.Forms.ToolStripButton toolStripButton_measureAera;
        private System.Windows.Forms.ToolStripButton toolStripButton_correct;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator2;
        private System.Windows.Forms.PictureBox pictureBox;
        private System.Windows.Forms.OpenFileDialog openFileDialog;
        private System.Windows.Forms.ToolStripMenuItem 关于ToolStripMenuItem;
        private System.Windows.Forms.StatusStrip statusStrip;
        public System.Windows.Forms.ToolStripStatusLabel toolStrip_StatusLabel;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabel;
        private System.Windows.Forms.ToolStripMenuItem 打印ToolStripMenuItem;
        private System.Drawing.Printing.PrintDocument printDocument;
    }
}


namespace BasicWinForm
{
    partial class NewForm
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
            this.components = new System.ComponentModel.Container();
            this.listBox = new System.Windows.Forms.ListBox();
            this.btnOKList = new System.Windows.Forms.Button();
            this.comboBox = new System.Windows.Forms.ComboBox();
            this.checkBox_LiHua = new System.Windows.Forms.CheckBox();
            this.checkBox_LiuYu = new System.Windows.Forms.CheckBox();
            this.checkBox_All = new System.Windows.Forms.CheckBox();
            this.textBox = new System.Windows.Forms.TextBox();
            this.radioButton_Woman = new System.Windows.Forms.RadioButton();
            this.radioButton_Man = new System.Windows.Forms.RadioButton();
            this.tabControl = new System.Windows.Forms.TabControl();
            this.tabPage_Food = new System.Windows.Forms.TabPage();
            this.btnMilk = new System.Windows.Forms.Button();
            this.tabPage_Hobby = new System.Windows.Forms.TabPage();
            this.btnRead = new System.Windows.Forms.Button();
            this.treeView = new System.Windows.Forms.TreeView();
            this.btnSelectColor = new System.Windows.Forms.Button();
            this.colorDialog = new System.Windows.Forms.ColorDialog();
            this.btnSelectFont = new System.Windows.Forms.Button();
            this.fontDialog = new System.Windows.Forms.FontDialog();
            this.openFileDialog = new System.Windows.Forms.OpenFileDialog();
            this.btnOpenFile = new System.Windows.Forms.Button();
            this.btnSaveFile = new System.Windows.Forms.Button();
            this.saveFileDialog = new System.Windows.Forms.SaveFileDialog();
            this.contextMenuStrip = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.学校ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.同学ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.老师ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.家庭ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.爸妈ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.menuStrip = new System.Windows.Forms.MenuStrip();
            this.开始ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.程序ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.附件ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.btnDrawTriangle = new System.Windows.Forms.Button();
            this.btnDrawEllipse = new System.Windows.Forms.Button();
            this.btnCreateRegion = new System.Windows.Forms.Button();
            this.btnChangeBrush = new System.Windows.Forms.Button();
            this.btnTextureFill = new System.Windows.Forms.Button();
            this.btnLinearChange = new System.Windows.Forms.Button();
            this.btnShadowBrush = new System.Windows.Forms.Button();
            this.tabControl.SuspendLayout();
            this.tabPage_Food.SuspendLayout();
            this.tabPage_Hobby.SuspendLayout();
            this.contextMenuStrip.SuspendLayout();
            this.menuStrip.SuspendLayout();
            this.SuspendLayout();
            // 
            // listBox
            // 
            this.listBox.FormattingEnabled = true;
            this.listBox.ItemHeight = 15;
            this.listBox.Location = new System.Drawing.Point(0, 31);
            this.listBox.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.listBox.Name = "listBox";
            this.listBox.Size = new System.Drawing.Size(108, 79);
            this.listBox.TabIndex = 2;
            // 
            // btnOKList
            // 
            this.btnOKList.Location = new System.Drawing.Point(0, 118);
            this.btnOKList.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.btnOKList.Name = "btnOKList";
            this.btnOKList.Size = new System.Drawing.Size(109, 29);
            this.btnOKList.TabIndex = 3;
            this.btnOKList.Text = "确定";
            this.btnOKList.UseVisualStyleBackColor = true;
            this.btnOKList.Click += new System.EventHandler(this.btnOKList_Click);
            // 
            // comboBox
            // 
            this.comboBox.FormattingEnabled = true;
            this.comboBox.Location = new System.Drawing.Point(0, 154);
            this.comboBox.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.comboBox.Name = "comboBox";
            this.comboBox.Size = new System.Drawing.Size(108, 23);
            this.comboBox.TabIndex = 4;
            this.comboBox.SelectedIndexChanged += new System.EventHandler(this.comboBox_SelectedIndexChanged);
            // 
            // checkBox_LiHua
            // 
            this.checkBox_LiHua.AutoSize = true;
            this.checkBox_LiHua.Location = new System.Drawing.Point(0, 184);
            this.checkBox_LiHua.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.checkBox_LiHua.Name = "checkBox_LiHua";
            this.checkBox_LiHua.Size = new System.Drawing.Size(69, 19);
            this.checkBox_LiHua.TabIndex = 5;
            this.checkBox_LiHua.Text = "LiHua";
            this.checkBox_LiHua.UseVisualStyleBackColor = true;
            this.checkBox_LiHua.CheckedChanged += new System.EventHandler(this.checkBox_LiHua_CheckedChanged);
            this.checkBox_LiHua.Click += new System.EventHandler(this.checkBox_LiHua_Click);
            // 
            // checkBox_LiuYu
            // 
            this.checkBox_LiuYu.AutoSize = true;
            this.checkBox_LiuYu.Location = new System.Drawing.Point(0, 201);
            this.checkBox_LiuYu.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.checkBox_LiuYu.Name = "checkBox_LiuYu";
            this.checkBox_LiuYu.Size = new System.Drawing.Size(69, 19);
            this.checkBox_LiuYu.TabIndex = 6;
            this.checkBox_LiuYu.Text = "LiuYu";
            this.checkBox_LiuYu.UseVisualStyleBackColor = true;
            this.checkBox_LiuYu.CheckedChanged += new System.EventHandler(this.checkBox_LiuYu_CheckedChanged);
            this.checkBox_LiuYu.Click += new System.EventHandler(this.checkBox_LiuYu_Click);
            // 
            // checkBox_All
            // 
            this.checkBox_All.AutoSize = true;
            this.checkBox_All.Location = new System.Drawing.Point(0, 219);
            this.checkBox_All.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.checkBox_All.Name = "checkBox_All";
            this.checkBox_All.Size = new System.Drawing.Size(53, 19);
            this.checkBox_All.TabIndex = 7;
            this.checkBox_All.Text = "All";
            this.checkBox_All.UseVisualStyleBackColor = true;
            this.checkBox_All.CheckedChanged += new System.EventHandler(this.checkBox_All_CheckedChanged);
            // 
            // textBox
            // 
            this.textBox.Location = new System.Drawing.Point(0, 244);
            this.textBox.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.textBox.Name = "textBox";
            this.textBox.Size = new System.Drawing.Size(108, 25);
            this.textBox.TabIndex = 10;
            // 
            // radioButton_Woman
            // 
            this.radioButton_Woman.AutoSize = true;
            this.radioButton_Woman.Location = new System.Drawing.Point(63, 282);
            this.radioButton_Woman.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.radioButton_Woman.Name = "radioButton_Woman";
            this.radioButton_Woman.Size = new System.Drawing.Size(43, 19);
            this.radioButton_Woman.TabIndex = 1;
            this.radioButton_Woman.Text = "女";
            this.radioButton_Woman.UseVisualStyleBackColor = true;
            this.radioButton_Woman.CheckedChanged += new System.EventHandler(this.radioButton_CheckedChanged);
            // 
            // radioButton_Man
            // 
            this.radioButton_Man.AutoSize = true;
            this.radioButton_Man.Location = new System.Drawing.Point(8, 282);
            this.radioButton_Man.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.radioButton_Man.Name = "radioButton_Man";
            this.radioButton_Man.Size = new System.Drawing.Size(43, 19);
            this.radioButton_Man.TabIndex = 0;
            this.radioButton_Man.TabStop = true;
            this.radioButton_Man.Text = "男";
            this.radioButton_Man.UseVisualStyleBackColor = true;
            this.radioButton_Man.CheckedChanged += new System.EventHandler(this.radioButton_CheckedChanged);
            // 
            // tabControl
            // 
            this.tabControl.Controls.Add(this.tabPage_Food);
            this.tabControl.Controls.Add(this.tabPage_Hobby);
            this.tabControl.Location = new System.Drawing.Point(117, 154);
            this.tabControl.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.tabControl.Name = "tabControl";
            this.tabControl.SelectedIndex = 0;
            this.tabControl.Size = new System.Drawing.Size(139, 80);
            this.tabControl.TabIndex = 11;
            // 
            // tabPage_Food
            // 
            this.tabPage_Food.Controls.Add(this.btnMilk);
            this.tabPage_Food.Location = new System.Drawing.Point(4, 25);
            this.tabPage_Food.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.tabPage_Food.Name = "tabPage_Food";
            this.tabPage_Food.Padding = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.tabPage_Food.Size = new System.Drawing.Size(131, 51);
            this.tabPage_Food.TabIndex = 0;
            this.tabPage_Food.Text = "食物";
            this.tabPage_Food.UseVisualStyleBackColor = true;
            // 
            // btnMilk
            // 
            this.btnMilk.Location = new System.Drawing.Point(13, 11);
            this.btnMilk.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.btnMilk.Name = "btnMilk";
            this.btnMilk.Size = new System.Drawing.Size(100, 29);
            this.btnMilk.TabIndex = 0;
            this.btnMilk.Text = "牛奶";
            this.btnMilk.UseVisualStyleBackColor = true;
            // 
            // tabPage_Hobby
            // 
            this.tabPage_Hobby.Controls.Add(this.btnRead);
            this.tabPage_Hobby.Location = new System.Drawing.Point(4, 25);
            this.tabPage_Hobby.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.tabPage_Hobby.Name = "tabPage_Hobby";
            this.tabPage_Hobby.Padding = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.tabPage_Hobby.Size = new System.Drawing.Size(131, 51);
            this.tabPage_Hobby.TabIndex = 1;
            this.tabPage_Hobby.Text = "爱好";
            this.tabPage_Hobby.UseVisualStyleBackColor = true;
            // 
            // btnRead
            // 
            this.btnRead.Location = new System.Drawing.Point(15, 11);
            this.btnRead.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.btnRead.Name = "btnRead";
            this.btnRead.Size = new System.Drawing.Size(100, 29);
            this.btnRead.TabIndex = 5;
            this.btnRead.Text = "读书";
            this.btnRead.UseVisualStyleBackColor = true;
            // 
            // treeView
            // 
            this.treeView.Location = new System.Drawing.Point(117, 31);
            this.treeView.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.treeView.Name = "treeView";
            this.treeView.Size = new System.Drawing.Size(137, 114);
            this.treeView.TabIndex = 12;
            this.treeView.AfterSelect += new System.Windows.Forms.TreeViewEventHandler(this.treeView_AfterSelect);
            // 
            // btnSelectColor
            // 
            this.btnSelectColor.Location = new System.Drawing.Point(117, 239);
            this.btnSelectColor.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.btnSelectColor.Name = "btnSelectColor";
            this.btnSelectColor.Size = new System.Drawing.Size(133, 31);
            this.btnSelectColor.TabIndex = 13;
            this.btnSelectColor.Text = "颜色选择对话框";
            this.btnSelectColor.UseVisualStyleBackColor = true;
            this.btnSelectColor.Click += new System.EventHandler(this.btnSelectColor_Click);
            // 
            // btnSelectFont
            // 
            this.btnSelectFont.Location = new System.Drawing.Point(117, 278);
            this.btnSelectFont.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.btnSelectFont.Name = "btnSelectFont";
            this.btnSelectFont.Size = new System.Drawing.Size(133, 31);
            this.btnSelectFont.TabIndex = 14;
            this.btnSelectFont.Text = "字体选择对话框";
            this.btnSelectFont.UseVisualStyleBackColor = true;
            this.btnSelectFont.Click += new System.EventHandler(this.btnSelectFont_Click);
            // 
            // openFileDialog
            // 
            this.openFileDialog.Filter = "Word文档|*.doc|所有文件|*.*";
            this.openFileDialog.InitialDirectory = "C:\\";
            this.openFileDialog.Multiselect = true;
            // 
            // btnOpenFile
            // 
            this.btnOpenFile.Location = new System.Drawing.Point(0, 316);
            this.btnOpenFile.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.btnOpenFile.Name = "btnOpenFile";
            this.btnOpenFile.Size = new System.Drawing.Size(109, 29);
            this.btnOpenFile.TabIndex = 15;
            this.btnOpenFile.Text = "打开文件";
            this.btnOpenFile.UseVisualStyleBackColor = true;
            this.btnOpenFile.Click += new System.EventHandler(this.btnOpenFile_Click);
            // 
            // btnSaveFile
            // 
            this.btnSaveFile.Location = new System.Drawing.Point(117, 316);
            this.btnSaveFile.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.btnSaveFile.Name = "btnSaveFile";
            this.btnSaveFile.Size = new System.Drawing.Size(133, 29);
            this.btnSaveFile.TabIndex = 16;
            this.btnSaveFile.Text = "保存文件对话框";
            this.btnSaveFile.UseVisualStyleBackColor = true;
            this.btnSaveFile.Click += new System.EventHandler(this.btnSaveFile_Click);
            // 
            // saveFileDialog
            // 
            this.saveFileDialog.Filter = "文本文件|*.txt";
            this.saveFileDialog.InitialDirectory = "C:\\";
            // 
            // contextMenuStrip
            // 
            this.contextMenuStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.学校ToolStripMenuItem,
            this.家庭ToolStripMenuItem});
            this.contextMenuStrip.Name = "contextMenuStrip";
            this.contextMenuStrip.Size = new System.Drawing.Size(109, 52);
            // 
            // 学校ToolStripMenuItem
            // 
            this.学校ToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.同学ToolStripMenuItem,
            this.老师ToolStripMenuItem});
            this.学校ToolStripMenuItem.Name = "学校ToolStripMenuItem";
            this.学校ToolStripMenuItem.Size = new System.Drawing.Size(108, 24);
            this.学校ToolStripMenuItem.Text = "学校";
            // 
            // 同学ToolStripMenuItem
            // 
            this.同学ToolStripMenuItem.Name = "同学ToolStripMenuItem";
            this.同学ToolStripMenuItem.Size = new System.Drawing.Size(108, 24);
            this.同学ToolStripMenuItem.Text = "同学";
            this.同学ToolStripMenuItem.Click += new System.EventHandler(this.同学ToolStripMenuItem_Click);
            // 
            // 老师ToolStripMenuItem
            // 
            this.老师ToolStripMenuItem.Name = "老师ToolStripMenuItem";
            this.老师ToolStripMenuItem.Size = new System.Drawing.Size(108, 24);
            this.老师ToolStripMenuItem.Text = "老师";
            // 
            // 家庭ToolStripMenuItem
            // 
            this.家庭ToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.爸妈ToolStripMenuItem});
            this.家庭ToolStripMenuItem.Name = "家庭ToolStripMenuItem";
            this.家庭ToolStripMenuItem.Size = new System.Drawing.Size(108, 24);
            this.家庭ToolStripMenuItem.Text = "家庭";
            // 
            // 爸妈ToolStripMenuItem
            // 
            this.爸妈ToolStripMenuItem.Name = "爸妈ToolStripMenuItem";
            this.爸妈ToolStripMenuItem.Size = new System.Drawing.Size(108, 24);
            this.爸妈ToolStripMenuItem.Text = "爸妈";
            // 
            // menuStrip
            // 
            this.menuStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.开始ToolStripMenuItem});
            this.menuStrip.Location = new System.Drawing.Point(0, 0);
            this.menuStrip.Name = "menuStrip";
            this.menuStrip.Padding = new System.Windows.Forms.Padding(8, 2, 0, 2);
            this.menuStrip.Size = new System.Drawing.Size(659, 28);
            this.menuStrip.TabIndex = 17;
            this.menuStrip.Text = "menuStrip1";
            // 
            // 开始ToolStripMenuItem
            // 
            this.开始ToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.程序ToolStripMenuItem});
            this.开始ToolStripMenuItem.Name = "开始ToolStripMenuItem";
            this.开始ToolStripMenuItem.Size = new System.Drawing.Size(51, 24);
            this.开始ToolStripMenuItem.Text = "开始";
            // 
            // 程序ToolStripMenuItem
            // 
            this.程序ToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.附件ToolStripMenuItem});
            this.程序ToolStripMenuItem.Name = "程序ToolStripMenuItem";
            this.程序ToolStripMenuItem.Size = new System.Drawing.Size(152, 24);
            this.程序ToolStripMenuItem.Text = "程序";
            // 
            // 附件ToolStripMenuItem
            // 
            this.附件ToolStripMenuItem.Name = "附件ToolStripMenuItem";
            this.附件ToolStripMenuItem.Size = new System.Drawing.Size(108, 24);
            this.附件ToolStripMenuItem.Text = "附件";
            this.附件ToolStripMenuItem.Click += new System.EventHandler(this.附件ToolStripMenuItem_Click);
            // 
            // btnDrawTriangle
            // 
            this.btnDrawTriangle.Location = new System.Drawing.Point(264, 31);
            this.btnDrawTriangle.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.btnDrawTriangle.Name = "btnDrawTriangle";
            this.btnDrawTriangle.Size = new System.Drawing.Size(100, 29);
            this.btnDrawTriangle.TabIndex = 18;
            this.btnDrawTriangle.Text = "绘制三角形";
            this.btnDrawTriangle.UseVisualStyleBackColor = true;
            this.btnDrawTriangle.Click += new System.EventHandler(this.btnDrawTriangle_Click);
            // 
            // btnDrawEllipse
            // 
            this.btnDrawEllipse.Location = new System.Drawing.Point(264, 69);
            this.btnDrawEllipse.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.btnDrawEllipse.Name = "btnDrawEllipse";
            this.btnDrawEllipse.Size = new System.Drawing.Size(100, 29);
            this.btnDrawEllipse.TabIndex = 19;
            this.btnDrawEllipse.Text = "画椭圆";
            this.btnDrawEllipse.UseVisualStyleBackColor = true;
            this.btnDrawEllipse.Click += new System.EventHandler(this.btnDrawEllipse_Click);
            // 
            // btnCreateRegion
            // 
            this.btnCreateRegion.Location = new System.Drawing.Point(264, 108);
            this.btnCreateRegion.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.btnCreateRegion.Name = "btnCreateRegion";
            this.btnCreateRegion.Size = new System.Drawing.Size(100, 29);
            this.btnCreateRegion.TabIndex = 20;
            this.btnCreateRegion.Text = "创建区域";
            this.btnCreateRegion.UseVisualStyleBackColor = true;
            this.btnCreateRegion.Click += new System.EventHandler(this.btnCreateRegion_Click);
            // 
            // btnChangeBrush
            // 
            this.btnChangeBrush.Location = new System.Drawing.Point(264, 144);
            this.btnChangeBrush.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.btnChangeBrush.Name = "btnChangeBrush";
            this.btnChangeBrush.Size = new System.Drawing.Size(100, 29);
            this.btnChangeBrush.TabIndex = 21;
            this.btnChangeBrush.Text = "径向渐变";
            this.btnChangeBrush.UseVisualStyleBackColor = true;
            this.btnChangeBrush.Click += new System.EventHandler(this.btnChangeBrush_Click);
            // 
            // btnTextureFill
            // 
            this.btnTextureFill.Location = new System.Drawing.Point(264, 181);
            this.btnTextureFill.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.btnTextureFill.Name = "btnTextureFill";
            this.btnTextureFill.Size = new System.Drawing.Size(100, 29);
            this.btnTextureFill.TabIndex = 22;
            this.btnTextureFill.Text = "纹理画刷";
            this.btnTextureFill.UseVisualStyleBackColor = true;
            this.btnTextureFill.Click += new System.EventHandler(this.btnTextureFill_Click);
            // 
            // btnLinearChange
            // 
            this.btnLinearChange.Location = new System.Drawing.Point(265, 219);
            this.btnLinearChange.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.btnLinearChange.Name = "btnLinearChange";
            this.btnLinearChange.Size = new System.Drawing.Size(100, 29);
            this.btnLinearChange.TabIndex = 23;
            this.btnLinearChange.Text = "线性渐变";
            this.btnLinearChange.UseVisualStyleBackColor = true;
            this.btnLinearChange.Click += new System.EventHandler(this.btnLinearChange_Click);
            // 
            // btnShadowBrush
            // 
            this.btnShadowBrush.Location = new System.Drawing.Point(265, 256);
            this.btnShadowBrush.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.btnShadowBrush.Name = "btnShadowBrush";
            this.btnShadowBrush.Size = new System.Drawing.Size(100, 29);
            this.btnShadowBrush.TabIndex = 24;
            this.btnShadowBrush.Text = "阴影线画刷";
            this.btnShadowBrush.UseVisualStyleBackColor = true;
            this.btnShadowBrush.Click += new System.EventHandler(this.btnShadowBrush_Click);
            // 
            // NewForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(659, 366);
            this.ContextMenuStrip = this.contextMenuStrip;
            this.Controls.Add(this.btnShadowBrush);
            this.Controls.Add(this.btnLinearChange);
            this.Controls.Add(this.btnTextureFill);
            this.Controls.Add(this.btnChangeBrush);
            this.Controls.Add(this.btnCreateRegion);
            this.Controls.Add(this.btnDrawEllipse);
            this.Controls.Add(this.btnDrawTriangle);
            this.Controls.Add(this.menuStrip);
            this.Controls.Add(this.btnSaveFile);
            this.Controls.Add(this.btnOpenFile);
            this.Controls.Add(this.btnSelectFont);
            this.Controls.Add(this.btnSelectColor);
            this.Controls.Add(this.treeView);
            this.Controls.Add(this.tabControl);
            this.Controls.Add(this.textBox);
            this.Controls.Add(this.radioButton_Woman);
            this.Controls.Add(this.radioButton_Man);
            this.Controls.Add(this.checkBox_All);
            this.Controls.Add(this.checkBox_LiuYu);
            this.Controls.Add(this.checkBox_LiHua);
            this.Controls.Add(this.comboBox);
            this.Controls.Add(this.btnOKList);
            this.Controls.Add(this.listBox);
            this.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.Name = "NewForm";
            this.Text = "NewForm";
            this.Load += new System.EventHandler(this.NewForm_Load);
            this.tabControl.ResumeLayout(false);
            this.tabPage_Food.ResumeLayout(false);
            this.tabPage_Hobby.ResumeLayout(false);
            this.contextMenuStrip.ResumeLayout(false);
            this.menuStrip.ResumeLayout(false);
            this.menuStrip.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ListBox listBox;
        private System.Windows.Forms.Button btnOKList;
        private System.Windows.Forms.ComboBox comboBox;
        private System.Windows.Forms.CheckBox checkBox_LiHua;
        private System.Windows.Forms.CheckBox checkBox_LiuYu;
        private System.Windows.Forms.CheckBox checkBox_All;
        private System.Windows.Forms.TextBox textBox;
        private System.Windows.Forms.RadioButton radioButton_Woman;
        private System.Windows.Forms.RadioButton radioButton_Man;
        private System.Windows.Forms.TabControl tabControl;
        private System.Windows.Forms.TabPage tabPage_Food;
        private System.Windows.Forms.Button btnMilk;
        private System.Windows.Forms.TabPage tabPage_Hobby;
        private System.Windows.Forms.Button btnRead;
        private System.Windows.Forms.TreeView treeView;
        private System.Windows.Forms.Button btnSelectColor;
        private System.Windows.Forms.ColorDialog colorDialog;
        private System.Windows.Forms.Button btnSelectFont;
        private System.Windows.Forms.FontDialog fontDialog;
        private System.Windows.Forms.OpenFileDialog openFileDialog;
        private System.Windows.Forms.Button btnOpenFile;
        private System.Windows.Forms.Button btnSaveFile;
        private System.Windows.Forms.SaveFileDialog saveFileDialog;
        private System.Windows.Forms.ContextMenuStrip contextMenuStrip;
        private System.Windows.Forms.ToolStripMenuItem 学校ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 同学ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 老师ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 家庭ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 爸妈ToolStripMenuItem;
        private System.Windows.Forms.MenuStrip menuStrip;
        private System.Windows.Forms.ToolStripMenuItem 开始ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 程序ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 附件ToolStripMenuItem;
        private System.Windows.Forms.Button btnDrawTriangle;
        private System.Windows.Forms.Button btnDrawEllipse;
        private System.Windows.Forms.Button btnCreateRegion;
        private System.Windows.Forms.Button btnChangeBrush;
        private System.Windows.Forms.Button btnTextureFill;
        private System.Windows.Forms.Button btnLinearChange;
        private System.Windows.Forms.Button btnShadowBrush;
    }
}
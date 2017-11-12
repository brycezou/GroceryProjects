namespace clock
{
    partial class Form1
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
            this.components = new System.ComponentModel.Container();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.contextMenuStrip1 = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.样式ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.绿色ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.蓝色ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.金属ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.黄色ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.退出ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.contextMenuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // timer1
            // 
            this.timer1.Enabled = true;
            this.timer1.Interval = 1000;
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // contextMenuStrip1
            // 
            this.contextMenuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.样式ToolStripMenuItem,
            this.退出ToolStripMenuItem});
            this.contextMenuStrip1.Name = "contextMenuStrip1";
            this.contextMenuStrip1.Size = new System.Drawing.Size(101, 48);
            // 
            // 样式ToolStripMenuItem
            // 
            this.样式ToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.绿色ToolStripMenuItem,
            this.蓝色ToolStripMenuItem,
            this.金属ToolStripMenuItem,
            this.黄色ToolStripMenuItem});
            this.样式ToolStripMenuItem.Name = "样式ToolStripMenuItem";
            this.样式ToolStripMenuItem.Size = new System.Drawing.Size(100, 22);
            this.样式ToolStripMenuItem.Text = "样式";
            // 
            // 绿色ToolStripMenuItem
            // 
            this.绿色ToolStripMenuItem.Checked = true;
            this.绿色ToolStripMenuItem.CheckOnClick = true;
            this.绿色ToolStripMenuItem.CheckState = System.Windows.Forms.CheckState.Checked;
            this.绿色ToolStripMenuItem.Name = "绿色ToolStripMenuItem";
            this.绿色ToolStripMenuItem.Size = new System.Drawing.Size(100, 22);
            this.绿色ToolStripMenuItem.Text = "绿色";
            this.绿色ToolStripMenuItem.Click += new System.EventHandler(this.绿色ToolStripMenuItem_Click);
            // 
            // 蓝色ToolStripMenuItem
            // 
            this.蓝色ToolStripMenuItem.CheckOnClick = true;
            this.蓝色ToolStripMenuItem.Name = "蓝色ToolStripMenuItem";
            this.蓝色ToolStripMenuItem.Size = new System.Drawing.Size(100, 22);
            this.蓝色ToolStripMenuItem.Text = "蓝色";
            this.蓝色ToolStripMenuItem.Click += new System.EventHandler(this.蓝色ToolStripMenuItem_Click);
            // 
            // 金属ToolStripMenuItem
            // 
            this.金属ToolStripMenuItem.CheckOnClick = true;
            this.金属ToolStripMenuItem.Name = "金属ToolStripMenuItem";
            this.金属ToolStripMenuItem.Size = new System.Drawing.Size(100, 22);
            this.金属ToolStripMenuItem.Text = "金属";
            this.金属ToolStripMenuItem.Click += new System.EventHandler(this.金属ToolStripMenuItem_Click);
            // 
            // 黄色ToolStripMenuItem
            // 
            this.黄色ToolStripMenuItem.CheckOnClick = true;
            this.黄色ToolStripMenuItem.Name = "黄色ToolStripMenuItem";
            this.黄色ToolStripMenuItem.Size = new System.Drawing.Size(100, 22);
            this.黄色ToolStripMenuItem.Text = "黄色";
            this.黄色ToolStripMenuItem.Click += new System.EventHandler(this.黄色ToolStripMenuItem_Click);
            // 
            // 退出ToolStripMenuItem
            // 
            this.退出ToolStripMenuItem.Name = "退出ToolStripMenuItem";
            this.退出ToolStripMenuItem.Size = new System.Drawing.Size(100, 22);
            this.退出ToolStripMenuItem.Text = "退出";
            this.退出ToolStripMenuItem.Click += new System.EventHandler(this.退出ToolStripMenuItem_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(200, 200);
            this.ContextMenuStrip = this.contextMenuStrip1;
            this.ControlBox = false;
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.Name = "Form1";
            this.ShowInTaskbar = false;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.TopMost = true;
            this.MouseDown += new System.Windows.Forms.MouseEventHandler(this.Form1_MouseDown);
            this.contextMenuStrip1.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.ContextMenuStrip contextMenuStrip1;
        private System.Windows.Forms.ToolStripMenuItem 退出ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 样式ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 绿色ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 蓝色ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 金属ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 黄色ToolStripMenuItem;

    }
}


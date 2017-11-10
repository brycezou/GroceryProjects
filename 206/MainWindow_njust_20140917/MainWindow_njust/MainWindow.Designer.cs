namespace MainWindow_njust
{
    partial class MainWindow
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
            this.label_address = new System.Windows.Forms.Label();
            this.label_port = new System.Windows.Forms.Label();
            this.textBox_address = new System.Windows.Forms.TextBox();
            this.textBox_port = new System.Windows.Forms.TextBox();
            this.button_connect = new System.Windows.Forms.Button();
            this.button_parameter = new System.Windows.Forms.Button();
            this.button_grasp = new System.Windows.Forms.Button();
            this.button_restart = new System.Windows.Forms.Button();
            this.button_exit = new System.Windows.Forms.Button();
            this.label_Status = new System.Windows.Forms.Label();
            this.textBox_status = new System.Windows.Forms.TextBox();
            this.button_RunOnce = new System.Windows.Forms.Button();
            this.radioButton_BlueScreen = new System.Windows.Forms.RadioButton();
            this.radioButton_NormalLCD = new System.Windows.Forms.RadioButton();
            this.button_EnvironmentSetting = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // label_address
            // 
            this.label_address.AutoSize = true;
            this.label_address.Location = new System.Drawing.Point(12, 25);
            this.label_address.Name = "label_address";
            this.label_address.Size = new System.Drawing.Size(45, 15);
            this.label_address.TabIndex = 0;
            this.label_address.Text = "地址:";
            // 
            // label_port
            // 
            this.label_port.AutoSize = true;
            this.label_port.Location = new System.Drawing.Point(205, 25);
            this.label_port.Name = "label_port";
            this.label_port.Size = new System.Drawing.Size(45, 15);
            this.label_port.TabIndex = 1;
            this.label_port.Text = "端口:";
            // 
            // textBox_address
            // 
            this.textBox_address.Location = new System.Drawing.Point(60, 20);
            this.textBox_address.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.textBox_address.Name = "textBox_address";
            this.textBox_address.Size = new System.Drawing.Size(132, 25);
            this.textBox_address.TabIndex = 2;
            // 
            // textBox_port
            // 
            this.textBox_port.Location = new System.Drawing.Point(251, 20);
            this.textBox_port.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.textBox_port.Name = "textBox_port";
            this.textBox_port.Size = new System.Drawing.Size(77, 25);
            this.textBox_port.TabIndex = 3;
            // 
            // button_connect
            // 
            this.button_connect.Location = new System.Drawing.Point(15, 66);
            this.button_connect.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.button_connect.Name = "button_connect";
            this.button_connect.Size = new System.Drawing.Size(219, 48);
            this.button_connect.TabIndex = 4;
            this.button_connect.Text = "系统连接";
            this.button_connect.UseVisualStyleBackColor = true;
            this.button_connect.Click += new System.EventHandler(this.button_connect_Click);
            // 
            // button_parameter
            // 
            this.button_parameter.Location = new System.Drawing.Point(147, 129);
            this.button_parameter.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.button_parameter.Name = "button_parameter";
            this.button_parameter.Size = new System.Drawing.Size(183, 48);
            this.button_parameter.TabIndex = 5;
            this.button_parameter.Text = "参数设置";
            this.button_parameter.UseVisualStyleBackColor = true;
            this.button_parameter.Click += new System.EventHandler(this.button_parameter_Click);
            // 
            // button_grasp
            // 
            this.button_grasp.Location = new System.Drawing.Point(15, 192);
            this.button_grasp.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.button_grasp.Name = "button_grasp";
            this.button_grasp.Size = new System.Drawing.Size(315, 48);
            this.button_grasp.TabIndex = 6;
            this.button_grasp.Text = "图像抓取";
            this.button_grasp.UseVisualStyleBackColor = true;
            this.button_grasp.Click += new System.EventHandler(this.button_grasp_Click);
            // 
            // button_restart
            // 
            this.button_restart.Location = new System.Drawing.Point(15, 255);
            this.button_restart.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.button_restart.Name = "button_restart";
            this.button_restart.Size = new System.Drawing.Size(315, 48);
            this.button_restart.TabIndex = 7;
            this.button_restart.Text = "服务器重启";
            this.button_restart.UseVisualStyleBackColor = true;
            this.button_restart.Click += new System.EventHandler(this.button_restart_Click);
            // 
            // button_exit
            // 
            this.button_exit.Location = new System.Drawing.Point(15, 317);
            this.button_exit.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.button_exit.Name = "button_exit";
            this.button_exit.Size = new System.Drawing.Size(315, 48);
            this.button_exit.TabIndex = 8;
            this.button_exit.Text = "程序退出";
            this.button_exit.UseVisualStyleBackColor = true;
            this.button_exit.Click += new System.EventHandler(this.button_exit_Click);
            // 
            // label_Status
            // 
            this.label_Status.AutoSize = true;
            this.label_Status.Location = new System.Drawing.Point(15, 388);
            this.label_Status.Name = "label_Status";
            this.label_Status.Size = new System.Drawing.Size(75, 15);
            this.label_Status.TabIndex = 9;
            this.label_Status.Text = "系统状态:";
            // 
            // textBox_status
            // 
            this.textBox_status.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.textBox_status.Location = new System.Drawing.Point(97, 386);
            this.textBox_status.Margin = new System.Windows.Forms.Padding(4);
            this.textBox_status.Name = "textBox_status";
            this.textBox_status.ReadOnly = true;
            this.textBox_status.Size = new System.Drawing.Size(149, 18);
            this.textBox_status.TabIndex = 10;
            // 
            // button_RunOnce
            // 
            this.button_RunOnce.Location = new System.Drawing.Point(15, 129);
            this.button_RunOnce.Margin = new System.Windows.Forms.Padding(4);
            this.button_RunOnce.Name = "button_RunOnce";
            this.button_RunOnce.Size = new System.Drawing.Size(113, 48);
            this.button_RunOnce.TabIndex = 11;
            this.button_RunOnce.Text = "运行一次";
            this.button_RunOnce.UseVisualStyleBackColor = true;
            this.button_RunOnce.Click += new System.EventHandler(this.button__Click);
            // 
            // radioButton_BlueScreen
            // 
            this.radioButton_BlueScreen.AutoSize = true;
            this.radioButton_BlueScreen.Location = new System.Drawing.Point(252, 94);
            this.radioButton_BlueScreen.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.radioButton_BlueScreen.Name = "radioButton_BlueScreen";
            this.radioButton_BlueScreen.Size = new System.Drawing.Size(73, 19);
            this.radioButton_BlueScreen.TabIndex = 12;
            this.radioButton_BlueScreen.TabStop = true;
            this.radioButton_BlueScreen.Text = "蓝相屏";
            this.radioButton_BlueScreen.UseVisualStyleBackColor = true;
            this.radioButton_BlueScreen.CheckedChanged += new System.EventHandler(this.radioCheckChanged);
            // 
            // radioButton_NormalLCD
            // 
            this.radioButton_NormalLCD.AutoSize = true;
            this.radioButton_NormalLCD.Location = new System.Drawing.Point(252, 69);
            this.radioButton_NormalLCD.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.radioButton_NormalLCD.Name = "radioButton_NormalLCD";
            this.radioButton_NormalLCD.Size = new System.Drawing.Size(73, 19);
            this.radioButton_NormalLCD.TabIndex = 13;
            this.radioButton_NormalLCD.TabStop = true;
            this.radioButton_NormalLCD.Text = "工业屏";
            this.radioButton_NormalLCD.UseVisualStyleBackColor = true;
            // 
            // button_EnvironmentSetting
            // 
            this.button_EnvironmentSetting.Location = new System.Drawing.Point(255, 384);
            this.button_EnvironmentSetting.Name = "button_EnvironmentSetting";
            this.button_EnvironmentSetting.Size = new System.Drawing.Size(75, 23);
            this.button_EnvironmentSetting.TabIndex = 14;
            this.button_EnvironmentSetting.Text = "环境设置";
            this.button_EnvironmentSetting.UseVisualStyleBackColor = true;
            this.button_EnvironmentSetting.Click += new System.EventHandler(this.button_EnvironmentSetting_Click);
            // 
            // MainWindow
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(344, 415);
            this.Controls.Add(this.button_EnvironmentSetting);
            this.Controls.Add(this.radioButton_BlueScreen);
            this.Controls.Add(this.radioButton_NormalLCD);
            this.Controls.Add(this.button_RunOnce);
            this.Controls.Add(this.textBox_status);
            this.Controls.Add(this.label_Status);
            this.Controls.Add(this.button_exit);
            this.Controls.Add(this.button_restart);
            this.Controls.Add(this.button_grasp);
            this.Controls.Add(this.button_parameter);
            this.Controls.Add(this.button_connect);
            this.Controls.Add(this.textBox_port);
            this.Controls.Add(this.textBox_address);
            this.Controls.Add(this.label_port);
            this.Controls.Add(this.label_address);
            this.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.MaximumSize = new System.Drawing.Size(362, 460);
            this.MinimumSize = new System.Drawing.Size(362, 460);
            this.Name = "MainWindow";
            this.Text = "MainWindow";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label_address;
        private System.Windows.Forms.Label label_port;
        private System.Windows.Forms.TextBox textBox_address;
        private System.Windows.Forms.TextBox textBox_port;
        private System.Windows.Forms.Button button_connect;
        private System.Windows.Forms.Button button_parameter;
        private System.Windows.Forms.Button button_grasp;
        private System.Windows.Forms.Button button_restart;
        private System.Windows.Forms.Button button_exit;
        private System.Windows.Forms.Label label_Status;
        private System.Windows.Forms.TextBox textBox_status;
        private System.Windows.Forms.Button button_RunOnce;
        private System.Windows.Forms.RadioButton radioButton_BlueScreen;
        private System.Windows.Forms.RadioButton radioButton_NormalLCD;
        private System.Windows.Forms.Button button_EnvironmentSetting;
    }
}


namespace FlameAreaCalcu
{
    partial class AboutForm
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
            this.label_software_name = new System.Windows.Forms.Label();
            this.label_company_name = new System.Windows.Forms.Label();
            this.label_name = new System.Windows.Forms.Label();
            this.label_company = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // label_software_name
            // 
            this.label_software_name.AutoSize = true;
            this.label_software_name.Font = new System.Drawing.Font("Times New Roman", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label_software_name.Location = new System.Drawing.Point(138, 24);
            this.label_software_name.Name = "label_software_name";
            this.label_software_name.Size = new System.Drawing.Size(200, 17);
            this.label_software_name.TabIndex = 0;
            this.label_software_name.Text = "膛口火焰面积计算分析软件";
            // 
            // label_company_name
            // 
            this.label_company_name.AutoSize = true;
            this.label_company_name.Font = new System.Drawing.Font("Times New Roman", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label_company_name.Location = new System.Drawing.Point(138, 61);
            this.label_company_name.Name = "label_company_name";
            this.label_company_name.Size = new System.Drawing.Size(104, 17);
            this.label_company_name.TabIndex = 1;
            this.label_company_name.Text = "南京理工大学";
            // 
            // label_name
            // 
            this.label_name.AutoSize = true;
            this.label_name.Font = new System.Drawing.Font("Times New Roman", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label_name.Location = new System.Drawing.Point(34, 24);
            this.label_name.Name = "label_name";
            this.label_name.Size = new System.Drawing.Size(56, 17);
            this.label_name.TabIndex = 2;
            this.label_name.Text = "名称：";
            // 
            // label_company
            // 
            this.label_company.AutoSize = true;
            this.label_company.Font = new System.Drawing.Font("Times New Roman", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label_company.Location = new System.Drawing.Point(34, 61);
            this.label_company.Name = "label_company";
            this.label_company.Size = new System.Drawing.Size(56, 17);
            this.label_company.TabIndex = 3;
            this.label_company.Text = "组织：";
            // 
            // AboutForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(592, 105);
            this.Controls.Add(this.label_company);
            this.Controls.Add(this.label_name);
            this.Controls.Add(this.label_company_name);
            this.Controls.Add(this.label_software_name);
            this.MaximizeBox = false;
            this.MaximumSize = new System.Drawing.Size(610, 150);
            this.MinimizeBox = false;
            this.MinimumSize = new System.Drawing.Size(610, 150);
            this.Name = "AboutForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "关于";
            this.Load += new System.EventHandler(this.AboutForm_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label_software_name;
        private System.Windows.Forms.Label label_company_name;
        private System.Windows.Forms.Label label_name;
        private System.Windows.Forms.Label label_company;
    }
}
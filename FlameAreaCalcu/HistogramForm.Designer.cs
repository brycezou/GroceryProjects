namespace FlameAreaCalcu
{
    partial class HistogramForm
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
            this.hScrollBar_low = new System.Windows.Forms.HScrollBar();
            this.hScrollBar_high = new System.Windows.Forms.HScrollBar();
            this.pictureBox_histogram = new System.Windows.Forms.PictureBox();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox_histogram)).BeginInit();
            this.SuspendLayout();
            // 
            // hScrollBar_low
            // 
            this.hScrollBar_low.Location = new System.Drawing.Point(3, 333);
            this.hScrollBar_low.Maximum = 255;
            this.hScrollBar_low.Name = "hScrollBar_low";
            this.hScrollBar_low.Size = new System.Drawing.Size(529, 21);
            this.hScrollBar_low.TabIndex = 0;
            this.hScrollBar_low.Value = 1;
            this.hScrollBar_low.ValueChanged += new System.EventHandler(this.hScrollBar_ValueChanged);
            // 
            // hScrollBar_high
            // 
            this.hScrollBar_high.Location = new System.Drawing.Point(3, 359);
            this.hScrollBar_high.Maximum = 255;
            this.hScrollBar_high.Name = "hScrollBar_high";
            this.hScrollBar_high.Size = new System.Drawing.Size(529, 21);
            this.hScrollBar_high.TabIndex = 1;
            this.hScrollBar_high.Value = 2;
            this.hScrollBar_high.ValueChanged += new System.EventHandler(this.hScrollBar_ValueChanged);
            // 
            // pictureBox_histogram
            // 
            this.pictureBox_histogram.Location = new System.Drawing.Point(3, 4);
            this.pictureBox_histogram.Name = "pictureBox_histogram";
            this.pictureBox_histogram.Size = new System.Drawing.Size(529, 320);
            this.pictureBox_histogram.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.pictureBox_histogram.TabIndex = 2;
            this.pictureBox_histogram.TabStop = false;
            // 
            // HistogramForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(536, 385);
            this.Controls.Add(this.pictureBox_histogram);
            this.Controls.Add(this.hScrollBar_high);
            this.Controls.Add(this.hScrollBar_low);
            this.MaximizeBox = false;
            this.MaximumSize = new System.Drawing.Size(554, 430);
            this.MinimizeBox = false;
            this.MinimumSize = new System.Drawing.Size(554, 430);
            this.Name = "HistogramForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "HistogramForm";
            this.Load += new System.EventHandler(this.HistogramForm_Load);
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox_histogram)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.HScrollBar hScrollBar_low;
        private System.Windows.Forms.HScrollBar hScrollBar_high;
        private System.Windows.Forms.PictureBox pictureBox_histogram;
    }
}
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace FlameAreaCalcu
{
    public partial class AboutForm : Form
    {
        public AboutForm()
        {
            InitializeComponent();
        }

        private void AboutForm_Load(object sender, EventArgs e)
        {
            LanguageControl.SetLanguage();
            this.Text = LanguageControl.STR_ABOUT_FORM;
            this.label_name.Text = LanguageControl.STR_ABOUT_NAME;
            this.label_software_name.Text = LanguageControl.STR_ABOUT__SOFTWARE_NAME;
            this.label_company.Text = LanguageControl.STR_ABOUT_COMPANY;
            this.label_company_name.Text = LanguageControl.STR_ABOUT__COMPANY_NAME;
        }
    }
}

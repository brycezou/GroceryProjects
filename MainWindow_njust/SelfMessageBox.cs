using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace MainWindow_njust
{
    public partial class SelfMessageBox : Form
    {
        public ClientSocket m_clientSocket = null;

        public SelfMessageBox(ClientSocket clntSocket)
        {
            InitializeComponent();
            m_clientSocket = clntSocket;
        }

        private void button_OK_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void button_set_Click(object sender, EventArgs e)
        {
            this.Hide();
            EnviromentSelectionForm esf = new EnviromentSelectionForm(m_clientSocket);
            esf.ShowDialog(this.ParentForm);
            this.Close();
        }
    }
}

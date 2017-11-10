using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;

namespace MainWindow_njust
{
    static class Program
    {
        /// <summary>
        /// 应用程序的主入口点。
        /// </summary>
        [STAThread]
        static void Main() //自动生成的代码
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new MainWindow());
        }
    }
}

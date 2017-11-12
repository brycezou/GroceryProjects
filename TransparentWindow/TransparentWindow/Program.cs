using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;
using System.Threading;

namespace TransparentWindow
{
    static class Program
    {
        /// <summary>
        /// 应用程序的主入口点。
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            //Application.Run(new MainWindow());
            //下面是单实例运行代码
            bool bIsNotRunning;
            using (Mutex mutex = new Mutex(true, Application.ProductName, out bIsNotRunning))
            {
                if (bIsNotRunning)    
                    Application.Run(new MainWindow());
                else
                    System.Environment.Exit(1);
            }

        }
    }
}

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace FlameAreaCalcu
{
    class LanguageControl
    {
        public static bool m_bChinese = true;
        //图像上的“面积”二字
        public static string PIC_AREA;
        //主界面上的字符串
        public static string STR_MAIN_FORM_NAME;
        public static string STR_MENU_FILE;
        public static string STR_MENU_ANALYZE;
        public static string STR_MENU_LANGUAGE;
        public static string STR_MENU_ABOUT;
        public static string STR_MENU_OPEN;
        public static string STR_MENU_SAVE_AS;
        public static string STR_MENU_SAVE_DATA;
        public static string STR_MENU_PRINT_IMAGE;
        public static string STR_MENU_CLOSE;
        public static string STR_MENU_EXIT;
        public static string STR_MENU_MEASURE_DISTANCE;
        public static string STR_MENU_MEASURE_AREA;
        public static string STR_MENU_CALIBRATE;
        //直方图窗口界面
        public static string STR_HISOGRAM_FORM_NAME;
        //标定界面上的字符串
        public static string STR_CALIBRATE_DIP;
        public static string STR_CALIBRATE_KD;
        public static string STR_CALIBRATE_UOL;
        public static string STR_CALIBRATE_READ_IMAGE;
        public static string STR_CALIBRATE_CREATE_FILE;
        public static string STR_CALIBRATE_LOAD_FILE;
        public static string STR_CALIBRATE_PERPIXEL_LENGTH; 
        public static string STR_CALIBRATE_SCALE_VALUE;
        public static string STR_CALIBRATE_CANCEL;
        public static string STR_CALIBRATE_HELP;
        public static string STR_CALIBRATE_OK;
        public static string STR_CALIBRATE_FORM_NAME;
        //关于对话框上的字符串
        public static string STR_ABOUT_FORM;
        public static string STR_ABOUT_NAME;
        public static string STR_ABOUT_COMPANY;
        public static string STR_ABOUT__SOFTWARE_NAME;
        public static string STR_ABOUT__COMPANY_NAME;
        //主界面状态栏和消息对话框
        public static string MSG_STATUS_LABEL;       //未标定
        public static string MSG_STATUS_LABEL2;     //已标定
        public static string MSG_ILLEGAL_INPUT;
        public static string MSG_LINE_LENGTH1;
        public static string MSG_LINE_LENGTH2;
        public static string MSG_READ_IMAGE_FAILED;
        public static string MSG_SAVE_SUCCESSFULLY;
        public static string MSG_SAVE_FILE_FAILED;
        public static string MSG_IF_EXIT;
        public static string MSG_NOTICE;
        //标定界面消息对话框
        public static string MSG_CALIBRATE_FIRST;
        public static string MSG_LOAD_SUCCESSFULLY;


        LanguageControl()   {}

        public static void SetLanguage()
        {
            SetMainFormLanguage();
            SetScaleFormLanguage();
            SetAboutFormLanguage();
            SetMainFormMessageBoxLanguage();
            SetScaleFormMessageBoxLanguage();

            //SetMainFormLanguage_F();
            //SetScaleFormLanguage_F();
            //SetAboutFormLanguage_F();
            //SetMainFormMessageBoxLanguage_F();
            //SetScaleFormMessageBoxLanguage_F();
        }

        //中英文切换
        private static void SetMainFormLanguage()
        {
            PIC_AREA = m_bChinese ? "面积：" : "Area：";
            STR_MAIN_FORM_NAME = m_bChinese ? "膛口火焰面积计算分析软件" : "Flame Area Analysis Tool";
            STR_MENU_FILE = m_bChinese ? "文件" : "File";
            STR_MENU_ANALYZE = m_bChinese ? "分析" : "Analyze";
            STR_MENU_LANGUAGE = m_bChinese ? "语言" : "Language";
            STR_MENU_ABOUT = m_bChinese ? "关于" : "About";

            STR_MENU_OPEN = m_bChinese ? "打开" : "Open";
            STR_MENU_SAVE_AS = m_bChinese ? "另存为" : "Save As";
            STR_MENU_SAVE_DATA = m_bChinese ? "保存数据" : "Save Data";
            STR_MENU_PRINT_IMAGE = m_bChinese ? "打印图像" : "Print Image";
            STR_MENU_CLOSE = m_bChinese ? "关闭" : "Close";
            STR_MENU_EXIT = m_bChinese ? "退出" : "Exit";

            STR_MENU_MEASURE_DISTANCE = m_bChinese ? "测量距离" : "Measure Distance";
            STR_MENU_MEASURE_AREA = m_bChinese ? "测量面积" : "Measure Area";
            STR_MENU_CALIBRATE = m_bChinese ? "标定" : "Calibrate";
            STR_HISOGRAM_FORM_NAME = m_bChinese ? "直方图" : "Histogram"; ;
        }
        private static void SetScaleFormLanguage()
        {
            STR_CALIBRATE_FORM_NAME = m_bChinese ? "标定窗口" : "Calibration Window";
            STR_CALIBRATE_DIP = m_bChinese ? "像素距离" : "Distance in pixels";
            STR_CALIBRATE_KD = m_bChinese ? "实际距离" : "Known distance";
            STR_CALIBRATE_UOL = m_bChinese ? "长度单位" : "Unit of length";
            STR_CALIBRATE_READ_IMAGE = m_bChinese ? "读入标定图像" : "Read image";
            STR_CALIBRATE_CREATE_FILE = m_bChinese ? "生成标定文件" : "Save to file";
            STR_CALIBRATE_LOAD_FILE = m_bChinese ? "导入标定文件" : "Load from file";
            STR_CALIBRATE_PERPIXEL_LENGTH = m_bChinese ? "单位像素长度" : "Per pixel length";
            STR_CALIBRATE_SCALE_VALUE = m_bChinese ? "<无>" : "<none>";
            STR_CALIBRATE_CANCEL = m_bChinese ? "取消" : "Cancel";
            STR_CALIBRATE_HELP = m_bChinese ? "帮助" : "Help";
            STR_CALIBRATE_OK = m_bChinese ? "确定" : "OK";
        }
        private static void SetAboutFormLanguage()
        {
            STR_ABOUT_FORM = m_bChinese ? "关于" : "About";
            STR_ABOUT_NAME = m_bChinese ? "名称：" : "Name:";
            STR_ABOUT_COMPANY = m_bChinese ? "组织：" : "Company:";
            STR_ABOUT__SOFTWARE_NAME = m_bChinese ? "膛口火焰面积计算分析软件" : "Flame Area Analysis Tool";
            STR_ABOUT__COMPANY_NAME = m_bChinese ? "南京理工大学" : "Nanjing University of Sci. and Tech."; 
        }
        private static void SetMainFormMessageBoxLanguage()
        {
            MSG_STATUS_LABEL = m_bChinese ? "未标定，比例尺为：1.00" : "Need to be calibrated, present scale : 1.00";
            MSG_STATUS_LABEL2 = m_bChinese ? "已标定，比例尺为：" : "Calibrated, present scale : ";
            MSG_ILLEGAL_INPUT = m_bChinese ? "非法输入!" : "Illegal input!";
            MSG_LINE_LENGTH1 = m_bChinese ? "线段1长度" : "Segment length 1";
            MSG_LINE_LENGTH2 = m_bChinese ? "线段2长度" : "Segment length 2";
            MSG_READ_IMAGE_FAILED = m_bChinese ? "读取图像失败!" : "Read image failed!";
            MSG_IF_EXIT = m_bChinese ? "确定退出吗?" : "Are you sure to quit?";
            MSG_NOTICE = m_bChinese ? "提示" : "Notice";
            MSG_SAVE_SUCCESSFULLY = m_bChinese ? "保存成功!" : "Save sucessfully!";
            MSG_SAVE_FILE_FAILED = m_bChinese ? "保存文件失败!" : "Save file failed!";
        }
        private static void SetScaleFormMessageBoxLanguage()
        {
            MSG_CALIBRATE_FIRST = m_bChinese ? "请先进行标定!" : "Please calibrate first!";
            MSG_LOAD_SUCCESSFULLY = m_bChinese ? "导入成功!" : "Load sucessfully!";
        }

        //中法文切换
        private static void SetMainFormLanguage_F()
        {
            PIC_AREA = m_bChinese ? "面积：" : "La surface：";
            STR_MAIN_FORM_NAME = m_bChinese ? "膛口火焰面积计算分析软件" : "Logiciel de calcul et d'analyse de la surface de la flamme de bouche";
            STR_MENU_FILE = m_bChinese ? "文件" : "Le fichier";
            STR_MENU_ANALYZE = m_bChinese ? "分析" : "Analyser";
            STR_MENU_LANGUAGE = m_bChinese ? "语言" : "La langue";
            STR_MENU_ABOUT = m_bChinese ? "关于" : "Concernant";

            STR_MENU_OPEN = m_bChinese ? "打开" : "Ouvrir";
            STR_MENU_SAVE_AS = m_bChinese ? "另存为" : "Enregistrer sous";
            STR_MENU_SAVE_DATA = m_bChinese ? "保存数据" : "Conserver les données";
            STR_MENU_CLOSE = m_bChinese ? "关闭" : "Fermer";
            STR_MENU_EXIT = m_bChinese ? "退出" : "Quitter";

            STR_MENU_MEASURE_DISTANCE = m_bChinese ? "测量距离" : "Mesurer la distance";
            STR_MENU_MEASURE_AREA = m_bChinese ? "测量面积" : "Mesurer la surface";
            STR_MENU_CALIBRATE = m_bChinese ? "标定" : "Calibrer";
        }
        private static void SetScaleFormLanguage_F()
        {
            STR_CALIBRATE_FORM_NAME = m_bChinese ? "标定窗口" : "Fenêtre de la calibration";
            STR_CALIBRATE_DIP = m_bChinese ? "像素距离" : "La distance de pixels";
            STR_CALIBRATE_KD = m_bChinese ? "实际距离" : "La distance réelle";
            STR_CALIBRATE_UOL = m_bChinese ? "长度单位" : "L'unité de distance";
            STR_CALIBRATE_READ_IMAGE = m_bChinese ? "读入标定图像" : "Ouvrir l’image de calibration";
            STR_CALIBRATE_CREATE_FILE = m_bChinese ? "生成标定文件" : "Générer le fichier de calibration";
            STR_CALIBRATE_LOAD_FILE = m_bChinese ? "导入标定文件" : "Importer le fichier de calibration";
            STR_CALIBRATE_PERPIXEL_LENGTH = m_bChinese ? "单位像素长度" : "La longueur de pixel unitaire";
            STR_CALIBRATE_SCALE_VALUE = m_bChinese ? "<无>" : "<Non>";
            STR_CALIBRATE_CANCEL = m_bChinese ? "取消" : "Annuler";
            STR_CALIBRATE_HELP = m_bChinese ? "帮助" : "Aide";
            STR_CALIBRATE_OK = m_bChinese ? "确定" : "Confirmer";
        }
        private static void SetAboutFormLanguage_F()
        {
            STR_ABOUT_FORM = m_bChinese ? "关于" : "Concernant";
            STR_ABOUT_NAME = m_bChinese ? "名称：" : "Nom:";
            STR_ABOUT_COMPANY = m_bChinese ? "组织：" : "Organisation:";
            STR_ABOUT__SOFTWARE_NAME = m_bChinese ? "膛口火焰面积计算分析软件" : "Logiciel de calcul et d'analyse de la surface de la flamme de bouche";
            STR_ABOUT__COMPANY_NAME = m_bChinese ? "南京理工大学" : "Université des Sciences et Technologies de Nanjing";
        }
        private static void SetMainFormMessageBoxLanguage_F()
        {
            MSG_STATUS_LABEL = m_bChinese ? "未标定，比例尺为：1.00" : "Need to be calibrated, present scale : 1.00";
            MSG_STATUS_LABEL2 = m_bChinese ? "已标定，比例尺为：" : "Calibrated, present scale : ";
            MSG_ILLEGAL_INPUT = m_bChinese ? "非法输入!" : "Illegal input!";
            MSG_LINE_LENGTH1 = m_bChinese ? "线段1长度" : "Segment length 1";
            MSG_LINE_LENGTH2 = m_bChinese ? "线段2长度" : "Segment length 2";
            MSG_READ_IMAGE_FAILED = m_bChinese ? "读取图像失败!" : "Read image failed!";
            MSG_IF_EXIT = m_bChinese ? "确定退出吗?" : "Are you sure to quit?";
            MSG_NOTICE = m_bChinese ? "提示" : "Notice";
            MSG_SAVE_SUCCESSFULLY = m_bChinese ? "保存成功!" : "Save sucessfully!";
            MSG_SAVE_FILE_FAILED = m_bChinese ? "保存文件失败!" : "Save file failed!";
        }
        private static void SetScaleFormMessageBoxLanguage_F()
        {
            MSG_CALIBRATE_FIRST = m_bChinese ? "请先进行标定!" : "Please calibrate first!";
            MSG_LOAD_SUCCESSFULLY = m_bChinese ? "导入成功!" : "Load sucessfully!";
        }

    }
}

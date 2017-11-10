using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace MainWindow_njust
{
    //保存服务器状态变量名的类
    public static class GlobalVariable
    {
        //调试状态变量名称
        public const string SYS_DEBUG = "config.debug";
        //相机配置变量名
        public const string SYS_CAMER = "config.camera";
        //系统工作状态变量名
        public const string SYS_SERVER_STATUS = "server.status";
        //系统显示器状态变量名
        public const string SYS_DISPLAY_IN_BLUESCREEN = "config.IsBlueScreen";
        //抠图第一张图片的颜色值变量名
	    public const string MATTING_RGB1_R = "config.matting.RGB1.R";
	    public const string MATTING_RGB1_G = "config.matting.RGB1.G";
        public const string MATTING_RGB1_B = "config.matting.RGB1.B";
        //抠图第二张图片的颜色值变量名
        public const string MATTING_RGB2_R = "config.matting.RGB2.R";
	    public const string MATTING_RGB2_G = "config.matting.RGB2.G";
        public const string MATTING_RGB2_B= "config.matting.RGB2.B";
        //抠图第三张图片的颜色值变量名
        public const string MATTING_RGB3_R = "config.matting.RGB3.R";
	    public const string MATTING_RGB3_G = "config.matting.RGB3.G";
        public const string MATTING_RGB3_B = "config.matting.RGB3.B";
        //抠图的屏高比变量名
	    public const string MATTING_BORDER = "config.matting.border";
        //抠图三张图片的显示时间间隔变量名
	    public const string MATTING_DTIME = "config.matting.deltaTime";
        //纹理合成块个数变量名
        public const string FILLING_BLOCK_NUM = "config.filling.block.num";
        //纹理合成块大小变量名
        public const string FILLING_BLOCK_SIZE = "config.filling.block.size";
	    //纹理合成屏高比变量名
        public const string FILLING_BORDER = "config.filling.border";
        //目标区域当前的L, a, b均值的变量名
        public const string EVALUATION_CURRENT_L = "config.evaluation.current.L";
	    public const string EVALUATION_CURRENT_A = "config.evaluation.current.a";
	    public const string EVALUATION_CURRENT_B = "config.evaluation.current.b";
        //lab相似性阈值变量名
	    public const string EVALUATION_LAB_THREHOLD = "config.evaluation.labThreshold";
	    //自动颜色校正最大迭代次数变量名
        public const string EVALUATION_ITERATION = "config.evaluation.iteration";
        //定时校正的定时间隔变量名
        public const string EVALUATION_INTERVAL = "config.evaluation.interval";
        //自动颜色校正屏高比变量名
        public const string EVALUATION_BORDER = "config.evaluation.border";
        //手动颜色校正使能变量名
        public const string EVALUATION_MANUAL = "config.evaluation.manual";
    }
}

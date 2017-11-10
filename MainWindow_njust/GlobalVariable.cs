using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace MainWindow_njust
{
    public static class GlobalVariable
    {
        public const string SYS_DEBUG = "config.debug";
        public const string SYS_CAMER = "config.camera";
        public const string SYS_SERVER_STATUS = "server.status";
        public const string SYS_DISPLAY_IN_BLUESCREEN = "config.IsBlueScreen";

	    public const string MATTING_RGB1_R = "config.matting.RGB1.R";
	    public const string MATTING_RGB1_G = "config.matting.RGB1.G";
        public const string MATTING_RGB1_B = "config.matting.RGB1.B";
        public const string MATTING_RGB2_R = "config.matting.RGB2.R";
	    public const string MATTING_RGB2_G = "config.matting.RGB2.G";
        public const string MATTING_RGB2_B= "config.matting.RGB2.B";
        public const string MATTING_RGB3_R = "config.matting.RGB3.R";
	    public const string MATTING_RGB3_G = "config.matting.RGB3.G";
        public const string MATTING_RGB3_B = "config.matting.RGB3.B";
	    public const string MATTING_BORDER = "config.matting.border";
	    public const string MATTING_DTIME = "config.matting.deltaTime";

        public const string FILLING_BLOCK_NUM = "config.filling.block.num";
	    public const string FILLING_BLOCK_SIZE = "config.filling.block.size";
	    public const string FILLING_BORDER = "config.filling.border";

        public const string EVALUATION_CURRENT_L = "config.evaluation.current.L";
	    public const string EVALUATION_CURRENT_A = "config.evaluation.current.a";
	    public const string EVALUATION_CURRENT_B = "config.evaluation.current.b";
	    public const string EVALUATION_LAB_THREHOLD = "config.evaluation.labThreshold";
	    public const string EVALUATION_ITERATION = "config.evaluation.iteration";
        public const string EVALUATION_INTERVAL = "config.evaluation.interval";
        public const string EVALUATION_BORDER = "config.evaluation.border";
        public const string EVALUATION_MANUAL = "config.evaluation.manual";
    }
}

require("server")   -- tcp server
require("utils")    -- image IO, basic image operation
require("imgproc")  -- inpainting



--系统参数配置表
config =
{
	--服务器参数
	server =
  {
  		--服务器端口号
		port = 1400,
	},

	--显示屏参数
	screen =
  {
  		--显示屏宽度
		width = 640,
		--显示屏高度
		height = 480,
	},

	--相机参数
  camera = "640x480",

  --抠图参数
	matting =
  {
  	--第一种颜色参数
		RGB1 = { R=255, G=0, B=0 },
	--第二种颜色参数
    RGB2 = { R=0, G=255, B=0 },
    --第三种颜色参数
    RGB3 = { R=0, G=0, B=255 },
    --显示间隔时间
    deltaTime = 5,
    --屏高比
		border = 0.05,
	},

	--纹理合成参数
	filling =
  {
  	--纹理合成块参数
		block =
    {
    	--块大小
			size = 14,
		--块个数
			num = 4000,
		},
		--屏高比
		border = 0.2,
	},

	--颜色校正参数
	evaluation =
  {
  	--相似性阈值
		labThreshold = 2,
	--最大迭代次数
		iteration = 4,
	--手动Lab校正时的差值
    editDelta = { L=1, a=2, b=3 },
    --目标图像的Lab均值
    current = { L=5, a=10, b=15 },
    --定时颜色校正的时间间隔
    interval = 60,
    --颜色校正的屏高比
    border = 0.01,            --???????????????????????应该和filling.border相同
    --是否为定时Lab颜色校正
    manual = true,
	},

	debug = false,
  IsBlueScreen = false,       --是否使用蓝相屏
  IsNetCamera = false,        --是否使用网口摄像头
  IsMixed = false,            --是否对纹理进行融合

  IsLab = true,               --是否Lab校正
  IsHist = false,             --是否直方图校正
  IsMao = false,              --是否是茅老师的方法
  IsGamma = false,            --是否使用Gamma校正
  Thresh = 100,               --Lab校正的限幅阈值
  gamma = 0.3,                --Gamma校正的参数
}

--加载参数配置文件
pcall(loadfile('saved_config.lua'))

--将参数从Lua的表中写到参数映射表
function write_table_to_statue(prefix, tbl)
   for key,val in pairs(tbl) do --遍历表中的元素
      if 'table' == type(val) then --如果val的类型为表, 递归调用
        write_table_to_statue(prefix .. '.' .. tostring(key), val, save_config)
      else --如果为非table类型, 直接写到参数映射表里
        server.write(prefix .. '.' .. tostring(key), tostring(val))
      end
   end
end

--将参数从Lua的表中写到配置文件里
function write_table_to_file(prefix, tbl, saved_config)
   saved_config = saved_config or nil
   local do_close = false
   if saved_config == nil then --如果文件没打开
   		--打开文件
      saved_config = io.open('saved_config.lua', 'w')
      do_close = true
   end
   for key,val in pairs(tbl) do --遍历表中的元素
      if 'table' == type(val) then --如果val类型为表, 递归调用
        write_table_to_file(prefix .. '.' .. tostring(key), val, saved_config)
      else --如果为非table类型, 则写入到文件里
         if 'string' == type(val) then
            val = '"' .. val .. '"'
         end
         msg = string.format('%s = %s', prefix .. '.' .. tostring(key), tostring(val) .. '\n')
         saved_config:write(msg) --写文件
      end
   end
   if do_close then
      saved_config:close() --关闭文件
      saved_config = nil 
      print(saved_config) --输出信息
   end
end

--写日志文件
function write_logs(msg)
  --打开文件
  logfile = io.open('logs.txt', 'a')
  --写文本
  logfile:write(msg)
  --关闭文件
  logfile:close()
  --输出信息
  print(msg)
end

----------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------

--将图像img显示在蓝相屏上
function showImg2lcd(img, width, height)
  --清屏
  utils.lcd_clean()
  --延时
  utils.waitKey_Sleep(1500)
  --显示图像
  utils.imshow_2lcd("lcd", img, width, height, 24, 0)
  --延时
  utils.waitKey_Sleep(1500)
end

--将图像img显示在屏幕上，根据参数选择相应的显示方法
function show_image(img, width, height)
  if config.IsBlueScreen then --如果是蓝相屏
    showImg2lcd(img, width, height) --显示图像到蓝相屏
  else --如果是工业屏
  	--显示到工业屏
    utils.imshow("full", img, width, height, 24, 0)
  end 
end

--延时函数，根据参数选择相应的延时方法
function just_wait(dt1, dt2)
  if config.IsBlueScreen then --如果是蓝相屏
    utils.waitKey_Sleep(dt1) --延时
  else --如果不是蓝相屏
    utils.waitKey(dt2) --延时
  end
end

--全局变量
InitImg, Width, Height, PixFmt = nil, 0, 0, 0       -- 摄像头图像

--抓图
function capture_img()
  if config.IsNetCamera then --如果是网口相机
  	--调用网口相机拍照
    InitImg, Width, Height, PixFmt = utils.EthernetCameraCapture()
  else --如果不是网口相机
  	--调用普通相机拍照
    InitImg, Width, Height, PixFmt = utils.camera()
  end
end

--调整RGB系数
gRR, gGG, gBB = 1, 1, 1 			--140916
function AjustRgbs(rr, gg, bb)
  gRR = rr
  gGG = gg
  gBB = bb
end

----------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------

--安全地分配内存
function safe_malloc(addr, size)
   if addr then --如果地址非空
      utils.free(addr) --释放内存
   end
   return utils.malloc(size) --返回分配新内存
end

--安全地释放内存
function safe_free(addr)
   if addr then --如果地址非空
      utils.free(addr) --释放内存
   end
   return nil --返回空地址
end

timer = 0
--打开定时器
function enable_timer()
   timer = os.clock() --得到当前的系统时间
end

--检查定时器时间值
function check_timer()
   if timer then --如果定时器有效
      if timer == -1 then
	 	   return true 
      else
      		--如果到达定时时间则返回true，否则返回false
	 	   return os.clock() > timer + config.evaluation.interval
      end
   end
   --如果定时器无效则返回false
   return false
end

--关闭定时器
function disable_timer()
   timer = nil
end

--更新系统状态
function update_status(step, status)
   local msg = ""
   if status then --如果状态值为true, 显示操作已完成
      msg = string.format("%s完成", step.name)
   else --如果状态值为false, 显示操作失败
      msg = string.format("%s失败", step.name)
   end
   print (msg) --输出信息
   server.write("server.status", msg) --写系统状态
end

----------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------

timer = enable_timer()  --打开定时器                                  -- start timer
server.start_mserver(config.server.port) --打开监听服务器                 -- start tcp server
server.clear() --清理状态信息
--写系统状态信息
server.write("server.status", "初始化") 

print ("Opening camera.")
--打开相机
utils.open_camera(config.camera)
--得到相机类型
config.IsNetCamera = utils.CameraType()
print ("Camera opened.")

--声明全局变量,依次为屏幕区域模板图像,屏幕区域宽度,屏幕区域高度
--显示器模板图像,显示器宽度,显示器高度,伪装图像,伪装图像副本
--Lab图像,目标区域参数,放射变换参数
DisplayMsk, DisplayWidth, DisplayHeight = nil, 0, 0       -- 显示Mask
ScreenMsk, ScreenWidth, ScreenHeight = nil, 0, 0          -- 屏幕Mask
CamouflageImg = nil                                       -- 伪装图像
CopyOfCamouflageImg = nil
LabImg = nil
TargetRegion = utils.malloc(1024)
PerspectParam = utils.malloc(1024)                        -- 仿射变换矩阵

--用摄像头采集一张图片并保存
function saveImg(filename)
  InitImg = safe_free(InitImg) --释放图像内存
  capture_img() --采集图像
	utils.imwrite(filename, InitImg, Width, Height, PixFmt) --写图像文件
end

--用纯色背景填充屏幕
fillRGB = {name = "填充", img = nil}
function fillRGB.call(...)
   local RGB = {}
   if ... and select('#',...) == 4 then --如果参数个数为四
      self, RGB.R, RGB.G, RGB.B = ...  --获得参数值
   end
   server.write("server.status", "正在填充屏幕") --写系统状态
   fillRGB.img = safe_free(fillRGB.img) --释放图像内存
   --创建新的纯色图像
   fillRGB.img = utils.imnew(320, 240, RGB.R, RGB.G, RGB.B)
   --显示图像
   show_image(fillRGB.img, 320, 240)
   --延时等待
   just_wait(config.matting.deltaTime*1000, config.matting.deltaTime*1000)
   --更新系统状态
   update_status(fillRGB, true)
end
setmetatable(fillRGB, {__call = fillRGB.call})

--抠图，得到显示屏所在区域
matting = {name = "抠图"}
function matting.call()
   if config.IsNetCamera then		--140916 如果是网口相机
     utils.AjustRgb(1, 1, 1) --调整白平衡
	 just_wait(2000, 2000) --延时
   end
   if config.IsBlueScreen then		--140916 如果是蓝相屏
      config.evaluation.iteration = 1 --迭代次数设为1
   end
   --填充第一种颜色
   fillRGB(config.matting.RGB1.R, config.matting.RGB1.G, config.matting.RGB1.B) --填充屏幕
   local InitImg1 = safe_free(InitImg1)
   if config.IsNetCamera then --如果是网口相机
   		--调用网口相机拍摄图片
     InitImg1, Width, Height, PixFmt = utils.EthernetCameraCapture()
   else --如果不是网口相机
     InitImg1, Width, Height, PixFmt = utils.camera() --拍摄图片
   end
   utils.imwrite("cap1.jpg", InitImg1, Width, Height, 24) --保存图片                     --保存图像
   write_logs("010-matting: image1 finished\n") --写日志文件                            --写日志文件
   --填充第二种颜色
   fillRGB(config.matting.RGB2.R, config.matting.RGB2.G, config.matting.RGB2.B)
   local InitImg2 = safe_free(InitImg2)
   if config.IsNetCamera then --如果是网口相机
   	 --调用网口相机拍摄图片
     InitImg2, Width, Height, PixFmt = utils.EthernetCameraCapture()
   else --如果不是网口相机
     InitImg2, Width, Height, PixFmt = utils.camera() --拍摄图片
   end
   utils.imwrite("cap2.jpg", InitImg2, Width, Height, 24) --保存图片
   write_logs("020-matting: image2 finished\n") --写日志文件
   --填充第三种颜色
   fillRGB(config.matting.RGB3.R, config.matting.RGB3.G, config.matting.RGB3.B)
   local InitImg3 = safe_free(InitImg3)
   if config.IsNetCamera then --如果是网口相机
   	 --调用网口相机拍摄图片
     InitImg3, Width, Height, PixFmt = utils.EthernetCameraCapture()
   else --如果不是网口相机
     InitImg3, Width, Height, PixFmt = utils.camera()
   end
   utils.imwrite("cap3.jpg", InitImg3, Width, Height, 24) --保存图片
   write_logs("030-matting: image3 finished\n") --写日志文件
   --写系统状态
   server.write("server.status", "正在抠图") --写系统状态
   DisplayMsk = safe_malloc(DisplayMsk, Width*Height) --分配图像内存
   ScreenMsk = safe_malloc(ScreenMsk, Width*Height) --分配图像内存
   --抠取目标区域
   local retval = imgproc.TargetMatting( InitImg1, InitImg2, InitImg3, DisplayMsk,
                                         ScreenMsk, Width, Height, config.matting.border,
					                               Width, Height, TargetRegion, PerspectParam )
   utils.imwrite("DisplayMsk.bmp", DisplayMsk, Width, Height, 8) --保存图片
   utils.imwrite("ScreenMsk.bmp", ScreenMsk, Width, Height, 8) --保存图片
   utils.imwrite("cap.jpg", ScreenMsk, Width, Height, 8) --保存图片
   write_logs("040-matting: mask got\n") --写日志文件
   --释放内存
   InitImg1 = safe_free(InitImg1)
   InitImg2 = safe_free(InitImg2)
   InitImg3 = safe_free(InitImg3)
   --让蜂鸣器鸣叫一声
   utils.beep()
   --更新系统状态
   update_status(matting, retval)
end
setmetatable(matting, {__call=matting.call})

--生成纹理图像
filling = {name = "纹理合成", done = false}
function filling.call()
   if config.IsNetCamera then		--140916如果是网口相机
     utils.AjustRgb(gRR, gGG, gBB) --调整白平衡
     just_wait(2000, 2000) --延时
   end
   --创建纹理合成所需的初始图像
   InitImg = safe_free(InitImg)
   capture_img()
   --用来指示纹理合成是否成功
   filling.done = false

   --给伪装图像和其副本分配存储空间
   CamouflageImg = safe_malloc(CamouflageImg, config.screen.width*config.screen.height*3) --分配图像内存
   CopyOfCamouflageImg = safe_malloc(CopyOfCamouflageImg, config.screen.width*config.screen.height*3) --分配图像内存
   server.write("server.status", "正在纹理合成") --写系统状态
   write_logs("041-filling: before TextureSynthesis\n") --写日志文件
   --生成纹理图像
   local retval = imgproc.TextureSynthesis(InitImg, ScreenMsk, Width, Height, CamouflageImg, config.screen.width,
                                           config.screen.height, PerspectParam, config.filling.border,
                                           config.filling.block.size, config.filling.block.num, 
                                           config.IsNetCamera, config.IsMixed)
   update_status(filling, retval) --更新系统状态
   utils.imwrite("fill.bmp", CamouflageImg, config.screen.width, config.screen.height, 24) --保存图片
   utils.imwrite("cap.jpg", CamouflageImg, config.screen.width, config.screen.height, 24) --保存图片
   write_logs("050-filling: fill image got\n") --写日志文件
   --将纹理合成的结果显示出来
   show_image(CamouflageImg, config.screen.width, config.screen.height)
   --留一个初始伪装图像的副本,用于校正
   utils.imcopy(CamouflageImg, CopyOfCamouflageImg, config.screen.width, config.screen.height)
   if config.IsGamma then --如果是gamma校正
      local gammaImg = safe_free(gammaImg) --声明临时图像
      --对图像进行非线性gamma校正
      gammaImg = imgproc.gammaCorrection( CamouflageImg, config.screen.width, config.screen.height, 
                                          config.gamma, config.gamma, config.gamma, config.gamma)
      --显示图像
      show_image(gammaImg, config.screen.width, config.screen.height)
      utils.imwrite("gammaImg.bmp", gammaImg, config.screen.width, config.screen.height, 24) --保存图像
   end
   --释放内存
   InitImg = safe_free(InitImg) 
   --让蜂鸣器鸣叫一声
   utils.beep()
   filling.done = retval
end
setmetatable(filling, {__call=filling.call})

--自动Lab校正
autoevaluating = {name = "自动Lab颜色纠正", done = false}
function autoevaluating.call()
   --写日志文件
   write_logs("060-evaluating: auto lab start\n")
   --写服务器状态
   server.write("server.status", "正在自动Lab颜色纠正")
   --准备工作,生成一些临时图像
   local LabCamouflageImg = safe_malloc(LabCamouflageImg, 8*3*config.screen.width*config.screen.height)
   --将RGB转换为lab图像
   imgproc.RGB2LabImg(CamouflageImg, LabCamouflageImg, config.screen.width, config.screen.height, true)
   --获取用于校正的目标区域模板
   local MskImg = imgproc.gen_msk(DisplayMsk, ScreenMsk, Width, Height, config.evaluation.border)
   --保存图像文件
   utils.imwrite("labmsk.bmp", MskImg, Width, Height, 8)
   --用来指示自动Lab颜色纠正是否成功
   local retval = false

   local nn = 0;
   --迭代地进行自动Lab颜色纠正
   for i = 1, config.evaluation.iteration do
      just_wait(2000, 2000) --延时
      InitImg = safe_free(InitImg) --初始化图像
      capture_img() --用相机抓图
      nn = i --用来记录生成图像的序号
      --分配图像内存
      LabImg = utils.malloc(8*3*Width*Height) 
      --将RGB转换为lab图像
      imgproc.RGB2LabImg(InitImg, LabImg, Width, Height, true) 
      --保存图像文件
      utils.imwrite(string.format("init_lab%d.bmp", i-1), InitImg, Width, Height, 24) 
      --保存图像文件
      utils.imwrite("cap.jpg", InitImg, Width, Height, 24) 
      --进行单次Lab颜色纠正
      retval = imgproc.SingleLabCorrection( LabCamouflageImg, config.screen.width, config.screen.height,
                                            LabImg, MskImg, Width, Height, config.evaluation.labThreshold,
                                            config.evaluation.labThreshold, config.evaluation.labThreshold,
                                            config.Thresh)
      LabImg = safe_free(LabImg) --释放内存
      --将lab图像转换为RGB图像
      imgproc.Lab2RGBImg(LabCamouflageImg, CamouflageImg, config.screen.width, config.screen.height, true)
      --将纠正的的结果显示出来
      show_image(CamouflageImg, config.screen.width, config.screen.height)
      --写图像文件
      utils.imwrite(string.format("lab%d.bmp", i), CamouflageImg, config.screen.width, config.screen.height, 24)
      --如果校正失败则退出
      if (not retval) then 
        break
      end
   end
   --释放图像内存
   MskImg = safe_free(MskImg)
   LabCamouflageImg = safe_free(LabCamouflageImg)
   --延时等待
   just_wait(2000, 2000)
   --释放图像内存
   InitImg = safe_free(InitImg)
   --用相机抓图
   capture_img()
   --保存图像文件
   utils.imwrite("cap.jpg", InitImg, Width, Height, 24)
   --保存图像文件
   utils.imwrite(string.format("init_lab%d.bmp", nn), InitImg, Width, Height, 24)
   --写日志文件
   write_logs("070-evaluating: auto finished\n")
   --得到当前的lab参数
   getlab()
   --让蜂鸣器鸣叫一声
   utils.beep()
   --更新系统状态
   update_status(autoevaluating, not retval)
end
setmetatable(autoevaluating, {__call=autoevaluating.call})

--手动lab校正
manualevaluating = {name="手动颜色纠正", done=false}
function manualevaluating.call()
   --写日志文件
   write_logs("080-evaluating: manual start\n")
   --写服务器状态
   server.write("server.status", "正在手动颜色纠正")
   --分配图像内存
   local LabCamouflageImg = safe_malloc(LabCamouflageImg, 8*3*config.screen.width*config.screen.height)
   --将RGB转为lab图像
   imgproc.RGB2LabImg(CamouflageImg, LabCamouflageImg, config.screen.width, config.screen.height, true)
   --获取用于校正的目标区域模板
   local MskImg = imgproc.gen_msk(DisplayMsk, ScreenMsk, Width, Height, config.evaluation.border)
   --保存图像文件
   utils.imwrite("labmsk.bmp", MskImg, Width, Height, 8)
   local retval = false
   --进行手动lab颜色校正
   retval = imgproc.ManualLabCorrection(LabCamouflageImg, config.screen.width, config.screen.height,
                                        config.evaluation.editDelta.L, config.evaluation.editDelta.a, 
                                        config.evaluation.editDelta.b)
   --将lab转为RGB图像
   imgproc.Lab2RGBImg(LabCamouflageImg, CamouflageImg, config.screen.width, config.screen.height, true)
   --显示图像
   show_image(CamouflageImg, config.screen.width, config.screen.height)
   --释放图像内存
   MskImg = safe_free(MskImg)
   --释放图像内存
   LabCamouflageImg = safe_free(LabCamouflageImg)
   --释放图像内存
   InitImg = safe_free(InitImg)
   --延时等待
   just_wait(2000, 2000)
   --用相机抓图
   capture_img()
   --保存图像文件
   utils.imwrite("cap.jpg", InitImg, Width, Height, 24)
   --写日志文件
   write_logs("090-evaluating: manual finished\n")
   --获取当前lab值
   getlab()
   --让蜂鸣器鸣叫一声
   utils.beep()
   --更新系统状态
   update_status(manualevaluating, not retval)
end
setmetatable(manualevaluating, {__call=manualevaluating.call})

--自动RGB颜色校正
autoRGBevaluating = {name = "自动RGB颜色纠正", done = false}
function autoRGBevaluating.call()
   --写日志文件
   write_logs("060-evaluating: rgb auto start\n")
   --写系统状态
   server.write("server.status", "正在自动RGB颜色纠正")
   --获取用于校正的目标区域模板
   local MskImg = imgproc.gen_msk(DisplayMsk, ScreenMsk, Width, Height, config.evaluation.border)
   --保存图像文件
   utils.imwrite("rgbmsk.bmp", MskImg, Width, Height, 8)
   --用来指示自动RGB颜色纠正是否成功
   local retval = false

   --迭代地进行自动RGB颜色纠正
   for i = 1, config.evaluation.iteration do
   	  --延时等待
      just_wait(2000, 2000)
      --释放图像文件
      InitImg = safe_free(InitImg)
      --用相机抓图
      capture_img()
      --写图像文件
      utils.imwrite(string.format("init_rgb%d.bmp", i), InitImg, Width, Height, 24)
      --写图像文件
      utils.imwrite("cap.jpg", InitImg, Width, Height, 24)
      --进行单次RGB颜色纠正
      retval = imgproc.SingleRGBCorrection( CamouflageImg, config.screen.width, config.screen.height,
                                            InitImg, MskImg, Width, Height, config.evaluation.labThreshold,
                                            config.evaluation.labThreshold, config.evaluation.labThreshold,
                                            config.Thresh)
      --将纠正的的结果显示出来
      show_image(CamouflageImg, config.screen.width, config.screen.height)
      --写图像文件
      utils.imwrite(string.format("rgb%d.bmp", i), CamouflageImg, config.screen.width, config.screen.height, 24)
      --如果校正失败则退出
      if (not retval) then
        break
      end
   end
   --释放图像内存
   MskImg = safe_free(MskImg)
   --释放图像内存
   InitImg = safe_free(InitImg)
   --延时等待
   just_wait(2000, 2000)
   --用相机抓图
   capture_img()
   --写图像文件
   utils.imwrite("cap.jpg", InitImg, Width, Height, 24)
   --写日志文件
   write_logs("070-evaluating: rgb auto finished\n")
   --得到当前的lab参数
   getlab()
   --让蜂鸣器鸣叫一声
   utils.beep()
   --更新系统状态
   update_status(autoRGBevaluating, not retval)
end
setmetatable(autoRGBevaluating, {__call=autoRGBevaluating.call})

--直方图匹配和茅老师的方法
autoHistevaluating = {name = "自动hist颜色纠正", done = false}
function autoHistevaluating.call()
   --写日志文件
   write_logs("060-evaluating: hist auto start\n")
   --写系统状态
   server.write("server.status", "正在自动hist颜色纠正")
   --获取用于校正的目标区域模板
   local MskImg = imgproc.gen_msk(DisplayMsk, ScreenMsk, Width, Height, config.evaluation.border)
   --保存图像文件
   utils.imwrite("histmsk.bmp", MskImg, Width, Height, 8)

   --迭代地进行自动RGB颜色纠正
   for i = 1, config.evaluation.iteration do
   	  --延时等待
      just_wait(2000, 2000)
      --释放内存
      InitImg = safe_free(InitImg)
      --用相机抓图
      capture_img()
      --写图像文件
      utils.imwrite(string.format("init_hist%d.bmp", i), InitImg, Width, Height, 24)
      --写图像文件
      utils.imwrite("cap.jpg", InitImg, Width, Height, 24)
      --进行单次Hist颜色纠正
      if config.IsMao then --如果是茅老师的方法(均值和方差)
        imgproc.SingleHistogramCorrection_mao( CamouflageImg, config.screen.width, config.screen.height,
                                               InitImg, ScreenMsk, Width, Height )
      else --如果是直方图匹配方法
        imgproc.SingleHistogramCorrection( CamouflageImg, config.screen.width, config.screen.height,
                                         InitImg, ScreenMsk, Width, Height )
      end
      --将纠正的的结果显示出来
      show_image(CamouflageImg, config.screen.width, config.screen.height)
      --写图像文件
      utils.imwrite(string.format("hist%d.bmp", i), CamouflageImg, config.screen.width, config.screen.height, 24)
   end
   --释放图像内存
   MskImg = safe_free(MskImg)
   --释放图像内存
   InitImg = safe_free(InitImg)
   --延时等待
   just_wait(2000, 2000)
   --用相机抓图
   capture_img()
   --写图像文件
   utils.imwrite("cap.jpg", InitImg, Width, Height, 24)
   --写日志文件
   write_logs("070-evaluating: hist auto finished\n")
   --让蜂鸣器鸣叫一下
   utils.beep()
   --更新系统状态
   update_status(autoHistevaluating, true)
end
setmetatable(autoHistevaluating, {__call=autoHistevaluating.call})

----------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------

--整个流程执行以便：抠图、纹理合成、自动颜色校正
function donce()
  write_logs("\n************************************************\n") --写日志文件
  if config.IsBlueScreen then --如果使用蓝相屏
      utils.lcd_on() --给屏幕加驱动电压
      utils.waitKey_Sleep(1000) --延时等待
  end
  matting() --抠图
  filling() --纹理合成
  if config.IsGamma then --如果是gamma校正则结束
    return
  end

  if filling.done then --如果纹理合成已经成功
    if config.IsLab then --如果是原始lab校正
      autoevaluating.done = false
      autoevaluating() --自动lab颜色校正
      autoevaluating.done = true 
    else --如果是其他校正方法
      if config.IsHist then --如果是直方图校正
        autoHistevaluating.done = false
        autoHistevaluating() --基于直方图的颜色校正
        autoHistevaluating.done = true
      else --如果是RGB校正
        autoRGBevaluating.done = false
        autoRGBevaluating() --基于RGB通道的颜色校正
        autoRGBevaluating.done = true
      end
    end
  end
end

--手动lab校正
function manual(newL, newa, newb)
  disautimer() --关闭定时器
  if filling.done then --如果纹理合成已经成功
    config.evaluation.editDelta.L = newL --获取L参数值
    config.evaluation.editDelta.a = newa --获取a参数值
    config.evaluation.editDelta.b = newb --获取b参数值
    manualevaluating.done = false
    --备份伪装图像
    utils.imcopy(CopyOfCamouflageImg, CamouflageImg, config.screen.width, config.screen.height)
    manualevaluating() --手动lab颜色校正
    manualevaluating.done = true
  end
end

--仅手动/自动执行一次
function autonce()
  if filling.done then --如果纹理合成已经成功
    if config.IsLab then --如果是lab颜色校正
      autoevaluating.done = false
      --备份伪装图像
      utils.imcopy(CopyOfCamouflageImg, CamouflageImg, config.screen.width, config.screen.height)
      autoevaluating() --自动lab颜色校正
      autoevaluating.done = true
    else --如果是RGB颜色校正
      autoRGBevaluating.done = false
      --备份伪装图像
      utils.imcopy(CopyOfCamouflageImg, CamouflageImg, config.screen.width, config.screen.height)
      autoRGBevaluating() --自动RGB颜色校正
      autoRGBevaluating.done = true
    end
  end
end

--是否使用定时器
gIsUsingTimer = false

--打开定时执行功能
function autimer()
  gIsUsingTimer = true --使用定时器
  config.evaluation.manual = false --关闭手动功能
end

--关闭定时执行功能
function disautimer()
  gIsUsingTimer = false --不使用定时器
  config.evaluation.manual = true --打开手动功能
end

--得到当前的lab参数
function getlab()
  local cL, ca, cb = imgproc.getLab() --得到当前的lab参数
  config.evaluation.current.L = cL
  config.evaluation.current.a = ca
  config.evaluation.current.b = cb
end

--系统初始化函数
function initshow()
  local img, wid, hei, bi
  img, wid, hei, bi = utils.imread("rgb.bmp") --读取初始图像

  if config.IsBlueScreen then --如果使用蓝相屏
      utils.lcd_on() --加驱动电压
      utils.waitKey_Sleep(1000) --延时等待
      showImg2lcd(img, wid, hei) --显示图像到蓝相屏
      utils.waitKey_Sleep(1000) --延时等待
  else --如果使用工业屏
      utils.imshow("full", img, wid, hei, 24, 0) --显示图像到工业屏
      utils.waitKey(2000) --延时等待
  end 
end

----------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------

gIsUsingTimer = false --默认不使用定时器
config.evaluation.manual = true --默认为手动执行

server.append("initshow()") --向指令队列添加指令
timer = -1

--系统工作流程函数
function main()
  write_table_to_statue('config', config) --将系统状态从表中写到服务器端
    while true do
      cmd = server.read() --从指令队列读取指令
      if cmd then --如果指令不为空
        print (cmd) --打印指令
        loadstring(cmd)() --执行指令
        write_table_to_file('config', config) --将系统状态从表中写到配置文件
      else --如果指令为空
        break --跳出循环
      end
    end
  saveImg('cap.jpg') --用摄像头采集图像
  just_wait(1000, 1000) --延时等待

  if gIsUsingTimer then --如果使用定时器
    if check_timer() and not config.evaluation.manual then --如果到达定时时间且为定时状态
      if filling.done then --如果纹理合成已经成功
        server.append("autonce()") --向指令队列添加指令
      end
      enable_timer() --打开定时器
    end
  end
end

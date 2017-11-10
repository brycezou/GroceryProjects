package com.commonsware.android.CamControl;

//包含java包
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.net.*;
import java.io.PrintStream;
//import java.io.FileOutputStream;

//包含Android包
import android.app.Activity;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Color;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
//import android.net.*;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.SeekBar;
import android.widget.TableLayout;
import android.widget.TableRow;
import android.widget.TextView;
import android.widget.Toast;
import android.widget.ToggleButton;

//包含其它包
import org.apache.http.HttpEntity;
import org.apache.http.HttpResponse;
import org.apache.http.HttpStatus;
import org.apache.http.client.HttpClient;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.impl.client.DefaultHttpClient;
//import org.apache.http.params.HttpParams;
import org.json.*;

//应用程序类
public class CamControlActivity extends Activity
{
	/** 建立对象变量  **/
	//1. 建立按钮
	ToggleButton btnConnect; 	//连接按钮
	ToggleButton btnSetConnect; //网络连接设置按钮
	ToggleButton btnSetRGB; //抠图设置按钮
	ToggleButton btnSetWenLiHeCheng;//纹理合成设置按钮
	ToggleButton btnSetLabCorrect; //自动lab校正设置按钮
	ToggleButton btnSetManuLab;//手动lab校正设置按钮
	
	Button btnOKConnect;//网络连接设置中的确定按钮
	Button btnOKRGB; //抠图设置中的确定按钮
	Button btnOKWenLiHeCheng; //纹理合成设置中的确定按钮
	Button btnWenLiHeChengDoIt;//纹理合成设置中的执行按钮
	
	Button btnSimilarityPlus; //Lab阈值加按钮
	Button btnSimilarityMinus; //lab阈值减按钮
	Button btnMaxCorrectPlus; //最大纠正次数加按钮
	Button btnMaxCorrectMinus; //最大纠正次数减按钮
	Button btnOKLabCorrect; //自动Lab校正确定按钮
	Button btnLabDoIt; //自动lab校正自动按钮
	
	Button btnPlusL; //手动Lab校正L加按钮
	Button btnPlusA;//手动Lab校正a加按钮
	Button btnPlusB;//手动Lab校正b加按钮
	Button btnMinusL;//手动Lab校正L减按钮
	Button btnMinusA;//手动Lab校正a减按钮
	Button btnMinusB;//手动Lab校正b减按钮
	Button btnDoOneTimeLab; //手动Lab校正执行一次按钮
	
	Button btnGetPicture; //抓图按钮
	Button btnRefresh; //刷新按钮
		
	//2.建立输入框
	EditText editIP; //网络连接设置IP文本框
	EditText editPort;//网络连接设置端口文本框
	
	EditText editR1;//抠图设置RGB1第1个文本框
	EditText editG1;//抠图设置RGB1第2个文本框
	EditText editB1;//抠图设置RGB1第3个文本框
	EditText editR2;//抠图设置RGB2第1个文本框
	EditText editG2;//抠图设置RGB2第2个文本框
	EditText editB2;//抠图设置RGB2第3个文本框
	EditText editR3;//抠图设置RGB3第1个文本框
	EditText editG3;//抠图设置RGB3第2个文本框
	EditText editB3;//抠图设置RGB3第3个文本框
	EditText editKouTuBorder; //抠图设置屏高比文本框
	EditText editDeltaTime; //抠图设置显示间隔文本框
	
	EditText editBlockSize; //纹理合成块大小文本框
	EditText editBlockNum; //纹理合成块个数文本框
	EditText editWenLiHeChengBorder; //纹理合成屏高比文本框
	
	EditText editLabSimilarity; //lab阈值文本框
	EditText editMaxCorrect; //最大纠正次数文本框
	EditText editLabBorder; //自动lab校正屏高比文本框
	EditText editRunDeltTime; //自动lab校正运行间隔文本框

	EditText editLabL;//L文本框
	EditText editLabA;//a文本框
	EditText editLabB;//b文本框
	EditText editManuLabStep;//步长文本框
	
	//3.建立表格行
	TableRow tableRowConnect;//网络连接表格
	TableRow tableRowRGB;//抠图设置表格
	TableRow tableRowWenLiHeCheng;//纹理合成表格
	TableRow tableRowLab;//自动lab校正表格
	TableRow tableRowManuLab;//手动lab校正表格
	
	//4.建立其他元素
	TextView textIsConnected;  //显示是否连接
	TextView textNowState;  //状态消息
	TableLayout tableMain; //表格布局
	ImageView imgShow; //图片显示控件
	
	final String FILE_NAME="config.dat";    //配置文件保存地址
	SocketClient myClientSocket;    //建立的Socket对象
	boolean isConnected=false;         //是否有连接	
	public String answerMessage; //接收到的数据
	HttpURLConnection connHttp; //用于抓图的HTTP连接对象
	
    @Override
    public void onCreate(Bundle savedInstanceState) 
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);//设置视图
        
        OnSetupLink();				//连接组件与变量
    	OnSetupRow();         		//对折叠菜单进行初始化
    	file(2);            		//读取IP和端口地址
    	OnInitialButtons(false); 	//初始化所有的按钮
    }
    
    public void OnSetupLink()	//连接组件与变量
    {         
    	//1. 将按钮与对应的视图联系起来
        btnConnect=(ToggleButton)findViewById(R.id.bConn);
    	btnSetConnect=(ToggleButton)findViewById(R.id.bSetConn);
    	btnSetRGB=(ToggleButton)findViewById(R.id.bSetRGB);
    	btnSetWenLiHeCheng=(ToggleButton)findViewById(R.id.bSetComb);
    	btnSetLabCorrect=(ToggleButton)findViewById(R.id.bSetLab);
    	btnGetPicture=(Button)findViewById(R.id.bShoot);
    	btnRefresh=(Button)findViewById(R.id.bRefresh);
    	btnOKConnect=(Button)findViewById(R.id.bOKConn);
    	btnOKRGB=(Button)findViewById(R.id.bOKRGB);
    	btnOKWenLiHeCheng=(Button)findViewById(R.id.bOKComb);
    	btnOKLabCorrect=(Button)findViewById(R.id.bOKLab);
    	btnSimilarityPlus=(Button)findViewById(R.id.bThresPlus);
    	btnSimilarityMinus=(Button)findViewById(R.id.bThresMinus);
    	btnMaxCorrectPlus=(Button)findViewById(R.id.bCorrPlus);
    	btnMaxCorrectMinus=(Button)findViewById(R.id.bCorrMinus);
    	btnSetManuLab=(ToggleButton)findViewById(R.id.bSetManuLab);
    	btnWenLiHeChengDoIt=(Button)findViewById(R.id.bDoComb);
    	btnLabDoIt=(Button)findViewById(R.id.bDoLab);
    	btnPlusL=(Button)findViewById(R.id.bLPlus);
    	btnPlusA=(Button)findViewById(R.id.bAPlus);
    	btnMinusL=(Button)findViewById(R.id.bLMinus);
    	btnMinusA=(Button)findViewById(R.id.bAMinus);
    	btnDoOneTimeLab=(Button)findViewById(R.id.bDoOneTimeLab);
    	
    	//2.将文本框与对应的视图联系起来
    	editIP=(EditText)findViewById(R.id.tIP);
    	editPort=(EditText)findViewById(R.id.tPort);
    	editBlockSize=(EditText)findViewById(R.id.tComSize);
    	editBlockNum=(EditText)findViewById(R.id.tComNum);
    	editLabSimilarity=(EditText)findViewById(R.id.tLabThres);
    	editMaxCorrect=(EditText)findViewById(R.id.tLabCorr);
    	editRunDeltTime=(EditText)findViewById(R.id.tParaTime);
    	editR1=(EditText)findViewById(R.id.tR1);
    	editG1=(EditText)findViewById(R.id.tG1);
    	editB1=(EditText)findViewById(R.id.tB1);
    	editR2=(EditText)findViewById(R.id.tR2);
    	editG2=(EditText)findViewById(R.id.tG2);
    	editB2=(EditText)findViewById(R.id.tB2);
    	editR3=(EditText)findViewById(R.id.tR3);
    	editG3=(EditText)findViewById(R.id.tG3);
    	editB3=(EditText)findViewById(R.id.tB3);
    	editWenLiHeChengBorder=(EditText)findViewById(R.id.tWenLiHeChengBorder);
    	editDeltaTime=(EditText)findViewById(R.id.tDeltaTime);
    	editKouTuBorder=(EditText)findViewById(R.id.tKouTuBorder);
    	editLabBorder=(EditText)findViewById(R.id.tLabBorder);
    	editLabL=(EditText)findViewById(R.id.tLabL);
    	editLabA=(EditText)findViewById(R.id.tLabA);
    	editLabB=(EditText)findViewById(R.id.tLabB);
    	editManuLabStep=(EditText)findViewById(R.id.tLabStep);
    	
    	//3.将表格行与对应的视图联系起来
    	tableRowConnect=(TableRow)findViewById(R.id.rConn);
    	tableRowRGB=(TableRow)findViewById(R.id.rRGB);
    	tableRowWenLiHeCheng=(TableRow)findViewById(R.id.rComb);
    	tableRowLab=(TableRow)findViewById(R.id.rLab);
    	tableRowManuLab=(TableRow)findViewById(R.id.rManuLab);
    	  	
    	//4.将其它控件与对应的视图联系起来
    	textIsConnected=(TextView)findViewById(R.id.tIsConn);
    	textNowState=(TextView)findViewById(R.id.tState);
    	tableMain=(TableLayout)findViewById(R.id.tbMain);
    	imgShow=(ImageView)findViewById(R.id.imgShow);
    }
    
    public void OnSetupRow()	//对折叠菜单进行初始化
    {          
    	tableMain.removeView(tableRowConnect);//移除连接表格
    	tableMain.removeView(tableRowRGB);//移除抠图设置表格
    	tableMain.removeView(tableRowWenLiHeCheng);//移除纹理合成表格
    	tableMain.removeView(tableRowLab);//移除自动lab校正表格
    	tableMain.removeView(tableRowManuLab);//移除手动lab校正表格
    }
    
    public void OnInitialButtons(boolean flag)	//设置按钮状态
    {
    	if(flag==false)	//如果是未连接状态
    	{          
    		//禁用部分按钮
    		btnSetConnect.setEnabled(true);
        	btnSetRGB.setEnabled(false);
        	btnSetWenLiHeCheng.setEnabled(false);
        	btnSetLabCorrect.setEnabled(false);
        	btnGetPicture.setEnabled(false);
        	btnRefresh.setEnabled(false);
        	btnSetManuLab.setEnabled(false);
        	//移除所有表格
        	tableMain.removeView(tableRowConnect);
        	tableMain.removeView(tableRowRGB);
        	tableMain.removeView(tableRowWenLiHeCheng);
        	tableMain.removeView(tableRowLab);
        	tableMain.removeView(tableRowManuLab);
        	//设置开关按钮的状态
        	btnSetRGB.setChecked(false);
        	btnSetWenLiHeCheng.setChecked(false);
        	btnSetLabCorrect.setChecked(false);
        	btnSetManuLab.setChecked(false);
    	}
    	else //如果不是程序初始化,但仍需要改变按钮状态
    	{
    		//使能部分按钮
    		btnSetConnect.setEnabled(true);
        	btnSetRGB.setEnabled(true);
        	btnSetWenLiHeCheng.setEnabled(true);
        	btnSetLabCorrect.setEnabled(true);
        	btnSetManuLab.setEnabled(true);
        	btnGetPicture.setEnabled(true);
        	btnRefresh.setEnabled(true);
    	}
    }
    
    public void file(int type)	//读写IP地址和端口号缓存文件
    {        
    	if(type==1)	//写文件
    	{                   
    		String tIP,tPort;//声明变量
    		tIP=editIP.getText().toString(); //读取IP地址
    		tPort=editPort.getText().toString(); //读取端口号
    		if((tIP!="")&&(tPort!="")) //如果IP地址和端口号都不为空
    		{
    			try 
    			{
    				//创建输出流对象
    				OutputStreamWriter out=new OutputStreamWriter(openFileOutput(FILE_NAME, 0));
    				out.write(tIP+"\n"+tPort); //写数据
    				out.close(); //关闭输出流
    				OnShowDlg("设置成功，信息已保存！");
    			}
    			catch(Throwable t) //如果发生异常
    			{
    	    		OnShowDlg("信息保存失败："+t.toString());
    	    	}
    		}
    		else //如果IP地址或端口号为空
    			OnShowDlg("IP地址、端口号不能为空！");
    	}
    	else if(type==2)	//读文件
    	{                       
    		try
    		{
    			String tIP,tPort; //声明变量
    			InputStream in=openFileInput(FILE_NAME); //打开文件
    			if(in!=null)
    			{
    				//获取文件输入流
    				InputStreamReader tmp=new InputStreamReader(in);
    				BufferedReader reader=new BufferedReader(tmp);
    					
    				tIP=reader.readLine(); //读取IP地址
    				tPort=reader.readLine(); //读取端口号
    				
    				editIP.setText(tIP); //将IP地址和端口号显示在控件上
    				editPort.setText(tPort);
    				in.close();//关闭输入流
    			}
    		}
    		catch(Throwable t) //如果发生异常
    		{
    			
    		}
    	}
    }
       
    public void clickConnect(View view)	//处理连接按钮事件
    {     
    	if(isConnected==false)	//如果还未连接
    	{              
    		textIsConnected.setText("连接中...");//设置连接状态文字
			textIsConnected.setTextColor(Color.YELLOW); //设置连接状态文字颜色
			btnConnect.setEnabled(false); //连接按钮失效
			textNowState.setText("连接正常，可以进行操作"); //设置客户端运行状态
			String IP=editIP.getText().toString();//获取IP地址
			int Port=Integer.valueOf(editPort.getText().toString()); //获取端口号

			myClientSocket=new SocketClient(IP,Port);   //连接服务器
    	}
    	else //如果已连接
    	{
    		textIsConnected.setText("未连接 ");//设置连接状态文字
    		textIsConnected.setTextColor(Color.WHITE);//设置连接状态文字颜色
    		OnInitialButtons(false); //设置按钮状态
    		btnSetConnect.setText("折叠"); //设置连接设置按钮文字
    		btnSetConnect.setChecked(false); //更改连接设置按钮状态
    		textNowState.setText("目前没有连接"); //设置客户端运行状态
    		myClientSocket.closeSocket(); //关闭通信套接字
    	}
    }
    
    public void clickSet(View view)	//处理设置按钮，展开和折叠相应栏目
    {	 		
    	ToggleButton button=(ToggleButton)view; //获取按钮对象
    	TableRow row;
    	int sum=2;	
    	if(view==btnSetConnect)//如果是网络连接设置按钮
    	{
    		row=tableRowConnect;//设置当前行
    		sum=4;
    	}
    	else if(view==btnSetRGB)//如果是抠图设置按钮
    	{
    		row=tableRowRGB;//设置当前行
    		sum=5;
    		if(btnSetConnect.isChecked()==true) sum++; //如果已展开就多一行
    	}
    	else if(view==btnSetWenLiHeCheng) //如果是纹理合成设置按钮
    	{
    		row=tableRowWenLiHeCheng;//设置当前行
    		sum=6;
    		if(btnSetConnect.isChecked()==true) sum++;//如果已展开就多一行
    		if(btnSetRGB.isChecked()==true) sum++;//如果已展开就多一行
    	}
    	else if(view==btnSetLabCorrect)//如果是自动lab校正设置按钮
    	{
    		row=tableRowLab;//设置当前行
    		sum=7;
    		if(btnSetConnect.isChecked()==true) sum++;//如果已展开就多一行
    		if(btnSetRGB.isChecked()==true) sum++;//如果已展开就多一行
    		if(btnSetWenLiHeCheng.isChecked()==true) sum++;//如果已展开就多一行
    	}
    	else //如果是手动lab校正设置按钮
    	{
    		row=tableRowManuLab;//设置当前行
    		sum=8;
    		if(btnSetConnect.isChecked()==true) sum++;//如果已展开就多一行
    		if(btnSetRGB.isChecked()==true) sum++;//如果已展开就多一行
    		if(btnSetWenLiHeCheng.isChecked()==true) sum++;//如果已展开就多一行
    		if(btnSetLabCorrect.isChecked()==true) sum++;//如果已展开就多一行
    	}
    	
    	if(button.isChecked()==true) //如果是按下了按钮，展开界面
    	{
    		switch(row.getId()) //看按下了哪一个按钮
    		{
       		case R.id.rConn: //如果是连接参数设置按钮
    			tableMain.addView(row,sum);//展开网络连接参数设置视图
    			return;
    		case R.id.rRGB: //如果是抠图设置按钮
        		this.btnSetManuLab.setEnabled(false);
        		this.btnSetLabCorrect.setEnabled(false);
        		this.btnSetWenLiHeCheng.setEnabled(false);
        		tableMain.addView(row,sum);//展开抠图设置视图
        		break;
    		case R.id.rComb://如果是纹理合成设置按钮
    			this.btnSetRGB.setEnabled(false);
        		this.btnSetManuLab.setEnabled(false);
        		this.btnSetLabCorrect.setEnabled(false);
    			tableMain.addView(row,sum);//展开纹理合成参数设置视图
    			break;
    		case R.id.rLab: //如果是自动lab校正设置按钮
    			this.btnSetRGB.setEnabled(false);
        		this.btnSetManuLab.setEnabled(false);
        		this.btnSetWenLiHeCheng.setEnabled(false);
        		tableMain.addView(row,sum);//展开自动lab校正设置视图
        		break;
    		case R.id.rManuLab: //如果是手动lab校正按钮
    			this.btnSetRGB.setEnabled(false);
        		this.btnSetLabCorrect.setEnabled(false);
        		this.btnSetWenLiHeCheng.setEnabled(false);
        		tableMain.addView(row,sum); //展开手动lab校正设置视图
        		break;
    		default:break;
    		}
    
    		answerMessage="";//接收到的数据
    		myClientSocket.writer.println("?");//向服务器发送查询指令
     		try 
    		{
    			answerMessage=myClientSocket.br.readLine();//接收数据
	   			if(answerMessage==null) //如果网络连接错误
    			{
    		   		textIsConnected.setText("未连接 ");//设置连接状态文字
    		   		OnShowDlg("网络异常，请重新连接!");
    	    		textIsConnected.setTextColor(Color.WHITE);//设置连接状态文字颜色
    	    		OnInitialButtons(false);//设置未连接按钮状态
    	    		//下面都是改变页面控件状态
    	    		btnSetConnect.setChecked(false);
    	    		textNowState.setText("目前没有连接");
    	    		this.btnConnect.setEnabled(true);
    	    		this.btnConnect.setChecked(false);
    	    		this.btnConnect.setText("连接");
    	    		myClientSocket.closeSocket();//关闭网络通信套接字
    				return;
    			}
	   			//如果网络连接正常,则接受到了服务器返回数据
    			int strlen=answerMessage.length();//获取字符串长度
    	  		String json=answerMessage.substring(0,strlen-2)+"}";//构造新的字符串
        		JSONObject object;//声明Json对象
    			try 
    			{
    				object=(JSONObject) new JSONTokener(json).nextValue();//构造Json对象
    				//以下为解析Json数据并为控件赋值
    				//设置R1
					editR1.setText(object.getString("config.matting.RGB1.R").toString());
					//设置G1
					editG1.setText(object.getString("config.matting.RGB1.G").toString());
					//设置B1
					editB1.setText(object.getString("config.matting.RGB1.B").toString());
					//设置R2
					editR2.setText(object.getString("config.matting.RGB2.R").toString());
					//设置G2
					editG2.setText(object.getString("config.matting.RGB2.G").toString());
					//设置B2
					editB2.setText(object.getString("config.matting.RGB2.B").toString());
					//设置R3
					editR3.setText(object.getString("config.matting.RGB3.R").toString());
					//设置G3
					editG3.setText(object.getString("config.matting.RGB3.G").toString());
					//设置B3
					editB3.setText(object.getString("config.matting.RGB3.B").toString());
					//设置抠图屏高比
    			    editKouTuBorder.setText(object.getString("config.matting.border").toString());
    			    //设置抠图显示间隔
    			    editDeltaTime.setText(object.getString("config.matting.deltaTime").toString());
    			    //设置纹理合成块大小
    				editBlockSize.setText(object.getString("config.filling.block.size").toString());
    				//设置纹理合成块个数
    				editBlockNum.setText(object.getString("config.filling.block.num").toString());
    				//设置纹理合成屏高比
    				editWenLiHeChengBorder.setText(object.getString("config.filling.border").toString());
    				//设置lab阈值
    				editLabSimilarity.setText(object.getString("config.evaluation.labThreshold").toString());
    				//设置最大校正次数
    				editMaxCorrect.setText(object.getString("config.evaluation.iteration").toString());
    				//设置颜色校正屏高比
    				editLabBorder.setText(object.getString("config.evaluation.border").toString());
    				//设置定时时间
    				editRunDeltTime.setText(object.getString("config.evaluation.interval").toString());
    				//设置L
    				editLabL.setText(object.getString("config.evaluation.current.L").toString());
    				//设置a
    				editLabA.setText(object.getString("config.evaluation.current.a").toString());
    				//设置b
    				editLabB.setText(object.getString("config.evaluation.current.b").toString());	
    				//设置服务器运行状态
    				textNowState.setText(object.getString("server.status").toString());
    			} 
    			catch (JSONException e) //如果发生错误
    			{
    				OnShowDlg("更新数据失败!");
    				return;
    			}    		
    		} 
    		catch (IOException e) //如果发生错误
    		{
    			OnShowDlg("更新数据失败!");
    			return;
    		}
    	}
    	else //如果是弹出了按钮，折叠
    	{
    		switch(row.getId()) //看弹起了哪一个按钮
    		{
       		case R.id.rConn://如果是网络连接参数设置按钮
       			tableMain.removeView(row);//折叠网络连接参数设置视图
       			break;
       		case R.id.rRGB://如果是抠图设置按钮
    			this.btnSetRGB.setEnabled(true);
        		this.btnSetManuLab.setEnabled(true);
        		this.btnSetLabCorrect.setEnabled(true);
        		this.btnSetWenLiHeCheng.setEnabled(true);
        		tableMain.removeView(row); //折叠抠图设置视图
        		break;
       		case R.id.rComb://如果是纹理合成设置按钮
    			this.btnSetRGB.setEnabled(true);
        		this.btnSetManuLab.setEnabled(true);
        		this.btnSetLabCorrect.setEnabled(true);
        		this.btnSetWenLiHeCheng.setEnabled(true);
        		tableMain.removeView(row); //折叠纹理合成设置视图
        		break;
       		case R.id.rLab://如果是自动lab校正设置按钮
    			this.btnSetRGB.setEnabled(true);
        		this.btnSetManuLab.setEnabled(true);
        		this.btnSetLabCorrect.setEnabled(true);
        		this.btnSetWenLiHeCheng.setEnabled(true);
        		tableMain.removeView(row); //折叠自动lab校正设置视图
        		break;
       		case R.id.rManuLab://如果是手动lab校正设置按钮
    			this.btnSetRGB.setEnabled(true);
        		this.btnSetManuLab.setEnabled(true);
        		this.btnSetLabCorrect.setEnabled(true);
        		this.btnSetWenLiHeCheng.setEnabled(true);
        		tableMain.removeView(row); //折叠手动lab校正视图
        		break;
       		default:break;	
    		}
    	}    		  	
    }
    
    public void clickPlusOrMinus(View view)	//处理加减按钮
    {    
    	int temp=0,labStep=0;//声明临时变量
    	int intLabL=0,intLabA=0,intLabB=0;
    	switch(view.getId()) //看是哪一个按钮被按下
    	{   		
    	case R.id.bThresPlus: //lab阈值加按钮
    		temp=Integer.valueOf(editLabSimilarity.getText().toString());//得到lab阈值
    		if(temp<=10) temp++;//如果阈值在合法范围内则加1
    		if(temp<=10)
    			editLabSimilarity.setText(Integer.toString(temp));//设置lab阈值文本框的值
    		break;
    		
    	case R.id.bThresMinus://lab阈值减按钮
    		temp=Integer.valueOf(editLabSimilarity.getText().toString());//得到lab阈值
    		if(temp>=1) temp--;//如果阈值在合法范围内则减1
    		if(temp>=1)
    			editLabSimilarity.setText(Integer.toString(temp));//设置lab阈值文本框的值
    		break;
    		
    	case R.id.bCorrPlus://最大校正次数加按钮
    		temp=Integer.valueOf(editMaxCorrect.getText().toString());//得到最大校正次数
    		if(temp<=20) temp++;//如果在合法范围内则加1
    		if(temp<=20)
    			editMaxCorrect.setText(Integer.toString(temp));//设置最大校正次数文本框的值
    		break;
    	
    	case R.id.bCorrMinus://最大校正次数减按钮
    		temp=Integer.valueOf(editMaxCorrect.getText().toString());//得到最大校正次数
    		if(temp>=0) temp--;//如果在合法范围内则减1
    		if(temp>=0)
    			editMaxCorrect.setText(Integer.toString(temp));//设置最大校正次数文本框的值
    		break;
    		
    	case R.id.bLPlus://L加按钮
    		labStep=Integer.valueOf(editManuLabStep.getText().toString());//得到步长
    		temp=Integer.valueOf(editLabL.getText().toString());//得到L的值
    		if(temp<=100-labStep) temp+=labStep;//如果在合法范围内则改变值
    		else temp=100;//否则设置为上限
    		editLabL.setText(Integer.toString(temp));//设置L文本框的值
    		
			intLabL=Integer.valueOf(this.editLabL.getText().toString());//得到L
			intLabA=Integer.valueOf(this.editLabA.getText().toString());//得到a
			intLabB=Integer.valueOf(this.editLabB.getText().toString());//得到b
    		try 
    		{
    			//向服务器发送手动lab校正指令
        		myClientSocket.writer.println("manual("+intLabL+","+intLabA+","+intLabB+")");
				answerMessage=myClientSocket.br.readLine(); //接收数据
				OnShowDlg("正在发送手动Lab校正参数。。。");
    		}
      		catch (IOException e) //如果发生错误
    		{
				OnShowDlg("发送失败，请检查网络");
				return;
			}   
    		break;
    		
    	case R.id.bAPlus://a加按钮
    		labStep=Integer.valueOf(editManuLabStep.getText().toString());//得到步长
    		temp=Integer.valueOf(editLabA.getText().toString());//得到a的值
    		if(temp<=108-labStep) temp+=labStep;//如果在合法范围内则改变值
    		else temp=108;//否则设置为上限
    		editLabA.setText(Integer.toString(temp));//设置a文本框的值
    		
			intLabL=Integer.valueOf(this.editLabL.getText().toString());//得到L
			intLabA=Integer.valueOf(this.editLabA.getText().toString());//得到a
			intLabB=Integer.valueOf(this.editLabB.getText().toString());//得到b
    		try 
    		{
    			//向服务器发送手动lab校正指令
        		myClientSocket.writer.println("manual("+intLabL+","+intLabA+","+intLabB+")");
				answerMessage=myClientSocket.br.readLine();//接收数据
				OnShowDlg("正在发送手动Lab校正参数。。。");
    		}
      		catch (IOException e) //如果发生错误
    		{
				OnShowDlg("发送失败，请检查网络");
				return;
			}   
    		break;
    		
    	case R.id.bLabBPlus://b加按钮
    		labStep=Integer.valueOf(editManuLabStep.getText().toString());//得到步长
    		temp=Integer.valueOf(editLabB.getText().toString());//得到b的值
    		if(temp<=95-labStep) temp+=labStep;//如果在合法范围内则改变值
    		else temp=95;//否则设置为上限
    		editLabB.setText(Integer.toString(temp));//设置b文本框的值
    		
			intLabL=Integer.valueOf(this.editLabL.getText().toString());//得到L
			intLabA=Integer.valueOf(this.editLabA.getText().toString());//得到a
			intLabB=Integer.valueOf(this.editLabB.getText().toString());//得到b
    		try 
    		{
    			//向服务器发送手动lab校正指令
        		myClientSocket.writer.println("manual("+intLabL+","+intLabA+","+intLabB+")");
				answerMessage=myClientSocket.br.readLine();//接收数据
				OnShowDlg("正在发送手动Lab校正参数。。。");
    		}
      		catch (IOException e) //如果发生错误
    		{
				OnShowDlg("发送失败，请检查网络");
				return;
			}   
    		break;
    		
    	case R.id.bLMinus://L减按钮
       		labStep=Integer.valueOf(editManuLabStep.getText().toString());//得到步长
    		temp=Integer.valueOf(editLabL.getText().toString());//得到L的值
    		if(temp>=0+labStep) temp-=labStep;//如果在合法范围内则改变值
    		else temp=0;//否则设置为下限
    		editLabL.setText(Integer.toString(temp));//设置L文本框的值
    		
			intLabL=Integer.valueOf(this.editLabL.getText().toString());//得到L
			intLabA=Integer.valueOf(this.editLabA.getText().toString());//得到a
			intLabB=Integer.valueOf(this.editLabB.getText().toString());//得到b
    		try 
    		{
    			//向服务器发送手动lab校正指令
        		myClientSocket.writer.println("manual("+intLabL+","+intLabA+","+intLabB+")");
				answerMessage=myClientSocket.br.readLine(); //接收数据
				OnShowDlg("正在发送手动Lab校正参数。。。");
    		}
      		catch (IOException e) //如果发生错误
    		{
				OnShowDlg("发送失败，请检查网络");
				return;
			}   
    		break;
    		
    	case R.id.bAMinus://a减按钮
    		labStep=Integer.valueOf(editManuLabStep.getText().toString());//得到步长
    		temp=Integer.valueOf(editLabA.getText().toString());//得到a的值
    		if(temp>=-94+labStep) temp-=labStep;//如果在合法范围内则改变值
    		else temp=-94;//否则设置为下限
    		editLabA.setText(Integer.toString(temp));//设置a文本框的值
    		
			intLabL=Integer.valueOf(this.editLabL.getText().toString());//得到L
			intLabA=Integer.valueOf(this.editLabA.getText().toString());//得到a
			intLabB=Integer.valueOf(this.editLabB.getText().toString());//得到b
    		try 
    		{
    			//向服务器发送手动lab校正指令
        		myClientSocket.writer.println("manual("+intLabL+","+intLabA+","+intLabB+")");
				answerMessage=myClientSocket.br.readLine();//接收数据
				OnShowDlg("正在发送手动Lab校正参数。。。");
    		}
      		catch (IOException e) //如果发生错误
    		{
				OnShowDlg("发送失败，请检查网络");
				return;
			}   
    		break;
    		
    	case R.id.bLabBMinus://b减按钮
    		labStep=Integer.valueOf(editManuLabStep.getText().toString());//得到步长
    		temp=Integer.valueOf(editLabB.getText().toString());//得到b的值
    		if(temp>=-108+labStep) temp-=labStep;//如果在合法范围内则改变值
    		else temp=-108;//否则设置为下限
    		editLabB.setText(Integer.toString(temp));//设置b文本框的值
    		
			intLabL=Integer.valueOf(this.editLabL.getText().toString());//得到L
			intLabA=Integer.valueOf(this.editLabA.getText().toString());//得到a
			intLabB=Integer.valueOf(this.editLabB.getText().toString());//得到b
    		try 
    		{
    			//向服务器发送手动lab校正指令
        		myClientSocket.writer.println("manual("+intLabL+","+intLabA+","+intLabB+")");
				answerMessage=myClientSocket.br.readLine();//接收数据
				OnShowDlg("正在发送手动Lab校正参数。。。");
    		}
      		catch (IOException e) //如果发生错误
    		{
				OnShowDlg("发送失败，请检查网络");
				return;
			}   
    		break;
	
    	default:break;
    	}
    }
    
    public void clickSetOK(View view)	//处理设置完成按钮
    {     
		answerMessage="";
		switch(view.getId()) //看是按下了哪一个按钮
		{
		case R.id.bOKConn: //如果是网络连接参数确定按钮             
    		file(1);	//存储到本地文件中
    		return;
    		
		case R.id.bOKRGB: //如果是抠图设置确定按钮            
    		int intR1=Integer.valueOf(editR1.getText().toString());  //读取用户输入的RGB值
    		int intG1=Integer.valueOf(editG1.getText().toString());
    		int intB1=Integer.valueOf(editB1.getText().toString());	
    		
    		int intR2=Integer.valueOf(editR2.getText().toString());  //读取用户输入的RGB值
    		int intG2=Integer.valueOf(editG2.getText().toString());
    		int intB2=Integer.valueOf(editB2.getText().toString());	
    		
    		int intR3=Integer.valueOf(editR3.getText().toString());  //读取用户输入的RGB值
    		int intG3=Integer.valueOf(editG3.getText().toString());
    		int intB3=Integer.valueOf(editB3.getText().toString());	
    		
    		double dbKouTuBorder=Double.valueOf(editKouTuBorder.getText().toString());//得到屏高比
    		int intDeltaTime=Integer.valueOf(editDeltaTime.getText().toString());	//得到显示间隔
    		if((intR1>255)||(intG1>255)||(intB1>255)||(intR2>255)||(intG2>255)||(intB2>255)||(intR3>255)||(intG3>255)||(intB3>255))	//判断输入合法性
    		{  //如果输入的颜色值不合法
    			OnShowDlg("RGB值范围为0~255，请重新输入!");
    			return;
    		}
    		if(dbKouTuBorder>0.5 || dbKouTuBorder<0.01)//如果屏高比不合法
    		{
    			OnShowDlg("屏高比范围0.01~0.5!");
    			return;
    		}
    		if(intDeltaTime>120 || intDeltaTime<5)//如果显示间隔不合法
    		{
    			intDeltaTime=intDeltaTime>120?120:5;//限定到合法范围内
    			editDeltaTime.setText(Integer.toString(intDeltaTime));//设置显示间隔文本框的值
    		}

    		try 
    		{
    			//下面的语句依次向服务器发送参数设置指令
    			//发送RGB1参数
        		myClientSocket.writer.println("config.matting.RGB1.R="+intR1);
				answerMessage=myClientSocket.br.readLine();//接收数据，不作任何处理，下同
				OnShowDlg("正在发送抠图设置参数...");
        		myClientSocket.writer.println("config.matting.RGB1.G="+intG1);
				answerMessage=myClientSocket.br.readLine();//接收数据
        		myClientSocket.writer.println("config.matting.RGB1.B="+intB1);
				answerMessage=myClientSocket.br.readLine();//接收数据
				//发送RGB2参数
        		myClientSocket.writer.println("config.matting.RGB2.R="+intR2);
				answerMessage=myClientSocket.br.readLine();//接收数据
        		myClientSocket.writer.println("config.matting.RGB2.G="+intG2);
				answerMessage=myClientSocket.br.readLine();//接收数据
        		myClientSocket.writer.println("config.matting.RGB2.B="+intB2);
				answerMessage=myClientSocket.br.readLine();//接收数据
				//发送RGB3参数
        		myClientSocket.writer.println("config.matting.RGB3.R="+intR3);
				answerMessage=myClientSocket.br.readLine();//接收数据
        		myClientSocket.writer.println("config.matting.RGB3.G="+intG3);
				answerMessage=myClientSocket.br.readLine();//接收数据
        		myClientSocket.writer.println("config.matting.RGB3.B="+intB3);
				answerMessage=myClientSocket.br.readLine();//接收数据
				//发送屏高比
        		myClientSocket.writer.println("config.matting.border="+dbKouTuBorder);
				answerMessage=myClientSocket.br.readLine();//接收数据
				//发送显示间隔
        		myClientSocket.writer.println("config.matting.deltaTime="+intDeltaTime);
				answerMessage=myClientSocket.br.readLine();//接收数据
		    	textNowState.setText("连接正常，可以进行操作");//设置客户端运行状态
			} 
    		catch (IOException e) //如果发生错误
    		{
				OnShowDlg("发送失败，请检查网络");
				return;
			}  
    		break;
    		
		case R.id.bOKComb://如果是纹理合成确定按钮	
    		int intBlockSize=Integer.valueOf(editBlockSize.getText().toString());//得到块大小
    		int intBlockNum=Integer.valueOf(editBlockNum.getText().toString());	//得到块个数	
    		//得到屏高比
    		double dbWenLiHeChengBorder=Double.valueOf(editWenLiHeChengBorder.getText().toString());
    		if((intBlockSize>1000)||(intBlockSize<1))//如果块大小不合法
    		{
    			OnShowDlg("块大小范围1~1000!");
    			return;
    		}
    		if((intBlockNum>480000))//如果块个数不合法
    		{
    			OnShowDlg("块个数范围0~480000!");
    			return;
    		}
    		if(dbWenLiHeChengBorder>0.5 || dbWenLiHeChengBorder<0.01)//如果屏高比不合法
    		{
    			OnShowDlg("屏高比范围0.01~0.5!");
    			return;
    		}

    		try 
    		{
    			//向服务器发送块大小参数
        		myClientSocket.writer.println("config.filling.block.size="+intBlockSize);
				answerMessage=myClientSocket.br.readLine();//接收数据
        		OnShowDlg("正在发送纹理合成参数...");
        		//向服务器发送块个数参数
        		myClientSocket.writer.println("config.filling.block.num="+intBlockNum);
				answerMessage=myClientSocket.br.readLine();//接收数据
				//向服务器发送屏高比参数
        		myClientSocket.writer.println("config.filling.border="+dbWenLiHeChengBorder);
				answerMessage=myClientSocket.br.readLine();//接收数据
		    	textNowState.setText("连接正常，可以进行操作");//设置客户端运行状态
			} 
    		catch (IOException e) //如果发生错误
    		{
				OnShowDlg("发送失败，请检查网络");
				return;
			}  	
    		break;
    		
		case R.id.bOKLab: //如果是自动lab校正确定按钮
    		int intLab=Integer.valueOf(editLabSimilarity.getText().toString());//得到lab阈值
    		int intMaxCorrect=Integer.valueOf(editMaxCorrect.getText().toString());//得到最大校正次数
       		double dbLabBorder=Double.valueOf(editLabBorder.getText().toString());//得到屏高比
       		int intDeltTime=Integer.valueOf(editRunDeltTime.getText().toString()); //得到定时间隔
    		if((intDeltTime>7200)||(intDeltTime<1))//如果定时间隔不合法
    		{
    			OnShowDlg("运行间隔范围1~7200 秒!");
    			return;
    		}
    		if((intLab>10)||(intLab<1))//如果lab阈值不合法
    		{
    			OnShowDlg("区域相似性阈值范围1~10!");
    			return;
    		}
    		if(intMaxCorrect>20)//如果最大校正次数不合法
    		{
    			OnShowDlg("最大纠正次数范围0~20!");
    			return;
    		}
    		if(dbLabBorder>0.5 || dbLabBorder<0.01)//如果屏高比不合法
    		{
    			OnShowDlg("屏高比范围0.01~0.5!");
    			return;
    		}

    		try 
    		{
    			//发送lab阈值参数
        		myClientSocket.writer.println("config.evaluation.labThreshold="+intLab);
				answerMessage=myClientSocket.br.readLine();//接收数据
				OnShowDlg("正在发送自动Lab校正参数...");
				//发送最大校正次数
        		myClientSocket.writer.println("config.evaluation.iteration="+intMaxCorrect); 
				answerMessage=myClientSocket.br.readLine();//接收数据
				//发送屏高比参数
        		myClientSocket.writer.println("config.evaluation.border="+dbLabBorder);
				answerMessage=myClientSocket.br.readLine();//接收数据
				//发送定时间隔参数
           		myClientSocket.writer.println("config.evaluation.interval="+intDeltTime);  
				answerMessage=myClientSocket.br.readLine();//接收数据
		    	textNowState.setText("连接正常，可以进行操作");//设置客户端运行状态
			} 
    		catch (IOException e) //如果发生错误
    		{
				OnShowDlg("发送失败，请检查网络");
				return;
			}	
    		break;
    		   		
		case R.id.bDoComb://如果是纹理合成执行按钮
    		try
    		{
    			//向服务器发送执行一次指令
    			myClientSocket.writer.println("donce()"); 
    			answerMessage=myClientSocket.br.readLine();//接收数据
    	    	textNowState.setText("连接正常，可以进行操作");//设置客户端运行状态
    		}
       		catch (IOException e) //如果发生错误
    		{
				OnShowDlg("发送失败，请检查网络");
				return;
			}
    		break;

		case R.id.bDoLab://如果是自动lab校正自动按钮
    		try
    		{
    			//向服务器发送定时执行指令
    			myClientSocket.writer.println("autimer()"); 
    			answerMessage=myClientSocket.br.readLine();//接收数据
    	    	textNowState.setText("连接正常，可以进行操作");//设置客户端运行状态
    		}
       		catch (IOException e) //如果发生错误
    		{
				OnShowDlg("发送失败，请检查网络");
				return;
			}   
    		break;

		case R.id.bShoot: //如果是抓图按钮
    		try 
    		{
/*
 				OnShowDlg("正在接收图片...请耐心等待!");
				URL url=new URL("http://"+myClientSocket.final_IP+":32766/tyr.jpg");
				connHttp=(HttpURLConnection)url.openConnection();
				InputStream is=connHttp.getInputStream();
				FileOutputStream os=new FileOutputStream("/sdcard/Received.jpg");
    			byte[] bytes=new byte[1024];
    			int fileLength=-1;
    			textNowState.setText("正在接收图片...");
    			while((fileLength=is.read(bytes))!=-1) 
    			{
    				os.write(bytes,0,fileLength);
    			} 
   			    is.close();
    			os.close();
    			BitmapFactory.Options bmpFactoryOptions=new BitmapFactory.Options();
       			Bitmap bmp=BitmapFactory.decodeFile("/sdcard/Received.jpg", bmpFactoryOptions);
    			imgShow.setImageBitmap(bmp); 
    			textNowState.setText("图片已接收完成");
*/
    			
	 			OnShowDlg("正在接收图片...请耐心等待!");
				String url="http://"+myClientSocket.final_IP+":80/cap.jpg";//创建图片链接
    			HttpClient client=new DefaultHttpClient();//构造HTTP客户端对象
    			HttpGet get=new HttpGet(url);//构造HTTP请求
    			HttpResponse response=client.execute(get);//执行请求
    			if(response.getStatusLine().getStatusCode()!=HttpStatus.SC_OK)//如果响应失败
    			{
    				OnShowDlg("图片接受失败!");
    				return;
    			}
    			HttpEntity entity=response.getEntity();//得到返回实体
    			InputStream is=entity.getContent();//得到返回的数据流
/*				FileOutputStream os=new FileOutputStream("/sdcard/Received.jpg");
    			byte[] bytes=new byte[1024];
    			int fileLength=-1;
    			textNowState.setText("正在接收图片...");
    			while((fileLength=is.read(bytes))!=-1) 
    			{
    				os.write(bytes,0,fileLength);
    			} 
   			    is.close();
    			os.close();
    			BitmapFactory.Options bmpFactoryOptions=new BitmapFactory.Options();
       			Bitmap bmp=BitmapFactory.decodeFile("/sdcard/Received.jpg", bmpFactoryOptions);
*/				Bitmap bmp=BitmapFactory.decodeStream(is);//从数据中构建位图
				imgShow.setImageBitmap(bmp); //显示图像
    			is.close();//关闭数据流
    			textNowState.setText("图片已接收完成");	//设置客户端运行状态
				
/*
				OnShowDlg("正在接收图片...请耐心等待!");
				URL url=new URL("http://"+myClientSocket.final_IP+":80/cap.jpg");
				connHttp=(HttpURLConnection)url.openConnection();
	            connHttp.setDoInput(true);
	            connHttp.connect();
	            InputStream is=connHttp.getInputStream();
	            Bitmap bmp=BitmapFactory.decodeStream(is);
	            is.close();
	            imgShow.setImageBitmap(bmp); 
	            textNowState.setText("图片已接收完成");	 
*/ 
			} 
    		catch (MalformedURLException e) //如果发生错误
    		{

			} 
       		catch (IOException e) //如果发生错误
    		{
				OnShowDlg("接收图片失败，请检查网络");
				return;
			}
    		break;		
    		
		case R.id.bRefresh: //如果是刷新按钮
			//以下内容的详细注释请参见clickSet(View view)函数
    		answerMessage="";//接收到的数据
     		try 
    		{
        		myClientSocket.writer.println("?"); //向服务器发送查询指令
    			answerMessage=myClientSocket.br.readLine();//接收数据
	   			if(answerMessage==null) //如果网络连接错误
    			{
    		   		textIsConnected.setText("未连接 ");//设置连接状态文字
    		   		OnShowDlg("网络异常，请重新连接!");
    	    		textIsConnected.setTextColor(Color.WHITE);//设置连接状态文字颜色
    	    		OnInitialButtons(false);//设置未连接按钮状态
    	    		//下面都是改变页面控件状态
    	    		btnSetConnect.setChecked(false);
    	    		textNowState.setText("目前没有连接");
    	    		this.btnConnect.setEnabled(true);
    	    		this.btnConnect.setChecked(false);
    	    		this.btnConnect.setText("连接");
    	    		myClientSocket.closeSocket();//关闭网络通信套接字
    				return;
    			}
    			int strlen=answerMessage.length();//接收到的字符串长度
    	  		String json=answerMessage.substring(0,strlen-2)+"}";//构造Json字符串
        		JSONObject object;//声明Json对象
    			try 
    			{
    				object=(JSONObject) new JSONTokener(json).nextValue();//构造Json对象
    				//以下为解析Json数据并为控件赋值
    				//设置R1
					editR1.setText(object.getString("config.matting.RGB1.R").toString());
					//设置G1
					editG1.setText(object.getString("config.matting.RGB1.G").toString());
					//设置B1
					editB1.setText(object.getString("config.matting.RGB1.B").toString());
					//设置R2
					editR2.setText(object.getString("config.matting.RGB2.R").toString());
					//设置G2
					editG2.setText(object.getString("config.matting.RGB2.G").toString());
					//设置B2
					editB2.setText(object.getString("config.matting.RGB2.B").toString());
					//设置R3
					editR3.setText(object.getString("config.matting.RGB3.R").toString());
					//设置G3
					editG3.setText(object.getString("config.matting.RGB3.G").toString());
					//设置B3
					editB3.setText(object.getString("config.matting.RGB3.B").toString());
					//设置抠图屏高比
    			    editKouTuBorder.setText(object.getString("config.matting.border").toString());
    			    //设置抠图显示间隔
    			    editDeltaTime.setText(object.getString("config.matting.deltaTime").toString());
    			    //设置纹理合成块大小
    				editBlockSize.setText(object.getString("config.filling.block.size").toString());
    				//设置纹理合成块个数
    				editBlockNum.setText(object.getString("config.filling.block.num").toString());
    				//设置纹理合成屏高比
    				editWenLiHeChengBorder.setText(object.getString("config.filling.border").toString());
    				//设置lab阈值
    				editLabSimilarity.setText(object.getString("config.evaluation.labThreshold").toString());
    				//设置最大校正次数
    				editMaxCorrect.setText(object.getString("config.evaluation.iteration").toString());
    				//设置颜色校正屏高比
    				editLabBorder.setText(object.getString("config.evaluation.border").toString());
    				//设置定时时间
    				editRunDeltTime.setText(object.getString("config.evaluation.interval").toString());
    				//设置L
    				editLabL.setText(object.getString("config.evaluation.current.L").toString());
    				//设置a
    				editLabA.setText(object.getString("config.evaluation.current.a").toString());
    				//设置b
    				editLabB.setText(object.getString("config.evaluation.current.b").toString());	
    				//设置服务器运行状态
    				textNowState.setText(object.getString("server.status").toString());
    				
    			} 
    			catch (JSONException e) //如果发生错误
    			{
    				OnShowDlg("更新数据失败!");
    				return;
    			}    		
    		} 
    		catch (IOException e) //如果发生错误
    		{
    			OnShowDlg("更新数据失败!");
    			return;
    		}
			break;
			
		case R.id.bDoOneTimeLab://如果是手动lab校正执行一次按钮
    		try
    		{
    			//向服务器发送关闭定时器指令
    			myClientSocket.writer.println("disautimer()"); 
    			answerMessage=myClientSocket.br.readLine();//接收数据
    			//向服务器发送自动执行一次指令
    			myClientSocket.writer.println("autonce()"); 
    			answerMessage=myClientSocket.br.readLine(); //接收数据
    			textNowState.setText("连接正常，可以进行操作");//设置客户端运行状态
    		}
       		catch (IOException e) //如果发生错误
    		{
				OnShowDlg("发送失败，请检查网络");
				return;
			}   
    		break;
			
    	default:break;
		}
    }
    
    public class SocketClient	//Socket通信类
    {               
    	public Socket client;//通信套接字
        public InputStream serverReader;//输入流
        public BufferedReader br;
        public PrintStream writer;//输出流
        public String final_IP; //服务器IP地址
    	
    	public SocketClient(final String site,final int port) //构造函数
    	{
    		new Thread()//创建一个新线程
    		{
    			public void run() //线程的运行函数
    			{
    				try		//创建连接
    				{ 
    					textNowState.setText("正在连接服务器...");//设置客户端运行状态
    	    			client=new Socket(site,port);//尝试连接服务器
    	    			final_IP=site;//获得IP地址
    	    			isConnected=true;//连接成功的标志
    				}
    				catch(Exception e)		//无法连接
    				{                 
    					e.printStackTrace();//输出异常信息
    					Message message=handler.obtainMessage();//构造消息与主线程通信
    					message.what=1;//设置消息附加参数
    					message.arg1=1;//设置消息附加参数
    					handler.sendMessage(message);//发送消息
    				}			
    				if(isConnected==true)	//连接成功
    				{       
    					try
    					{
    						serverReader=client.getInputStream();//得到输入流
    						br=new BufferedReader(new InputStreamReader(serverReader,"utf-8"));
    						//构造输出打印流
    						writer=new PrintStream(client.getOutputStream(),true,"utf-8");
    						
    						Message message=handler.obtainMessage();//构造消息与主线程通信
    						message.what=2;//设置消息附加参数
    						message.arg1=1;//设置消息附加参数
    						handler.sendMessage(message);//发送消息
    					}
    					catch(Exception e)	//创建失败
    					{      
    						e.printStackTrace();//输出异常信息
    						isConnected=false;//连接失败的标志
    						Message message=handler.obtainMessage();//构造消息与主线程通信
    						message.what=1;//设置消息附加参数
    						message.arg1=2;//设置消息附加参数
    						handler.sendMessage(message);//发送消息
    					}
    				}
    			}
    		}.start();//开启线程
    	}
    	
    	public Handler handler=new Handler()//消息处理函数
    	{
			@Override
    		public void handleMessage(Message msg)
			{
				if(msg.what==1)		//连接出错
				{             
					switch(msg.arg1)
					{
					case 1://如果无法连接到服务器
						OnShowDlg("无法连接到服务器");
						break;
					case 2://如果已连接但无法建立输出流
						OnShowDlg("无法建立输入输出流");
						break;
					case 3:
						if(isConnected==true)//如果已连接
						{
							OnShowDlg("连接中断");
							isConnected=false;//连接失败的标志
						}
						break;
					}
					//以下代码设置控件的状态
					textIsConnected.setText("未连接");
					textIsConnected.setTextColor(Color.WHITE);
					textNowState.setText("当前没有连接");
					btnConnect.setText("连接");
					btnConnect.setEnabled(true);
					btnConnect.setChecked(false);
					OnInitialButtons(false);//设置未连接时的界面状态
				}
				else if(msg.what==2)	//连接无错误
				{
					switch(msg.arg1)
					{
					case 1: //连接成功
						//以下代码设置控件的状态
						textIsConnected.setText("已连接");
						textIsConnected.setTextColor(Color.GREEN);
						textNowState.setText("连接正常，可进行操作");
						btnConnect.setText("断开");
						btnConnect.setEnabled(true);
						OnInitialButtons(true);//设置成功连接时的界面状态
						
						answerMessage="";//接收到的数据
						myClientSocket.writer.println("?");//向服务器发送查询指令
				 		try 
			    		{
							answerMessage=myClientSocket.br.readLine();//接收数据
							int strlen=answerMessage.length();//得到接收字符串的长度
					  		String json=answerMessage.substring(0,strlen-2)+"}";//构造Json字符串
				    		JSONObject object;//声明Json对象
							try 
							{
			    				object=(JSONObject) new JSONTokener(json).nextValue();//构造Json对象
			    				//以下为解析Json数据并为控件赋值
			    				//设置R1
								editR1.setText(object.getString("config.matting.RGB1.R").toString());
								//设置G1
								editG1.setText(object.getString("config.matting.RGB1.G").toString());
								//设置B1
								editB1.setText(object.getString("config.matting.RGB1.B").toString());
								//设置R2
								editR2.setText(object.getString("config.matting.RGB2.R").toString());
								//设置G2
								editG2.setText(object.getString("config.matting.RGB2.G").toString());
								//设置B2
								editB2.setText(object.getString("config.matting.RGB2.B").toString());
								//设置R3
								editR3.setText(object.getString("config.matting.RGB3.R").toString());
								//设置G3
								editG3.setText(object.getString("config.matting.RGB3.G").toString());
								//设置B3
								editB3.setText(object.getString("config.matting.RGB3.B").toString());
								//设置抠图屏高比
			    			    editKouTuBorder.setText(object.getString("config.matting.border").toString());
			    			    //设置抠图显示间隔
			    			    editDeltaTime.setText(object.getString("config.matting.deltaTime").toString());
			    			    //设置纹理合成块大小
			    				editBlockSize.setText(object.getString("config.filling.block.size").toString());
			    				//设置纹理合成块个数
			    				editBlockNum.setText(object.getString("config.filling.block.num").toString());
			    				//设置纹理合成屏高比
			    				editWenLiHeChengBorder.setText(object.getString("config.filling.border").toString());
			    				//设置lab阈值
			    				editLabSimilarity.setText(object.getString("config.evaluation.labThreshold").toString());
			    				//设置最大校正次数
			    				editMaxCorrect.setText(object.getString("config.evaluation.iteration").toString());
			    				//设置颜色校正屏高比
			    				editLabBorder.setText(object.getString("config.evaluation.border").toString());
			    				//设置定时时间
			    				editRunDeltTime.setText(object.getString("config.evaluation.interval").toString());
			    				//设置L
			    				editLabL.setText(object.getString("config.evaluation.current.L").toString());
			    				//设置a
			    				editLabA.setText(object.getString("config.evaluation.current.a").toString());
			    				//设置b
			    				editLabB.setText(object.getString("config.evaluation.current.b").toString());	
			    				//设置服务器运行状态
			    				textNowState.setText(object.getString("server.status").toString());
							} 
							catch (JSONException e) //如果发生错误
							{
								OnShowDlg("数据更新失败!");
								return;
							}    		
						} 
			    		catch (IOException e)  //如果发生错误
			    		{
			    			OnShowDlg("数据更新失败!");
							return;
						}
						break;
					case 2: //传输图片
						textNowState.setText("正在接收图片("+Integer.toString(msg.arg2/1024)+"k)，请稍候");
						break;
					}
				}
			}
		};
	
		public void closeSocket() //关闭网络通信
		{
    		try
    		{
    		    client.shutdownInput();//关闭输入流
    		    client.shutdownOutput();//关闭输出流
    			if(!client.isClosed())//如果未关闭
    				client.close();//关闭套接字
    		}
    		catch(IOException e)//如果发生错误
    		{
    			e.printStackTrace();//输出错误信息
    		}
    		isConnected=false;//连接失败的标志
    	}		
    }

	public void OnShowDlg(String msg)	//显示弹出对话框
	{         
    	Toast.makeText(getApplicationContext(), msg, Toast.LENGTH_SHORT).show();//显示Toast提示框
    }
	
	public void onStartTrackingTouch(SeekBar seekBar) 
	{
		
	}

	public void onStopTrackingTouch(SeekBar seekBar) 
	{
		
	}
    
}
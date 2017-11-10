package njust.pr.homework.handwritting;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintStream;
import java.net.Socket;
import java.util.List;

import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.annotation.SuppressLint;
import android.app.Activity;
import android.graphics.PointF;
import android.view.View;
import android.view.Window;
import android.widget.EditText;
import android.widget.Toast;


public class MainActivity extends Activity 
{
	final int intPort=51113;
	final String FILE_NAME="config.dat";
	EditText editIP=null;
	MyPathView mpv = null;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) 
	{
		super.onCreate(savedInstanceState);
		requestWindowFeature(Window.FEATURE_NO_TITLE);
		
		setContentView(R.layout.activity_main);
		
		editIP = (EditText)findViewById(R.id.editIP);
		mpv = (MyPathView)findViewById(R.id.mpv);
		file(2);	//从文件中读取服务器的IP地址
	}
	
    public void clickClear(View view)
    { 
    	mpv.Clear();
    }
    
	@SuppressWarnings({ "unchecked", "unused" })
	public void clickFinish_EasyProtocol(View view)
    { 
		//以下代码是将一个文字的所有轨迹点序列组成Json格式的数据发送给服务器
		//具体的协议在文档中说明
		StringBuilder strOneTotal = new StringBuilder("{");   
    	for(int j=0; j<mpv.m_ObjList.size(); j++)							//得到一个文字的笔画数
    	{
    		List<PointF> tempList = (List<PointF>)mpv.m_ObjList.get(j);		//得到第j笔所经过的点列链表
    		StringBuilder strOnePath = new StringBuilder("[");
    		for(int i=0; i<tempList.size(); i++)
    		{
    			if(i==tempList.size()-1)
    				strOnePath.append("{\""+(int)tempList.get(i).x+"\""+":"+(int)tempList.get(i).y+"}");
    			else
    				strOnePath.append("{\""+(int)tempList.get(i).x+"\""+":"+(int)tempList.get(i).y+"},");
    		}
    		strOnePath.append("]");
    		
    		if(j==mpv.m_ObjList.size()-1)
    			strOneTotal.append("\""+(j+1)+"\""+":"+strOnePath);
    		else
    			strOneTotal.append("\""+(j+1)+"\""+":"+strOnePath+",");
    		
    	}
    	strOneTotal.append("}");
    	
		String strIP=editIP.getText().toString();
		//向服务器发送数据
		ClientSocket myClientSocket = new ClientSocket(strIP, intPort, strOneTotal.toString());
		
    	OnShowDlg("正在为您保存 . . .");
		strOneTotal.delete(0, strOneTotal.length());
		strOneTotal = null;
		myClientSocket = null;
    	mpv.Clear();
    	file(1);	//向文件中写入服务器的IP地址
    }
    
	public void OnShowDlg(String msg)	
	{         
    	Toast.makeText(getApplicationContext(), msg, Toast.LENGTH_SHORT).show();
    }
	
	//从（向）文件中读（写）IP地址
    public void file(int type)
    {        
    	if(type==1)				//save IP into file
    	{                   
    		String  tIP=editIP.getText().toString();
    		if((tIP!=""))
    		{
    			try
    			{
    				OutputStreamWriter out=new OutputStreamWriter(openFileOutput(FILE_NAME, 0));
    				out.write(tIP);
    				out.close();
    			}
    			catch(Throwable t)
    			{
    				
    	    	}
    		}
    		else
    			OnShowDlg("IP is essential !");
    	}
    	else if(type==2)		//read IP from file
    	{                       
    		try
    		{
    			InputStream in=openFileInput(FILE_NAME);
    			if(in!=null)
    			{
    				InputStreamReader tmp=new InputStreamReader(in);
    				BufferedReader reader=new BufferedReader(tmp);
    					
    				String tIP=reader.readLine();	
    				editIP.setText(tIP);
    				in.close();
    			}
    		}
    		catch(Throwable t)
    		{
    			
    		}
    	}
    }

    //通信类，向服务器发送数据
    public class ClientSocket
    {               
	    public Socket client=null;
	    public PrintStream writer=null;
	    public boolean isConnected=false;
	    	
	    public ClientSocket(final String site,final int port, final String strCmd)
	    {
	    	new Thread()
	    	{
	    		@Override
	    		public void run()
	    		{
	    			try										//connect to the server
	    			{ 
	    	    		client=new Socket(site,port);
	    	    		isConnected=true;
	    			}
	    			catch(Exception e)						//connecting failed
	    			{       
						isConnected=false;
	    				Message message=handler.obtainMessage();
	    				message.what=1;
	    				message.arg1=1;
	    				handler.sendMessage(message);
	    			}			
	    			if(isConnected==true)				//connecting successful
	    			{       
	    				try
	    				{
	    					writer=new PrintStream(client.getOutputStream(),true,"utf-8");
	    					writer.print(strCmd);
	    					
	    					Message message=handler.obtainMessage();
	    					message.what=2;
	    					message.arg1=1;
	    					handler.sendMessage(message);
	    				}
	    				catch(Exception e)					//creating iostream failed
	    				{      
	    					isConnected=false;
	    					Message message=handler.obtainMessage();
	    					message.what=1;
	    					message.arg1=2;
	    					handler.sendMessage(message);
	    				}
	    			}
	    		}
	    	}.start();
	    }
	    
	    @SuppressLint("HandlerLeak")
		public Handler handler=new Handler()
	    {
			@Override
	    	public void handleMessage(Message msg)
			{
				if(msg.what==1)							//failure
				{             
					switch(msg.arg1)
					{
					case 1:
						OnShowDlg("Connecting server failed!");
						break;
					case 2:
						OnShowDlg("Communicaion error!");
						closeSocket();
						break;
					}
				}
				else if(msg.what==2)
				{
					closeSocket();
				}
			}
	    };
	
		public void closeSocket()
		{
    		try
    		{
    		    client.shutdownInput();
    		    client.shutdownOutput();
    			if(!client.isClosed())
    				client.close();
    		}
    		catch(IOException e)
    		{
    			
    		}
    	}		
    }

}

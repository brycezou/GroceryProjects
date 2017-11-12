package zc.njust.BaiduMap;

import java.io.*;
import java.net.*;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import android.os.*;
import android.widget.*;
import android.telephony.TelephonyManager;
import android.view.KeyEvent;
import android.view.Window;
import android.annotation.SuppressLint;
import android.app.AlertDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.graphics.Canvas;
import android.graphics.drawable.Drawable;
import android.location.Location;
import com.baidu.mapapi.*;


import org.json.*;


public class SuperCarActivity extends MapActivity 
{
    final String strIP="192.168.1.106";
    final int LIST_NEARBY_CARS=1;
    final int CALL_A_CAR=2;
    final int WAIT_A_CAR=3;
    final int FORCE_EXIT=4;
    boolean IsCalledACar=false;
    
	TextView m_txtMyLocation = null;
    EditText m_editNumPerson = null;
    EditText m_editDestin = null;
	MapView  m_MapView = null;
    Drawable m_marker = null;
	
	LocationListener m_LocationListener = null;	//onResume时注册此listener，onPause时需要Remove
	MyLocationOverlay m_LocationOverlay = null;	//定位图层
	MKSearch m_Search = null;					//搜索模块，也可去掉地图模块独立使用
    MyOverItem overItem = null;

    List<Map<String, String>> m_carlist = new ArrayList<Map<String, String>>();      

    ClientSocket m_clientSocket = null;
    
    String strMyPosition="Latitude:-1,getLongitude:-1";		//表示当前地理坐标的Json格式的字符串
    String strToDisplayCar="";								//请求服务器返回附近出租车信息的请求字符串
    String strToCallCar="";									//招车请求字符串
    String strToForceExit="";
    String strIMEI="";										//客户手机的IMEI号码；根据手机区分客户
    String strToUpdateMyPosition="";						//叫车成功后向出租车方定时发送自己的位置信息
	String strCarNum="";									//所叫出租车的编号

    
    @Override
	protected void onCreate(Bundle savedInstanceState) 
	{
		super.onCreate(savedInstanceState);
		requestWindowFeature(Window.FEATURE_NO_TITLE);
        setContentView(R.layout.main);
        
        //得到手机的IMEI号码
		strIMEI=GetPhoneIMEI();			
		//初始化控件和地图相关的资源
        InitResource();					
        //注册定位监听事件
        m_LocationListener = new LocationListener()			
        {
			@Override
			public void onLocationChanged(Location location) 
			{
				if (location != null)
				{
					GeoPoint pt = new GeoPoint((int)(location.getLatitude()*1e6), (int)(location.getLongitude()*1e6));
					m_MapView.getController().animateTo(pt);	
					//地理坐标解码
					m_Search.reverseGeocode(pt);
					String strTemp=pt.toString().replace("GeoPoint: ", "").replace(" ", "")+",";
					//将地理坐标转换成为Json格式的字符串
					strMyPosition=strTemp.replace("Latitude","\"Latitude\"").replace("Longitude", "\"Longitude\"").replace(":", ":\"").replace(",", "\",");
				}
				
				if(IsCalledACar)
				{
					strToUpdateMyPosition="{\"From\":\"customer\","+"\"IMEI\":\""+strIMEI+"\","+strMyPosition+"\"Function\":\"update_both\","+"\"CarNumber\":\""+strCarNum+"\""+"}";
					m_clientSocket = null;
					m_clientSocket = new ClientSocket(strIP, 51111, WAIT_A_CAR); 	
				}
			}
        };       
        
        //首次登录服务器，并向服务器发出请求——招车前先查询附近的出租车信息
        m_clientSocket = new ClientSocket(strIP, 51111, LIST_NEARBY_CARS); 		
	}
    
	@Override
	protected void onPause() 
	{
		MyBaiduMapApp app = (MyBaiduMapApp)this.getApplication();
		app.m_BMapManager.getLocationManager().removeUpdates(m_LocationListener);
		m_LocationOverlay.disableMyLocation();
        m_LocationOverlay.disableCompass(); // 关闭指南针
		app.m_BMapManager.stop();		
		super.onPause();
	}
	
	@Override
	protected void onResume() 
	{
		MyBaiduMapApp app = (MyBaiduMapApp)this.getApplication();
		// 注册定位事件，定位后将地图移动到定位点
        app.m_BMapManager.getLocationManager().requestLocationUpdates(m_LocationListener);
        m_LocationOverlay.enableMyLocation();
        m_LocationOverlay.enableCompass(); // 打开指南针
		app.m_BMapManager.start();
		super.onResume();
	}
	
	@Override  
    public boolean onKeyDown(int keyCode, KeyEvent event)  
    {  
        if (keyCode == KeyEvent.KEYCODE_BACK )  
        {  
        	if(IsCalledACar)
        	{
        		String strTitle = "提示:\n您已成功招车, 退出后您将错过该车!";
				new AlertDialog.Builder(SuperCarActivity.this).setIcon(R.drawable.question).setTitle(
					strTitle).setPositiveButton("确定退出",
					new DialogInterface.OnClickListener()
					{
						public void onClick(DialogInterface dialog, int whichButton)
						{
							IsCalledACar=false;
							m_clientSocket=null;
							strToForceExit="{\"From\":\"customer\","+"\"IMEI\":\""+strIMEI+"\","+"\"Function\":\"force_exit\""+",\"CarNumber\":\""+strCarNum+"\"}";
							m_clientSocket = new ClientSocket(strIP, 51111, FORCE_EXIT); 
							MyBaiduMapApp app = (MyBaiduMapApp)SuperCarActivity.this.getApplication();
							app.m_BMapManager.getLocationManager().removeUpdates(m_LocationListener);
							m_LocationOverlay.disableMyLocation();
					        m_LocationOverlay.disableCompass();
							app.m_BMapManager.stop();
							m_carlist.clear();	
							SuperCarActivity.this.finish();
						}
					}).setNegativeButton("我点错了",
					new DialogInterface.OnClickListener()
					{
						public void onClick(DialogInterface dialog, int whichButton)
						{
	
						}
					}).show();
        	}
        	else
        	{
				MyBaiduMapApp app = (MyBaiduMapApp)SuperCarActivity.this.getApplication();
				app.m_BMapManager.getLocationManager().removeUpdates(m_LocationListener);
				m_LocationOverlay.disableMyLocation();
		        m_LocationOverlay.disableCompass();
				app.m_BMapManager.stop();
				m_carlist.clear();	
				this.finish();
        	}
        }  
          
        return true;     
    }  
  
	//得到手机的IMEI号码
	private String 	GetPhoneIMEI()
	{
		TelephonyManager telephonyManager= (TelephonyManager) this.getSystemService(Context.TELEPHONY_SERVICE);
		return telephonyManager.getDeviceId();
	}
	
	//初始化控件和地图相关的资源
	private void InitResource()
	{
		//关联控件及其id
        m_txtMyLocation = (TextView)findViewById(R.id.iMyLocation);
        m_MapView = (MapView)findViewById(R.id.iMapView);
		m_editDestin = (EditText)findViewById(R.id.editDestination);
		m_editNumPerson = (EditText)findViewById(R.id.editNumPerson);
		m_editNumPerson.setText("1");
		
		//初始化百度地图
        MyBaiduMapApp app = (MyBaiduMapApp)this.getApplication();
        InitBaiduMap(app);			
        
		//在地图上添加定位图层
        m_LocationOverlay = new MyLocationOverlay(this, m_MapView); 
		m_MapView.getOverlays().add(m_LocationOverlay);	
		
        //得到需要标在地图上的出租车标记图片资源
		m_marker = getResources().getDrawable(R.drawable.iconmarka);  
		//为maker定义位置和边界
		m_marker.setBounds(0, 0, m_marker.getIntrinsicWidth(), m_marker.getIntrinsicHeight()); 
	}
	
	//初始化百度地图
	private void InitBaiduMap(MyBaiduMapApp app)
	{
		if (app.m_BMapManager == null) 
		{
			app.m_BMapManager = new BMapManager(getApplication());
			app.m_BMapManager.init(app.myKey, new MyBaiduMapApp.MyGeneralListener());
		}
		app.m_BMapManager.start();
        super.initMapActivity(app.m_BMapManager);	//如果使用地图SDK，请初始化地图Activity
        
        m_MapView.setBuiltInZoomControls(true);
        m_MapView.getController().setZoom(16); 		//设置mapController的缩放级别为16
        m_MapView.setDrawOverlayWhenZooming(true);	//设置在缩放动画过程中也显示overlay,默认为不绘制

		m_Search = new MKSearch();
	    m_Search.init(app.m_BMapManager, new MKSearchListener() 
	    {
	        @Override
	        public void onGetPoiDetailSearchResult(int type, int error) 
	        {
	        }
	        
			public void onGetAddrResult(MKAddrInfo res, int error) 
			{
				if (error != 0) 
				{
					String str = String.format("错误号:%d", error);
					m_txtMyLocation.setText(str);
					return;
				}
				String strInfo = String.format(res.strAddr);
				m_txtMyLocation.setText(strInfo);
			}

			public void onGetPoiResult(MKPoiResult res, int type, int error) 
			{
			}
			public void onGetDrivingRouteResult(MKDrivingRouteResult res, int error) 
			{
			}
			public void onGetTransitRouteResult(MKTransitRouteResult res, int error) 
			{
			}
			public void onGetWalkingRouteResult(MKWalkingRouteResult res, int error) 
			{
			}
			public void onGetBusDetailResult(MKBusLineResult result, int iError) 
			{
			}
			@Override
			public void onGetSuggestionResult(MKSuggestionResult res, int arg1) 
			{
				// TODO Auto-generated method stub				
			}
	        @Override
	        public void onGetRGCShareUrlResult(String arg0, int arg1) 
	        {
	            // TODO Auto-generated method stub                
	        }
	    });
	}
	
	//显示弹出对话框
	public void OnShowDlg(String msg)	
	{         
    	Toast.makeText(getApplicationContext(), msg, Toast.LENGTH_SHORT).show();
    }
	
	@Override
	protected boolean isRouteDisplayed() 
	{
		// TODO Auto-generated method stub
		return false;
	}
		
	
	//******************************************************************************************
	//******************************************************************************************
	
	public class ClientSocket 
	{             
	    public Socket client=null;
	    public BufferedReader reader=null;
	    public PrintStream writer=null;
	    public boolean isConnected=false;
	    public String strFromServer="";
	    	
	    public ClientSocket(final String site, final int port, final int state)
	    {
	    	new Thread()
	    	{
	    		@Override
	    		public void run()
	    		{
	    			try		//创建连接
	    			{ 
	    	    		client=new Socket(site, port);
	    	    		isConnected=true;
	    			}
	    			catch(Exception e)		//无法连接
	    			{       
						isConnected=false;
	    				Message message=handler.obtainMessage();
	    				message.what=1;
	    				message.arg1=1;
	    				handler.sendMessage(message);
	    			}			
	    			if(isConnected==true)	//连接成功
	    			{       
	    				try
	    				{
	    					reader=new BufferedReader(new InputStreamReader(client.getInputStream(),"utf-8"));
	    					writer=new PrintStream(client.getOutputStream(),true,"utf-8");
	    					
					 		while(strMyPosition.equals("Latitude:-1,getLongitude:-1"));
					 		
					 		if(state==LIST_NEARBY_CARS)
					 		{
					 			strToDisplayCar="{\"From\":\"customer\","+strMyPosition+"\"Function\":\"query\""+"}";
					 			writer.print(strToDisplayCar);
					 			strFromServer=reader.readLine();
					 			
		    					Message message=handler.obtainMessage();
		    					message.what=2;
		    					message.arg1=1;
		    					handler.sendMessage(message);
					 		}
					 		else if(state==CALL_A_CAR)
					 		{
					 			writer.print(strToCallCar);
					 			strFromServer=reader.readLine();
					 			
		    					Message message=handler.obtainMessage();
		    					message.what=2;
		    					message.arg1=2;
		    					handler.sendMessage(message);
					 		}	
					 		else if(state==WAIT_A_CAR)
					 		{
					 			writer.print(strToUpdateMyPosition);
					 			strFromServer=reader.readLine();
					 			
		    					Message message=handler.obtainMessage();
		    					message.what=2;
		    					message.arg1=3;
		    					handler.sendMessage(message);
					 		}
					 		else if(state==FORCE_EXIT)
					 		{
					 			writer.print(strToForceExit);
					 		}
	    				}
	    				catch(Exception e)	//创建失败
	    				{      
	    					isConnected=false;
	    					closeSocket();
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
				if(msg.what==1)			//连接出错
				{             
					switch(msg.arg1)
					{
						case 1:	OnShowDlg("无法连接到服务器!");		break;
						case 2:	OnShowDlg("与服务器应答时出现错误!");	break;
					}	
				}
				else if(msg.what==2)	//无错误
				{
					switch(msg.arg1)
					{
					case 1:
						//OnShowDlg(strFromServer);
						closeSocket();
						if(strFromServer.equals("NoNearCars"))
						{
							OnShowDlg("对不起 , 目前没有空车!\n请您稍等...");
							return;
						}
						
				 		JSONObject object = null;
				 	    Map<String, String> map = null;  
						try 
						{
							object=(JSONObject) new JSONObject(strFromServer);
							JSONArray jsonArray = object.getJSONArray("Info");
							for (int i=0; i<jsonArray.length(); i++) 
							{
								//得到附近的第i辆出租车的信息：编号和地理坐标
								JSONObject item = jsonArray.getJSONObject(i);
								int num = item.getInt("Num");				
								int latitude = item.getInt("Latitude");
								int longitude = item.getInt("Longitude");
								
								//将每一辆出租车的信息存入MAP中，然后加入到链表里，以备后用
				                map = new HashMap<String, String>();      
				                map.put("Num", num+"");      
				                map.put("Latitude", latitude+""); 
				                map.put("Longitude", longitude+""); 
				                m_carlist.add(map);      
							}
						}
						catch (JSONException e) 
						{
							OnShowDlg("Json数据解析失败!");
							return;
						}  
						
						overItem = null;
						overItem = new MyOverItem(m_marker, SuperCarActivity.this, true);
						m_MapView.getOverlays().add(overItem); 
						m_carlist.clear();
						
						break;
					case 2:
						closeSocket();
						if(strFromServer.equals("no"))
						{
							OnShowDlg("对不起 , 您的请求被拒绝了!\n您可以试试其它车辆...");
							IsCalledACar=false;
							return;
						}
						else if(strFromServer.equals("yes"))
						{
							IsCalledACar=true;
						}
						
						break;
					case 3:
						//OnShowDlg(strFromServer);
						closeSocket();
						
						JSONObject object1 = null;
				 	    Map<String, String> map1 = null;  
						try 
						{
							object1=(JSONObject) new JSONObject(strFromServer);
							JSONArray jsonArray = object1.getJSONArray("Info");
							for (int i=0; i<jsonArray.length(); i++) 
							{
								//jsonArray.length()==1
								JSONObject item = jsonArray.getJSONObject(i);
								int num = item.getInt("Num");				
								int latitude = item.getInt("Latitude");
								int longitude = item.getInt("Longitude");
								
				                map1 = new HashMap<String, String>();      
				                map1.put("Num", num+"");      
				                map1.put("Latitude", latitude+""); 
				                map1.put("Longitude", longitude+""); 
				                m_carlist.add(map1);      
							}
						}
						catch (JSONException e) 
						{
							OnShowDlg("Json数据解析失败!");
							return;
						}  
						
						m_MapView.getOverlays().clear();
						overItem = null;
						overItem = new MyOverItem(m_marker, SuperCarActivity.this, false);
						m_MapView.getOverlays().add(m_LocationOverlay);	
						m_MapView.getOverlays().add(overItem); 
						m_carlist.clear();
					}
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
	
	
	//******************************************************************************************
	//******************************************************************************************
	
	class MyOverItem extends ItemizedOverlay<OverlayItem> 
	{
		public List<OverlayItem> m_GeoList = new ArrayList<OverlayItem>();
		//private Context m_Context;
		boolean m_EnableTouch;
		
		//将m_carlist中的数据转到m_GeoList中
		public MyOverItem(Drawable marker, Context context, boolean IsTouchable) 
		{
			super(boundCenterBottom(marker));
			//this.m_Context = context;
			m_EnableTouch = IsTouchable;
			
			for (Map<String, String> list : m_carlist) 
			{      
				String carNum = list.get("Num");
				int latitude = Integer.parseInt(list.get("Latitude"));      
				int longitude = Integer.parseInt(list.get("Longitude"));   
				
				GeoPoint pt = new GeoPoint(latitude, longitude);
				//构造OverlayItem的三个参数依次为：item的位置，标题文本，文字片段
				m_GeoList.add(new OverlayItem(pt, "", ""+carNum));	
			}

			populate();  //createItem(int)方法构造item。一旦有了数据，在调用其它方法前，首先调用这个方法
		}

		//可以在地图上绘制自定义内容
		@Override
		public void draw(Canvas canvas, MapView mapView, boolean shadow) 
		{
			/*
				//Projection接口用于屏幕像素坐标和经纬度坐标之间的变换
				Projection projection = mapView.getProjection(); 
				for (int index = size() - 1; index >= 0; index--) // 遍历m_GeoList
				{ 	
					//得到给定索引的item
					OverlayItem overLayItem = getItem(index); 
					//把经纬度变换到相对于MapView左上角的屏幕像素坐标
					Point point = projection.toPixels(overLayItem.getPoint(), null); 
					
					//绘制文本，可在此处添加自己的绘制代码
					Paint paintText = new Paint();
					paintText.setColor(Color.BLUE);
					paintText.setTextSize(15);
					String title = overLayItem.getTitle();
					canvas.drawText(title, point.x-30, point.y, paintText); // 绘制文本
				}
			*/
			super.draw(canvas, mapView, shadow);
			//调整一个drawable边界，使得（0，0）是这个drawable底部最后一行中心的一个像素
			//boundCenterBottom(marker);
		}

		//处理当点击事件	
		@Override
		protected boolean onTap(int i) 
		{
			if(m_EnableTouch)
			{
				setFocus(m_GeoList.get(i));
				strCarNum = m_GeoList.get(i).getSnippet();
							
				new AlertDialog.Builder(SuperCarActivity.this).setIcon(R.drawable.question).setTitle(
				"是否确定呼叫？").setPositiveButton("是",
						new DialogInterface.OnClickListener()
						{
							public void onClick(DialogInterface dialog, int whichButton)
							{
								m_clientSocket.closeSocket();
								
						 		String strNumPerson = m_editNumPerson.getText().toString();
						 		String strDestin = m_editDestin.getText().toString();			
						 		strToCallCar="{\"From\":\"customer\","+"\"IMEI\":\""+strIMEI+"\","+strMyPosition+"\"Function\":\"callcar\","+"\"CarNumber\":\""+strCarNum+"\","+"\"Destination\":\""+strDestin+"\","+"\"PersonNumber\":\""+strNumPerson+"\""+"}";
						 		m_clientSocket = null;
						 		m_clientSocket = new ClientSocket(strIP,51111,CALL_A_CAR); 
						 		
						 		OnShowDlg("请求已发送,请您稍等片刻!");
							}
						}).setNegativeButton("否",
						new DialogInterface.OnClickListener()
						{
							public void onClick(DialogInterface dialog, int whichButton)
							{
								OnShowDlg("请您重新选择!");
							}
						}).show();
			}
			
			return true;
		}

		@Override
		protected OverlayItem createItem(int i) 
		{
			// TODO Auto-generated method stub
			return m_GeoList.get(i);
		}

		public void updateOverlay()
		{
			populate();
		}

		@Override
		public int size() 
		{
			// TODO Auto-generated method stub
			return m_GeoList.size();
		}

		@Override
		public boolean onTap(GeoPoint arg0, MapView arg1) 
		{
			// TODO Auto-generated method stub
			return super.onTap(arg0, arg1);
		}
	}

}





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
	
	LocationListener m_LocationListener = null;	//onResumeʱע���listener��onPauseʱ��ҪRemove
	MyLocationOverlay m_LocationOverlay = null;	//��λͼ��
	MKSearch m_Search = null;					//����ģ�飬Ҳ��ȥ����ͼģ�����ʹ��
    MyOverItem overItem = null;

    List<Map<String, String>> m_carlist = new ArrayList<Map<String, String>>();      

    ClientSocket m_clientSocket = null;
    
    String strMyPosition="Latitude:-1,getLongitude:-1";		//��ʾ��ǰ���������Json��ʽ���ַ���
    String strToDisplayCar="";								//������������ظ������⳵��Ϣ�������ַ���
    String strToCallCar="";									//�г������ַ���
    String strToForceExit="";
    String strIMEI="";										//�ͻ��ֻ���IMEI���룻�����ֻ����ֿͻ�
    String strToUpdateMyPosition="";						//�г��ɹ�������⳵����ʱ�����Լ���λ����Ϣ
	String strCarNum="";									//���г��⳵�ı��

    
    @Override
	protected void onCreate(Bundle savedInstanceState) 
	{
		super.onCreate(savedInstanceState);
		requestWindowFeature(Window.FEATURE_NO_TITLE);
        setContentView(R.layout.main);
        
        //�õ��ֻ���IMEI����
		strIMEI=GetPhoneIMEI();			
		//��ʼ���ؼ��͵�ͼ��ص���Դ
        InitResource();					
        //ע�ᶨλ�����¼�
        m_LocationListener = new LocationListener()			
        {
			@Override
			public void onLocationChanged(Location location) 
			{
				if (location != null)
				{
					GeoPoint pt = new GeoPoint((int)(location.getLatitude()*1e6), (int)(location.getLongitude()*1e6));
					m_MapView.getController().animateTo(pt);	
					//�����������
					m_Search.reverseGeocode(pt);
					String strTemp=pt.toString().replace("GeoPoint: ", "").replace(" ", "")+",";
					//����������ת����ΪJson��ʽ���ַ���
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
        
        //�״ε�¼������������������������󡪡��г�ǰ�Ȳ�ѯ�����ĳ��⳵��Ϣ
        m_clientSocket = new ClientSocket(strIP, 51111, LIST_NEARBY_CARS); 		
	}
    
	@Override
	protected void onPause() 
	{
		MyBaiduMapApp app = (MyBaiduMapApp)this.getApplication();
		app.m_BMapManager.getLocationManager().removeUpdates(m_LocationListener);
		m_LocationOverlay.disableMyLocation();
        m_LocationOverlay.disableCompass(); // �ر�ָ����
		app.m_BMapManager.stop();		
		super.onPause();
	}
	
	@Override
	protected void onResume() 
	{
		MyBaiduMapApp app = (MyBaiduMapApp)this.getApplication();
		// ע�ᶨλ�¼�����λ�󽫵�ͼ�ƶ�����λ��
        app.m_BMapManager.getLocationManager().requestLocationUpdates(m_LocationListener);
        m_LocationOverlay.enableMyLocation();
        m_LocationOverlay.enableCompass(); // ��ָ����
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
        		String strTitle = "��ʾ:\n���ѳɹ��г�, �˳�����������ó�!";
				new AlertDialog.Builder(SuperCarActivity.this).setIcon(R.drawable.question).setTitle(
					strTitle).setPositiveButton("ȷ���˳�",
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
					}).setNegativeButton("�ҵ����",
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
  
	//�õ��ֻ���IMEI����
	private String 	GetPhoneIMEI()
	{
		TelephonyManager telephonyManager= (TelephonyManager) this.getSystemService(Context.TELEPHONY_SERVICE);
		return telephonyManager.getDeviceId();
	}
	
	//��ʼ���ؼ��͵�ͼ��ص���Դ
	private void InitResource()
	{
		//�����ؼ�����id
        m_txtMyLocation = (TextView)findViewById(R.id.iMyLocation);
        m_MapView = (MapView)findViewById(R.id.iMapView);
		m_editDestin = (EditText)findViewById(R.id.editDestination);
		m_editNumPerson = (EditText)findViewById(R.id.editNumPerson);
		m_editNumPerson.setText("1");
		
		//��ʼ���ٶȵ�ͼ
        MyBaiduMapApp app = (MyBaiduMapApp)this.getApplication();
        InitBaiduMap(app);			
        
		//�ڵ�ͼ����Ӷ�λͼ��
        m_LocationOverlay = new MyLocationOverlay(this, m_MapView); 
		m_MapView.getOverlays().add(m_LocationOverlay);	
		
        //�õ���Ҫ���ڵ�ͼ�ϵĳ��⳵���ͼƬ��Դ
		m_marker = getResources().getDrawable(R.drawable.iconmarka);  
		//Ϊmaker����λ�úͱ߽�
		m_marker.setBounds(0, 0, m_marker.getIntrinsicWidth(), m_marker.getIntrinsicHeight()); 
	}
	
	//��ʼ���ٶȵ�ͼ
	private void InitBaiduMap(MyBaiduMapApp app)
	{
		if (app.m_BMapManager == null) 
		{
			app.m_BMapManager = new BMapManager(getApplication());
			app.m_BMapManager.init(app.myKey, new MyBaiduMapApp.MyGeneralListener());
		}
		app.m_BMapManager.start();
        super.initMapActivity(app.m_BMapManager);	//���ʹ�õ�ͼSDK�����ʼ����ͼActivity
        
        m_MapView.setBuiltInZoomControls(true);
        m_MapView.getController().setZoom(16); 		//����mapController�����ż���Ϊ16
        m_MapView.setDrawOverlayWhenZooming(true);	//���������Ŷ���������Ҳ��ʾoverlay,Ĭ��Ϊ������

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
					String str = String.format("�����:%d", error);
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
	
	//��ʾ�����Ի���
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
	    			try		//��������
	    			{ 
	    	    		client=new Socket(site, port);
	    	    		isConnected=true;
	    			}
	    			catch(Exception e)		//�޷�����
	    			{       
						isConnected=false;
	    				Message message=handler.obtainMessage();
	    				message.what=1;
	    				message.arg1=1;
	    				handler.sendMessage(message);
	    			}			
	    			if(isConnected==true)	//���ӳɹ�
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
	    				catch(Exception e)	//����ʧ��
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
				if(msg.what==1)			//���ӳ���
				{             
					switch(msg.arg1)
					{
						case 1:	OnShowDlg("�޷����ӵ�������!");		break;
						case 2:	OnShowDlg("�������Ӧ��ʱ���ִ���!");	break;
					}	
				}
				else if(msg.what==2)	//�޴���
				{
					switch(msg.arg1)
					{
					case 1:
						//OnShowDlg(strFromServer);
						closeSocket();
						if(strFromServer.equals("NoNearCars"))
						{
							OnShowDlg("�Բ��� , Ŀǰû�пճ�!\n�����Ե�...");
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
								//�õ������ĵ�i�����⳵����Ϣ����ź͵�������
								JSONObject item = jsonArray.getJSONObject(i);
								int num = item.getInt("Num");				
								int latitude = item.getInt("Latitude");
								int longitude = item.getInt("Longitude");
								
								//��ÿһ�����⳵����Ϣ����MAP�У�Ȼ����뵽������Ա�����
				                map = new HashMap<String, String>();      
				                map.put("Num", num+"");      
				                map.put("Latitude", latitude+""); 
				                map.put("Longitude", longitude+""); 
				                m_carlist.add(map);      
							}
						}
						catch (JSONException e) 
						{
							OnShowDlg("Json���ݽ���ʧ��!");
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
							OnShowDlg("�Բ��� , �������󱻾ܾ���!\n������������������...");
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
							OnShowDlg("Json���ݽ���ʧ��!");
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
		
		//��m_carlist�е�����ת��m_GeoList��
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
				//����OverlayItem��������������Ϊ��item��λ�ã������ı�������Ƭ��
				m_GeoList.add(new OverlayItem(pt, "", ""+carNum));	
			}

			populate();  //createItem(int)��������item��һ���������ݣ��ڵ�����������ǰ�����ȵ����������
		}

		//�����ڵ�ͼ�ϻ����Զ�������
		@Override
		public void draw(Canvas canvas, MapView mapView, boolean shadow) 
		{
			/*
				//Projection�ӿ�������Ļ��������;�γ������֮��ı任
				Projection projection = mapView.getProjection(); 
				for (int index = size() - 1; index >= 0; index--) // ����m_GeoList
				{ 	
					//�õ�����������item
					OverlayItem overLayItem = getItem(index); 
					//�Ѿ�γ�ȱ任�������MapView���Ͻǵ���Ļ��������
					Point point = projection.toPixels(overLayItem.getPoint(), null); 
					
					//�����ı������ڴ˴�����Լ��Ļ��ƴ���
					Paint paintText = new Paint();
					paintText.setColor(Color.BLUE);
					paintText.setTextSize(15);
					String title = overLayItem.getTitle();
					canvas.drawText(title, point.x-30, point.y, paintText); // �����ı�
				}
			*/
			super.draw(canvas, mapView, shadow);
			//����һ��drawable�߽磬ʹ�ã�0��0�������drawable�ײ����һ�����ĵ�һ������
			//boundCenterBottom(marker);
		}

		//��������¼�	
		@Override
		protected boolean onTap(int i) 
		{
			if(m_EnableTouch)
			{
				setFocus(m_GeoList.get(i));
				strCarNum = m_GeoList.get(i).getSnippet();
							
				new AlertDialog.Builder(SuperCarActivity.this).setIcon(R.drawable.question).setTitle(
				"�Ƿ�ȷ�����У�").setPositiveButton("��",
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
						 		
						 		OnShowDlg("�����ѷ���,�����Ե�Ƭ��!");
							}
						}).setNegativeButton("��",
						new DialogInterface.OnClickListener()
						{
							public void onClick(DialogInterface dialog, int whichButton)
							{
								OnShowDlg("��������ѡ��!");
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





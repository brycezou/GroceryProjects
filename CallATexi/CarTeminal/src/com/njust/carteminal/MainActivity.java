package com.njust.carteminal;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintStream;
import java.net.Socket;
import java.util.ArrayList;
import java.util.List;

import android.annotation.SuppressLint;
import android.app.AlertDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.graphics.Canvas;
import android.graphics.drawable.Drawable;
import android.location.Location;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.view.Window;
import android.widget.TextView;
import android.widget.Toast;

import com.baidu.mapapi.*;

import org.json.*;


public class MainActivity extends MapActivity 
{
    final String strIP="192.168.1.106";
    final int UPDATE_CAR_POSITION=1;
    final int REFULSE_OR_ACCEPT=2;
    boolean IsOnBusiness=false;
    boolean isComming = true;
    final int carNum = 5;
    
	TextView m_txtMyLocation = null;
	MapView  m_MapView = null;
    Drawable m_marker = null;
	
	LocationListener m_LocationListener = null;	//onResumeʱע���listener��onPauseʱ��ҪRemove
	MyLocationOverlay m_LocationOverlay = null;	//��λͼ��
	MKSearch m_Search = null;					//����ģ�飬Ҳ��ȥ����ͼģ�����ʹ��
    MyOverItem overItem = null;
    
	ClientSocket m_clientSocket = null;
	
	String strMyPosition="Latitude:-1,getLongitude:-1";	//��ʾ��ǰ���������Json��ʽ���ַ���
    String strReplyForCallCar="";
    String strToUpdatePos="";
	int longitude=0;
	int latitude=0;      
	
	
	@Override
	protected void onCreate(Bundle savedInstanceState) 
	{
		super.onCreate(savedInstanceState);
		requestWindowFeature(Window.FEATURE_NO_TITLE);
		setContentView(R.layout.activity_main);
		      
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
				
				if(isComming)
				{
			        m_clientSocket = new ClientSocket(strIP, 51111, UPDATE_CAR_POSITION); 
				}
			}
        };       
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

	//��ʼ���ؼ��͵�ͼ��ص���Դ
	private void InitResource()
	{
		//�����ؼ�����id
        m_txtMyLocation = (TextView)findViewById(R.id.iMyLocation);
        m_MapView = (MapView)findViewById(R.id.iMapView);
		
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
	    			try						//��������
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
					 		
					 		if(state==UPDATE_CAR_POSITION)
					 		{				 			
					 			if(!IsOnBusiness)
					 			{
						 			strToUpdatePos="{\"From\":\"driver\","+strMyPosition+"\"Function\":\"update\","+"\"CarNumber\":\""+carNum+"\""+"}";
						 			writer.print(strToUpdatePos);
					 				strFromServer=reader.readLine();
					 				
					 				Message message=handler.obtainMessage();
					 				message.what=2;
					 				message.arg1=1;
					 				handler.sendMessage(message);
					 			}
					 			else
					 			{
						 			strToUpdatePos="{\"From\":\"driver\","+strMyPosition+"\"Function\":\"update_both\","+"\"CarNumber\":\""+carNum+"\""+"}";
						 			writer.print(strToUpdatePos);
					 				strFromServer=reader.readLine();
					 				
					 				Message message=handler.obtainMessage();
					 				message.what=2;
					 				message.arg1=3;
					 				handler.sendMessage(message);
					 			}
					 		}
					 		else if(state==REFULSE_OR_ACCEPT)
					 		{
					 			writer.print(strReplyForCallCar);
					 			
		    					Message message=handler.obtainMessage();
		    					message.what=2;
		    					message.arg1=2;
		    					handler.sendMessage(message);
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
						
						JSONObject object;
						String strDestin="";
						String strPersonNum="";
						try 
						{
							object=(JSONObject) new JSONTokener(strFromServer).nextValue();
							if(object.getString("IsCalled").equals("no"))
							{
								//OnShowDlg("��û���г���");
								return;
							}
							else
							{
								latitude = Integer.parseInt(object.getString("Latitude").replace("E+07", "4").replace(".", ""));
								longitude = Integer.parseInt(object.getString("Longitude").replace("E+08", "45").replace(".", ""));
								strPersonNum = object.getString("PersonNumber");
								strDestin = object.getString("Destination").equals("1")?"":object.getString("Destination");
								//OnShowDlg("�������г���");
							}
						}
						catch (JSONException e) 
						{
							OnShowDlg("Json���ݽ���ʧ��!");
							return;
						}  
						
					    overItem = new MyOverItem(m_marker, MainActivity.this);
						m_MapView.getOverlays().add(overItem); 
						
						isComming = false;
						String strTitle = "�����г�,�Ƿ����?\n����:"+strPersonNum+"  Ŀ�ĵ�:"+strDestin;
						new AlertDialog.Builder(MainActivity.this).setIcon(R.drawable.question).setTitle(
							strTitle).setPositiveButton("����",
							new DialogInterface.OnClickListener()
							{
								public void onClick(DialogInterface dialog, int whichButton)
								{
									OnShowDlg("���ѽ���������\n�뾡��ǰ���˿ʹ�,ף��˳��!");		
									strReplyForCallCar="{\"From\":\"driver\","+strMyPosition+"\"Function\":\"reply\","+"\"Reply\":\"yes\","+"\"CarNumber\":\""+carNum+"\""+"}";
									m_clientSocket = new ClientSocket(strIP, 51111, REFULSE_OR_ACCEPT); 
									IsOnBusiness=true;
									//isComming = true;
								}
							}).setNegativeButton("�ܾ�",
							new DialogInterface.OnClickListener()
							{
								public void onClick(DialogInterface dialog, int whichButton)
								{
									OnShowDlg("���ܾ�������!");	
									strReplyForCallCar="{\"From\":\"driver\","+strMyPosition+"\"Function\":\"reply\","+"\"Reply\":\"no\","+"\"CarNumber\":\""+carNum+"\""+"}";
									m_clientSocket = new ClientSocket(strIP, 51111, REFULSE_OR_ACCEPT); 
									IsOnBusiness=false;
									m_MapView.getOverlays().clear();
									m_MapView.getOverlays().add(m_LocationOverlay);	
									//isComming = true;
								}
							}).show();
						
						isComming = true;
	
						break;
					case 2:
						closeSocket();
						
						break;
					case 3:
						//OnShowDlg(strFromServer);
						closeSocket();
						
						JSONObject object1 = null;
						try 
						{
							object1=(JSONObject) new JSONTokener(strFromServer).nextValue();
							if(object1.getString("IsCalled").equals("yes"))
							{
								latitude = Integer.parseInt(object1.getString("Latitude").replace("E+07", "4").replace(".", ""));
								longitude = Integer.parseInt(object1.getString("Longitude").replace("E+08", "45").replace(".", ""));
							}
							else if(object1.getString("IsCalled").equals("force_exit"))
							{
								IsOnBusiness=false;
								m_MapView.getOverlays().clear();
								m_MapView.getOverlays().add(m_LocationOverlay);	
								OnShowDlg("�˿���ǿ���˳�,�����ȴ������˿�!");
								return;
							}
						}
						catch (JSONException e) 
						{
							OnShowDlg("Json���ݽ���ʧ��!");
							return;
						}  
						
						m_MapView.getOverlays().clear();
						overItem = null;
						overItem = new MyOverItem(m_marker, MainActivity.this);
						m_MapView.getOverlays().add(m_LocationOverlay);	
						m_MapView.getOverlays().add(overItem); 
						
						break;
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

		//��m_carlist�е�����ת��m_GeoList��
		public MyOverItem(Drawable marker, Context context) 
		{
			super(boundCenterBottom(marker));
			
			GeoPoint pt = new GeoPoint(latitude, longitude);
			//����OverlayItem��������������Ϊ��item��λ�ã������ı�������Ƭ��
			m_GeoList.add(new OverlayItem(pt, "", ""));	
			
			populate();  //createItem(int)��������item��һ���������ݣ��ڵ�����������ǰ�����ȵ����������
		}

		public void updateOverlay()
		{
			populate();
		}

		@Override
		public void draw(Canvas canvas, MapView mapView, boolean shadow) 
		{
			super.draw(canvas, mapView, shadow);
		}

		@Override
		protected OverlayItem createItem(int i) 
		{
			// TODO Auto-generated method stub
			return m_GeoList.get(i);
		}

		@Override
		public int size() 
		{
			// TODO Auto-generated method stub
			return m_GeoList.size();
		}
		
		@Override
		protected boolean onTap(int i) 
		{				
			return true;
		}

		@Override
		public boolean onTap(GeoPoint arg0, MapView arg1) 
		{
			// TODO Auto-generated method stub
			return super.onTap(arg0, arg1);
		}
	}

}

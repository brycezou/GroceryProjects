package com.njust.carteminal;

import android.app.Application;
import android.widget.Toast;

import com.baidu.mapapi.BMapManager;
import com.baidu.mapapi.MKEvent;
import com.baidu.mapapi.MKGeneralListener;

public class MyBaiduMapApp extends Application 
{
	static MyBaiduMapApp m_BMapApp;	
	//�ٶ�MapAPI�Ĺ�����
	BMapManager m_BMapManager = null;
	// ��ȨKey
	String myKey = "DCC93245F62181B7670BA818B62FFE5688E9760A";
	
	// �����¼���������������ͨ�������������Ȩ��֤�����
	static class MyGeneralListener implements MKGeneralListener 
	{
		@Override
		public void onGetNetworkState(int iError) 
		{
			Toast.makeText(MyBaiduMapApp.m_BMapApp.getApplicationContext(), 
							"���������������",Toast.LENGTH_LONG).show();
		}

		@Override
		public void onGetPermissionState(int iError) 
		{
			if (iError ==  MKEvent.ERROR_PERMISSION_DENIED) 
			{
				// ��ȨKey����
				Toast.makeText(MyBaiduMapApp.m_BMapApp.getApplicationContext(), 
						"����MyBaiduMapApp.java�ļ�������ȷ����ȨKey��",
						Toast.LENGTH_LONG).show();
			}
		}
	}

	@Override
    public void onCreate() 
	{
		m_BMapApp = this;
		m_BMapManager = new BMapManager(this);
		boolean isSuccess = m_BMapManager.init(this.myKey, new MyGeneralListener());
		// ��ʼ����ͼsdk�ɹ������ö�λ����ʱ��
		if (isSuccess) 
		{
		    m_BMapManager.getLocationManager().setNotifyInternal(11, 6);
		}
		else 
		{
		    // ��ͼsdk��ʼ��ʧ�ܣ�����ʹ��sdk
		}
		super.onCreate();
	}

	@Override
	//��������app���˳�֮ǰ����mapadpi��destroy()�����������ظ���ʼ��������ʱ������
	public void onTerminate() 
	{
		// TODO Auto-generated method stub
		if (m_BMapManager != null) 
		{
			m_BMapManager.destroy();
			m_BMapManager = null;
		}
		super.onTerminate();
	}
}


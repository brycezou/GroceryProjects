package com.njust.carteminal;

import android.app.Application;
import android.widget.Toast;

import com.baidu.mapapi.BMapManager;
import com.baidu.mapapi.MKEvent;
import com.baidu.mapapi.MKGeneralListener;

public class MyBaiduMapApp extends Application 
{
	static MyBaiduMapApp m_BMapApp;	
	//百度MapAPI的管理类
	BMapManager m_BMapManager = null;
	// 授权Key
	String myKey = "DCC93245F62181B7670BA818B62FFE5688E9760A";
	
	// 常用事件监听，用来处理通常的网络错误，授权验证错误等
	static class MyGeneralListener implements MKGeneralListener 
	{
		@Override
		public void onGetNetworkState(int iError) 
		{
			Toast.makeText(MyBaiduMapApp.m_BMapApp.getApplicationContext(), 
							"您的网络出错啦！",Toast.LENGTH_LONG).show();
		}

		@Override
		public void onGetPermissionState(int iError) 
		{
			if (iError ==  MKEvent.ERROR_PERMISSION_DENIED) 
			{
				// 授权Key错误：
				Toast.makeText(MyBaiduMapApp.m_BMapApp.getApplicationContext(), 
						"请在MyBaiduMapApp.java文件输入正确的授权Key！",
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
		// 初始化地图sdk成功，设置定位监听时间
		if (isSuccess) 
		{
		    m_BMapManager.getLocationManager().setNotifyInternal(11, 6);
		}
		else 
		{
		    // 地图sdk初始化失败，不能使用sdk
		}
		super.onCreate();
	}

	@Override
	//建议在您app的退出之前调用mapadpi的destroy()函数，避免重复初始化带来的时间消耗
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


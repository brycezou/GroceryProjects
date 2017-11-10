package njust.pr.homework.handwritting;

import java.util.ArrayList;
import java.util.List;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.Bitmap.Config;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Path;
import android.graphics.PointF;
import android.util.AttributeSet;
import android.util.DisplayMetrics;
import android.view.MotionEvent;
import android.view.View;

//自定义视图控件类
public class MyPathView extends View 
{
    Path   m_path = null;			//路径，用于保存当前的绘图轨迹
    Paint  m_paint = null;			//画笔，用于绘制图形
    PointF m_prePoint = null;		//用于记录每一个路径的起点
    Bitmap m_cacheBitmap = null;	//位图，用于保存绘图的中间状态
    Canvas m_cacheCanvas = null;    //临时画布
    boolean isToClear = false;		//是否清除画布内容
	public List<PointF> m_CharacterList = new ArrayList<PointF>();	//用于保存当前路径上的点列的链表
	public List<Object> m_ObjList = new ArrayList<Object>();		//用于保存上述链表的链表
    
    public MyPathView(Context context, AttributeSet attrs) 
    {
        super(context, attrs);
         
        m_path = new Path();						//创建路径
        
        m_paint = new Paint();						//创建画笔
        m_paint.setStrokeWidth(10);
        m_paint.setColor(Color.YELLOW);
        m_paint.setStyle(Paint.Style.STROKE);
        m_paint.setDither(true); 					//抗抖动，更饱满圆润
        m_paint.setAntiAlias(true);					//抗锯齿
        m_paint.setStrokeCap(Paint.Cap.ROUND);		//头尾圆润
        m_paint.setStrokeJoin(Paint.Join.ROUND); 	//关节处圆润
         
        m_prePoint = new PointF();
        
        DisplayMetrics metric = new DisplayMetrics();
        ((MainActivity)context).getWindowManager().getDefaultDisplay().getMetrics(metric);
        int width = metric.widthPixels;  			//屏幕宽度（像素）
        int height = metric.heightPixels;  			//屏幕高度（像素）
        m_cacheBitmap = Bitmap.createBitmap(width, height, Config.ARGB_8888);
        m_cacheCanvas = new Canvas(m_cacheBitmap);	//创建临时画布
    }
        
    //视图重绘函数
	@Override
    public void onDraw(Canvas canvas)
    {
		if(isToClear)											//如果要清除画布
		{
			super.onDraw(canvas);
			canvas.drawColor(Color.BLACK);						//设置背景颜色
			m_cacheBitmap.eraseColor(0);						//清除绘制中间结果的位图
			canvas.drawBitmap(m_cacheBitmap, 0, 0, m_paint);	
		}
		else
		{
			super.onDraw(canvas);
			canvas.drawColor(Color.BLACK);						//设置背景颜色
			canvas.drawBitmap(m_cacheBitmap, 0, 0, m_paint);	//绘制中间结果位图
			canvas.drawPath(m_path, m_paint); 					//在中间结果位图上添加当前所绘的路径 
		}
    }
       
	//触屏事件处理函数
    @Override
    public boolean onTouchEvent(MotionEvent event)
    {
        float x = event.getX();
        float y = event.getY();									//获取触点的坐标值

        switch(event.getAction())
        {
        case MotionEvent.ACTION_DOWN:
             
            m_path.moveTo(x, y);
            m_prePoint.x = x;
            m_prePoint.y = y;									//记录起始点坐标
            
			m_CharacterList.clear();							//清空点列链表
			m_CharacterList.add(new PointF(x, y));				//将起始点加入当前的点列链表
			
			isToClear = false;
             
            break;
        case MotionEvent.ACTION_MOVE:
             
        	m_path.quadTo(m_prePoint.x, m_prePoint.y, x, y);	//在前一个点和当前点之间绘制路径
        	m_prePoint.x = x;									//将当前点标记为前一个点
        	m_prePoint.y = y;
            
        	m_CharacterList.add(new PointF(x, y));				//将当前点加入链表中
        	invalidate();										//刷新
             
            break;
        case MotionEvent.ACTION_UP:
             
            m_cacheCanvas.drawPath(m_path, m_paint);			//在临时画布上绘制出路径
            m_path.reset();										//重置当前路径
            
			List<PointF> tempList = new ArrayList<PointF>(); 
			for(int i=0; i<m_CharacterList.size(); i++)			//将当前点列中的点都存储到新的点列中
			{
				tempList.add(m_CharacterList.get(i));
			}
			m_ObjList.add(tempList);							//将新的点列链表加入到链表中					
            invalidate();										//刷新
            
            break;    
        }
        
        return true;
    }

    public void Clear()
    {
    	m_ObjList.clear();
    	isToClear = true;
    	invalidate();
    }
        
}

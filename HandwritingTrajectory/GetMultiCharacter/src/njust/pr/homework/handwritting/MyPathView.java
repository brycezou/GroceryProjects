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

//�Զ�����ͼ�ؼ���
public class MyPathView extends View 
{
    Path   m_path = null;			//·�������ڱ��浱ǰ�Ļ�ͼ�켣
    Paint  m_paint = null;			//���ʣ����ڻ���ͼ��
    PointF m_prePoint = null;		//���ڼ�¼ÿһ��·�������
    Bitmap m_cacheBitmap = null;	//λͼ�����ڱ����ͼ���м�״̬
    Canvas m_cacheCanvas = null;    //��ʱ����
    boolean isToClear = false;		//�Ƿ������������
	public List<PointF> m_CharacterList = new ArrayList<PointF>();	//���ڱ��浱ǰ·���ϵĵ��е�����
	public List<Object> m_ObjList = new ArrayList<Object>();		//���ڱ����������������
    
    public MyPathView(Context context, AttributeSet attrs) 
    {
        super(context, attrs);
         
        m_path = new Path();						//����·��
        
        m_paint = new Paint();						//��������
        m_paint.setStrokeWidth(10);
        m_paint.setColor(Color.YELLOW);
        m_paint.setStyle(Paint.Style.STROKE);
        m_paint.setDither(true); 					//��������������Բ��
        m_paint.setAntiAlias(true);					//�����
        m_paint.setStrokeCap(Paint.Cap.ROUND);		//ͷβԲ��
        m_paint.setStrokeJoin(Paint.Join.ROUND); 	//�ؽڴ�Բ��
         
        m_prePoint = new PointF();
        
        DisplayMetrics metric = new DisplayMetrics();
        ((MainActivity)context).getWindowManager().getDefaultDisplay().getMetrics(metric);
        int width = metric.widthPixels;  			//��Ļ��ȣ����أ�
        int height = metric.heightPixels;  			//��Ļ�߶ȣ����أ�
        m_cacheBitmap = Bitmap.createBitmap(width, height, Config.ARGB_8888);
        m_cacheCanvas = new Canvas(m_cacheBitmap);	//������ʱ����
    }
        
    //��ͼ�ػ溯��
	@Override
    public void onDraw(Canvas canvas)
    {
		if(isToClear)											//���Ҫ�������
		{
			super.onDraw(canvas);
			canvas.drawColor(Color.BLACK);						//���ñ�����ɫ
			m_cacheBitmap.eraseColor(0);						//��������м�����λͼ
			canvas.drawBitmap(m_cacheBitmap, 0, 0, m_paint);	
		}
		else
		{
			super.onDraw(canvas);
			canvas.drawColor(Color.BLACK);						//���ñ�����ɫ
			canvas.drawBitmap(m_cacheBitmap, 0, 0, m_paint);	//�����м���λͼ
			canvas.drawPath(m_path, m_paint); 					//���м���λͼ����ӵ�ǰ�����·�� 
		}
    }
       
	//�����¼�������
    @Override
    public boolean onTouchEvent(MotionEvent event)
    {
        float x = event.getX();
        float y = event.getY();									//��ȡ���������ֵ

        switch(event.getAction())
        {
        case MotionEvent.ACTION_DOWN:
             
            m_path.moveTo(x, y);
            m_prePoint.x = x;
            m_prePoint.y = y;									//��¼��ʼ������
            
			m_CharacterList.clear();							//��յ�������
			m_CharacterList.add(new PointF(x, y));				//����ʼ����뵱ǰ�ĵ�������
			
			isToClear = false;
             
            break;
        case MotionEvent.ACTION_MOVE:
             
        	m_path.quadTo(m_prePoint.x, m_prePoint.y, x, y);	//��ǰһ����͵�ǰ��֮�����·��
        	m_prePoint.x = x;									//����ǰ����Ϊǰһ����
        	m_prePoint.y = y;
            
        	m_CharacterList.add(new PointF(x, y));				//����ǰ�����������
        	invalidate();										//ˢ��
             
            break;
        case MotionEvent.ACTION_UP:
             
            m_cacheCanvas.drawPath(m_path, m_paint);			//����ʱ�����ϻ��Ƴ�·��
            m_path.reset();										//���õ�ǰ·��
            
			List<PointF> tempList = new ArrayList<PointF>(); 
			for(int i=0; i<m_CharacterList.size(); i++)			//����ǰ�����еĵ㶼�洢���µĵ�����
			{
				tempList.add(m_CharacterList.get(i));
			}
			m_ObjList.add(tempList);							//���µĵ���������뵽������					
            invalidate();										//ˢ��
            
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

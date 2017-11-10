package com.commonsware.android.CamControl;

//����java��
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.net.*;
import java.io.PrintStream;
//import java.io.FileOutputStream;

//����Android��
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

//����������
import org.apache.http.HttpEntity;
import org.apache.http.HttpResponse;
import org.apache.http.HttpStatus;
import org.apache.http.client.HttpClient;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.impl.client.DefaultHttpClient;
//import org.apache.http.params.HttpParams;
import org.json.*;

//Ӧ�ó�����
public class CamControlActivity extends Activity
{
	/** �����������  **/
	//1. ������ť
	ToggleButton btnConnect; 	//���Ӱ�ť
	ToggleButton btnSetConnect; //�����������ð�ť
	ToggleButton btnSetRGB; //��ͼ���ð�ť
	ToggleButton btnSetWenLiHeCheng;//����ϳ����ð�ť
	ToggleButton btnSetLabCorrect; //�Զ�labУ�����ð�ť
	ToggleButton btnSetManuLab;//�ֶ�labУ�����ð�ť
	
	Button btnOKConnect;//�������������е�ȷ����ť
	Button btnOKRGB; //��ͼ�����е�ȷ����ť
	Button btnOKWenLiHeCheng; //����ϳ������е�ȷ����ť
	Button btnWenLiHeChengDoIt;//����ϳ������е�ִ�а�ť
	
	Button btnSimilarityPlus; //Lab��ֵ�Ӱ�ť
	Button btnSimilarityMinus; //lab��ֵ����ť
	Button btnMaxCorrectPlus; //�����������Ӱ�ť
	Button btnMaxCorrectMinus; //��������������ť
	Button btnOKLabCorrect; //�Զ�LabУ��ȷ����ť
	Button btnLabDoIt; //�Զ�labУ���Զ���ť
	
	Button btnPlusL; //�ֶ�LabУ��L�Ӱ�ť
	Button btnPlusA;//�ֶ�LabУ��a�Ӱ�ť
	Button btnPlusB;//�ֶ�LabУ��b�Ӱ�ť
	Button btnMinusL;//�ֶ�LabУ��L����ť
	Button btnMinusA;//�ֶ�LabУ��a����ť
	Button btnMinusB;//�ֶ�LabУ��b����ť
	Button btnDoOneTimeLab; //�ֶ�LabУ��ִ��һ�ΰ�ť
	
	Button btnGetPicture; //ץͼ��ť
	Button btnRefresh; //ˢ�°�ť
		
	//2.���������
	EditText editIP; //������������IP�ı���
	EditText editPort;//�����������ö˿��ı���
	
	EditText editR1;//��ͼ����RGB1��1���ı���
	EditText editG1;//��ͼ����RGB1��2���ı���
	EditText editB1;//��ͼ����RGB1��3���ı���
	EditText editR2;//��ͼ����RGB2��1���ı���
	EditText editG2;//��ͼ����RGB2��2���ı���
	EditText editB2;//��ͼ����RGB2��3���ı���
	EditText editR3;//��ͼ����RGB3��1���ı���
	EditText editG3;//��ͼ����RGB3��2���ı���
	EditText editB3;//��ͼ����RGB3��3���ı���
	EditText editKouTuBorder; //��ͼ�������߱��ı���
	EditText editDeltaTime; //��ͼ������ʾ����ı���
	
	EditText editBlockSize; //����ϳɿ��С�ı���
	EditText editBlockNum; //����ϳɿ�����ı���
	EditText editWenLiHeChengBorder; //����ϳ����߱��ı���
	
	EditText editLabSimilarity; //lab��ֵ�ı���
	EditText editMaxCorrect; //�����������ı���
	EditText editLabBorder; //�Զ�labУ�����߱��ı���
	EditText editRunDeltTime; //�Զ�labУ�����м���ı���

	EditText editLabL;//L�ı���
	EditText editLabA;//a�ı���
	EditText editLabB;//b�ı���
	EditText editManuLabStep;//�����ı���
	
	//3.���������
	TableRow tableRowConnect;//�������ӱ��
	TableRow tableRowRGB;//��ͼ���ñ��
	TableRow tableRowWenLiHeCheng;//����ϳɱ��
	TableRow tableRowLab;//�Զ�labУ�����
	TableRow tableRowManuLab;//�ֶ�labУ�����
	
	//4.��������Ԫ��
	TextView textIsConnected;  //��ʾ�Ƿ�����
	TextView textNowState;  //״̬��Ϣ
	TableLayout tableMain; //��񲼾�
	ImageView imgShow; //ͼƬ��ʾ�ؼ�
	
	final String FILE_NAME="config.dat";    //�����ļ������ַ
	SocketClient myClientSocket;    //������Socket����
	boolean isConnected=false;         //�Ƿ�������	
	public String answerMessage; //���յ�������
	HttpURLConnection connHttp; //����ץͼ��HTTP���Ӷ���
	
    @Override
    public void onCreate(Bundle savedInstanceState) 
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);//������ͼ
        
        OnSetupLink();				//������������
    	OnSetupRow();         		//���۵��˵����г�ʼ��
    	file(2);            		//��ȡIP�Ͷ˿ڵ�ַ
    	OnInitialButtons(false); 	//��ʼ�����еİ�ť
    }
    
    public void OnSetupLink()	//������������
    {         
    	//1. ����ť���Ӧ����ͼ��ϵ����
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
    	
    	//2.���ı������Ӧ����ͼ��ϵ����
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
    	
    	//3.����������Ӧ����ͼ��ϵ����
    	tableRowConnect=(TableRow)findViewById(R.id.rConn);
    	tableRowRGB=(TableRow)findViewById(R.id.rRGB);
    	tableRowWenLiHeCheng=(TableRow)findViewById(R.id.rComb);
    	tableRowLab=(TableRow)findViewById(R.id.rLab);
    	tableRowManuLab=(TableRow)findViewById(R.id.rManuLab);
    	  	
    	//4.�������ؼ����Ӧ����ͼ��ϵ����
    	textIsConnected=(TextView)findViewById(R.id.tIsConn);
    	textNowState=(TextView)findViewById(R.id.tState);
    	tableMain=(TableLayout)findViewById(R.id.tbMain);
    	imgShow=(ImageView)findViewById(R.id.imgShow);
    }
    
    public void OnSetupRow()	//���۵��˵����г�ʼ��
    {          
    	tableMain.removeView(tableRowConnect);//�Ƴ����ӱ��
    	tableMain.removeView(tableRowRGB);//�Ƴ���ͼ���ñ��
    	tableMain.removeView(tableRowWenLiHeCheng);//�Ƴ�����ϳɱ��
    	tableMain.removeView(tableRowLab);//�Ƴ��Զ�labУ�����
    	tableMain.removeView(tableRowManuLab);//�Ƴ��ֶ�labУ�����
    }
    
    public void OnInitialButtons(boolean flag)	//���ð�ť״̬
    {
    	if(flag==false)	//�����δ����״̬
    	{          
    		//���ò��ְ�ť
    		btnSetConnect.setEnabled(true);
        	btnSetRGB.setEnabled(false);
        	btnSetWenLiHeCheng.setEnabled(false);
        	btnSetLabCorrect.setEnabled(false);
        	btnGetPicture.setEnabled(false);
        	btnRefresh.setEnabled(false);
        	btnSetManuLab.setEnabled(false);
        	//�Ƴ����б��
        	tableMain.removeView(tableRowConnect);
        	tableMain.removeView(tableRowRGB);
        	tableMain.removeView(tableRowWenLiHeCheng);
        	tableMain.removeView(tableRowLab);
        	tableMain.removeView(tableRowManuLab);
        	//���ÿ��ذ�ť��״̬
        	btnSetRGB.setChecked(false);
        	btnSetWenLiHeCheng.setChecked(false);
        	btnSetLabCorrect.setChecked(false);
        	btnSetManuLab.setChecked(false);
    	}
    	else //������ǳ����ʼ��,������Ҫ�ı䰴ť״̬
    	{
    		//ʹ�ܲ��ְ�ť
    		btnSetConnect.setEnabled(true);
        	btnSetRGB.setEnabled(true);
        	btnSetWenLiHeCheng.setEnabled(true);
        	btnSetLabCorrect.setEnabled(true);
        	btnSetManuLab.setEnabled(true);
        	btnGetPicture.setEnabled(true);
        	btnRefresh.setEnabled(true);
    	}
    }
    
    public void file(int type)	//��дIP��ַ�Ͷ˿ںŻ����ļ�
    {        
    	if(type==1)	//д�ļ�
    	{                   
    		String tIP,tPort;//��������
    		tIP=editIP.getText().toString(); //��ȡIP��ַ
    		tPort=editPort.getText().toString(); //��ȡ�˿ں�
    		if((tIP!="")&&(tPort!="")) //���IP��ַ�Ͷ˿ںŶ���Ϊ��
    		{
    			try 
    			{
    				//�������������
    				OutputStreamWriter out=new OutputStreamWriter(openFileOutput(FILE_NAME, 0));
    				out.write(tIP+"\n"+tPort); //д����
    				out.close(); //�ر������
    				OnShowDlg("���óɹ�����Ϣ�ѱ��棡");
    			}
    			catch(Throwable t) //��������쳣
    			{
    	    		OnShowDlg("��Ϣ����ʧ�ܣ�"+t.toString());
    	    	}
    		}
    		else //���IP��ַ��˿ں�Ϊ��
    			OnShowDlg("IP��ַ���˿ںŲ���Ϊ�գ�");
    	}
    	else if(type==2)	//���ļ�
    	{                       
    		try
    		{
    			String tIP,tPort; //��������
    			InputStream in=openFileInput(FILE_NAME); //���ļ�
    			if(in!=null)
    			{
    				//��ȡ�ļ�������
    				InputStreamReader tmp=new InputStreamReader(in);
    				BufferedReader reader=new BufferedReader(tmp);
    					
    				tIP=reader.readLine(); //��ȡIP��ַ
    				tPort=reader.readLine(); //��ȡ�˿ں�
    				
    				editIP.setText(tIP); //��IP��ַ�Ͷ˿ں���ʾ�ڿؼ���
    				editPort.setText(tPort);
    				in.close();//�ر�������
    			}
    		}
    		catch(Throwable t) //��������쳣
    		{
    			
    		}
    	}
    }
       
    public void clickConnect(View view)	//�������Ӱ�ť�¼�
    {     
    	if(isConnected==false)	//�����δ����
    	{              
    		textIsConnected.setText("������...");//��������״̬����
			textIsConnected.setTextColor(Color.YELLOW); //��������״̬������ɫ
			btnConnect.setEnabled(false); //���Ӱ�ťʧЧ
			textNowState.setText("�������������Խ��в���"); //���ÿͻ�������״̬
			String IP=editIP.getText().toString();//��ȡIP��ַ
			int Port=Integer.valueOf(editPort.getText().toString()); //��ȡ�˿ں�

			myClientSocket=new SocketClient(IP,Port);   //���ӷ�����
    	}
    	else //���������
    	{
    		textIsConnected.setText("δ���� ");//��������״̬����
    		textIsConnected.setTextColor(Color.WHITE);//��������״̬������ɫ
    		OnInitialButtons(false); //���ð�ť״̬
    		btnSetConnect.setText("�۵�"); //�����������ð�ť����
    		btnSetConnect.setChecked(false); //�����������ð�ť״̬
    		textNowState.setText("Ŀǰû������"); //���ÿͻ�������״̬
    		myClientSocket.closeSocket(); //�ر�ͨ���׽���
    	}
    }
    
    public void clickSet(View view)	//�������ð�ť��չ�����۵���Ӧ��Ŀ
    {	 		
    	ToggleButton button=(ToggleButton)view; //��ȡ��ť����
    	TableRow row;
    	int sum=2;	
    	if(view==btnSetConnect)//����������������ð�ť
    	{
    		row=tableRowConnect;//���õ�ǰ��
    		sum=4;
    	}
    	else if(view==btnSetRGB)//����ǿ�ͼ���ð�ť
    	{
    		row=tableRowRGB;//���õ�ǰ��
    		sum=5;
    		if(btnSetConnect.isChecked()==true) sum++; //�����չ���Ͷ�һ��
    	}
    	else if(view==btnSetWenLiHeCheng) //���������ϳ����ð�ť
    	{
    		row=tableRowWenLiHeCheng;//���õ�ǰ��
    		sum=6;
    		if(btnSetConnect.isChecked()==true) sum++;//�����չ���Ͷ�һ��
    		if(btnSetRGB.isChecked()==true) sum++;//�����չ���Ͷ�һ��
    	}
    	else if(view==btnSetLabCorrect)//������Զ�labУ�����ð�ť
    	{
    		row=tableRowLab;//���õ�ǰ��
    		sum=7;
    		if(btnSetConnect.isChecked()==true) sum++;//�����չ���Ͷ�һ��
    		if(btnSetRGB.isChecked()==true) sum++;//�����չ���Ͷ�һ��
    		if(btnSetWenLiHeCheng.isChecked()==true) sum++;//�����չ���Ͷ�һ��
    	}
    	else //������ֶ�labУ�����ð�ť
    	{
    		row=tableRowManuLab;//���õ�ǰ��
    		sum=8;
    		if(btnSetConnect.isChecked()==true) sum++;//�����չ���Ͷ�һ��
    		if(btnSetRGB.isChecked()==true) sum++;//�����չ���Ͷ�һ��
    		if(btnSetWenLiHeCheng.isChecked()==true) sum++;//�����չ���Ͷ�һ��
    		if(btnSetLabCorrect.isChecked()==true) sum++;//�����չ���Ͷ�һ��
    	}
    	
    	if(button.isChecked()==true) //����ǰ����˰�ť��չ������
    	{
    		switch(row.getId()) //����������һ����ť
    		{
       		case R.id.rConn: //��������Ӳ������ð�ť
    			tableMain.addView(row,sum);//չ���������Ӳ���������ͼ
    			return;
    		case R.id.rRGB: //����ǿ�ͼ���ð�ť
        		this.btnSetManuLab.setEnabled(false);
        		this.btnSetLabCorrect.setEnabled(false);
        		this.btnSetWenLiHeCheng.setEnabled(false);
        		tableMain.addView(row,sum);//չ����ͼ������ͼ
        		break;
    		case R.id.rComb://���������ϳ����ð�ť
    			this.btnSetRGB.setEnabled(false);
        		this.btnSetManuLab.setEnabled(false);
        		this.btnSetLabCorrect.setEnabled(false);
    			tableMain.addView(row,sum);//չ������ϳɲ���������ͼ
    			break;
    		case R.id.rLab: //������Զ�labУ�����ð�ť
    			this.btnSetRGB.setEnabled(false);
        		this.btnSetManuLab.setEnabled(false);
        		this.btnSetWenLiHeCheng.setEnabled(false);
        		tableMain.addView(row,sum);//չ���Զ�labУ��������ͼ
        		break;
    		case R.id.rManuLab: //������ֶ�labУ����ť
    			this.btnSetRGB.setEnabled(false);
        		this.btnSetLabCorrect.setEnabled(false);
        		this.btnSetWenLiHeCheng.setEnabled(false);
        		tableMain.addView(row,sum); //չ���ֶ�labУ��������ͼ
        		break;
    		default:break;
    		}
    
    		answerMessage="";//���յ�������
    		myClientSocket.writer.println("?");//����������Ͳ�ѯָ��
     		try 
    		{
    			answerMessage=myClientSocket.br.readLine();//��������
	   			if(answerMessage==null) //����������Ӵ���
    			{
    		   		textIsConnected.setText("δ���� ");//��������״̬����
    		   		OnShowDlg("�����쳣������������!");
    	    		textIsConnected.setTextColor(Color.WHITE);//��������״̬������ɫ
    	    		OnInitialButtons(false);//����δ���Ӱ�ť״̬
    	    		//���涼�Ǹı�ҳ��ؼ�״̬
    	    		btnSetConnect.setChecked(false);
    	    		textNowState.setText("Ŀǰû������");
    	    		this.btnConnect.setEnabled(true);
    	    		this.btnConnect.setChecked(false);
    	    		this.btnConnect.setText("����");
    	    		myClientSocket.closeSocket();//�ر�����ͨ���׽���
    				return;
    			}
	   			//���������������,����ܵ��˷�������������
    			int strlen=answerMessage.length();//��ȡ�ַ�������
    	  		String json=answerMessage.substring(0,strlen-2)+"}";//�����µ��ַ���
        		JSONObject object;//����Json����
    			try 
    			{
    				object=(JSONObject) new JSONTokener(json).nextValue();//����Json����
    				//����Ϊ����Json���ݲ�Ϊ�ؼ���ֵ
    				//����R1
					editR1.setText(object.getString("config.matting.RGB1.R").toString());
					//����G1
					editG1.setText(object.getString("config.matting.RGB1.G").toString());
					//����B1
					editB1.setText(object.getString("config.matting.RGB1.B").toString());
					//����R2
					editR2.setText(object.getString("config.matting.RGB2.R").toString());
					//����G2
					editG2.setText(object.getString("config.matting.RGB2.G").toString());
					//����B2
					editB2.setText(object.getString("config.matting.RGB2.B").toString());
					//����R3
					editR3.setText(object.getString("config.matting.RGB3.R").toString());
					//����G3
					editG3.setText(object.getString("config.matting.RGB3.G").toString());
					//����B3
					editB3.setText(object.getString("config.matting.RGB3.B").toString());
					//���ÿ�ͼ���߱�
    			    editKouTuBorder.setText(object.getString("config.matting.border").toString());
    			    //���ÿ�ͼ��ʾ���
    			    editDeltaTime.setText(object.getString("config.matting.deltaTime").toString());
    			    //��������ϳɿ��С
    				editBlockSize.setText(object.getString("config.filling.block.size").toString());
    				//��������ϳɿ����
    				editBlockNum.setText(object.getString("config.filling.block.num").toString());
    				//��������ϳ����߱�
    				editWenLiHeChengBorder.setText(object.getString("config.filling.border").toString());
    				//����lab��ֵ
    				editLabSimilarity.setText(object.getString("config.evaluation.labThreshold").toString());
    				//�������У������
    				editMaxCorrect.setText(object.getString("config.evaluation.iteration").toString());
    				//������ɫУ�����߱�
    				editLabBorder.setText(object.getString("config.evaluation.border").toString());
    				//���ö�ʱʱ��
    				editRunDeltTime.setText(object.getString("config.evaluation.interval").toString());
    				//����L
    				editLabL.setText(object.getString("config.evaluation.current.L").toString());
    				//����a
    				editLabA.setText(object.getString("config.evaluation.current.a").toString());
    				//����b
    				editLabB.setText(object.getString("config.evaluation.current.b").toString());	
    				//���÷���������״̬
    				textNowState.setText(object.getString("server.status").toString());
    			} 
    			catch (JSONException e) //�����������
    			{
    				OnShowDlg("��������ʧ��!");
    				return;
    			}    		
    		} 
    		catch (IOException e) //�����������
    		{
    			OnShowDlg("��������ʧ��!");
    			return;
    		}
    	}
    	else //����ǵ����˰�ť���۵�
    	{
    		switch(row.getId()) //����������һ����ť
    		{
       		case R.id.rConn://������������Ӳ������ð�ť
       			tableMain.removeView(row);//�۵��������Ӳ���������ͼ
       			break;
       		case R.id.rRGB://����ǿ�ͼ���ð�ť
    			this.btnSetRGB.setEnabled(true);
        		this.btnSetManuLab.setEnabled(true);
        		this.btnSetLabCorrect.setEnabled(true);
        		this.btnSetWenLiHeCheng.setEnabled(true);
        		tableMain.removeView(row); //�۵���ͼ������ͼ
        		break;
       		case R.id.rComb://���������ϳ����ð�ť
    			this.btnSetRGB.setEnabled(true);
        		this.btnSetManuLab.setEnabled(true);
        		this.btnSetLabCorrect.setEnabled(true);
        		this.btnSetWenLiHeCheng.setEnabled(true);
        		tableMain.removeView(row); //�۵�����ϳ�������ͼ
        		break;
       		case R.id.rLab://������Զ�labУ�����ð�ť
    			this.btnSetRGB.setEnabled(true);
        		this.btnSetManuLab.setEnabled(true);
        		this.btnSetLabCorrect.setEnabled(true);
        		this.btnSetWenLiHeCheng.setEnabled(true);
        		tableMain.removeView(row); //�۵��Զ�labУ��������ͼ
        		break;
       		case R.id.rManuLab://������ֶ�labУ�����ð�ť
    			this.btnSetRGB.setEnabled(true);
        		this.btnSetManuLab.setEnabled(true);
        		this.btnSetLabCorrect.setEnabled(true);
        		this.btnSetWenLiHeCheng.setEnabled(true);
        		tableMain.removeView(row); //�۵��ֶ�labУ����ͼ
        		break;
       		default:break;	
    		}
    	}    		  	
    }
    
    public void clickPlusOrMinus(View view)	//����Ӽ���ť
    {    
    	int temp=0,labStep=0;//������ʱ����
    	int intLabL=0,intLabA=0,intLabB=0;
    	switch(view.getId()) //������һ����ť������
    	{   		
    	case R.id.bThresPlus: //lab��ֵ�Ӱ�ť
    		temp=Integer.valueOf(editLabSimilarity.getText().toString());//�õ�lab��ֵ
    		if(temp<=10) temp++;//�����ֵ�ںϷ���Χ�����1
    		if(temp<=10)
    			editLabSimilarity.setText(Integer.toString(temp));//����lab��ֵ�ı����ֵ
    		break;
    		
    	case R.id.bThresMinus://lab��ֵ����ť
    		temp=Integer.valueOf(editLabSimilarity.getText().toString());//�õ�lab��ֵ
    		if(temp>=1) temp--;//�����ֵ�ںϷ���Χ�����1
    		if(temp>=1)
    			editLabSimilarity.setText(Integer.toString(temp));//����lab��ֵ�ı����ֵ
    		break;
    		
    	case R.id.bCorrPlus://���У�������Ӱ�ť
    		temp=Integer.valueOf(editMaxCorrect.getText().toString());//�õ����У������
    		if(temp<=20) temp++;//����ںϷ���Χ�����1
    		if(temp<=20)
    			editMaxCorrect.setText(Integer.toString(temp));//�������У�������ı����ֵ
    		break;
    	
    	case R.id.bCorrMinus://���У����������ť
    		temp=Integer.valueOf(editMaxCorrect.getText().toString());//�õ����У������
    		if(temp>=0) temp--;//����ںϷ���Χ�����1
    		if(temp>=0)
    			editMaxCorrect.setText(Integer.toString(temp));//�������У�������ı����ֵ
    		break;
    		
    	case R.id.bLPlus://L�Ӱ�ť
    		labStep=Integer.valueOf(editManuLabStep.getText().toString());//�õ�����
    		temp=Integer.valueOf(editLabL.getText().toString());//�õ�L��ֵ
    		if(temp<=100-labStep) temp+=labStep;//����ںϷ���Χ����ı�ֵ
    		else temp=100;//��������Ϊ����
    		editLabL.setText(Integer.toString(temp));//����L�ı����ֵ
    		
			intLabL=Integer.valueOf(this.editLabL.getText().toString());//�õ�L
			intLabA=Integer.valueOf(this.editLabA.getText().toString());//�õ�a
			intLabB=Integer.valueOf(this.editLabB.getText().toString());//�õ�b
    		try 
    		{
    			//������������ֶ�labУ��ָ��
        		myClientSocket.writer.println("manual("+intLabL+","+intLabA+","+intLabB+")");
				answerMessage=myClientSocket.br.readLine(); //��������
				OnShowDlg("���ڷ����ֶ�LabУ������������");
    		}
      		catch (IOException e) //�����������
    		{
				OnShowDlg("����ʧ�ܣ���������");
				return;
			}   
    		break;
    		
    	case R.id.bAPlus://a�Ӱ�ť
    		labStep=Integer.valueOf(editManuLabStep.getText().toString());//�õ�����
    		temp=Integer.valueOf(editLabA.getText().toString());//�õ�a��ֵ
    		if(temp<=108-labStep) temp+=labStep;//����ںϷ���Χ����ı�ֵ
    		else temp=108;//��������Ϊ����
    		editLabA.setText(Integer.toString(temp));//����a�ı����ֵ
    		
			intLabL=Integer.valueOf(this.editLabL.getText().toString());//�õ�L
			intLabA=Integer.valueOf(this.editLabA.getText().toString());//�õ�a
			intLabB=Integer.valueOf(this.editLabB.getText().toString());//�õ�b
    		try 
    		{
    			//������������ֶ�labУ��ָ��
        		myClientSocket.writer.println("manual("+intLabL+","+intLabA+","+intLabB+")");
				answerMessage=myClientSocket.br.readLine();//��������
				OnShowDlg("���ڷ����ֶ�LabУ������������");
    		}
      		catch (IOException e) //�����������
    		{
				OnShowDlg("����ʧ�ܣ���������");
				return;
			}   
    		break;
    		
    	case R.id.bLabBPlus://b�Ӱ�ť
    		labStep=Integer.valueOf(editManuLabStep.getText().toString());//�õ�����
    		temp=Integer.valueOf(editLabB.getText().toString());//�õ�b��ֵ
    		if(temp<=95-labStep) temp+=labStep;//����ںϷ���Χ����ı�ֵ
    		else temp=95;//��������Ϊ����
    		editLabB.setText(Integer.toString(temp));//����b�ı����ֵ
    		
			intLabL=Integer.valueOf(this.editLabL.getText().toString());//�õ�L
			intLabA=Integer.valueOf(this.editLabA.getText().toString());//�õ�a
			intLabB=Integer.valueOf(this.editLabB.getText().toString());//�õ�b
    		try 
    		{
    			//������������ֶ�labУ��ָ��
        		myClientSocket.writer.println("manual("+intLabL+","+intLabA+","+intLabB+")");
				answerMessage=myClientSocket.br.readLine();//��������
				OnShowDlg("���ڷ����ֶ�LabУ������������");
    		}
      		catch (IOException e) //�����������
    		{
				OnShowDlg("����ʧ�ܣ���������");
				return;
			}   
    		break;
    		
    	case R.id.bLMinus://L����ť
       		labStep=Integer.valueOf(editManuLabStep.getText().toString());//�õ�����
    		temp=Integer.valueOf(editLabL.getText().toString());//�õ�L��ֵ
    		if(temp>=0+labStep) temp-=labStep;//����ںϷ���Χ����ı�ֵ
    		else temp=0;//��������Ϊ����
    		editLabL.setText(Integer.toString(temp));//����L�ı����ֵ
    		
			intLabL=Integer.valueOf(this.editLabL.getText().toString());//�õ�L
			intLabA=Integer.valueOf(this.editLabA.getText().toString());//�õ�a
			intLabB=Integer.valueOf(this.editLabB.getText().toString());//�õ�b
    		try 
    		{
    			//������������ֶ�labУ��ָ��
        		myClientSocket.writer.println("manual("+intLabL+","+intLabA+","+intLabB+")");
				answerMessage=myClientSocket.br.readLine(); //��������
				OnShowDlg("���ڷ����ֶ�LabУ������������");
    		}
      		catch (IOException e) //�����������
    		{
				OnShowDlg("����ʧ�ܣ���������");
				return;
			}   
    		break;
    		
    	case R.id.bAMinus://a����ť
    		labStep=Integer.valueOf(editManuLabStep.getText().toString());//�õ�����
    		temp=Integer.valueOf(editLabA.getText().toString());//�õ�a��ֵ
    		if(temp>=-94+labStep) temp-=labStep;//����ںϷ���Χ����ı�ֵ
    		else temp=-94;//��������Ϊ����
    		editLabA.setText(Integer.toString(temp));//����a�ı����ֵ
    		
			intLabL=Integer.valueOf(this.editLabL.getText().toString());//�õ�L
			intLabA=Integer.valueOf(this.editLabA.getText().toString());//�õ�a
			intLabB=Integer.valueOf(this.editLabB.getText().toString());//�õ�b
    		try 
    		{
    			//������������ֶ�labУ��ָ��
        		myClientSocket.writer.println("manual("+intLabL+","+intLabA+","+intLabB+")");
				answerMessage=myClientSocket.br.readLine();//��������
				OnShowDlg("���ڷ����ֶ�LabУ������������");
    		}
      		catch (IOException e) //�����������
    		{
				OnShowDlg("����ʧ�ܣ���������");
				return;
			}   
    		break;
    		
    	case R.id.bLabBMinus://b����ť
    		labStep=Integer.valueOf(editManuLabStep.getText().toString());//�õ�����
    		temp=Integer.valueOf(editLabB.getText().toString());//�õ�b��ֵ
    		if(temp>=-108+labStep) temp-=labStep;//����ںϷ���Χ����ı�ֵ
    		else temp=-108;//��������Ϊ����
    		editLabB.setText(Integer.toString(temp));//����b�ı����ֵ
    		
			intLabL=Integer.valueOf(this.editLabL.getText().toString());//�õ�L
			intLabA=Integer.valueOf(this.editLabA.getText().toString());//�õ�a
			intLabB=Integer.valueOf(this.editLabB.getText().toString());//�õ�b
    		try 
    		{
    			//������������ֶ�labУ��ָ��
        		myClientSocket.writer.println("manual("+intLabL+","+intLabA+","+intLabB+")");
				answerMessage=myClientSocket.br.readLine();//��������
				OnShowDlg("���ڷ����ֶ�LabУ������������");
    		}
      		catch (IOException e) //�����������
    		{
				OnShowDlg("����ʧ�ܣ���������");
				return;
			}   
    		break;
	
    	default:break;
    	}
    }
    
    public void clickSetOK(View view)	//����������ɰ�ť
    {     
		answerMessage="";
		switch(view.getId()) //���ǰ�������һ����ť
		{
		case R.id.bOKConn: //������������Ӳ���ȷ����ť             
    		file(1);	//�洢�������ļ���
    		return;
    		
		case R.id.bOKRGB: //����ǿ�ͼ����ȷ����ť            
    		int intR1=Integer.valueOf(editR1.getText().toString());  //��ȡ�û������RGBֵ
    		int intG1=Integer.valueOf(editG1.getText().toString());
    		int intB1=Integer.valueOf(editB1.getText().toString());	
    		
    		int intR2=Integer.valueOf(editR2.getText().toString());  //��ȡ�û������RGBֵ
    		int intG2=Integer.valueOf(editG2.getText().toString());
    		int intB2=Integer.valueOf(editB2.getText().toString());	
    		
    		int intR3=Integer.valueOf(editR3.getText().toString());  //��ȡ�û������RGBֵ
    		int intG3=Integer.valueOf(editG3.getText().toString());
    		int intB3=Integer.valueOf(editB3.getText().toString());	
    		
    		double dbKouTuBorder=Double.valueOf(editKouTuBorder.getText().toString());//�õ����߱�
    		int intDeltaTime=Integer.valueOf(editDeltaTime.getText().toString());	//�õ���ʾ���
    		if((intR1>255)||(intG1>255)||(intB1>255)||(intR2>255)||(intG2>255)||(intB2>255)||(intR3>255)||(intG3>255)||(intB3>255))	//�ж�����Ϸ���
    		{  //����������ɫֵ���Ϸ�
    			OnShowDlg("RGBֵ��ΧΪ0~255������������!");
    			return;
    		}
    		if(dbKouTuBorder>0.5 || dbKouTuBorder<0.01)//������߱Ȳ��Ϸ�
    		{
    			OnShowDlg("���߱ȷ�Χ0.01~0.5!");
    			return;
    		}
    		if(intDeltaTime>120 || intDeltaTime<5)//�����ʾ������Ϸ�
    		{
    			intDeltaTime=intDeltaTime>120?120:5;//�޶����Ϸ���Χ��
    			editDeltaTime.setText(Integer.toString(intDeltaTime));//������ʾ����ı����ֵ
    		}

    		try 
    		{
    			//����������������������Ͳ�������ָ��
    			//����RGB1����
        		myClientSocket.writer.println("config.matting.RGB1.R="+intR1);
				answerMessage=myClientSocket.br.readLine();//�������ݣ������κδ�����ͬ
				OnShowDlg("���ڷ��Ϳ�ͼ���ò���...");
        		myClientSocket.writer.println("config.matting.RGB1.G="+intG1);
				answerMessage=myClientSocket.br.readLine();//��������
        		myClientSocket.writer.println("config.matting.RGB1.B="+intB1);
				answerMessage=myClientSocket.br.readLine();//��������
				//����RGB2����
        		myClientSocket.writer.println("config.matting.RGB2.R="+intR2);
				answerMessage=myClientSocket.br.readLine();//��������
        		myClientSocket.writer.println("config.matting.RGB2.G="+intG2);
				answerMessage=myClientSocket.br.readLine();//��������
        		myClientSocket.writer.println("config.matting.RGB2.B="+intB2);
				answerMessage=myClientSocket.br.readLine();//��������
				//����RGB3����
        		myClientSocket.writer.println("config.matting.RGB3.R="+intR3);
				answerMessage=myClientSocket.br.readLine();//��������
        		myClientSocket.writer.println("config.matting.RGB3.G="+intG3);
				answerMessage=myClientSocket.br.readLine();//��������
        		myClientSocket.writer.println("config.matting.RGB3.B="+intB3);
				answerMessage=myClientSocket.br.readLine();//��������
				//�������߱�
        		myClientSocket.writer.println("config.matting.border="+dbKouTuBorder);
				answerMessage=myClientSocket.br.readLine();//��������
				//������ʾ���
        		myClientSocket.writer.println("config.matting.deltaTime="+intDeltaTime);
				answerMessage=myClientSocket.br.readLine();//��������
		    	textNowState.setText("�������������Խ��в���");//���ÿͻ�������״̬
			} 
    		catch (IOException e) //�����������
    		{
				OnShowDlg("����ʧ�ܣ���������");
				return;
			}  
    		break;
    		
		case R.id.bOKComb://���������ϳ�ȷ����ť	
    		int intBlockSize=Integer.valueOf(editBlockSize.getText().toString());//�õ����С
    		int intBlockNum=Integer.valueOf(editBlockNum.getText().toString());	//�õ������	
    		//�õ����߱�
    		double dbWenLiHeChengBorder=Double.valueOf(editWenLiHeChengBorder.getText().toString());
    		if((intBlockSize>1000)||(intBlockSize<1))//������С���Ϸ�
    		{
    			OnShowDlg("���С��Χ1~1000!");
    			return;
    		}
    		if((intBlockNum>480000))//�����������Ϸ�
    		{
    			OnShowDlg("�������Χ0~480000!");
    			return;
    		}
    		if(dbWenLiHeChengBorder>0.5 || dbWenLiHeChengBorder<0.01)//������߱Ȳ��Ϸ�
    		{
    			OnShowDlg("���߱ȷ�Χ0.01~0.5!");
    			return;
    		}

    		try 
    		{
    			//����������Ϳ��С����
        		myClientSocket.writer.println("config.filling.block.size="+intBlockSize);
				answerMessage=myClientSocket.br.readLine();//��������
        		OnShowDlg("���ڷ�������ϳɲ���...");
        		//����������Ϳ��������
        		myClientSocket.writer.println("config.filling.block.num="+intBlockNum);
				answerMessage=myClientSocket.br.readLine();//��������
				//��������������߱Ȳ���
        		myClientSocket.writer.println("config.filling.border="+dbWenLiHeChengBorder);
				answerMessage=myClientSocket.br.readLine();//��������
		    	textNowState.setText("�������������Խ��в���");//���ÿͻ�������״̬
			} 
    		catch (IOException e) //�����������
    		{
				OnShowDlg("����ʧ�ܣ���������");
				return;
			}  	
    		break;
    		
		case R.id.bOKLab: //������Զ�labУ��ȷ����ť
    		int intLab=Integer.valueOf(editLabSimilarity.getText().toString());//�õ�lab��ֵ
    		int intMaxCorrect=Integer.valueOf(editMaxCorrect.getText().toString());//�õ����У������
       		double dbLabBorder=Double.valueOf(editLabBorder.getText().toString());//�õ����߱�
       		int intDeltTime=Integer.valueOf(editRunDeltTime.getText().toString()); //�õ���ʱ���
    		if((intDeltTime>7200)||(intDeltTime<1))//�����ʱ������Ϸ�
    		{
    			OnShowDlg("���м����Χ1~7200 ��!");
    			return;
    		}
    		if((intLab>10)||(intLab<1))//���lab��ֵ���Ϸ�
    		{
    			OnShowDlg("������������ֵ��Χ1~10!");
    			return;
    		}
    		if(intMaxCorrect>20)//������У���������Ϸ�
    		{
    			OnShowDlg("������������Χ0~20!");
    			return;
    		}
    		if(dbLabBorder>0.5 || dbLabBorder<0.01)//������߱Ȳ��Ϸ�
    		{
    			OnShowDlg("���߱ȷ�Χ0.01~0.5!");
    			return;
    		}

    		try 
    		{
    			//����lab��ֵ����
        		myClientSocket.writer.println("config.evaluation.labThreshold="+intLab);
				answerMessage=myClientSocket.br.readLine();//��������
				OnShowDlg("���ڷ����Զ�LabУ������...");
				//�������У������
        		myClientSocket.writer.println("config.evaluation.iteration="+intMaxCorrect); 
				answerMessage=myClientSocket.br.readLine();//��������
				//�������߱Ȳ���
        		myClientSocket.writer.println("config.evaluation.border="+dbLabBorder);
				answerMessage=myClientSocket.br.readLine();//��������
				//���Ͷ�ʱ�������
           		myClientSocket.writer.println("config.evaluation.interval="+intDeltTime);  
				answerMessage=myClientSocket.br.readLine();//��������
		    	textNowState.setText("�������������Խ��в���");//���ÿͻ�������״̬
			} 
    		catch (IOException e) //�����������
    		{
				OnShowDlg("����ʧ�ܣ���������");
				return;
			}	
    		break;
    		   		
		case R.id.bDoComb://���������ϳ�ִ�а�ť
    		try
    		{
    			//�����������ִ��һ��ָ��
    			myClientSocket.writer.println("donce()"); 
    			answerMessage=myClientSocket.br.readLine();//��������
    	    	textNowState.setText("�������������Խ��в���");//���ÿͻ�������״̬
    		}
       		catch (IOException e) //�����������
    		{
				OnShowDlg("����ʧ�ܣ���������");
				return;
			}
    		break;

		case R.id.bDoLab://������Զ�labУ���Զ���ť
    		try
    		{
    			//����������Ͷ�ʱִ��ָ��
    			myClientSocket.writer.println("autimer()"); 
    			answerMessage=myClientSocket.br.readLine();//��������
    	    	textNowState.setText("�������������Խ��в���");//���ÿͻ�������״̬
    		}
       		catch (IOException e) //�����������
    		{
				OnShowDlg("����ʧ�ܣ���������");
				return;
			}   
    		break;

		case R.id.bShoot: //�����ץͼ��ť
    		try 
    		{
/*
 				OnShowDlg("���ڽ���ͼƬ...�����ĵȴ�!");
				URL url=new URL("http://"+myClientSocket.final_IP+":32766/tyr.jpg");
				connHttp=(HttpURLConnection)url.openConnection();
				InputStream is=connHttp.getInputStream();
				FileOutputStream os=new FileOutputStream("/sdcard/Received.jpg");
    			byte[] bytes=new byte[1024];
    			int fileLength=-1;
    			textNowState.setText("���ڽ���ͼƬ...");
    			while((fileLength=is.read(bytes))!=-1) 
    			{
    				os.write(bytes,0,fileLength);
    			} 
   			    is.close();
    			os.close();
    			BitmapFactory.Options bmpFactoryOptions=new BitmapFactory.Options();
       			Bitmap bmp=BitmapFactory.decodeFile("/sdcard/Received.jpg", bmpFactoryOptions);
    			imgShow.setImageBitmap(bmp); 
    			textNowState.setText("ͼƬ�ѽ������");
*/
    			
	 			OnShowDlg("���ڽ���ͼƬ...�����ĵȴ�!");
				String url="http://"+myClientSocket.final_IP+":80/cap.jpg";//����ͼƬ����
    			HttpClient client=new DefaultHttpClient();//����HTTP�ͻ��˶���
    			HttpGet get=new HttpGet(url);//����HTTP����
    			HttpResponse response=client.execute(get);//ִ������
    			if(response.getStatusLine().getStatusCode()!=HttpStatus.SC_OK)//�����Ӧʧ��
    			{
    				OnShowDlg("ͼƬ����ʧ��!");
    				return;
    			}
    			HttpEntity entity=response.getEntity();//�õ�����ʵ��
    			InputStream is=entity.getContent();//�õ����ص�������
/*				FileOutputStream os=new FileOutputStream("/sdcard/Received.jpg");
    			byte[] bytes=new byte[1024];
    			int fileLength=-1;
    			textNowState.setText("���ڽ���ͼƬ...");
    			while((fileLength=is.read(bytes))!=-1) 
    			{
    				os.write(bytes,0,fileLength);
    			} 
   			    is.close();
    			os.close();
    			BitmapFactory.Options bmpFactoryOptions=new BitmapFactory.Options();
       			Bitmap bmp=BitmapFactory.decodeFile("/sdcard/Received.jpg", bmpFactoryOptions);
*/				Bitmap bmp=BitmapFactory.decodeStream(is);//�������й���λͼ
				imgShow.setImageBitmap(bmp); //��ʾͼ��
    			is.close();//�ر�������
    			textNowState.setText("ͼƬ�ѽ������");	//���ÿͻ�������״̬
				
/*
				OnShowDlg("���ڽ���ͼƬ...�����ĵȴ�!");
				URL url=new URL("http://"+myClientSocket.final_IP+":80/cap.jpg");
				connHttp=(HttpURLConnection)url.openConnection();
	            connHttp.setDoInput(true);
	            connHttp.connect();
	            InputStream is=connHttp.getInputStream();
	            Bitmap bmp=BitmapFactory.decodeStream(is);
	            is.close();
	            imgShow.setImageBitmap(bmp); 
	            textNowState.setText("ͼƬ�ѽ������");	 
*/ 
			} 
    		catch (MalformedURLException e) //�����������
    		{

			} 
       		catch (IOException e) //�����������
    		{
				OnShowDlg("����ͼƬʧ�ܣ���������");
				return;
			}
    		break;		
    		
		case R.id.bRefresh: //�����ˢ�°�ť
			//�������ݵ���ϸע����μ�clickSet(View view)����
    		answerMessage="";//���յ�������
     		try 
    		{
        		myClientSocket.writer.println("?"); //����������Ͳ�ѯָ��
    			answerMessage=myClientSocket.br.readLine();//��������
	   			if(answerMessage==null) //����������Ӵ���
    			{
    		   		textIsConnected.setText("δ���� ");//��������״̬����
    		   		OnShowDlg("�����쳣������������!");
    	    		textIsConnected.setTextColor(Color.WHITE);//��������״̬������ɫ
    	    		OnInitialButtons(false);//����δ���Ӱ�ť״̬
    	    		//���涼�Ǹı�ҳ��ؼ�״̬
    	    		btnSetConnect.setChecked(false);
    	    		textNowState.setText("Ŀǰû������");
    	    		this.btnConnect.setEnabled(true);
    	    		this.btnConnect.setChecked(false);
    	    		this.btnConnect.setText("����");
    	    		myClientSocket.closeSocket();//�ر�����ͨ���׽���
    				return;
    			}
    			int strlen=answerMessage.length();//���յ����ַ�������
    	  		String json=answerMessage.substring(0,strlen-2)+"}";//����Json�ַ���
        		JSONObject object;//����Json����
    			try 
    			{
    				object=(JSONObject) new JSONTokener(json).nextValue();//����Json����
    				//����Ϊ����Json���ݲ�Ϊ�ؼ���ֵ
    				//����R1
					editR1.setText(object.getString("config.matting.RGB1.R").toString());
					//����G1
					editG1.setText(object.getString("config.matting.RGB1.G").toString());
					//����B1
					editB1.setText(object.getString("config.matting.RGB1.B").toString());
					//����R2
					editR2.setText(object.getString("config.matting.RGB2.R").toString());
					//����G2
					editG2.setText(object.getString("config.matting.RGB2.G").toString());
					//����B2
					editB2.setText(object.getString("config.matting.RGB2.B").toString());
					//����R3
					editR3.setText(object.getString("config.matting.RGB3.R").toString());
					//����G3
					editG3.setText(object.getString("config.matting.RGB3.G").toString());
					//����B3
					editB3.setText(object.getString("config.matting.RGB3.B").toString());
					//���ÿ�ͼ���߱�
    			    editKouTuBorder.setText(object.getString("config.matting.border").toString());
    			    //���ÿ�ͼ��ʾ���
    			    editDeltaTime.setText(object.getString("config.matting.deltaTime").toString());
    			    //��������ϳɿ��С
    				editBlockSize.setText(object.getString("config.filling.block.size").toString());
    				//��������ϳɿ����
    				editBlockNum.setText(object.getString("config.filling.block.num").toString());
    				//��������ϳ����߱�
    				editWenLiHeChengBorder.setText(object.getString("config.filling.border").toString());
    				//����lab��ֵ
    				editLabSimilarity.setText(object.getString("config.evaluation.labThreshold").toString());
    				//�������У������
    				editMaxCorrect.setText(object.getString("config.evaluation.iteration").toString());
    				//������ɫУ�����߱�
    				editLabBorder.setText(object.getString("config.evaluation.border").toString());
    				//���ö�ʱʱ��
    				editRunDeltTime.setText(object.getString("config.evaluation.interval").toString());
    				//����L
    				editLabL.setText(object.getString("config.evaluation.current.L").toString());
    				//����a
    				editLabA.setText(object.getString("config.evaluation.current.a").toString());
    				//����b
    				editLabB.setText(object.getString("config.evaluation.current.b").toString());	
    				//���÷���������״̬
    				textNowState.setText(object.getString("server.status").toString());
    				
    			} 
    			catch (JSONException e) //�����������
    			{
    				OnShowDlg("��������ʧ��!");
    				return;
    			}    		
    		} 
    		catch (IOException e) //�����������
    		{
    			OnShowDlg("��������ʧ��!");
    			return;
    		}
			break;
			
		case R.id.bDoOneTimeLab://������ֶ�labУ��ִ��һ�ΰ�ť
    		try
    		{
    			//����������͹رն�ʱ��ָ��
    			myClientSocket.writer.println("disautimer()"); 
    			answerMessage=myClientSocket.br.readLine();//��������
    			//������������Զ�ִ��һ��ָ��
    			myClientSocket.writer.println("autonce()"); 
    			answerMessage=myClientSocket.br.readLine(); //��������
    			textNowState.setText("�������������Խ��в���");//���ÿͻ�������״̬
    		}
       		catch (IOException e) //�����������
    		{
				OnShowDlg("����ʧ�ܣ���������");
				return;
			}   
    		break;
			
    	default:break;
		}
    }
    
    public class SocketClient	//Socketͨ����
    {               
    	public Socket client;//ͨ���׽���
        public InputStream serverReader;//������
        public BufferedReader br;
        public PrintStream writer;//�����
        public String final_IP; //������IP��ַ
    	
    	public SocketClient(final String site,final int port) //���캯��
    	{
    		new Thread()//����һ�����߳�
    		{
    			public void run() //�̵߳����к���
    			{
    				try		//��������
    				{ 
    					textNowState.setText("�������ӷ�����...");//���ÿͻ�������״̬
    	    			client=new Socket(site,port);//�������ӷ�����
    	    			final_IP=site;//���IP��ַ
    	    			isConnected=true;//���ӳɹ��ı�־
    				}
    				catch(Exception e)		//�޷�����
    				{                 
    					e.printStackTrace();//����쳣��Ϣ
    					Message message=handler.obtainMessage();//������Ϣ�����߳�ͨ��
    					message.what=1;//������Ϣ���Ӳ���
    					message.arg1=1;//������Ϣ���Ӳ���
    					handler.sendMessage(message);//������Ϣ
    				}			
    				if(isConnected==true)	//���ӳɹ�
    				{       
    					try
    					{
    						serverReader=client.getInputStream();//�õ�������
    						br=new BufferedReader(new InputStreamReader(serverReader,"utf-8"));
    						//���������ӡ��
    						writer=new PrintStream(client.getOutputStream(),true,"utf-8");
    						
    						Message message=handler.obtainMessage();//������Ϣ�����߳�ͨ��
    						message.what=2;//������Ϣ���Ӳ���
    						message.arg1=1;//������Ϣ���Ӳ���
    						handler.sendMessage(message);//������Ϣ
    					}
    					catch(Exception e)	//����ʧ��
    					{      
    						e.printStackTrace();//����쳣��Ϣ
    						isConnected=false;//����ʧ�ܵı�־
    						Message message=handler.obtainMessage();//������Ϣ�����߳�ͨ��
    						message.what=1;//������Ϣ���Ӳ���
    						message.arg1=2;//������Ϣ���Ӳ���
    						handler.sendMessage(message);//������Ϣ
    					}
    				}
    			}
    		}.start();//�����߳�
    	}
    	
    	public Handler handler=new Handler()//��Ϣ������
    	{
			@Override
    		public void handleMessage(Message msg)
			{
				if(msg.what==1)		//���ӳ���
				{             
					switch(msg.arg1)
					{
					case 1://����޷����ӵ�������
						OnShowDlg("�޷����ӵ�������");
						break;
					case 2://��������ӵ��޷����������
						OnShowDlg("�޷��������������");
						break;
					case 3:
						if(isConnected==true)//���������
						{
							OnShowDlg("�����ж�");
							isConnected=false;//����ʧ�ܵı�־
						}
						break;
					}
					//���´������ÿؼ���״̬
					textIsConnected.setText("δ����");
					textIsConnected.setTextColor(Color.WHITE);
					textNowState.setText("��ǰû������");
					btnConnect.setText("����");
					btnConnect.setEnabled(true);
					btnConnect.setChecked(false);
					OnInitialButtons(false);//����δ����ʱ�Ľ���״̬
				}
				else if(msg.what==2)	//�����޴���
				{
					switch(msg.arg1)
					{
					case 1: //���ӳɹ�
						//���´������ÿؼ���״̬
						textIsConnected.setText("������");
						textIsConnected.setTextColor(Color.GREEN);
						textNowState.setText("�����������ɽ��в���");
						btnConnect.setText("�Ͽ�");
						btnConnect.setEnabled(true);
						OnInitialButtons(true);//���óɹ�����ʱ�Ľ���״̬
						
						answerMessage="";//���յ�������
						myClientSocket.writer.println("?");//����������Ͳ�ѯָ��
				 		try 
			    		{
							answerMessage=myClientSocket.br.readLine();//��������
							int strlen=answerMessage.length();//�õ������ַ����ĳ���
					  		String json=answerMessage.substring(0,strlen-2)+"}";//����Json�ַ���
				    		JSONObject object;//����Json����
							try 
							{
			    				object=(JSONObject) new JSONTokener(json).nextValue();//����Json����
			    				//����Ϊ����Json���ݲ�Ϊ�ؼ���ֵ
			    				//����R1
								editR1.setText(object.getString("config.matting.RGB1.R").toString());
								//����G1
								editG1.setText(object.getString("config.matting.RGB1.G").toString());
								//����B1
								editB1.setText(object.getString("config.matting.RGB1.B").toString());
								//����R2
								editR2.setText(object.getString("config.matting.RGB2.R").toString());
								//����G2
								editG2.setText(object.getString("config.matting.RGB2.G").toString());
								//����B2
								editB2.setText(object.getString("config.matting.RGB2.B").toString());
								//����R3
								editR3.setText(object.getString("config.matting.RGB3.R").toString());
								//����G3
								editG3.setText(object.getString("config.matting.RGB3.G").toString());
								//����B3
								editB3.setText(object.getString("config.matting.RGB3.B").toString());
								//���ÿ�ͼ���߱�
			    			    editKouTuBorder.setText(object.getString("config.matting.border").toString());
			    			    //���ÿ�ͼ��ʾ���
			    			    editDeltaTime.setText(object.getString("config.matting.deltaTime").toString());
			    			    //��������ϳɿ��С
			    				editBlockSize.setText(object.getString("config.filling.block.size").toString());
			    				//��������ϳɿ����
			    				editBlockNum.setText(object.getString("config.filling.block.num").toString());
			    				//��������ϳ����߱�
			    				editWenLiHeChengBorder.setText(object.getString("config.filling.border").toString());
			    				//����lab��ֵ
			    				editLabSimilarity.setText(object.getString("config.evaluation.labThreshold").toString());
			    				//�������У������
			    				editMaxCorrect.setText(object.getString("config.evaluation.iteration").toString());
			    				//������ɫУ�����߱�
			    				editLabBorder.setText(object.getString("config.evaluation.border").toString());
			    				//���ö�ʱʱ��
			    				editRunDeltTime.setText(object.getString("config.evaluation.interval").toString());
			    				//����L
			    				editLabL.setText(object.getString("config.evaluation.current.L").toString());
			    				//����a
			    				editLabA.setText(object.getString("config.evaluation.current.a").toString());
			    				//����b
			    				editLabB.setText(object.getString("config.evaluation.current.b").toString());	
			    				//���÷���������״̬
			    				textNowState.setText(object.getString("server.status").toString());
							} 
							catch (JSONException e) //�����������
							{
								OnShowDlg("���ݸ���ʧ��!");
								return;
							}    		
						} 
			    		catch (IOException e)  //�����������
			    		{
			    			OnShowDlg("���ݸ���ʧ��!");
							return;
						}
						break;
					case 2: //����ͼƬ
						textNowState.setText("���ڽ���ͼƬ("+Integer.toString(msg.arg2/1024)+"k)�����Ժ�");
						break;
					}
				}
			}
		};
	
		public void closeSocket() //�ر�����ͨ��
		{
    		try
    		{
    		    client.shutdownInput();//�ر�������
    		    client.shutdownOutput();//�ر������
    			if(!client.isClosed())//���δ�ر�
    				client.close();//�ر��׽���
    		}
    		catch(IOException e)//�����������
    		{
    			e.printStackTrace();//���������Ϣ
    		}
    		isConnected=false;//����ʧ�ܵı�־
    	}		
    }

	public void OnShowDlg(String msg)	//��ʾ�����Ի���
	{         
    	Toast.makeText(getApplicationContext(), msg, Toast.LENGTH_SHORT).show();//��ʾToast��ʾ��
    }
	
	public void onStartTrackingTouch(SeekBar seekBar) 
	{
		
	}

	public void onStopTrackingTouch(SeekBar seekBar) 
	{
		
	}
    
}
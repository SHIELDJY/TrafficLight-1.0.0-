#include "common.h"

//ATK-ESP8266 WIFI AP����
//���ڲ���TCP/UDP����
//����ֵ:0,����
//    ����,�������
u8 atk_8266_wifiap_test(void)
{
	u8 netpro=0;	//����ģʽ
	u8 key;
	u8 timex=0; 
	u8 ipbuf[16]; 	//IP����
	u8 *p;
	u16 t=999;		//���ٵ�һ�λ�ȡ����״̬
	u8 res=0;
	u16 rlen=0;
	u8 constate=0;	//����״̬
	p=mymalloc(32);							//����32�ֽ��ڴ�
	
PRESTA:
			//TCP Server
	atk_8266_send_cmd("AT+CIPMUX=1","OK",20);   //0�������ӣ�1��������
	sprintf((char*)p,"AT+CIPSERVER=1,%s",(u8*)portnum);
	atk_8266_send_cmd(p,"OK",20);     //����Serverģʽ���˿ں�Ϊ8086
	
	USART2_RX_STA=0;
	while(1)
	{
		sprintf((char*)p,"ATK-8266%s����%02d\r\n",ATK_ESP8266_WORKMODE_TBL[netpro],t/10);//��������
		Show_Str(30+54,100,200,12,p,12,0);
		atk_8266_send_cmd("AT+CIPSEND=0,25","OK",200);  //����ָ�����ȵ�����
		delay_ms(200);
		atk_8266_send_data(p,"OK",100);  //����ָ�����ȵ�����
			
		if(USART2_RX_STA&0X8000)		//���յ�һ��������
		{ 
			rlen=USART2_RX_STA&0X7FFF;	//�õ����ν��յ������ݳ���
			USART2_RX_BUF[rlen]=0;		//��ӽ����� 
			printf("%s",USART2_RX_BUF);	//���͵�����   
			USART2_RX_STA=0;
			if(constate!='+')t=1000;		//״̬Ϊ��δ����,������������״̬
			else t=0;                   //״̬Ϊ�Ѿ�������,10����ټ��
		}  
		if(t==1000)//����10����û���յ��κ�����,��������ǲ��ǻ�����.
		{
			constate=atk_8266_consta_check();//�õ�����״̬	  	 
			t=0;
		}
		atk_8266_at_response(1);
}
	myfree(p);		//�ͷ��ڴ�
	return res;		
} 








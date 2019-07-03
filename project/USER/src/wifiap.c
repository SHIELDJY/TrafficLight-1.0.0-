#include "common.h"

//ATK-ESP8266 WIFI AP测试
//用于测试TCP/UDP连接
//返回值:0,正常
//    其他,错误代码
u8 atk_8266_wifiap_test(void)
{
	u8 netpro=0;	//网络模式
	u8 key;
	u8 timex=0; 
	u8 ipbuf[16]; 	//IP缓存
	u8 *p;
	u16 t=999;		//加速第一次获取链接状态
	u8 res=0;
	u16 rlen=0;
	u8 constate=0;	//连接状态
	p=mymalloc(32);							//申请32字节内存
	
PRESTA:
			//TCP Server
	atk_8266_send_cmd("AT+CIPMUX=1","OK",20);   //0：单连接，1：多连接
	sprintf((char*)p,"AT+CIPSERVER=1,%s",(u8*)portnum);
	atk_8266_send_cmd(p,"OK",20);     //开启Server模式，端口号为8086
	
	USART2_RX_STA=0;
	while(1)
	{
		sprintf((char*)p,"ATK-8266%s测试%02d\r\n",ATK_ESP8266_WORKMODE_TBL[netpro],t/10);//测试数据
		Show_Str(30+54,100,200,12,p,12,0);
		atk_8266_send_cmd("AT+CIPSEND=0,25","OK",200);  //发送指定长度的数据
		delay_ms(200);
		atk_8266_send_data(p,"OK",100);  //发送指定长度的数据
			
		if(USART2_RX_STA&0X8000)		//接收到一次数据了
		{ 
			rlen=USART2_RX_STA&0X7FFF;	//得到本次接收到的数据长度
			USART2_RX_BUF[rlen]=0;		//添加结束符 
			printf("%s",USART2_RX_BUF);	//发送到串口   
			USART2_RX_STA=0;
			if(constate!='+')t=1000;		//状态为还未连接,立即更新连接状态
			else t=0;                   //状态为已经连接了,10秒后再检查
		}  
		if(t==1000)//连续10秒钟没有收到任何数据,检查连接是不是还存在.
		{
			constate=atk_8266_consta_check();//得到连接状态	  	 
			t=0;
		}
		atk_8266_at_response(1);
}
	myfree(p);		//释放内存
	return res;		
} 








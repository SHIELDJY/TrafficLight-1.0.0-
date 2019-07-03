/**
 * @File:   System_Init.c
 * @Brief:  Funtions prototype used for traffic light
 * @Author: J.T. Yu
 * @Date:   2019/7/1
 */

/* Includes----------- */
#include "Traffic_Light.h"

/* Constants----------- */
#define A 200   //delay time in ms
#define B 100   //delay time in ms

/* Function Prototype---------- */
/**
  * @brief  LED Configuration.
  * @param  None
  * @retval None
  */
void Init_Configuration(void)
{
	GPIO_ResetBits(GPIOA, GPIO_Pin_0);
	GPIO_ResetBits(GPIOA, GPIO_Pin_1);
	GPIO_ResetBits(GPIOA, GPIO_Pin_2);   //led
		
	GPIO_ResetBits(GPIOA, GPIO_Pin_3);
	GPIO_ResetBits(GPIOA, GPIO_Pin_4);
	GPIO_ResetBits(GPIOA, GPIO_Pin_5);
	GPIO_ResetBits(GPIOA, GPIO_Pin_6);
	GPIO_ResetBits(GPIOA, GPIO_Pin_7);
	GPIO_ResetBits(GPIOA, GPIO_Pin_8);
	GPIO_ResetBits(GPIOA, GPIO_Pin_9);
	GPIO_ResetBits(GPIOA, GPIO_Pin_10);     //7  led input
		
	GPIO_ResetBits(GPIOB, GPIO_Pin_0);
	GPIO_ResetBits(GPIOB, GPIO_Pin_1);  //  7LED   CHOICE	
	GPIO_ResetBits(GPIOB, GPIO_Pin_5);
	GPIO_ResetBits(GPIOB, GPIO_Pin_6);    //MODULE  CHOICE	
	GPIO_ResetBits(GPIOB, GPIO_Pin_7);     // BUMPER
}
/**
  * @brief  function for how 7Segments work .
  * @param  None
  * @retval None
  */
void Segment_led(u32 a)
{
	uint32_t b1,c1,d1,b2,c2,d2,f;
	if (a<3800)
	{
		b1=40500-a;
		c1=b1/10000;
		d1=b1%10000/1000;
		b2=38500-a;
		c2=b2/10000;
		d2=b2%10000/1000;
		f=a%4;
		if(f==0)
		{
			GPIO_ResetBits(GPIOB, GPIO_Pin_6);	
			GPIO_ResetBits(GPIOB, GPIO_Pin_0);
			GPIO_ResetBits(GPIOB, GPIO_Pin_5);	
			GPIO_ResetBits(GPIOB, GPIO_Pin_1);	
			translate(c1);
			GPIO_SetBits(GPIOB, GPIO_Pin_0);
			GPIO_SetBits(GPIOB, GPIO_Pin_6);		
		}
		else if (f==1)
		{
			GPIO_ResetBits(GPIOB, GPIO_Pin_6);	
			GPIO_ResetBits(GPIOB, GPIO_Pin_0);
			GPIO_ResetBits(GPIOB, GPIO_Pin_5);	
			GPIO_ResetBits(GPIOB, GPIO_Pin_1);	
			translate(d1);
			GPIO_SetBits(GPIOB, GPIO_Pin_6);
			GPIO_SetBits(GPIOB, GPIO_Pin_1);	
		} 

		//EW
		else if (f==2)
		{
			GPIO_ResetBits(GPIOB, GPIO_Pin_6);	
			GPIO_ResetBits(GPIOB, GPIO_Pin_0);
			GPIO_ResetBits(GPIOB, GPIO_Pin_5);	
			GPIO_ResetBits(GPIOB, GPIO_Pin_1);
			translate(c2);		
			GPIO_SetBits(GPIOB, GPIO_Pin_5);
			GPIO_SetBits(GPIOB, GPIO_Pin_0);
		}
	
		else if (f==3)
		{
			GPIO_ResetBits(GPIOB, GPIO_Pin_6);	
			GPIO_ResetBits(GPIOB, GPIO_Pin_0);
			GPIO_ResetBits(GPIOB, GPIO_Pin_5);	
			GPIO_ResetBits(GPIOB, GPIO_Pin_1);
			translate(d2);		
			GPIO_SetBits(GPIOB, GPIO_Pin_5);	
			GPIO_SetBits(GPIOB, GPIO_Pin_1);
		} 
	}
	else if (a>=38000 && a<40000)
	{
		b1=40500-a;
		c1=b1/10000;
		d1=b1%10000/1000;
		b2=40500-a;
		c2=b2/10000;
		d2=b2%10000/1000;
		f=a%4;
		if(f==0)
		{
			GPIO_SetBits(GPIOB, GPIO_Pin_6);
			GPIO_ResetBits(GPIOB, GPIO_Pin_5);	
			GPIO_SetBits(GPIOB, GPIO_Pin_0);
			GPIO_ResetBits(GPIOB, GPIO_Pin_1);	
			translate(c1);
		}
		else if (f==1)
		{
			GPIO_SetBits(GPIOB, GPIO_Pin_6);
			GPIO_ResetBits(GPIOB, GPIO_Pin_5);	
			GPIO_SetBits(GPIOB, GPIO_Pin_1);
			GPIO_ResetBits(GPIOB, GPIO_Pin_0);	
			translate(d1);	
		}       //EW
		else if (f==2)
		{
			GPIO_SetBits(GPIOB, GPIO_Pin_5);
			GPIO_ResetBits(GPIOB, GPIO_Pin_6);	
			GPIO_SetBits(GPIOB, GPIO_Pin_0);
			GPIO_ResetBits(GPIOB, GPIO_Pin_1);	
			translate(c2);
		}
		else if (f==3)
		{
			GPIO_SetBits(GPIOB, GPIO_Pin_5);
			GPIO_ResetBits(GPIOB, GPIO_Pin_6);	
			GPIO_SetBits(GPIOB, GPIO_Pin_1);
			GPIO_ResetBits(GPIOB, GPIO_Pin_0);	
			translate(d2);
		}  //SN
  
	}
	else if (a>=40000 && a<78000 )
	{
		b1=78500-a;
		c1=b1/10000;
		d1=b1%10000/1000;
		b2=80500-a;
		c2=b2/10000;
		d2=b2%10000/1000;
		f=a%4;
		if(f==0)
		{
			GPIO_SetBits(GPIOB, GPIO_Pin_6);
			GPIO_ResetBits(GPIOB, GPIO_Pin_5);	
			GPIO_SetBits(GPIOB, GPIO_Pin_0);
			GPIO_ResetBits(GPIOB, GPIO_Pin_1);	
			translate(c1);
		}
		else if (f==1)
		{
			GPIO_SetBits(GPIOB, GPIO_Pin_6);
			GPIO_ResetBits(GPIOB, GPIO_Pin_5);	
			GPIO_SetBits(GPIOB, GPIO_Pin_1);
			GPIO_ResetBits(GPIOB, GPIO_Pin_0);	
			translate(d1);
		}       //EW
		else if (f==2)
		{
			GPIO_SetBits(GPIOB, GPIO_Pin_5);
			GPIO_ResetBits(GPIOB, GPIO_Pin_6);	
			GPIO_SetBits(GPIOB, GPIO_Pin_0);
			GPIO_ResetBits(GPIOB, GPIO_Pin_1);	
			translate(c2);
		}
		else if (f==3)
		{
			GPIO_SetBits(GPIOB, GPIO_Pin_5);
			GPIO_ResetBits(GPIOB, GPIO_Pin_6);	
			GPIO_SetBits(GPIOB, GPIO_Pin_1);
			GPIO_ResetBits(GPIOB, GPIO_Pin_0);	
			translate(d2);
		}  //SN
	}
	else if (a>=78000 && a<80000)
	{
		b1=80500-a;
		c1=b1/10000;
		d1=b1%10000/1000;
		b2=80500-a;
		c2=b2/10000;
		d2=b2%10000/1000;
		f=a%2;
		if(f==0)
		{
			GPIO_SetBits(GPIOB, GPIO_Pin_6);
			GPIO_ResetBits(GPIOB, GPIO_Pin_5);	
			GPIO_SetBits(GPIOB, GPIO_Pin_0);
			GPIO_ResetBits(GPIOB, GPIO_Pin_1);	
			translate(c1);
		}
		else if (f==1)
		{
			GPIO_SetBits(GPIOB, GPIO_Pin_6);
			GPIO_ResetBits(GPIOB, GPIO_Pin_5);	
			GPIO_SetBits(GPIOB, GPIO_Pin_1);
			GPIO_ResetBits(GPIOB, GPIO_Pin_0);	
			translate(d1);
		}       //EW
		else if (f==2)
		{
			GPIO_SetBits(GPIOB, GPIO_Pin_5);
			GPIO_ResetBits(GPIOB, GPIO_Pin_6);	
			GPIO_SetBits(GPIOB, GPIO_Pin_0);
			GPIO_ResetBits(GPIOB, GPIO_Pin_1);	
			translate(c2);
		}
		else if (f==3)
		{
			GPIO_SetBits(GPIOB, GPIO_Pin_5);
			GPIO_ResetBits(GPIOB, GPIO_Pin_6);	
			GPIO_SetBits(GPIOB, GPIO_Pin_1);
			GPIO_ResetBits(GPIOB, GPIO_Pin_0);	
			translate(d2);
		}  //SN
	}
}//Segment_led

/**
  * @brief  function for how 7Segments translate the signal .
  * @param  None
  * @retval None
  */
void translate(u8 a)
{
	switch(a)
	{
		case 0:
		{GPIO_SetBits(GPIOA, GPIO_Pin_3);GPIO_SetBits(GPIOA, GPIO_Pin_4);
		GPIO_SetBits(GPIOA, GPIO_Pin_5);GPIO_SetBits(GPIOA, GPIO_Pin_6);
		GPIO_SetBits(GPIOA, GPIO_Pin_7);GPIO_SetBits(GPIOA, GPIO_Pin_8);
		GPIO_ResetBits(GPIOA, GPIO_Pin_9);break;}		
		case 1:      
		{GPIO_ResetBits(GPIOA, GPIO_Pin_3);GPIO_SetBits(GPIOA, GPIO_Pin_4);
		GPIO_SetBits(GPIOA, GPIO_Pin_5);GPIO_ResetBits(GPIOA, GPIO_Pin_6);
		GPIO_ResetBits(GPIOA, GPIO_Pin_7);GPIO_ResetBits(GPIOA, GPIO_Pin_8);
		GPIO_ResetBits(GPIOA, GPIO_Pin_9);break;}		
		case 2:
		{GPIO_SetBits(GPIOA, GPIO_Pin_3);GPIO_SetBits(GPIOA, GPIO_Pin_4);
		GPIO_ResetBits(GPIOA, GPIO_Pin_5);GPIO_SetBits(GPIOA, GPIO_Pin_6);
		GPIO_SetBits(GPIOA, GPIO_Pin_7);GPIO_ResetBits(GPIOA, GPIO_Pin_8);
		GPIO_SetBits(GPIOA, GPIO_Pin_9);break;}		
		case 3:
		{GPIO_SetBits(GPIOA, GPIO_Pin_3);GPIO_SetBits(GPIOA, GPIO_Pin_4);
		GPIO_SetBits(GPIOA, GPIO_Pin_5);GPIO_SetBits(GPIOA, GPIO_Pin_6);
		GPIO_ResetBits(GPIOA, GPIO_Pin_7);GPIO_ResetBits(GPIOA, GPIO_Pin_8);
		GPIO_SetBits(GPIOA, GPIO_Pin_9);break;}		
		case 4:
		{GPIO_ResetBits(GPIOA, GPIO_Pin_3);GPIO_SetBits(GPIOA, GPIO_Pin_4);
		GPIO_SetBits(GPIOA, GPIO_Pin_5);GPIO_ResetBits(GPIOA, GPIO_Pin_6);
		GPIO_ResetBits(GPIOA, GPIO_Pin_7);GPIO_SetBits(GPIOA, GPIO_Pin_8);
		GPIO_SetBits(GPIOA, GPIO_Pin_9);break;}		
		case 5:
		{GPIO_SetBits(GPIOA, GPIO_Pin_3);GPIO_ResetBits(GPIOA, GPIO_Pin_4);
		GPIO_SetBits(GPIOA, GPIO_Pin_5);GPIO_SetBits(GPIOA, GPIO_Pin_6);
		GPIO_ResetBits(GPIOA, GPIO_Pin_7);GPIO_SetBits(GPIOA, GPIO_Pin_8);
		GPIO_SetBits(GPIOA, GPIO_Pin_9);break;}		
		case 6:
		{GPIO_SetBits(GPIOA, GPIO_Pin_3);GPIO_ResetBits(GPIOA, GPIO_Pin_4);
		GPIO_SetBits(GPIOA, GPIO_Pin_5);GPIO_SetBits(GPIOA, GPIO_Pin_6);
		GPIO_SetBits(GPIOA, GPIO_Pin_7);GPIO_SetBits(GPIOA, GPIO_Pin_8);
		GPIO_SetBits(GPIOA, GPIO_Pin_9);break;}		
		case 7:
		{GPIO_SetBits(GPIOA, GPIO_Pin_3);GPIO_SetBits(GPIOA, GPIO_Pin_4);
		GPIO_SetBits(GPIOA, GPIO_Pin_5);GPIO_ResetBits(GPIOA, GPIO_Pin_6);
		GPIO_ResetBits(GPIOA, GPIO_Pin_7);GPIO_ResetBits(GPIOA, GPIO_Pin_8);
		GPIO_ResetBits(GPIOA, GPIO_Pin_9);break;}		
		case 9:	
		{GPIO_SetBits(GPIOA, GPIO_Pin_3);GPIO_SetBits(GPIOA, GPIO_Pin_4);
		GPIO_SetBits(GPIOA, GPIO_Pin_5);GPIO_SetBits(GPIOA, GPIO_Pin_6);
		GPIO_ResetBits(GPIOA, GPIO_Pin_7);GPIO_SetBits(GPIOA, GPIO_Pin_8);
		GPIO_SetBits(GPIOA, GPIO_Pin_9);break;}		
		case 8:
		{GPIO_SetBits(GPIOA, GPIO_Pin_3);GPIO_SetBits(GPIOA, GPIO_Pin_4);
		GPIO_SetBits(GPIOA, GPIO_Pin_5);GPIO_SetBits(GPIOA, GPIO_Pin_6);
		GPIO_SetBits(GPIOA, GPIO_Pin_7);GPIO_SetBits(GPIOA, GPIO_Pin_8);
		GPIO_SetBits(GPIOA, GPIO_Pin_9);break;}		

		default:     
		{GPIO_ResetBits(GPIOA, GPIO_Pin_3);GPIO_SetBits(GPIOA, GPIO_Pin_4);
		GPIO_SetBits(GPIOA, GPIO_Pin_5);GPIO_ResetBits(GPIOA, GPIO_Pin_6);
		GPIO_SetBits(GPIOA, GPIO_Pin_7);GPIO_SetBits(GPIOA, GPIO_Pin_8);
		GPIO_SetBits(GPIOA, GPIO_Pin_9);break;}		
	}//end switch
}//translate

/**
  * @brief  function for the GPIO output in one circle.
  * @param  uint32_t a,uint32_t b
  * @retval uint32_t
  */
u32 circle(u32 a,u32 b)
{
	uint32_t c,d,c1,d1,c2,d2;
	
	if (a<35000 )
	{
		if (a==1)  
		ESP8266_SendString("SouthNorth Green \n WestEast Red",32);
		c1=(38500-a)/10000;
		d1=(38500-a)%10000/1000;
		c2=(40500-a)/10000;
		d2=(40500-a)%10000/1000;

		c=a%4;
		if (c==0)
		{
			GPIO_ResetBits(GPIOB, GPIO_Pin_6);     
				
			GPIO_SetBits(GPIOA, GPIO_Pin_10);
			GPIO_SetBits(GPIOA, GPIO_Pin_2);
			GPIO_ResetBits(GPIOA, GPIO_Pin_0); 
			GPIO_ResetBits(GPIOA, GPIO_Pin_1);

			GPIO_ResetBits(GPIOB, GPIO_Pin_1); 
			translate(c1);
			GPIO_SetBits(GPIOB, GPIO_Pin_0);
			
			GPIO_SetBits(GPIOB, GPIO_Pin_5);  
		}      
		else if(c==1)
		{
			GPIO_ResetBits(GPIOB, GPIO_Pin_6);     
				
			GPIO_SetBits(GPIOA, GPIO_Pin_10);
			GPIO_SetBits(GPIOA, GPIO_Pin_2);
			GPIO_ResetBits(GPIOA, GPIO_Pin_0); 
			GPIO_ResetBits(GPIOA, GPIO_Pin_1);
		
			GPIO_ResetBits(GPIOB, GPIO_Pin_0); 
			translate(d1);
			GPIO_SetBits(GPIOB, GPIO_Pin_1);
		
			GPIO_SetBits(GPIOB, GPIO_Pin_5); 
		
		}
		else if(c==2)
		{
			GPIO_ResetBits(GPIOB, GPIO_Pin_5);     
			
			GPIO_SetBits(GPIOA, GPIO_Pin_0);
			GPIO_ResetBits(GPIOA, GPIO_Pin_10); 
			GPIO_ResetBits(GPIOA, GPIO_Pin_1);
			GPIO_ResetBits(GPIOA, GPIO_Pin_2);
				
			GPIO_ResetBits(GPIOB, GPIO_Pin_1); 
			translate(c2);
			GPIO_SetBits(GPIOB, GPIO_Pin_0);		
								
			GPIO_SetBits(GPIOB, GPIO_Pin_6);    
		}      		
		else if (c==3)
		{
			GPIO_ResetBits(GPIOB, GPIO_Pin_5);      
			
			GPIO_SetBits(GPIOA, GPIO_Pin_0);
			GPIO_ResetBits(GPIOA, GPIO_Pin_10); 
			GPIO_ResetBits(GPIOA, GPIO_Pin_1);
			GPIO_ResetBits(GPIOA, GPIO_Pin_2);
				
			GPIO_ResetBits(GPIOB, GPIO_Pin_0); 
			translate(d2);
			GPIO_SetBits(GPIOB, GPIO_Pin_1);		
						
			GPIO_SetBits(GPIOB, GPIO_Pin_6);
		}
	}      //0-35s     
	else if (a>=35000 && a<38000)
	{
		c1=(38500-a)/10000;
		d1=(38500-a)%10000/1000;
		c2=(40500-a)/10000;
		d2=(40500-a)%10000/1000;
		c=a%4;
		d=(a/500)%2;
		if(d)
		{
			if (c==0)
			{
				GPIO_ResetBits(GPIOB, GPIO_Pin_6);     //EW light off
					
				GPIO_SetBits(GPIOA, GPIO_Pin_10);
				GPIO_SetBits(GPIOA, GPIO_Pin_2);
				GPIO_ResetBits(GPIOA, GPIO_Pin_0); 
				GPIO_ResetBits(GPIOA, GPIO_Pin_1); 
					
				GPIO_ResetBits(GPIOB, GPIO_Pin_1); 
				translate(c1);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);	
				
				GPIO_SetBits(GPIOB, GPIO_Pin_5);  //SN light on
			}       
			else if (c==1)
			{
				GPIO_ResetBits(GPIOB, GPIO_Pin_6);      //SN light off
					
				GPIO_SetBits(GPIOA, GPIO_Pin_10);
				GPIO_SetBits(GPIOA, GPIO_Pin_2);
				GPIO_ResetBits(GPIOA, GPIO_Pin_0); 
				GPIO_ResetBits(GPIOA, GPIO_Pin_1); 	
					
				GPIO_ResetBits(GPIOB, GPIO_Pin_0); 
				translate(d1);
				GPIO_SetBits(GPIOB, GPIO_Pin_1);
					
				GPIO_SetBits(GPIOB, GPIO_Pin_5);    //EW  light  on
			}   
			else if (c==2)
			{
				GPIO_ResetBits(GPIOB, GPIO_Pin_5);      //SN light off
					
				GPIO_SetBits(GPIOA, GPIO_Pin_0);
				GPIO_ResetBits(GPIOA, GPIO_Pin_10); 
				GPIO_ResetBits(GPIOA, GPIO_Pin_1);
				GPIO_ResetBits(GPIOA, GPIO_Pin_2);
					
				GPIO_ResetBits(GPIOB, GPIO_Pin_1); 
				translate(c2);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
					
				GPIO_SetBits(GPIOB, GPIO_Pin_6);    //EW  light  on
			}   
			else if (c==3)
			{
				GPIO_ResetBits(GPIOB, GPIO_Pin_5);      
					
				GPIO_SetBits(GPIOA, GPIO_Pin_0);
				GPIO_ResetBits(GPIOA, GPIO_Pin_10); 
				GPIO_ResetBits(GPIOA, GPIO_Pin_1);
				GPIO_ResetBits(GPIOA, GPIO_Pin_2);
					
				GPIO_ResetBits(GPIOB, GPIO_Pin_0); 
				translate(d2);
				GPIO_SetBits(GPIOB, GPIO_Pin_1);
					
				GPIO_SetBits(GPIOB, GPIO_Pin_6);    
			}   
		}  
		else
		{
			if (c==0)
			{
				GPIO_ResetBits(GPIOB, GPIO_Pin_6);    
					
				GPIO_ResetBits(GPIOA, GPIO_Pin_10);
				GPIO_ResetBits(GPIOA, GPIO_Pin_2);
				GPIO_ResetBits(GPIOA, GPIO_Pin_0); 
				GPIO_ResetBits(GPIOA, GPIO_Pin_1); 
					
				GPIO_ResetBits(GPIOB, GPIO_Pin_1); 
				translate(c1);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);	
						
				GPIO_SetBits(GPIOB, GPIO_Pin_5);  
			
			}       
			else if (c==1)
			{
				GPIO_ResetBits(GPIOB, GPIO_Pin_6);     
					
				GPIO_ResetBits(GPIOA, GPIO_Pin_10);
				GPIO_ResetBits(GPIOA, GPIO_Pin_2);
				GPIO_ResetBits(GPIOA, GPIO_Pin_0); 
				GPIO_ResetBits(GPIOA, GPIO_Pin_1);
					
					
				GPIO_ResetBits(GPIOB, GPIO_Pin_0); 
				translate(d1);
				GPIO_SetBits(GPIOB, GPIO_Pin_1);
					
				GPIO_SetBits(GPIOB, GPIO_Pin_5);    
			}   
			else if (c==2)
			{
				GPIO_ResetBits(GPIOB, GPIO_Pin_5);      
					
				GPIO_SetBits(GPIOA, GPIO_Pin_0);
				GPIO_ResetBits(GPIOA, GPIO_Pin_10); 
				GPIO_ResetBits(GPIOA, GPIO_Pin_1);
				GPIO_ResetBits(GPIOA, GPIO_Pin_2);
					
				GPIO_ResetBits(GPIOB, GPIO_Pin_1); 
				translate(c2);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
					
				GPIO_SetBits(GPIOB, GPIO_Pin_6);   
			}   
			else if (c==3)
			{
				GPIO_ResetBits(GPIOB, GPIO_Pin_5);     
					
				GPIO_SetBits(GPIOA, GPIO_Pin_0);
				GPIO_ResetBits(GPIOA, GPIO_Pin_10); 
				GPIO_ResetBits(GPIOA, GPIO_Pin_1);
				GPIO_ResetBits(GPIOA, GPIO_Pin_2);
					
				GPIO_ResetBits(GPIOB, GPIO_Pin_0); 
				translate(d2);
				GPIO_SetBits(GPIOB, GPIO_Pin_1);
					
				GPIO_SetBits(GPIOB, GPIO_Pin_6);   
			}   
		}  
			
	}		     //35-38s,   SN lights are green and blink and EW lights are red.

	else if (a>=38000 && a<40000)
	{   
		if (a==38000)  
		ESP8266_SendString("SouthNorth Yellow\n WestEast Red",32);
		c1=(40500-a)/10000;
		d1=(40500-a)%10000/1000;
		c2=(40500-a)/10000;
		d2=(40500-a)%10000/1000;
		c=a%4;
		d=(a/500)%2;
		GPIO_SetBits(GPIOB, GPIO_Pin_7);
		if(d)
		{
			if (c==0)
			{
				GPIO_ResetBits(GPIOB, GPIO_Pin_6);     
					
				GPIO_SetBits(GPIOA, GPIO_Pin_1);
				GPIO_SetBits(GPIOA, GPIO_Pin_10);
				GPIO_ResetBits(GPIOA, GPIO_Pin_0); 
				GPIO_ResetBits(GPIOA, GPIO_Pin_2); 
					
				GPIO_ResetBits(GPIOB, GPIO_Pin_1); 
				translate(c1);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);					
				
				GPIO_SetBits(GPIOB, GPIO_Pin_5);  //SN light on
			}       
			else if (c==1)
			{
				GPIO_ResetBits(GPIOB, GPIO_Pin_6);      //SN light off
					
				GPIO_SetBits(GPIOA, GPIO_Pin_1);
				GPIO_SetBits(GPIOA, GPIO_Pin_10);
				GPIO_ResetBits(GPIOA, GPIO_Pin_0); 
				GPIO_ResetBits(GPIOA, GPIO_Pin_2); 
					
				GPIO_ResetBits(GPIOB, GPIO_Pin_0); 
				translate(d1);
				GPIO_SetBits(GPIOB, GPIO_Pin_1);
					
				GPIO_SetBits(GPIOB, GPIO_Pin_5);    //EW  light  on
			}   
			else if (c==2)
			{
				GPIO_ResetBits(GPIOB, GPIO_Pin_5);      //SN light off
					
				GPIO_SetBits(GPIOA, GPIO_Pin_0);
				GPIO_ResetBits(GPIOA, GPIO_Pin_10); 
				GPIO_ResetBits(GPIOA, GPIO_Pin_1);
				GPIO_ResetBits(GPIOA, GPIO_Pin_2);
					
				GPIO_ResetBits(GPIOB, GPIO_Pin_1); 
				translate(c2);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
					
				GPIO_SetBits(GPIOB, GPIO_Pin_6);    //EW  light  on
			}   
			else if (c==3)
			{
				GPIO_ResetBits(GPIOB, GPIO_Pin_5);      
					
				GPIO_SetBits(GPIOA, GPIO_Pin_0);
				GPIO_ResetBits(GPIOA, GPIO_Pin_10); 
				GPIO_ResetBits(GPIOA, GPIO_Pin_1);
				GPIO_ResetBits(GPIOA, GPIO_Pin_2);
					
				GPIO_ResetBits(GPIOB, GPIO_Pin_0); 
				translate(d2);
				GPIO_SetBits(GPIOB, GPIO_Pin_1);
					
				GPIO_SetBits(GPIOB, GPIO_Pin_6);    
			}   
		}  
		else
		{
			if (c==0)
			{
				GPIO_ResetBits(GPIOB, GPIO_Pin_6);    
					
				GPIO_ResetBits(GPIOA, GPIO_Pin_10);
				GPIO_ResetBits(GPIOA, GPIO_Pin_2);
				GPIO_ResetBits(GPIOA, GPIO_Pin_0); 
				GPIO_SetBits(GPIOA, GPIO_Pin_1); 
					
				GPIO_ResetBits(GPIOB, GPIO_Pin_1); 
				translate(c1);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);	
					
				GPIO_SetBits(GPIOB, GPIO_Pin_5);  
			
			}       
			else if (c==1)
			{
				GPIO_ResetBits(GPIOB, GPIO_Pin_6);     
					
				GPIO_ResetBits(GPIOA, GPIO_Pin_10);
				GPIO_ResetBits(GPIOA, GPIO_Pin_2);
				GPIO_ResetBits(GPIOA, GPIO_Pin_0); 
				GPIO_SetBits(GPIOA, GPIO_Pin_1); 
						
				GPIO_ResetBits(GPIOB, GPIO_Pin_0); 
				translate(d1);
				GPIO_SetBits(GPIOB, GPIO_Pin_1);
					
				GPIO_SetBits(GPIOB, GPIO_Pin_5);    
			}   
			else if (c==2)
			{
				GPIO_ResetBits(GPIOB, GPIO_Pin_5);      
					
				GPIO_SetBits(GPIOA, GPIO_Pin_0);
				GPIO_ResetBits(GPIOA, GPIO_Pin_10); 
				GPIO_ResetBits(GPIOA, GPIO_Pin_1);
				GPIO_ResetBits(GPIOA, GPIO_Pin_2);
					
				GPIO_ResetBits(GPIOB, GPIO_Pin_1); 
				translate(c2);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
					
				GPIO_SetBits(GPIOB, GPIO_Pin_6);   
			}   
			else if (c==3)
			{
				GPIO_ResetBits(GPIOB, GPIO_Pin_5);     
					
				GPIO_SetBits(GPIOA, GPIO_Pin_0);
				GPIO_ResetBits(GPIOA, GPIO_Pin_10); 
				GPIO_ResetBits(GPIOA, GPIO_Pin_1);
				GPIO_ResetBits(GPIOA, GPIO_Pin_2);
					
				GPIO_ResetBits(GPIOB, GPIO_Pin_0); 
				translate(d2);
				GPIO_SetBits(GPIOB, GPIO_Pin_1);
					
				GPIO_SetBits(GPIOB, GPIO_Pin_6);   
			}   
		}  
	}//38-40s     buzzer is sounding.  SN lights on main road yellow and on sub-road green and blink,   ,EW lights red.
	else if (a>=40000 && a<75000)
	{   
		if (a==40000)  
		ESP8266_SendString("SouthNorth Red\n WestEast Green",31);
		GPIO_ResetBits(GPIOB, GPIO_Pin_7);
		c1=(80500-a)/10000;
		d1=(80500-a)%10000/1000;
		c2=(78500-a)/10000;
		d2=(78500-a)%10000/1000;
		c=a%4;
		
		if (c==0)
		{
			GPIO_ResetBits(GPIOB, GPIO_Pin_6);     
				
			GPIO_ResetBits(GPIOA, GPIO_Pin_10);
			GPIO_ResetBits(GPIOA, GPIO_Pin_2);
			GPIO_SetBits(GPIOA, GPIO_Pin_0); 
			GPIO_ResetBits(GPIOA, GPIO_Pin_1);
		
			GPIO_ResetBits(GPIOB, GPIO_Pin_1); 
			translate(c1);
			GPIO_SetBits(GPIOB, GPIO_Pin_0);

			GPIO_SetBits(GPIOB, GPIO_Pin_5);  
		}      
			
		else if(c==1)
		{
			GPIO_ResetBits(GPIOB, GPIO_Pin_6);     
				
			GPIO_ResetBits(GPIOA, GPIO_Pin_10);
			GPIO_ResetBits(GPIOA, GPIO_Pin_2);
			GPIO_SetBits(GPIOA, GPIO_Pin_0); 
			GPIO_ResetBits(GPIOA, GPIO_Pin_1);
		
			GPIO_ResetBits(GPIOB, GPIO_Pin_0); 
			translate(d1);
			GPIO_SetBits(GPIOB, GPIO_Pin_1);

			GPIO_SetBits(GPIOB, GPIO_Pin_5); 	
		}
		else if(c==2)
		{
			GPIO_ResetBits(GPIOB, GPIO_Pin_5);     
			
			GPIO_SetBits(GPIOA, GPIO_Pin_2);
			GPIO_SetBits(GPIOA, GPIO_Pin_10); 
			GPIO_ResetBits(GPIOA, GPIO_Pin_1);
			GPIO_ResetBits(GPIOA, GPIO_Pin_0);
				
			GPIO_ResetBits(GPIOB, GPIO_Pin_1); 
			translate(c2);
			GPIO_SetBits(GPIOB, GPIO_Pin_0);			
						
			GPIO_SetBits(GPIOB, GPIO_Pin_6);    
		}      
		else if (c==3)
		{
			GPIO_ResetBits(GPIOB, GPIO_Pin_5);      
			
			GPIO_SetBits(GPIOA, GPIO_Pin_2);
			GPIO_SetBits(GPIOA, GPIO_Pin_10); 
			GPIO_ResetBits(GPIOA, GPIO_Pin_1);
			GPIO_ResetBits(GPIOA, GPIO_Pin_0);
				
			GPIO_ResetBits(GPIOB, GPIO_Pin_0); 
			translate(d2);
			GPIO_SetBits(GPIOB, GPIO_Pin_1);		
						
			GPIO_SetBits(GPIOB, GPIO_Pin_6);
		}
	}  //40~75S,   

	else if (a>=75000 && a<78000)
	{
		c1=(80500-a)/10000;
		d1=(80500-a)%10000/1000;
		c2=(78500-a)/10000;
		d2=(78500-a)%10000/1000;
		c=a%4;
		d=(a/500)%2;
		if(d)
		{
			if (c==0)
			{
				GPIO_ResetBits(GPIOB, GPIO_Pin_6);     //EW light off
					
				GPIO_ResetBits(GPIOA, GPIO_Pin_10);
				GPIO_ResetBits(GPIOA, GPIO_Pin_2);
				GPIO_ResetBits(GPIOA, GPIO_Pin_1); 
				GPIO_SetBits(GPIOA, GPIO_Pin_0); 
					
				GPIO_ResetBits(GPIOB, GPIO_Pin_1); 
				translate(c1);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);	
					
				GPIO_SetBits(GPIOB, GPIO_Pin_5);  //SN light on
			}       
			else if (c==1)
			{
				GPIO_ResetBits(GPIOB, GPIO_Pin_6);      //SN light off
					
				GPIO_ResetBits(GPIOA, GPIO_Pin_10);
				GPIO_ResetBits(GPIOA, GPIO_Pin_2);
				GPIO_ResetBits(GPIOA, GPIO_Pin_1); 
				GPIO_SetBits(GPIOA, GPIO_Pin_0); 
							
				GPIO_ResetBits(GPIOB, GPIO_Pin_0); 
				translate(d1);
				GPIO_SetBits(GPIOB, GPIO_Pin_1);
					
				GPIO_SetBits(GPIOB, GPIO_Pin_5);    //EW  light  on
			}   
			else if (c==2)
			{
				GPIO_ResetBits(GPIOB, GPIO_Pin_5);      //SN light off
					
				GPIO_SetBits(GPIOA, GPIO_Pin_2);
				GPIO_SetBits(GPIOA, GPIO_Pin_10); 
				GPIO_ResetBits(GPIOA, GPIO_Pin_1);
				GPIO_ResetBits(GPIOA, GPIO_Pin_0);
					
				GPIO_ResetBits(GPIOB, GPIO_Pin_1); 
				translate(c2);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
					
				GPIO_SetBits(GPIOB, GPIO_Pin_6);    //EW  light  on
			}   
			else if (c==3)
			{
				GPIO_ResetBits(GPIOB, GPIO_Pin_5);      
					
				GPIO_SetBits(GPIOA, GPIO_Pin_2);
				GPIO_SetBits(GPIOA, GPIO_Pin_10); 
				GPIO_ResetBits(GPIOA, GPIO_Pin_1);
				GPIO_ResetBits(GPIOA, GPIO_Pin_0);
					
				GPIO_ResetBits(GPIOB, GPIO_Pin_0); 
				translate(d2);
				GPIO_SetBits(GPIOB, GPIO_Pin_1);
					
				GPIO_SetBits(GPIOB, GPIO_Pin_6);    
			}   
		}  
		else
		{
			if (c==0)
			{
				GPIO_ResetBits(GPIOB, GPIO_Pin_6);    
					
				GPIO_ResetBits(GPIOA, GPIO_Pin_10);
				GPIO_ResetBits(GPIOA, GPIO_Pin_2);
				GPIO_ResetBits(GPIOA, GPIO_Pin_1); 
				GPIO_SetBits(GPIOA, GPIO_Pin_0); 
					
				GPIO_ResetBits(GPIOB, GPIO_Pin_1); 
				translate(c1);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);	
		
				GPIO_SetBits(GPIOB, GPIO_Pin_5);  
			}       
			else if (c==1)
			{
				GPIO_ResetBits(GPIOB, GPIO_Pin_6);     
					
				GPIO_ResetBits(GPIOA, GPIO_Pin_10);
				GPIO_ResetBits(GPIOA, GPIO_Pin_2);
				GPIO_ResetBits(GPIOA, GPIO_Pin_1); 
				GPIO_SetBits(GPIOA, GPIO_Pin_0); 
					
				GPIO_ResetBits(GPIOB, GPIO_Pin_0); 
				translate(d1);
				GPIO_SetBits(GPIOB, GPIO_Pin_1);
					
				GPIO_SetBits(GPIOB, GPIO_Pin_5);    
			}   
			else if (c==2)
			{
				GPIO_ResetBits(GPIOB, GPIO_Pin_5);      
					
				GPIO_ResetBits(GPIOA, GPIO_Pin_0);
				GPIO_ResetBits(GPIOA, GPIO_Pin_10); 
				GPIO_ResetBits(GPIOA, GPIO_Pin_1);
				GPIO_ResetBits(GPIOA, GPIO_Pin_2);
					
				GPIO_ResetBits(GPIOB, GPIO_Pin_1); 
				translate(c2);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
					
				GPIO_SetBits(GPIOB, GPIO_Pin_6);   
			}   
			else if (c==3)
			{
				GPIO_ResetBits(GPIOB, GPIO_Pin_5);     
					
				GPIO_ResetBits(GPIOA, GPIO_Pin_0);
				GPIO_ResetBits(GPIOA, GPIO_Pin_10); 
				GPIO_ResetBits(GPIOA, GPIO_Pin_1);
				GPIO_ResetBits(GPIOA, GPIO_Pin_2);
					
				GPIO_ResetBits(GPIOB, GPIO_Pin_0); 
				translate(d2);
				GPIO_SetBits(GPIOB, GPIO_Pin_1);
					
				GPIO_SetBits(GPIOB, GPIO_Pin_6);   
			}   
		}  
	}
	else if (a>=78000 && a<80000)
	{
		if (a==78000)     
		ESP8266_SendString("SouthNorth Red\n WestEast Yellow",32);
		c1=(80500-a)/10000;
		d1=(80500-a)%10000/1000;
		c2=(80500-a)/10000;
		d2=(80500-a)%10000/1000;
		c=a%4;
		d=(a/500)%2;
		
		GPIO_SetBits(GPIOB, GPIO_Pin_7);
		if(d)
		{
			if (c==0)
			{
				GPIO_ResetBits(GPIOB, GPIO_Pin_6);     
					
				GPIO_SetBits(GPIOA, GPIO_Pin_0);
				GPIO_ResetBits(GPIOA, GPIO_Pin_10);
				GPIO_ResetBits(GPIOA, GPIO_Pin_1); 
				GPIO_ResetBits(GPIOA, GPIO_Pin_2); 
					
				GPIO_ResetBits(GPIOB, GPIO_Pin_1); 
				translate(c1);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);	
				
				GPIO_SetBits(GPIOB, GPIO_Pin_5);  //SN light on
			}       
			else if (c==1)
			{
				GPIO_ResetBits(GPIOB, GPIO_Pin_6);      //SN light off
					
				GPIO_SetBits(GPIOA, GPIO_Pin_0);
				GPIO_ResetBits(GPIOA, GPIO_Pin_10);
				GPIO_ResetBits(GPIOA, GPIO_Pin_1); 
				GPIO_ResetBits(GPIOA, GPIO_Pin_2); 
			
				GPIO_ResetBits(GPIOB, GPIO_Pin_0); 
				translate(d1);
				GPIO_SetBits(GPIOB, GPIO_Pin_1);
					
				GPIO_SetBits(GPIOB, GPIO_Pin_5);    //EW  light  on
			}   
			else if (c==2)
			{
				GPIO_ResetBits(GPIOB, GPIO_Pin_5);      //SN light off
					
				GPIO_SetBits(GPIOA, GPIO_Pin_1);
				GPIO_SetBits(GPIOA, GPIO_Pin_10); 
				GPIO_ResetBits(GPIOA, GPIO_Pin_0);
				GPIO_ResetBits(GPIOA, GPIO_Pin_2);
					
				GPIO_ResetBits(GPIOB, GPIO_Pin_1); 
				translate(c2);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
					
				GPIO_SetBits(GPIOB, GPIO_Pin_6);    //EW  light  on
			}   
			else if (c==3)
			{
				GPIO_ResetBits(GPIOB, GPIO_Pin_5);      
					
				GPIO_SetBits(GPIOA, GPIO_Pin_1);
				GPIO_SetBits(GPIOA, GPIO_Pin_10); 
				GPIO_ResetBits(GPIOA, GPIO_Pin_0);
				GPIO_ResetBits(GPIOA, GPIO_Pin_2);
					
				GPIO_ResetBits(GPIOB, GPIO_Pin_0); 
				translate(d2);
				GPIO_SetBits(GPIOB, GPIO_Pin_1);
					
				GPIO_SetBits(GPIOB, GPIO_Pin_6);    
			}   
		}  
		else
		{
			if (c==0)
			{
				GPIO_ResetBits(GPIOB, GPIO_Pin_6);    
					
				GPIO_SetBits(GPIOA, GPIO_Pin_0);
				GPIO_ResetBits(GPIOA, GPIO_Pin_10);
				GPIO_ResetBits(GPIOA, GPIO_Pin_1); 
				GPIO_ResetBits(GPIOA, GPIO_Pin_2);  
					
				GPIO_ResetBits(GPIOB, GPIO_Pin_1); 
				translate(c1);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);	

				GPIO_SetBits(GPIOB, GPIO_Pin_5);  
			
			}       
			else if (c==1)
			{
				GPIO_ResetBits(GPIOB, GPIO_Pin_6);     
					
				GPIO_SetBits(GPIOA, GPIO_Pin_0);
				GPIO_ResetBits(GPIOA, GPIO_Pin_10);
				GPIO_ResetBits(GPIOA, GPIO_Pin_1); 
				GPIO_ResetBits(GPIOA, GPIO_Pin_2); 

				GPIO_ResetBits(GPIOB, GPIO_Pin_0); 
				translate(d1);
				GPIO_SetBits(GPIOB, GPIO_Pin_1);
					
				GPIO_SetBits(GPIOB, GPIO_Pin_5);    
			}   
			else if (c==2)
			{
				GPIO_ResetBits(GPIOB, GPIO_Pin_5);      
					
				GPIO_SetBits(GPIOA, GPIO_Pin_1);
				GPIO_ResetBits(GPIOA, GPIO_Pin_10); 
				GPIO_ResetBits(GPIOA, GPIO_Pin_0);
				GPIO_ResetBits(GPIOA, GPIO_Pin_2);
					
				GPIO_ResetBits(GPIOB, GPIO_Pin_1); 
				translate(c2);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
					
				GPIO_SetBits(GPIOB, GPIO_Pin_6);   
			}   
			else if (c==3)
			{
				GPIO_ResetBits(GPIOB, GPIO_Pin_5);     
					
				GPIO_SetBits(GPIOA, GPIO_Pin_1);
				GPIO_ResetBits(GPIOA, GPIO_Pin_10); 
				GPIO_ResetBits(GPIOA, GPIO_Pin_0);
				GPIO_ResetBits(GPIOA, GPIO_Pin_2);
					
				GPIO_ResetBits(GPIOB, GPIO_Pin_0); 
				translate(d2);
				GPIO_SetBits(GPIOB, GPIO_Pin_1);
					
				GPIO_SetBits(GPIOB, GPIO_Pin_6);   
			}   
		}  
	}	   //SN   RED     EW GREEN BLINKING AND YELLOW
	else if (a==80000)
	{
		GPIO_ResetBits(GPIOB, GPIO_Pin_7);
		b++;
	}
	return (b);
}//circle

/**
  * @brief  Check if there is malfunctioning in lights
  * @param  None
  * @retval None
  */
void TrafficLight_Check(void)
{
    GPIO_SetBits(GPIOB, GPIO_Pin_5);
    GPIO_ResetBits(GPIOB, GPIO_Pin_6);
    
    GPIO_SetBits(GPIOA, GPIO_Pin_0);
    delay_nms(A);
    GPIO_ResetBits(GPIOA, GPIO_Pin_0);
    delay_nms(A);
    GPIO_SetBits(GPIOA, GPIO_Pin_1);
    delay_nms(A);
    GPIO_ResetBits(GPIOA, GPIO_Pin_1);
    delay_nms(A);
    GPIO_SetBits(GPIOA, GPIO_Pin_2);
    delay_nms(A);
    GPIO_ResetBits(GPIOA, GPIO_Pin_2);
    delay_nms(A);
    GPIO_SetBits(GPIOA, GPIO_Pin_10);
    delay_nms(A);
    GPIO_ResetBits(GPIOA, GPIO_Pin_10);
    delay_nms(A);
    //SN lights on
    
    translate(8);
    
    GPIO_SetBits(GPIOB, GPIO_Pin_1);
    GPIO_SetBits(GPIOB, GPIO_Pin_0);     //SN segments show the number 8
    delay_nms(2*A);
    
    GPIO_SetBits(GPIOB, GPIO_Pin_6);
    GPIO_ResetBits(GPIOB, GPIO_Pin_5);  
        
    GPIO_SetBits(GPIOA, GPIO_Pin_0);
    delay_nms(A);
    GPIO_ResetBits(GPIOA, GPIO_Pin_0);
    delay_nms(A);
    GPIO_SetBits(GPIOA, GPIO_Pin_1);
    delay_nms(A);
    GPIO_ResetBits(GPIOA, GPIO_Pin_1);
    delay_nms(A);
    GPIO_SetBits(GPIOA, GPIO_Pin_2);
    delay_nms(A);
    GPIO_ResetBits(GPIOA, GPIO_Pin_2);
    delay_nms(A);
    GPIO_SetBits(GPIOA, GPIO_Pin_10);
    delay_nms(A);
    GPIO_ResetBits(GPIOA, GPIO_Pin_10);
    delay_nms(A);
    
    //EW lights on
        
    translate(8);
    
    GPIO_SetBits(GPIOB, GPIO_Pin_0);
    GPIO_SetBits(GPIOB, GPIO_Pin_1);     //EW segments show the number 8
    delay_nms(2*A);
    
    GPIO_SetBits(GPIOB, GPIO_Pin_7);	
    delay_nms(B);
    GPIO_ResetBits(GPIOB, GPIO_Pin_7);	
    delay_nms(B);
    GPIO_SetBits(GPIOB, GPIO_Pin_7);	
    delay_nms(B);
    GPIO_ResetBits(GPIOB, GPIO_Pin_7);	
        //   buzzer sounds twice.
    
    delay_nms(B);
}//TrafficLight_Check

/**
  * @brief  Test run all the lights
  * @param  None
  * @retval None
  */
void TestRun(void)
{
    Init_Configuration();
    TrafficLight_Check();
    Init_Configuration();
}//in the first circle, all device will be checked in order.

void AllYellow(void)
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_0);
	GPIO_ResetBits(GPIOA,GPIO_Pin_2);
	GPIO_SetBits(GPIOA,GPIO_Pin_1);
	GPIO_SetBits(GPIOB,GPIO_Pin_5);
	GPIO_SetBits(GPIOB,GPIO_Pin_6);
	GPIO_ResetBits(GPIOB,GPIO_Pin_0);
	GPIO_ResetBits(GPIOB,GPIO_Pin_1);
}

void AllRed(void)
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_1);
	GPIO_ResetBits(GPIOA,GPIO_Pin_2);
	GPIO_SetBits(GPIOA,GPIO_Pin_0);
	GPIO_SetBits(GPIOB,GPIO_Pin_5);
	GPIO_SetBits(GPIOB,GPIO_Pin_6);
	GPIO_ResetBits(GPIOB,GPIO_Pin_0);
	GPIO_ResetBits(GPIOB,GPIO_Pin_1);
}
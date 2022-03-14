/*key deal*/
#include "stm32f4xx.h"
#include "delay.h"
#include "key.h"



/*init key gpio
*KEY0 PE2,KEY1 PE3,KEY2 PE4 set input mode,pupd_UP
*WK_UP set input mode,pupd_DOWN
*
*
*/

void KeyInit(void)
{
	
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOE, ENABLE);//ʹ��GPIOA,GPIOEʱ��
 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4; //KEY0 KEY1 KEY2��Ӧ����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//��ͨ����ģʽ
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
	GPIO_Init(GPIOE, &GPIO_InitStructure);//��ʼ��GPIOE2,3,4
	
	 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;//WK_UP��Ӧ����PA0
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN ;//����
	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA0
	

}


/*Key scan deal() 
*mode:0,��֧��������;1,֧��������;
*
*
*
*/

u8 KeyScan(u8 mode)
{
	static u8 key_up =1;  /*key relese flag*/
	if(mode) 
	{
		key_up = 1;
	}
	if(key_up && (KEY0 == 0 || KEY1 ==0 || KEY2 ==0 || WK_UP ==1))
	{
		 delay_xms(10);
		 key_up = 0;
		 if(KEY0 == 0)return KEY0_PRESS;
		 else if(KEY1 == 0)	 return KEY1_PRESS;
		 else if(KEY2 ==0 ) return KEY2_PRESS;
		 else if(WK_UP == 1) return WK_UP_PRESS; 
	}
	else if(KEY0 == 1 && KEY1 ==1 &&KEY2 ==1 &&WK_UP ==0)
	{
		key_up =1;
	}

	return 0; /*û�а�������*/
}













#ifndef __KEY_H
#define __KEY_H
#include "sys.h"


#define KEY0_PRESS  1
#define KEY1_PRESS  2
#define KEY2_PRESS  3
#define WK_UP_PRESS 4


/*下面的方式是通过直接操作库函数方式读取IO*/
#define KEY0 		GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4) //PE4
#define KEY1 		GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)	//PE3 
#define KEY2 		GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2) //PE2
#define WK_UP 	GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)	//PA0



void KeyInit(void);

u8 KeyScan(u8 mode);





#endif 
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "FreeRTOS.h"
#include "task.h"
/************************************************

************************************************/


 
void start_Task( void * pvParameters );
char START_T_NAME[] ="start_task"; /*任务名称*/
#define START_T_SIZE  120
#define START_T_PIR 	1
TaskHandle_t start_taskHandle;

void task1_Task( void * pvParameters );
char TASK1_T_NAME[] ="task1_task"; 
#define TASK1_T_SIZE  120
#define TASK1_T_PIR 	2
TaskHandle_t task1_taskHandle;


void task2_Task( void * pvParameters );
char TASK2_T_NAME[] ="task2_task"; 
#define TASK2_T_SIZE  120
#define TASK2_T_PIR 	3
TaskHandle_t task2_taskHandle;
 

int main(void)
{ 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);//设置系统中断优先级分组4
	delay_init(168);		//初始化延时函数
	uart_init(115200);     	//初始化串口
	LED_Init();		        //初始化LED端口
	
	/*创建开始任务*/
	xTaskCreate((TaskFunction_t				 ) start_Task,
							(char *        				 ) START_T_NAME, 
							(configSTACK_DEPTH_TYPE) START_T_SIZE,
							(void *								 )NULL,
							(UBaseType_t					 ) START_T_PIR,
							(TaskHandle_t *				 )  &start_taskHandle);	     

	
   vTaskStartScheduler();          //开启任务调度
}
 



/*
* start_Task function
*
***************/
 void start_Task( void * pvParameters )
{
 
      /*创建任务1*/
			xTaskCreate((TaskFunction_t				 ) task1_Task,
									(char *        				 ) TASK1_T_NAME, 
									(configSTACK_DEPTH_TYPE) TASK1_T_SIZE,
									(void *								 )NULL,
									(UBaseType_t					 ) TASK1_T_PIR,
									(TaskHandle_t *				 ) &task1_taskHandle);	  
			
			/*创建任务2*/
			xTaskCreate((TaskFunction_t				 ) task2_Task,
						(char *        				 ) TASK2_T_NAME, 
						(configSTACK_DEPTH_TYPE) TASK2_T_SIZE,
						(void *								 )NULL,
						(UBaseType_t					 ) TASK2_T_PIR,
						(TaskHandle_t *				 ) &task2_taskHandle);	  
					
			
			/*删除本任务*/
			vTaskDelete(start_taskHandle);			
			
 }

 
 
 void task1_Task( void * pvParameters )
 {
		int task1_num = 0;
		for(;;)
		{
				task1_num++;
			  printf("task1_num =%d\n",task1_num);
				if(task1_num == 5)
				{
					if(task2_taskHandle != NULL)
					{
						vTaskDelete(task2_taskHandle);
					}						
				}
				LED0 =~LED0;
				vTaskDelay(500);
				
		}
 }
 
  void task2_Task( void * pvParameters )
 {
		int task2_num = 0;
		for(;;)
		{
				task2_num++;
				printf("task2_num =%d\n",task2_num);
			  LED1 = 1;
			  vTaskDelay(500);
			  LED1 = 0;
			  vTaskDelay(2000);
		}
 }
 
 
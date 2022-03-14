#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "key.h"
#include "exti.h"
#include "FreeRTOS.h"
#include "task.h"



/************************************************
task define
************************************************/
/*start task*/
void start_Task( void * pvParameters );
char START_T_NAME[] ="start_task"; /*��������*/
#define START_T_SIZE  128
#define START_T_PIR 	1
TaskHandle_t Start_TaskHandle;

/*key task*/
void key_Task( void * pvParameters );
char KEY_T_NAME[] ="key_task"; 
#define KEY_T_SIZE  128
#define KEY_T_PIR 	2
TaskHandle_t Key_TaskHandle;

/*task1 task*/
void task1_Task( void * pvParameters );
char TASK1_T_NAME[] ="task1_task"; 
#define TASK1_T_SIZE  128
#define TASK1_T_PIR 	3
TaskHandle_t Task1_TaskHandle;

/*task2 task*/
void task2_Task( void * pvParameters );
char TASK2_T_NAME[] ="task2_task"; 
#define TASK2_T_SIZE  128
#define TASK2_T_PIR 	3
TaskHandle_t Task2_TaskHandle;
			
					
int main(void)
{ 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);//����ϵͳ�ж����ȼ�����4
	delay_init(168);		//��ʼ����ʱ����
	uart_init(115200);     	//��ʼ������
	LED_Init();		        //��ʼ��LED�˿�
	
	KeyInit(); /*key gpio init*/	
	EXTIX_Init();
	
	xTaskCreate((TaskFunction_t				 ) start_Task,
							(char *        				 ) START_T_NAME, 
							(configSTACK_DEPTH_TYPE) START_T_SIZE,
							(void *								 )NULL,
							(UBaseType_t					 ) START_T_PIR,
							(TaskHandle_t *				 )  &Start_TaskHandle);	

															
   vTaskStartScheduler();          //�����������
}
 


/*
* start_Task function
*
***************/
 void start_Task( void * pvParameters )
{
		taskENTER_CRITICAL(); /*�����ٽ���*/

	     /*����KEY����*/
			xTaskCreate((TaskFunction_t				 ) key_Task,
									(char *        				 ) KEY_T_NAME, 
									(configSTACK_DEPTH_TYPE) KEY_T_SIZE,
									(void *								 )NULL,
									(UBaseType_t					 ) KEY_T_PIR,
									(TaskHandle_t *				 ) &Key_TaskHandle);	  
			
	
      /*��������1*/
			xTaskCreate((TaskFunction_t				 ) task1_Task,
									(char *        				 ) TASK1_T_NAME, 
									(configSTACK_DEPTH_TYPE) TASK1_T_SIZE,
									(void *								 )NULL,
									(UBaseType_t					 ) TASK1_T_PIR,
									(TaskHandle_t *				 ) &Task1_TaskHandle);	  
			
			/*��������2*/
			xTaskCreate((TaskFunction_t				 ) task2_Task,
									(char *        				 ) TASK2_T_NAME, 
									(configSTACK_DEPTH_TYPE) TASK2_T_SIZE,
									(void *								 )NULL,
									(UBaseType_t					 ) TASK2_T_PIR,
									(TaskHandle_t *				 ) &Task2_TaskHandle);	  

													
			
		/*ɾ��������*/
		vTaskDelete(Start_TaskHandle);	
		taskEXIT_CRITICAL(); /*�˳��ٽ���*/
			
 }

 
void key_Task( void * pvParameters )
{
	  u8 key =0;
	 for(;;)
	 {
			key = KeyScan(0);
			switch(key)
			{
				case KEY1_PRESS:
					vTaskResume(Task1_TaskHandle); 
					printf("Resume task1\n");
					break;
				case KEY2_PRESS:
					vTaskSuspend(Task2_TaskHandle);
					printf("Suspend task2\n");
					break;
				case WK_UP_PRESS:
					vTaskResume(Task2_TaskHandle); 
					printf("Resume task2\n");
					break;
				default:break;	
			}
	 }
}
 

 void task1_Task( void * pvParameters )
 {
		int task1_num = 0;
		for(;;)
		{
				task1_num++;
			  printf("task1_num =%d\n",task1_num);
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
 
 
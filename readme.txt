ƽ̨˵����
	stm32F4 ��ֲfreertos. by heyuan
	
���ļ�¼��
2022-3-10 by heyuan ��̬����������ϰ��
1����ϰxTaskCreate()-������̬����ѿռ䡣
	����ԭ������task.c��
	#if ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ע���Ҫ����Ϊ1
	�����÷���task.h�� ������������˵����
	ע�����ȼ� 0��������ȼ��Ѿ���ϵͳʹ���ˡ������Լ������Ĳ����á�
	

2��vTaskDelete() ɾ������
    �ڱ��������ڿ��Բ�����NULL.vTaskDelete(NULL).
	
3��vTaskStartScheduler();          //�����������

4���ӳٺ���
	vTaskDelay(); 

ע�⣺����ֻ��ϰ��δ��Ӳ�����ܹ���
/*******************************/
2022-3-11 ��̬����������ϰ

1��NVIC_PriorityGroupConfig(NVIC_PriorityGroup4); //����ϵͳ�ж����ȼ�����Ϊ4
2��taskENTER_CRITICAL(); //�����ٽ���
   taskEXIT_CRITICAL(); //�˳��ٽ���
3��  TaskHandle_t xTaskCreateStatic( TaskFunction_t pxTaskCode,/*������*/
                                    const char * const pcName, /*��������*/
                                    const uint32_t ulStackDepth,/*�����ջ��С*/
                                    void * const pvParameters,/*��������Ĳ���*/
                                    UBaseType_t uxPriority,/*�������ȼ�*/
                                    StackType_t * const puxStackBuffer, /*�����ջ��ַ*/
                                    StaticTask_t * const pxTaskBuffer ) /*������ƿ�*/  
   
TaskHandle_t /*������*/
4��
�����꣺configSUPPORT_STATIC_ALLOCATION == 1

5��   
���û��������º�����   
vApplicationGetIdleTaskMemory (referred from tasks.o).	 /*��������*/
vApplicationGetTimerTaskMemory (referred from timers.o). /*��ʱ������*/
/*Idle Task*/
static StackType_t IdleTaskStack[configMINIMAL_STACK_SIZE];
static StaticTask_t  IdleTaskTCB;

/*Timer Task*/
static StackType_t TimerTaskStack[configTIMER_TASK_STACK_DEPTH];
static StaticTask_t  TimerTaskTCB;

/*Idle Task*/
void vApplicationGetIdleTaskMemory( StaticTask_t ** ppxIdleTaskTCBBuffer, StackType_t ** ppxIdleTaskStackBuffer,uint32_t * pulIdleTaskStackSize )
{
	
	* ppxIdleTaskTCBBuffer =&IdleTaskTCB;
	* ppxIdleTaskStackBuffer =IdleTaskStack;
	* pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
}	

/*Timer Task*/
void vApplicationGetTimerTaskMemory( StaticTask_t ** ppxTimerTaskTCBBuffer, StackType_t ** ppxTimerTaskStackBuffer, uint32_t *pulTimerTaskStackSize )
{
	* ppxTimerTaskTCBBuffer = &TimerTaskTCB;
	* ppxTimerTaskStackBuffer = TimerTaskStack;
	* pulTimerTaskStackSize =configTIMER_TASK_STACK_DEPTH;
}

/*******************************/
2022-3-14 by heyuan �������ͻָ�API

1���������
#if ( INCLUDE_vTaskSuspend == 1 )

	 void vTaskSuspend( TaskHandle_t xTaskToSuspend )


2������ָ�

#if ( INCLUDE_vTaskSuspend == 1 )

    void vTaskResume( TaskHandle_t xTaskToResume )

3���ж��лָ�����
#if ( ( INCLUDE_xTaskResumeFromISR == 1 ) && ( INCLUDE_vTaskSuspend == 1 ) )

    BaseType_t xTaskResumeFromISR( TaskHandle_t xTaskToResume )
	xTaskResumeFromISR return == pdTRUE ��ִ��portYIELD_FROM_ISR
4���л��������
	portYIELD_FROM_ISR( x ) 

/*�������̣�
*����4������start_task��key_task��task1_task��task2_task
*start_task:���ڴ�������3������
*key_task:�����������񣬼�ⰴ���İ��½�������ݲ�ͬ�İ������ִ�в�ͬ�Ĳ���
*task1_task:Ӧ������1
*task2_task:Ӧ������2
*�ĸ�������KEY0��KEY1��KEY2��KEY_UP�����ĸ������Ĺ������� 
*KEY0���˰���Ϊ�ж�ģʽ�����жϷ������лָ�����2�����С�
*KEY1:�˰���Ϊ����ģʽ�����ڻָ�����1�����С�
*KEY2:�˰���Ϊ����ģʽ�����ڹ�������2�����С�
*KEY_UP:�˰���Ϊ����ģʽ�����ڹ�������1�����С�
*/

1��key.c key.h


	
ƽ̨˵����
	stm32F4 ��ֲfreertos.
	
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
2022-3-11 by heyuan ��̬����������ϰ

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





	
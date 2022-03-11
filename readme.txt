平台说明：
	stm32F4 移植freertos.
	
更改记录：
2022-3-10 by heyuan 动态创建任务练习。
1、练习xTaskCreate()-》任务动态分配堆空间。
	函数原代码在task.c中
	#if ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) 注意宏要设置为1
	函数用法在task.h中 函数声明中有说明。
	注意优先级 0和最大优先级已经被系统使用了。我们自己创建的不能用。
	

2、vTaskDelete() 删除任务。
    在本任务函数内可以参数填NULL.vTaskDelete(NULL).
	
3、vTaskStartScheduler();          //开启任务调度

4、延迟函数
	vTaskDelay(); 

注意：例程只练习，未在硬件上跑过。
/*******************************/
2022-3-11 by heyuan 静态创建任务练习

1、NVIC_PriorityGroupConfig(NVIC_PriorityGroup4); //设置系统中断优先级分组为4
2、taskENTER_CRITICAL(); //进入临界区
   taskEXIT_CRITICAL(); //退出临界区
3、  TaskHandle_t xTaskCreateStatic( TaskFunction_t pxTaskCode,/*任务函数*/
                                    const char * const pcName, /*任务名称*/
                                    const uint32_t ulStackDepth,/*任务堆栈大小*/
                                    void * const pvParameters,/*传入任务的参数*/
                                    UBaseType_t uxPriority,/*任务优先级*/
                                    StackType_t * const puxStackBuffer, /*任务堆栈地址*/
                                    StaticTask_t * const pxTaskBuffer ) /*任务控制块*/  
   
TaskHandle_t /*任务句柄*/
4、
声明宏：configSUPPORT_STATIC_ALLOCATION == 1

5、   
需用户完善以下函数：   
vApplicationGetIdleTaskMemory (referred from tasks.o).	 /*空闲任务*/
vApplicationGetTimerTaskMemory (referred from timers.o). /*定时器服务*/
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





	
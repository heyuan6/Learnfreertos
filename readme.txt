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
   


	
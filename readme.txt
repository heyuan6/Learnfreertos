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
   


	
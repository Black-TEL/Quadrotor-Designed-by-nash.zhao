#include "include.h"
#include "Driver.h"
#include "../HARDWARE/TIMER/timer.h"
extern struct ParameterStruct Par;
extern struct SysStruct Sys;
void QuadrotorInit(){
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(180);
	OLED_Init();
	OLED_P8x16Str(0,0,(uint8_t*)"SystemIniting...");
	LED_GPIO_Config();
	Buzzer();
	KEY_Init();
	TeleControlInit();
	digitalToggle(GPIOD,GPIO_Pin_12);
	uart_init(115200);//��ʼ�����ڲ�����Ϊ115200
  /*��ʼ��SDRAMģ��*/
  SDRAM_Init();
	delay_ms(2000);
	MPU6050_Initialize();    
	getOffset();
	/*MotorInit*/
	TIM9_OC1_PWM_Init(5000-1,90-1);
	TIM9_OC2_PWM_Init(5000-1,90-1);
	TIM2_OC3_PWM_Init(2500-1,90-1);
	TIM2_OC4_PWM_Init(2500-1,90-1);
	Sys.MotorDuty[0]=0;
	Sys.MotorDuty[1]=0;
	Sys.MotorDuty[2]=0;
	Sys.MotorDuty[3]=0;
	UpdateDuty(Sys.MotorDuty);
	Init_Quaternion();
	OLED_Fill(0);
}


void LED_GPIO_Config(void)
{		
	
		/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
		GPIO_InitTypeDef GPIO_InitStructure;

		/*����LED��ص�GPIO����ʱ��*/
		RCC_AHB1PeriphClockCmd ( RCC_AHB1Periph_GPIOD, ENABLE); 

		/*ѡ��Ҫ���Ƶ�GPIO����*/															   
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;	 

		/*��������ģʽΪ���ģʽ*/
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;   
    
    /*�������ŵ��������Ϊ�������*/
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    
    /*��������Ϊ����ģʽ��Ĭ��LED��*/
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;

		/*������������Ϊ50MHz */   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; 

		/*���ÿ⺯����ʹ���������õ�GPIO_InitStructure��ʼ��GPIO*/
		GPIO_Init(GPIOD, &GPIO_InitStructure);	
    GPIO_ResetBits(GPIOD,GPIO_Pin_12);
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;	 //������
		GPIO_Init(GPIOD, &GPIO_InitStructure);	
		GPIO_SetBits(GPIOD,GPIO_Pin_11);
/******************************************/
		/*����LED��ص�GPIO����ʱ��*/
		RCC_AHB1PeriphClockCmd ( RCC_AHB1Periph_GPIOI|RCC_AHB1Periph_GPIOH, ENABLE); 

		/*ѡ��Ҫ���Ƶ�GPIO����*/															   
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;	 

		/*��������ģʽΪ���ģʽ*/
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;   
    
    /*�������ŵ��������Ϊ�������*/
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    
    /*��������Ϊ����ģʽ��Ĭ��LED��*/
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;

		/*������������Ϊ50MHz */   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; 
				GPIO_Init(GPIOI, &GPIO_InitStructure);	

		GPIO_SetBits(GPIOI,GPIO_Pin_6);
		GPIO_SetBits(GPIOI,GPIO_Pin_7);
		GPIO_SetBits(GPIOI,GPIO_Pin_8);
		GPIO_SetBits(GPIOI,GPIO_Pin_9);
//		GPIO_SetBits(GPIOI,GPIO_Pin_10);
//		GPIO_SetBits(GPIOI,GPIO_Pin_11);
		GPIO_SetBits(GPIOI,GPIO_Pin_4);
		GPIO_SetBits(GPIOI,GPIO_Pin_5);
			RCC_AHB1PeriphClockCmd ( RCC_AHB1Periph_GPIOH, ENABLE); 

		/*ѡ��Ҫ���Ƶ�GPIO����*/															   
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;	 

		/*��������ģʽΪ���ģʽ*/
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;   
    
    /*�������ŵ��������Ϊ�������*/
    GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
    
    /*��������Ϊ����ģʽ��Ĭ��LED��*/
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;

		/*������������Ϊ50MHz */   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; 
				GPIO_Init(GPIOH, &GPIO_InitStructure);	
				GPIO_SetBits(GPIOH,GPIO_Pin_14);

}
/*
	u16 a,b,c,d,e=0;
	a=0;
	b=0;
	c=0;
	d=0;
	 int16_t aacx,aacy,aacz;		//���ٶȴ�����ԭʼ����
	short gyrox,gyroy,gyroz;	//������ԭʼ����
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);  //��ʼ����ʱ����
	uart_init(115200);//��ʼ�����ڲ�����Ϊ115200
 	//TIM14_PWM_Init(500-1,84-1);	//84M/84=1Mhz�ļ���Ƶ��,��װ��ֵ500������PWMƵ��Ϊ 1M/2500=400hz. 
		TIM9_OC1_PWM_Init(5000-1,90-1);
		TIM9_OC2_PWM_Init(5000-1,90-1);
		TIM2_OC3_PWM_Init(2500-1,90-1);
		TIM2_OC4_PWM_Init(2500-1,90-1);
		
		OLED_GPIO_Init();
		OLEDInit();
		//OLED_Display_On();
		OLEDClear();
		KEY_Init();
		MPU_Init();
		TIM_SetCompare1(TIM9,a);	//�޸ıȽ�ֵ���޸�ռ�ձ�
		TIM_SetCompare2(TIM9,b);	//�޸ıȽ�ֵ���޸�ռ�ձ�
		TIM_SetCompare3(TIM2,c);	//�޸ıȽ�ֵ���޸�ռ�ձ�
		TIM_SetCompare4(TIM2,d);	//�޸ıȽ�ֵ���޸�ռ�ձ� 
   while(1) //ʵ�ֱ Ƚ�ֵ��0-300��������300���300-0�ݼ���ѭ��
	{ 
		//KEY_Scan();
		//KEY_Scan1();
		delay_ms(100);
		OLEDShowNum(0,0,e,16,16);
		e++;
		MPU_Get_Accelerometer(&aacx,&aacy,&aacz);	//�õ����ٶȴ���������
		MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz);	//�õ�����������
		OLEDShowNum(0,2,(int)aacx,16,16);
		OLEDShowNum(0,4,(int)gyrox,16,16);
		USART_SendData(USART1,e);         //�򴮿�1��������
	}
	*/


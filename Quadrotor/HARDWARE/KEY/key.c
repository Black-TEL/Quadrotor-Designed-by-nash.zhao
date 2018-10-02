#include "key.h"
#include "delay.h" 
#include "include.h"
extern struct SysStruct Sys;
extern struct ParameterStruct Par;
extern struct FlagStruct Flag;
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F407������
//����������������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/5/3
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	 

//������ʼ������
u16 a,b,c,d;
void KEY_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; 
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	/*��������GPIO�ڵ�ʱ��*/
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOC|RCC_AHB1Periph_GPIOH,ENABLE);
	
  /*ѡ�񰴼�������*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; 
  
  /*��������Ϊ����ģʽ*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN; 
  
  /*�������Ų�����Ҳ������*/
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	
  /*ʹ������Ľṹ���ʼ������*/
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//ʹ��SYSCFGʱ��
	
 
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0);//PA0 ���ӵ��ж���0
	
  /* ����EXTI_Line0 */
  EXTI_InitStructure.EXTI_Line = EXTI_Line0;//LINE0
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising; //�����ش��� 
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;//ʹ��LINE0
  EXTI_Init(&EXTI_InitStructure);//����
	
 
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;//�ⲿ�ж�0
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x03;//��ռ���ȼ�0
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;//�����ȼ�2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
  NVIC_Init(&NVIC_InitStructure);//����
/**********************************************************/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14; 
	GPIO_Init(GPIOH, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3; 
	GPIO_Init(GPIOI, &GPIO_InitStructure);
//	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOH, EXTI_PinSource9);//PA0 ���ӵ��ж���0
//	EXTI_InitStructure.EXTI_Line = EXTI_Line9;//LINE0
//  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //�����ش��� 
//  EXTI_Init(&EXTI_InitStructure);//����
//	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;//�ⲿ�ж�0
//  NVIC_Init(&NVIC_InitStructure);//����

} 
void TeleControlInit(void){//PC 12345
	GPIO_InitTypeDef GPIO_InitStructure; 
//	EXTI_InitTypeDef EXTI_InitStructure;
//	NVIC_InitTypeDef NVIC_InitStructure;
	/*��������GPIO�ڵ�ʱ��*/
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
	
  /*ѡ�񰴼�������*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5; 
  
  /*��������Ϊ����ģʽ*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN; 
  
  /*�������Ų�����Ҳ������*/
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	
  /*ʹ������Ľṹ���ʼ������*/
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	
	/****************for PA8 VT ***************/

//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8; 
//	GPIO_Init(GPIOA, &GPIO_InitStructure);
//	RCC_APB1PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//ʹ��SYSCFGʱ��
//	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource8);//PA0 ���ӵ��ж���0
//  /* ����EXTI_Line0 */
//  EXTI_InitStructure.EXTI_Line = EXTI_Line8;//LINE0
//  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
//  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising; //�����ش��� 
//  EXTI_InitStructure.EXTI_LineCmd = ENABLE;//ʹ��LINE0
//  EXTI_Init(&EXTI_InitStructure);//����
//	
// 
//	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;//�ⲿ�ж�0
//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x03;//��ռ���ȼ�0
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//�����ȼ�2
//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
//  NVIC_Init(&NVIC_InitStructure);//����
}


















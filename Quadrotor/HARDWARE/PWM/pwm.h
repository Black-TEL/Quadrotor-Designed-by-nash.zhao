#ifndef _TIMER_H
#define _TIMER_H
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F407������
//��ʱ�� ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/6/16
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	

void TIM9_OC1_PWM_Init(u32 arr,u32 psc);				//PE5		APB2
void TIM9_OC2_PWM_Init(u32 arr,u32 psc);				//PE6		APB2
void TIM2_OC3_PWM_Init(u32 arr,u32 psc);				//PA2		APB1
void TIM2_OC4_PWM_Init(u32 arr,u32 psc);				//PA3		APB1
#endif

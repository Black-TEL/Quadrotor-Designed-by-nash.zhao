#ifndef _IMU_H_
#define _IMU_H_
#include <math.h>
#include "include.h"
#define M_PI  (float)3.1415926535
	
void Init_Quaternion(void);
void IMU_getYawPitchRoll(volatile float * ypr); //������̬
void GetPitchYawGxGyGz(void);
extern int16_t MPU6050_FIFO[6][11];//[0]-[9]Ϊ���10������ [10]Ϊ10�����ݵ�ƽ��ֵ
extern int16_t HMC5883_FIFO[3][11];//[0]-[9]Ϊ���10������ [10]Ϊ10�����ݵ�ƽ��ֵ ע���Ŵ������Ĳ���Ƶ���������Ե����г�
void IMU_getValues(volatile float * values);
extern volatile float angle[3];
extern volatile float yaw_angle,pitch_angle,roll_angle; //ʹ�õ��ĽǶ�ֵ
void IMU_AHRSupdate(void);
void IMU_getQ(volatile float * q);
void Q2Euler(volatile float * q,volatile float * angles);
#endif


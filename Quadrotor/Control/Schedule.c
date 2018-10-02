#include "include.h"
extern struct FlagStruct Flag;
extern struct ParameterStruct Par;
extern volatile float mygetqval[9];	//���ڴ�Ŵ�����ת�����������
extern volatile float q[4]; //����Ԫ��
extern int16_t MPU6050_Lastax,MPU6050_Lastay,MPU6050_Lastaz
				,MPU6050_Lastgx,MPU6050_Lastgy,MPU6050_Lastgz;
int16_t mag[3];
extern uint8_t Send_Count,i;
extern struct SysStruct Sys;
void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET) //����ж�
	{
		Sys.timer++;
		Flag.Flag1Ms++;
		Flag.Flag2Ms++;
		Flag.Flag5Ms++;
		Flag.Flag20Ms++;
		Flag.Flag254Ms++;
		TIM_ClearITPendingBit(TIM3,TIM_IT_Update);  //����жϱ�־λ
		if(Flag.Flag1Ms==1)Task1Ms(),Flag.Flag1Ms=0;
		if(Flag.Flag2Ms==2)Task2Ms(),Flag.Flag2Ms=0;
		if(Flag.Flag5Ms==5)Task5Ms(),Flag.Flag5Ms=0;
		if(Flag.Flag20Ms==20)Task20Ms(),Flag.Flag20Ms=0;
		if(Flag.Flag254Ms==0xff)Task254Ms(),Flag.Flag254Ms=0;
	}
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);  //����жϱ�־λ
}
void Task1Ms(){

}
void Task2Ms(){
	IMU_getValues(mygetqval);	 //��ȡԭʼ����,���ٶȼƺʹ�������ԭʼֵ��������ת������deg/s
	InnerLoopController();
//		Sys.MotorDuty[0]=Par.Thr;
//		Sys.MotorDuty[1]=Par.Thr;
//		Sys.MotorDuty[2]=Par.Thr;
//		Sys.MotorDuty[3]=Par.Thr;
		UpdateDuty(Sys.MotorDuty);
}
void Task5Ms(){
	IMU_getQ(q);
	Q2Euler(q,angle);
	OuterLoopController();
	Flag.FlagSendData=1;
}
void Task20Ms(){
//	Par.uartbuff[2] = (uint16_t)(USART2->DR & (uint16_t)0x01FF);
//	Decoder();
}
void Task254Ms(){
	digitalToggle(GPIOD,GPIO_Pin_12);
}
/*
	Sys.RawAX=mygetqval[0];
	Sys.RawAY=mygetqval[1];
	Sys.RawAZ=mygetqval[2];
	Sys.RawGX=mygetqval[3];
	Sys.RawGY=mygetqval[4];
	Sys.RawGZ=mygetqval[5];
	Sys.RawMX=mygetqval[6];
	Sys.RawMY=mygetqval[7];
	Sys.RawMZ=mygetqval[8];
*/



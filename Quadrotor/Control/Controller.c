#include "include.h"
extern struct SysStruct Sys;
extern struct ParameterStruct Par;
extern struct FlagStruct Flag;
void InnerLoopController(){ //�ڻ� PD ������
		Sys.InnerYaw = Sys.YawS * Par.IP;// + Sys.YawA * Par.ID;
		Sys.InnerPitch = Sys.PitchS * Par.IP + Sys.PitchA * Par.ID;
		Sys.InnerRoll = Sys.RollS * Par.IP + Sys.RollA * Par.ID;	

		/*���⻷�ں� ����� = �ڻ� * Inner2Outer + �⻷ * (1 - Inner2Outer)*/
		Sys.OutputYaw = Par.Inner2Outer/100.0f * (Sys.InnerYaw - Sys.OuterYaw) + Sys.OuterYaw;
		Sys.OutputPitch = Par.Inner2Outer/100.0f * (Sys.InnerPitch - Sys.OuterPitch) + Sys.OuterPitch;
		Sys.OutputRoll = Par.Inner2Outer/100.0f * (Sys.InnerRoll - Sys.OuterRoll) + Sys.OuterRoll;

		/*ypr����޷� ���� ����ռ�ձ� * DutyAvailabe */
		Sys.OutputYaw=LIMIT(Sys.OutputYaw,-DutyAvailable*YawAvailable,DutyAvailable*YawAvailable);
		Sys.OutputPitch=LIMIT(Sys.OutputPitch,-DutyAvailable*PitchAvailabe,DutyAvailable*PitchAvailabe);
		Sys.OutputRoll=LIMIT(Sys.OutputRoll,-DutyAvailable*RollAvailable,DutyAvailable*RollAvailable);
//		Sys.OutputYaw=0;
//		Sys.OutputRoll=0;
		/*ypr�ں���� ����� = ���� + roll + pitch + yaw + ���� */
		Sys.MotorDuty[0]=Par.Thr - Sys.OutputRoll - Sys.OutputPitch + Sys.OutputYaw + Par.IdleThr;
		Sys.MotorDuty[1]=Par.Thr + Sys.OutputRoll - Sys.OutputPitch - Sys.OutputYaw + Par.IdleThr;
		Sys.MotorDuty[2]=Par.Thr + Sys.OutputRoll + Sys.OutputPitch + Sys.OutputYaw + Par.IdleThr;
		Sys.MotorDuty[3]=Par.Thr - Sys.OutputRoll + Sys.OutputPitch - Sys.OutputYaw + Par.IdleThr;
	
		/*������޷�*/
		Sys.MotorDuty[0]=LIMIT(Sys.MotorDuty[0],3300,DutyMAX);
		Sys.MotorDuty[1]=LIMIT(Sys.MotorDuty[1],3300,DutyMAX);
		Sys.MotorDuty[2]=LIMIT(Sys.MotorDuty[2],3300,DutyMAX);
		Sys.MotorDuty[3]=LIMIT(Sys.MotorDuty[3],3300,DutyMAX);
}
void OuterLoopController(){//�⻷ PI ������
		float AngleError[3]={0,0,0};
		/*��Ƕ����*/
		
		AngleError[0]=Sys.Yaw - Par.EY/10.0f;
		AngleError[1]=Sys.Pitch - Par.EP/10.0f;
		AngleError[2]=Sys.Roll - Par.ER/10.0f;
		/*���ַ���*/
		Sys.YawErrInt += AngleError[0] * dt * Par.OI;
		Sys.PitchErrInt += AngleError[1] * dt * Par.OI;
		Sys.RollErrInt += AngleError[2] * dt * Par.OI;
		/*�����޷�*/
		Sys.YawErrInt = LIMIT(Sys.YawErrInt,-YEI,YEI);
		Sys.PitchErrInt = LIMIT(Sys.PitchErrInt,-PEI,PEI);
		Sys.RollErrInt = LIMIT(Sys.RollErrInt,-REI,REI);
		/*��������*/
		Sys.OuterYaw = AngleError[0] * Par.OP;
		Sys.OuterPitch = AngleError[1] * Par.OP;
		Sys.OuterRoll = AngleError[2] * Par.OP;
		/*�⻷��� PI*/
		Sys.OuterYaw += Sys.YawErrInt;
		//Sys.OuterYaw = 0; //��ֹ����ͻ�䣬����Yaw����
		Sys.OuterPitch += Sys.PitchErrInt;
		Sys.OuterRoll += Sys.RollErrInt;	
}
void UpdateDuty(uint16_t motor[]){
	if(Flag.MotorEnable==1){
		TIM_SetCompare1(TIM9,motor[0]);	//�޸ıȽ�ֵ���޸�ռ�ձ�5000
		TIM_SetCompare2(TIM9,motor[1]);	//�޸ıȽ�ֵ���޸�ռ�ձ�5000
		TIM_SetCompare3(TIM2,motor[2]/2);	//�޸ıȽ�ֵ���޸�ռ�ձ�2500
		TIM_SetCompare4(TIM2,motor[3]/2);	//�޸ıȽ�ֵ���޸�ռ�ձ�2500
	}else{
		Sys.MotorDuty[0]=3000;
		Sys.MotorDuty[1]=3000;
		Sys.MotorDuty[2]=3000;
		Sys.MotorDuty[3]=3000;
		TIM_SetCompare1(TIM9,motor[0]);	//�޸ıȽ�ֵ���޸�ռ�ձ�5000 //E5
		TIM_SetCompare2(TIM9,motor[1]);	//�޸ıȽ�ֵ���޸�ռ�ձ�5000//E6 MOTOR3
		TIM_SetCompare3(TIM2,motor[2]/2);	//�޸ıȽ�ֵ���޸�ռ�ձ�2500 //A2
		TIM_SetCompare4(TIM2,motor[3]/2);	//�޸ıȽ�ֵ���޸�ռ�ձ�2500 //A3
	}

}
//void YawOutputSmooth(){//
//  static uint8 cnt=0;
//  static float dValue;
//  cnt++;
//  if(cnt==1)dValue=(Info.turnduty-Info.turndutyLast)/(float),Info.turnduty=Info.turndutyLast;
//  Info.turnduty+=dValue;
//  if(cnt==TurnPeriod)cnt=0,Info.turndutyLast=Info.turnduty;
//}

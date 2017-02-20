#include <Constants.h>
#include "WPILib.h"
#include <VictorSP.h>
/*
 * Climber.cpp
 *
 *  Created on: Feb 3, 2017
 *      Author: Destin
 */

enum ClimberState{
	NotClimbing = 0,
	Climbing = 1,
	Up = 2,
	Nudge = 3,
	Unwind = 4
};

class Climber{
private:
	Joystick* Estick;
	AnalogInput ClimbingLimit;
	Talon ClimbingMotor;
	ClimberState state;
	int ClimbCycles;
public:
	Climber(Joystick* Ejoy):
		Estick(Ejoy),
		ClimbingLimit(CurrentSensor_ID),
		ClimbingMotor(Climbing_Motor_ID),
		state(NotClimbing),
		ClimbCycles(0)
	{
		ClimbingLimit.SetAverageBits(4);
	}

	void TeleOp(){
		Climb();
		setMotors();
		SmartDashboard::PutNumber("ClimbingMotor", ClimbingLimit.GetAverageValue());
	}
	inline void Climb(){
		if(Estick->GetRawButton(ClimberUnwindA_Button_ID) && Estick->GetRawButton(ClimberUnwindB_Button_ID)){
			state = ClimberState::Unwind;
		}else if(Estick->GetRawButton(ClimbNudge_Button_ID) == true){
			state = ClimberState::Nudge;
		}else if(abs(ClimbingLimit.GetAverageValue() - Motor_Offset_Value) >= 150){
			if(ClimbCycles > 10){
				state = ClimberState::Up;
				SmartDashboard::PutString("ClimberState", "Up");
			}
		}else if(state != ClimberState::Up){
			if(Estick->GetRawButton(ClimbStart_Button_ID) == true){
				ClimbCycles++;
				state = ClimberState::Climbing;
				SmartDashboard::PutString("ClimberState", "Climbing");
			}else{
				state = ClimberState::NotClimbing;
				ClimbCycles = 0;
				SmartDashboard::PutString("ClimberState", "NotClimbing");
			}
		}
	}

	inline void setMotors(){
		if(state == ClimberState::Unwind){
			ClimbingMotor.Set(Unwind_Motor_Speed);
		}else if(state == ClimberState::Nudge){
			ClimbingMotor.Set(Nudge_Motor_Speed);
			state = ClimberState::Up;
		}else if(state == ClimberState::Climbing){
			ClimbingMotor.Set(Climbing_Motor_Speed);
		}else if(state == ClimberState::Up){
			ClimbingMotor.Set(0);
		}else if(state == ClimberState::NotClimbing){
			ClimbingMotor.Set(0);
		}
	}
};



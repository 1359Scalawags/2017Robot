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
	Up = 2
};

class Climber{
private:
	Joystick* Estick;
	DigitalInput ClimbingLimit;
	Talon ClimbingMotor;
	ClimberState state;
public:
	Climber(Joystick* Ejoy):
		Estick(Ejoy),
		ClimbingLimit(Climbing_Limit_ID),
		ClimbingMotor(Climbing_Limit_ID),
		state(NotClimbing)
	{

	}

	void TeleOp(){
		Climb();
		setMotors();
	}
	inline void Climb(){
		if((Estick->GetRawButton(ClimbStart_Button_ID) == true) && (ClimbingLimit.Get() == Not_Pressed)){
			state = ClimberState::Climbing;
		}else if(ClimbingLimit.Get() == Pressed){
			state = ClimberState::Up;
		}else{
			state = ClimberState::NotClimbing;
		}
	}

	inline void setMotors(){
		if(state == ClimberState::Climbing){
			ClimbingMotor.Set(Climbing_Motor_Speed);
		}else if(state == ClimberState::Up){
			ClimbingMotor.Set(0);
		}else if(state == ClimberState::NotClimbing){
			ClimbingMotor.Set(0);
		}
	}
};



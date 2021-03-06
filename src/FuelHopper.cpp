#include <Constants.h>
#include "WPILib.h"
#include <VictorSP.h>
/*
 * FuelHopper.cpp
 *
 *  Created on: Feb 3, 2017
 *      Author: Destin
 */

enum PlatformState{
	up = 0,
	down = 1,
	goingUp = 3,
	goingDown = 4

};

class FuelHopper{
private:
	Joystick* Estick;
	DigitalInput PlatformUpLimit;
	DigitalInput PlatformDownLimit;
	Talon PlatformMotor;
public:
	FuelHopper(Joystick* Ejoy):
		Estick(Ejoy),
		PlatformUpLimit(Platform_Up_Limit_ID),
		PlatformDownLimit(Platform_Down_Limit_ID),
		PlatformMotor(Platform_Motor_ID)

	{

	}

	void TeleOp(){
		MovePlatform();
	}

	inline void MovePlatform(){
		if(Estick->GetY() < -0.1 && PlatformDownLimit.Get() == Not_Pressed){
			//PlatformMotor.Set(Estick->GetY() * SpeedMultiplier);
			//PlatformMotor.Set(Relay::kReverse);
			PlatformMotor.Set(Estick->GetY());
		}else if((Estick->GetY() > 0.1 && PlatformUpLimit.Get() == Not_Pressed)){
			//PlatformMotor.Set(Relay::kForward);
			PlatformMotor.Set(Estick->GetY());
		}else{
			//PlatformMotor.Set(0);
			//PlatformMotor.Set(Relay::kOff);
			PlatformMotor.Set(0);
		}
	}

};



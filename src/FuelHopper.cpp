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
	double SpeedMultiplier = .25; //For debuging and testing. Remove for competition.
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
		if((Estick->GetY() < 0 && PlatformDownLimit.Get()) || (Estick->GetY() > 0 && PlatformUpLimit.Get() == Not_Pressed)){
			PlatformMotor.Set(Estick->GetY() * SpeedMultiplier);
		}else{
			PlatformMotor.Set(0);
		}
	}

};



#include <Constants.h>
#include "WPILib.h"
#include <VictorSP.h>
#include <Servo.h>
#include <Joystick.h>
/*
 * GearHandler.cpp
 *
 *  Created on: Feb 3, 2017
 *      Author: Destin
 */


class GearHandler{
private:
	Joystick* Estick;
	Servo DoorControl;


public:
	GearHandler(Joystick* Ejoy):
		Estick(Ejoy),
		DoorControl(Door_Servo_ID)
	{

	}
	void TeleOp(){
		OpenDoors();
	}
	inline void OpenDoors(){
		if(Estick->GetRawButton(Door_Button_ID)){
			if(DoorControl.Get() < .1){
				DoorControl.Set(1);
			}else if(DoorControl.Get() > .9){
				DoorControl.Set(0);
			}
		}else{

		}
	}
};



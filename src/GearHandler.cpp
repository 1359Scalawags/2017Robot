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

enum DoorState{
	open = 0,
	closed = 1,
	opening = 2,
	closing = 3
};

class GearHandler{
private:
	Joystick* Estick;
	Servo DoorControl;
	DoorState state;


public:
	GearHandler(Joystick* Ejoy):
		Estick(Ejoy),
		DoorControl(Door_Servo_ID),
		state(closing)
	{

	}
	void TeleOp(){
		SetServo();
	}
	inline void SetServo(){
		if(state == DoorState::opening){
			if(DoorControl.Get() == Servo_Open){
				state = DoorState::open;
			}else{
				DoorControl.Set(Servo_Open);
			}
		}else if(state == DoorState::closing){
			if(DoorControl.Get() == Servo_Closed){
				state = DoorState::closed;
			}else{
				DoorControl.Set(Servo_Closed);
			}
		}else if(state == DoorState::open){
			if(Estick->GetRawButton(Door_Button_ID)){
				state = DoorState::closing;
			}
		}else if(state == DoorState::closed){
			if(Estick->GetRawButton(Door_Button_ID)){
				state = DoorState::opening;
			}
		}
	}
};



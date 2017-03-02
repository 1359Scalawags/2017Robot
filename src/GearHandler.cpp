#include <Constants.h>
#include "WPILib.h"
#include <VictorSP.h>
#include <Servo.h>
#include <Joystick.h>
#include <GearHandler.h>
/*
 * GearHandler.cpp
 *
 *  Created on: Feb 3, 2017
 *      Author: Destin
 */


	GearHandler::GearHandler(Joystick* Ejoy):
		Estick(Ejoy),
		DoorControl(Door_Servo_ID),
		state(closing)
	{
		DoorControl.Set(Servo_Closed);
	}
	void GearHandler::TeleOp(){
		SetServo();
	}
	inline void GearHandler::SetServo(){
		if(state == DoorState::opening){
			if(DoorControl.Get() == Servo_Open){
				state = DoorState::open;
			}
		}else if(state == DoorState::closing){
			if(DoorControl.Get() == Servo_Closed){
				state = DoorState::closed;
			}
		}else if(state == DoorState::open){
			if(Estick->GetRawButton(DoorClose_Button_ID)){
				state = DoorState::closing;
				DoorControl.Set(Servo_Closed);
			}
		}else if(state == DoorState::closed){
			if(Estick->GetRawButton(DoorOpen_Button_ID)){
				state = DoorState::opening;
				DoorControl.Set(Servo_Open);
			}
		}
	}
	void GearHandler::OpenDoor(){
		DoorControl.Set(Servo_Open);
	}
	void GearHandler::CloseDoor(){
		DoorControl.Set(Servo_Closed);
	}



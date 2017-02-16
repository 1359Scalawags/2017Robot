#include <Constants.h>
#include "WPILib.h"
#include <Drive.h>
#include <GearHandler.h>
#include <Vision.h>
/*
 * Autonomous.cpp
 *
 *  Created on: Feb 12, 2017
 *      Author: Destin
 */

enum StartingPosition{
	Left = 0,
	Middle = 1,
	Right = 2,
};

class Autonomous{

private:

	StartingPosition position;
	float DisFromWall;
	float RotateAngle;
	Drive *drive;
	GearHandler *gear;

public:
	Autonomous(StartingPosition Start_Position, Drive *maindrive, GearHandler *gearhandler):
		position(Start_Position),
		DisFromWall(0),
		RotateAngle(0),
		drive(maindrive),
		gear(gearhandler)
	{
		drive->GyroReset();
		if(position == StartingPosition::Middle){
			//need to move forward 3ft
			DisFromWall = 36;
			RotateAngle = 0;
		}else if(position == StartingPosition::Left){
			//need to move froward 16ft
			DisFromWall = 192;
			RotateAngle = 120;
		}else if(position == StartingPosition::Right){
			//need to move forward 16ft
			DisFromWall = 192;
			RotateAngle = -120;
		}
	}
	void Auton(){

	}
	void DriveForward(){
		if(drive->DriveToDistance(DisFromWall)){
			//go to next phase
		}
	}
	void Rotate(){
		if(drive->TurnToAngle(RotateAngle)){
			//go to next phase
		}
	}
	void TrackPeg(){
		float centerX = Vision::getAverageCenterX();
		float area = Vision::getLargestArea();
		SmartDashboard::PutNumber("CenterX", centerX);
		SmartDashboard::PutNumber("Area", area);
	}
	void PlaceGear(){

	}
};


/*

		int selected = *(chooser.GetSelected());
if(selected == 0){
				SmartDashboard::PutString("AutoSelector", "Left");
				drive.AutonLeft();
			}else if(selected == 1){
				SmartDashboard::PutString("AutoSelector", "Middle");
				drive.AutonMiddle();
			}else if(selected == 2){
				SmartDashboard::PutString("AutoSelector", "Right");
				drive.AutonRight();
			}else if(selected ==3){
				SmartDashboard::PutString("AutoSelector", "Tracking");
				drive.TrackTarget();
			}*/

#include "WPILib.h"
#include <VictorSP.h>
#include <Constants.h>
#include <ADXRS450_Gyro.h>
#include <AutoProgram.cpp>
#include <cmath>
#include <Drive.h>
#include <GearHandler.h>
#include <Climber.cpp>
#include <GripAreaPipeline.h>
#include <Vision.h>
#include <algorithm>
#include <iostream>
#include <ShowStats.cpp>
//#include <FuelHopper.cpp>

// April 01, 2017 - Tim Helland
// Commented out unused code
// Removed commented code not used for an extended period



class Robot: public frc::SampleRobot {

	Drive drive;
	AutoProgram auton;
	Joystick Estick;
//	FuelHopper hopper;
	GearHandler handler;
	Climber climber;
	ShowStats showstats;

	frc::SendableChooser<int*> chooser;
	int left = 0;
	int middle = 1;
	int right = 2;
	int test = 3;

	frc::SendableChooser<int*> AngleChooser;
	int test1 = 0;
	int test2 = 1;
	int test3 = 2;
	int test4 = 3;

	//bool DriveForward;
	//ADXRS450_Gyro Gyro;



public:



	Robot() :
		drive(),
		auton(&drive, &handler),
		Estick(Extra_Joystick_Port),
//		hopper(&Estick),
		handler(&Estick),
		climber(&Estick),
		showstats(&Estick)
		//Gyro()
	{

		//drive.SetExpiration(0.1);

		//Note SmartDashboard is not initialized here, wait until RobotInit to make SmartDashboard calls
		//myRobot.SetExpiration(0.1);

	}


	void RobotInit() {

		std::thread visionThread(Vision::VisionThread);
		visionThread.detach();

		RobotChooser();

		std::cout << " ____________  .________________ \n"
				  <<"/_   \\_____  \\ |   ____/   __   \\\n"
				  <<" |   | _(__  < |____  \\\\____    /\n"
				  <<" |   |/       \\/       \\  /    / \n"
				  <<" |___/______  /______  / /____/  \n"
				  <<"            \\/       \\/          \n";
		std::cout << "  _________             .__                                       \n"
				  <<" /   _____/ ____ _____  |  | _____ __  _  _______     ____  ______\n"
				  <<" \\_____  \\_/ ___\\\\__  \\ |  | \\__  \\\\ \\/ \\/ /\\__  \\   / ___\\/  ___/\n"
				  <<" /        \\  \\___ / __ \\|  |__/ __ \\\\     /  / __ \\_/ /_/  >___ \\ \n"
				  <<"/_______  /\\___  >____  /____(____  /\\/\\_/  (____  /\\___  /____  >\n"
				  <<"        \\/     \\/     \\/          \\/             \\//_____/     \\/ \n";


	}

	void RobotChooser(){
		chooser.AddDefault("Middle", &middle);
		chooser.AddObject("Left", &left);
		chooser.AddObject("Right", &right);
		chooser.AddObject("Test", &test);
		SmartDashboard::PutData("AutonModes", &chooser);


		AngleChooser.AddDefault("Test1", &test1);
		AngleChooser.AddObject("Test2", &test2);
		AngleChooser.AddObject("Test3", &test3);
		AngleChooser.AddObject("Test4", &test4);
		SmartDashboard::PutData("Angle Tester", &AngleChooser);
	}


	void Autonomous() override {
		drive.Safety();
		Vision::SetUseVision(true);
		//RobotChooser();
		int selectFieldPos = *(chooser.GetSelected());
		//keep track of the autonomouse mode
		StartingPosition botposition;
		if(selectFieldPos == 0){
			auton.SetFieldPosition(StartingPosition::Left);
			botposition = StartingPosition::Left;
			std::cout << "Autonomous Mode: LEFT\n";
		}else if(selectFieldPos == 2){
			auton.SetFieldPosition(StartingPosition::Right);
			botposition = StartingPosition::Right;
			std::cout << "Autonomous Mode: RIGHT\n";
		}else{
			auton.SetFieldPosition(StartingPosition::Middle);
			botposition = StartingPosition::Middle;
			std::cout << "Autonomous Mode: MIDDLE\n";
		}
		auton.AutoInit();
		while(IsAutonomous() && IsEnabled()){
			if(botposition == StartingPosition::Left){
				auton.AutonLeft();
			}else if(botposition == StartingPosition::Middle){
				auton.AutonMiddle();
			}else if(botposition == StartingPosition::Right){
				auton.AutonRight();
			}
			showstats.DesplayStats();
			Wait(0.005);  // should this be changed to match teleop timing?
		}
	}



	void OperatorControl() override {
//		mainDrive.SetSafetyEnabled(true);
		Vision::SetUseVision(false);
		drive.Safety();
		drive.InvertDrive(false);
		printf("Tellop Is Enabled");
		std::cout << "Tellop is Enabled\n" << "...\n" << "GO\n";

		while (IsOperatorControl() && IsEnabled()) {

			drive.TeleOp();
			//hopper.TeleOp();
			handler.TeleOp();
			climber.TeleOp();
			showstats.DesplayStats();
			SmartDashboard::PutNumber("Heading to target", Vision::GetHeadingToTarget(drive.PullGyroAngle()));

			frc::Wait(0.05);
		}
	}

	float getJoystickTransform(float input){
		return input;

	}



	void Test() override {
		drive.GyroReset();
		Vision::SetUseVision(true);
/*		//RobotChooser();
		float targetAngle = 0.0f;
		int selectTestAngle = *(AngleChooser.GetSelected());
					if(selectTestAngle == 0){
						targetAngle = 30.0f;
					}else if(selectTestAngle == 1){
						targetAngle = -90.0f;
					}else if(selectTestAngle == 2){
						targetAngle = 150.0f;
					}else if(selectTestAngle ==3){
						targetAngle = 190.0f;
					}*/
		int counter = 0;
		while(IsTest() && IsEnabled()){
			drive.TurnToAngle(Vision::GetHeadingToTarget(drive.PullGyroAngle()));
			if(counter >= 20){
				Vision::ShowVisionStats();
				counter = 0;
			}else{
				counter++;
			}

//			drive.TurnToAngle(targetAngle);
/*			Vision::UpdateSmartDashboard();
			SmartDashboard::PutNumber("Angle to target", Vision::getAproxAngleToTarget());*/
		}
	}
};

START_ROBOT_CLASS(Robot)

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

//Test for Vision Branch


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

	frc::SendableChooser<int*> MiddleDirChooser;
	int midleft = 0;
	int midright = 1;

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

		//CameraServer::GetInstance()->SetSize(CameraServer::kSize320x240);
		//CameraServer::GetInstance()->SetQuality(50);

		//CameraServer::GetInstance()->SetSize(CameraServer::kSize320x240);
		/*CameraServer::GetInstance()->SetSize(CameraServer::kSize640x480);
		CameraServer::GetInstance()->StartAutomaticCapture();*/

		std::thread visionThread(Vision::VisionThread);
		visionThread.detach();

		RobotChooser();
		//drive.DriveInit();


		/*if(fork() == 0){
			SmartDashboard::PutString("forked", "yes");
			system("/home/lvuser/grip &");

		}*/

		/*
		chooser.AddDefault(autoNameDefault, autoNameDefault);
		chooser.AddObject(autoNameCustom, autoNameCustom);
		frc::SmartDashboard::PutData("Auto Modes", &chooser);
		*/

	}

	void RobotChooser(){
		chooser.AddObject("Middle", &middle);
		chooser.AddDefault("Left", &left);
		chooser.AddObject("Right", &right);
		chooser.AddObject("Test", &test);
		SmartDashboard::PutData("AutonModes", &chooser);


		MiddleDirChooser.AddDefault("Middle Left", &midleft);
		MiddleDirChooser.AddObject("Middle Right", &midright);
		SmartDashboard::PutData("Middle Direction", &MiddleDirChooser);


		AngleChooser.AddDefault("Test1", &test1);
		AngleChooser.AddObject("Test2", &test2);
		AngleChooser.AddObject("Test3", &test3);
		AngleChooser.AddObject("Test4", &test4);
		SmartDashboard::PutData("Angle Tester", &AngleChooser);
	}

	/*void RobotInit() {

			//CameraServer::GetInstance()->SetSize(CameraServer::kSize320x240);
			//CameraServer::GetInstance()->SetQuality(50);

			//CameraServer::GetInstance()->SetSize(CameraServer::kSize320x240);
			CameraServer::GetInstance()->SetSize(CameraServer::kSize640x480);
			CameraServer::GetInstance()->StartAutomaticCapture();



			*
			chooser.AddDefault(autoNameDefault, autoNameDefault);
			chooser.AddObject(autoNameCustom, autoNameCustom);
			frc::SmartDashboard::PutData("Auto Modes", &chooser);
			*

		}*/



	void Autonomous() override {
		drive.Safety();
		//RobotChooser();
		int selectFieldPos = *(chooser.GetSelected());
			if(selectFieldPos == 0){
				auton.SetFieldPosition(StartingPosition::Left);
			}else if(selectFieldPos == 1){
				auton.SetFieldPosition(StartingPosition::Middle);
			}else if(selectFieldPos == 2){
				auton.SetFieldPosition(StartingPosition::Right);
			}else if(selectFieldPos ==3){
				auton.SetFieldPosition(StartingPosition::Test);
			}else{

			}
			auton.AutoInit();
		while(IsAutonomous() && IsEnabled()){
			if(StartingPosition::Left){
				auton.AutonLeft();
			}else if(StartingPosition::Middle){
				auton.AutonMiddle();
			}else if(StartingPosition::Right){
				auton.AutonRight();
			}
				auton.Auton();
			Wait(0.005);

		}


	}



	void OperatorControl() override {
//		mainDrive.SetSafetyEnabled(true);
		drive.Safety();
		drive.InvertDrive(false);
		printf("Tellop Is Enabled");
		std::cout << "Tellop is Enabled\n" << "...\n" << "GO\n";
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
		//RobotChooser();
		while (IsOperatorControl() && IsEnabled()) {
			//float angle = Gyro.GetAngle();
			//double angle = (kAnglePoint - Gyro.GetAngle()) * 0.005;

//			setDriveSpeed();
			drive.TeleOp();
			//hopper.TeleOp();
			handler.TeleOp();
			climber.TeleOp();
			showstats.DesplayStats();
			SmartDashboard::PutNumber("Angle to target", Vision::getAproxAngleToTarget());
			//int large_angle = (int)(angle * 1000);
			//angle = (large_angle % 360000) / 1000.0f;
			//SmartDashboard::PutNumber("GYRO", angle);
			frc::Wait(0.05);
		}
	}

	/*
	void setDriveSpeed(){
		float LeftStickValue = .75 * (-getJoystickTransform(Lstick.GetY()));
		float RightStickValue = .75 * (-getJoystickTransform(Rstick.GetY()));

		if(DriveForward==true){
			mainDrive.TankDrive(LeftStickValue, RightStickValue);
		}else{
			mainDrive.TankDrive(-LeftStickValue, -RightStickValue);
		}

	}
*/
	float getJoystickTransform(float input){
		return input;

	}



	void Test() override {
		drive.GyroReset();
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

		while(IsTest() && IsEnabled()){
			drive.GyroReset();
			drive.TurnToAngle(Vision::getAproxAngleToTarget());
//			drive.TurnToAngle(targetAngle);
/*			Vision::UpdateSmartDashboard();
			SmartDashboard::PutNumber("Angle to target", Vision::getAproxAngleToTarget());*/
		}
	}
};

START_ROBOT_CLASS(Robot)

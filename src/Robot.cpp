#include "WPILib.h"
#include <VictorSP.h>
#include <Constants.h>
#include <ADXRS450_Gyro.h>
#include <AutoProgram.cpp>
#include <cmath>
#include <Drive.h>
#include <FuelHopper.cpp>
#include <GearHandler.h>
#include <Climber.cpp>
#include <GripAreaPipeline.h>
#include <Vision.h>





class Robot: public frc::SampleRobot {

	Drive drive;
	AutoProgram auton;
	Joystick Estick;
	FuelHopper hopper;
	GearHandler handler;
	Climber climber;

	frc::SendableChooser<int*> chooser;
	int left = 0;
	int middle = 1;
	int right = 2;
	int test = 3;

	frc::SendableChooser<int*> MiddleDirChooser;
	int midleft = 0;
	int midright = 1;

	//bool DriveForward;
	//ADXRS450_Gyro Gyro;



public:



	Robot() :
		drive(),
		auton(&drive, &handler),
		Estick(Extra_Joystick_Port),
		hopper(&Estick),
		handler(&Estick),
		climber(&Estick)
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

		chooser.AddDefault("Middle", &middle);
		chooser.AddObject("Left", &left);
		chooser.AddObject("Right", &right);
		chooser.AddObject("Test", &test);
		SmartDashboard::PutData("AutonModes", &chooser);

		std::thread visionThread(Vision::VisionThread);
		visionThread.detach();

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
		int selectFieldPos = *(chooser.GetSelected());
			if(selectFieldPos == 0){
				auton.SetFieldPosition(StartingPosition::Left);
			}else if(selectFieldPos == 1){
				auton.SetFieldPosition(StartingPosition::Middle);
			}else if(selectFieldPos == 2){
				auton.SetFieldPosition(StartingPosition::Right);
			}else if(selectFieldPos ==3){
				auton.SetFieldPosition(StartingPosition::Test);
			}
			auton.AutoInit();
		while(IsAutonomous() && IsEnabled()){
				auton.Auton();
			Wait(0.005);

		}


	}



	void OperatorControl() override {
//		mainDrive.SetSafetyEnabled(true);
		drive.Safety();

		while (IsOperatorControl() && IsEnabled()) {
			//float angle = Gyro.GetAngle();
			//double angle = (kAnglePoint - Gyro.GetAngle()) * 0.005;

//			setDriveSpeed();
			drive.TeleOp();
			hopper.TeleOp();
			handler.TeleOp();
			climber.TeleOp();
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

	}
};

START_ROBOT_CLASS(Robot)

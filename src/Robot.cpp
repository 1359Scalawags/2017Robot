#include "WPILib.h"
#include <VictorSP.h>
#include <Constants.h>
#include <ADXRS450_Gyro.h>
#include <cmath>
#include <Drive.cpp>
#include <FuelHopper.cpp>
#include <GearHandler.cpp>
#include <Climber.cpp>

//NOTE: Its ok to delet setSource method in the grip pipline
/**
 * This is a demo program showing the use of the RobotDrive class.
 * The SampleRobot class is the base of a robot application that will
 * automatically call your Autonomous and OperatorControl methods at the right
 * time as controlled by the switches on the driver station or the field
 * controls.
 *
 * WARNING: While it may look like a good choice to use for your code if you're
 * inexperienced, don't. Unless you know what you are doing, complex code will
 * be much more difficult under this system. Use IterativeRobot or Command-Based
 * instead if you're new.
 */


class Robot: public frc::SampleRobot {

	//RobotDrive mainDrive;
	Drive drive;
	//Joystick Lstick;
	//Joystick Rstick;
	Joystick Estick;
	FuelHopper hopper;
	GearHandler handler;
	Climber climber;

	frc::SendableChooser<int*> chooser;
	int left = 0;
	int middle = 1;
	int right = 2;

	//bool DriveForward;
	//ADXRS450_Gyro Gyro;


	/*
	frc::RobotDrive myRobot { 0, 1 }; // robot drive system
	frc::Joystick stick { 0 }; // only joystick
	frc::SendableChooser<std::string> chooser;
	const std::string autoNameDefault = "Default";
	const std::string autoNameCustom = "My Auto";
	*/

public:



	Robot() : //mainDrive(LeftA_Motor_ID, LeftB_Motor_ID, RightA_Motor_ID, RightB_Motor_ID),
		//Lstick(Left_Joystick_Port),
		//Rstick(Right_Joystick_Port),
		//DriveForward(true),
		drive(),
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


		std::thread visionThread(VisionThread);
		visionThread.detach();

		chooser.AddDefault("Middle", &middle);
		chooser.AddObject("Left", &left);
		chooser.AddObject("Right", &right);
		SmartDashboard::PutData("Auton Modes", &chooser);

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

	static void VisionThread(){
		grip::GripAreaPipeline gap;
		cs::UsbCamera camera = CameraServer::GetInstance()->StartAutomaticCapture();
		        camera.SetResolution(320, 240);
		        cs::CvSink cvSink = CameraServer::GetInstance()->GetVideo();
		        cs::CvSource outputStreamStd = CameraServer::GetInstance()->PutVideo("Gray", 640, 480);
		        cv::Mat source;
		        cv::Mat output;
		        while(true) {
		            cvSink.GrabFrame(source);
		            gap.Process(source);
		            //std::vector<std::vector<cv::Point>>* output = gap.GetFilterContoursOutput();
		            //cvtColor(source, output, cv::COLOR_BGR2GRAY);
		            outputStreamStd.PutFrame(*gap.GetHslThresholdOutput());
		        }

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

	/*
	 * This autonomous (along with the chooser code above) shows how to select
	 * between different autonomous modes using the dashboard. The sendable
	 * chooser code works with the Java SmartDashboard. If you prefer the
	 * LabVIEW Dashboard, remove all of the chooser code and uncomment the
	 * GetString line to get the auto name from the text box below the Gyro.
	 *
	 * You can add additional auto modes by adding additional comparisons to the
	 * if-else structure below with additional strings. If using the
	 * SendableChooser make sure to add them to the chooser code above as well.
	 */

	void Autonomous() override {
		drive.Safety();
		drive.AutonStart();
		int selected = *(chooser.GetSelected());
		while(IsAutonomous() && IsEnabled()){
			if(selected == 0){
				SmartDashboard::PutString("Auto Selector", "Left");
				drive.AutonLeft();
			}else if(selected == 1){
				SmartDashboard::PutString("Auto Selector", "Middle");
				drive.AutonMiddle();
			}else if(selected == 2){
				SmartDashboard::PutString("Auto Selector", "Right");
				drive.AutonRight();
			}
			Wait(0.05);
			//drive.Auton();
		}
		/**
		auto autoSelected = chooser.GetSelected();
		// std::string autoSelected = frc::SmartDashboard::GetString("Auto Selector", autoNameDefault);
		std::cout << "Auto selected: " << autoSelected << std::endl;

		if (autoSelected == autoNameCustom) {
			// Custom Auto goes here
			std::cout << "Running custom Autonomous" << std::endl;
			myRobot.SetSafetyEnabled(false);
			myRobot.Drive(-0.5, 1.0); // spin at half speed
			frc::Wait(2.0);                // for 2 seconds
			myRobot.Drive(0.0, 0.0);  // stop robot
		} else {
			// Default Auto goes here
			std::cout << "Running default Autonomous" << std::endl;
			myRobot.SetSafetyEnabled(false);
			myRobot.Drive(-0.5, 0.0); // drive forwards half speed
			frc::Wait(2.0);                // for 2 seconds
			myRobot.Drive(0.0, 0.0);  // stop robot
		}
		**/

	}

	/*
	 * Runs the motors with arcade steering.
	 */

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

	/*
	 * Runs during test mode
	 */

	void Test() override {

	}
};

START_ROBOT_CLASS(Robot)

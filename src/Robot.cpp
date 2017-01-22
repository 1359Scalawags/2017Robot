#include "WPILib.h"
#include <VictorSP.h>
#include <Constants.h>
#include <ADXRS450_Gyro.h>

//hi...can you read me! testing
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

	RobotDrive mainDrive;

	Joystick Lstick;
	Joystick Rstick;
	//Joystick Estick;

	bool DriveForward;
	ADXRS450_Gyro Gyro;

	/**
	frc::RobotDrive myRobot { 0, 1 }; // robot drive system
	frc::Joystick stick { 0 }; // only joystick
	frc::SendableChooser<std::string> chooser;
	const std::string autoNameDefault = "Default";
	const std::string autoNameCustom = "My Auto";
	**/

public:
	Robot() : mainDrive(LeftA_Motor_ID, LeftB_Motor_ID, RightA_Motor_ID, RightB_Motor_ID),
		Lstick(Left_Joystick_Port),
		Rstick(Right_Joystick_Port),
		//Estick(Extra_Joystick_Port),
		DriveForward(true),
		Gyro()
	{

		mainDrive.SetExpiration(0.1);

		//Note SmartDashboard is not initialized here, wait until RobotInit to make SmartDashboard calls
		//myRobot.SetExpiration(0.1);

	}


	void RobotInit() {

		CameraServer::GetInstance()->StartAutomaticCapture();

		/**
		chooser.AddDefault(autoNameDefault, autoNameDefault);
		chooser.AddObject(autoNameCustom, autoNameCustom);
		frc::SmartDashboard::PutData("Auto Modes", &chooser);
		**/

	}


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

	void Autonomous() {

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
		mainDrive.SetSafetyEnabled(true);
		Gyro.Reset();

		while (IsOperatorControl() && IsEnabled()) {
			float angle = Gyro.GetAngle();
			setDriveSpeed();
			SmartDashboard::PutNumber("DB/Slider 0", angle * 5.0f / 360.0f);

			frc::Wait(0.005);
		}
	}

	void setDriveSpeed(){
		float LeftStickValue = .75 * (-getJoystickTransform(Lstick.GetY()));
		float RightStickValue = .75 * (-getJoystickTransform(Rstick.GetY()));

		if(DriveForward==true){
			mainDrive.TankDrive(LeftStickValue, RightStickValue);
		}else{
			mainDrive.TankDrive(-LeftStickValue, -RightStickValue);
		}

	}

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

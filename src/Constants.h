/*
 * Constants.h
 *
 *  Created on: Jan 14, 2017
 *      Author: Destin
 */

#ifndef SRC_CONSTANTS_H_
#define SRC_CONSTANTS_H_

const char LeftA_Motor_ID = 0;
const char LeftB_Motor_ID = 1;
const char RightA_Motor_ID = 2;
const char RightB_Motor_ID = 3;

const char Platform_Motor_ID = 4;
const char Climbing_Motor_ID = 5;

const int Climbing_Motor_Speed = -1.0f;
const char Nudge_Motor_Speed = -0.4f;

const char Door_Servo_ID = 9;


const char Left_Joystick_Port = 0;
const char Right_Joystick_Port = 1;
const char Extra_Joystick_Port = 2;

static constexpr char kAnglePoint = 0.0;
static const char ROTATE_TOLERANCE = 0.5f;
static const char STRAIT_TOLERANCE = 0.5f;

const int CENTER_X = 160;
const char TOLERANCE_X = 10;

const char Platform_Up_Limit_ID = 2;
const char Platform_Down_Limit_ID = 1;
const char Climbing_Limit_ID = 0;

const char ClimbStart_Button_ID = 1;
const char DoorOpen_Button_ID = 3;
const char DoorClose_Button_ID = 2;
const char ClimbNudge_Button_ID = 6;
const char DriveForward_Button_ID = 3;
const char DriveBackward_Button_ID = 2;

const char SonarLeft_ID = 0;
const char SonarRight_ID = 1;
const char CurrentSensor_ID = 3;

const char Servo_Open = 0.0f;
const char Servo_Closed = 1.0f;

const char AVERAGE_WEIGHT = 5;

const bool Pressed = false;
const bool Not_Pressed = true;
const float Motor_Stall_Current = 99999.9f;



#endif /* SRC_CONSTANTS_H_ */

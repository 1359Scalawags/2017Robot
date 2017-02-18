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
const int RightA_Motor_ID = 2;
const int RightB_Motor_ID = 3;

const int Platform_Motor_ID = 4;
const int Climbing_Motor_ID = 5;

const float Climbing_Motor_Speed = -0.8f;
const float Nudge_Motor_Speed = -0.4f;

const int Door_Servo_ID = 9;


const int Left_Joystick_Port = 0;
const int Right_Joystick_Port = 1;
const int Extra_Joystick_Port = 2;

static constexpr double kAnglePoint = 0.0;
static const float ROTATE_TOLERANCE = 0.5f;
static const float STRAIT_TOLERANCE = 0.5f;

const int CENTER_X = 160;
const int TOLERANCE_X = 10;

const int Platform_Up_Limit_ID = 2;
const int Platform_Down_Limit_ID = 1;
const int Climbing_Limit_ID = 0;

const int ClimbStart_Button_ID = 1;
const int DoorOpen_Button_ID = 3;
const int DoorClose_Button_ID = 2;
const int ClimbNudge_Button_ID = 6;
const int DriveForward_Button_ID = 3;
const int DriveBackward_Button_ID = 2;

const int SonarLeft_ID = 0;
const int SonarRight_ID = 1;
const int CurrentSensor_ID = 3;

const float Servo_Open = 0.0f;
const float Servo_Closed = 1.0f;

const float AVERAGE_WEIGHT = 5;

const bool Pressed = false;
const bool Not_Pressed = true;
const float Motor_Stall_Current = 5000.0f;



#endif /* SRC_CONSTANTS_H_ */

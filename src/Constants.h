/*
 * Constants.h
 *
 *  Created on: Jan 14, 2017
 *      Author: Destin
 */

#ifndef SRC_CONSTANTS_H_
#define SRC_CONSTANTS_H_

const int LeftA_Motor_ID = 0;
const int LeftB_Motor_ID = 1;
const int RightA_Motor_ID = 2;
const int RightB_Motor_ID = 3;

const int Platform_Motor_ID = 4;
const int Climbing_Motor_ID = 5;

const int Climbing_Motor_Speed = 0.75;

const int Door_Servo_ID = 0;


const int Left_Joystick_Port = 0;
const int Right_Joystick_Port = 1;
const int Extra_Joystick_Port = 2;

static constexpr double kAnglePoint = 0.0;

const int CENTER_X = 160;
const int TOLERANCE_X = 10;

const int Platform_Up_Limit_ID = 999;
const int Platform_Down_Limit_ID = 998;
const int Climbing_Limit_ID = 997;

const int ClimbStart_Button_ID = 0;
const int ClimbStop_Button_ID = 1;
const int Door_Button_ID = 2;

const bool Pressed = false;
const bool Not_Pressed = true;




#endif /* SRC_CONSTANTS_H_ */

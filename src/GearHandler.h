/*
 * GearHandler.h
 *
 *  Created on: Feb 13, 2017
 *      Author: Destin
 */

#ifndef SRC_GEARHANDLER_H_
#define SRC_GEARHANDLER_H_


#include <Constants.h>
#include "WPILib.h"
#include <VictorSP.h>
#include <Servo.h>
#include <Joystick.h>
/*
 * GearHandler.cpp
 *
 *  Created on: Feb 3, 2017
 *      Author: Destin
 */

enum DoorState{
	open = 0,
	closed = 1,
	opening = 2,
	closing = 3
};

class GearHandler{
private:
	Joystick* Estick;
	Servo DoorControl;
	DoorState state;


public:
	GearHandler(Joystick* Ejoy);
	void TeleOp();
	inline void SetServo();
};





#endif /* SRC_GEARHANDLER_H_ */

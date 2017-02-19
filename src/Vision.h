/*
 * Vision.h
 *
 *  Created on: Feb 15, 2017
 *      Author: Destin
 */

#ifndef SRC_VISION_H_
#define SRC_VISION_H_

#include "WPILib.h"
#include <VictorSP.h>
#include <Constants.h>
#include <cmath>
#include <GripAreaPipeline.h>
#include <Vision.h>
/*
 * Vision.cpp
 *
 *  Created on: Feb 13, 2017
 *      Author: Destin
 */



class Vision{
	private:

	public:
	Vision();
	static void VisionThread();
	static void VisionTargets();
	static float getLargestArea();
	static float getAverageCenterX();
	static int GetTargetNumber();
	static void UpdateSmartDashboard();
};

#endif /* SRC_VISION_H_ */

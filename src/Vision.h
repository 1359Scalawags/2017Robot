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
	static float getAverageCenterX();
	static void VisionTargets();
	static float getLargestArea();
	public:
	Vision();
	static void VisionThread();
	static int GetTargetNumber();
	static void UpdateSmartDashboard();
	static float GetAproxamatAngle(int target_center_x, int target_width);
	static float getAproxAngleToTarget();
	static void ShowVisionStats();
};

#endif /* SRC_VISION_H_ */

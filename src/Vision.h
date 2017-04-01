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
	static float GetAproxamatAngle(int target_center_x, int target_width);
	static float getAproxAngleToTarget();
	public:
	Vision();
	static void VisionThread();
	static int GetTargetNumber();
	static void SetUseVision(bool setvision);
	static void UpdateSmartDashboard();
	static float GetHeadingToTarget(float currentHeading);
	static void ShowVisionStats();
	static float GetDistanceFromTarget();
};

#endif /* SRC_VISION_H_ */

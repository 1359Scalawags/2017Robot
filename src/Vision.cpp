#include "WPILib.h"
#include <VictorSP.h>
#include <Constants.h>
#include <cmath>
#include <GripAreaPipeline.h>
/*
 * Vision.cpp
 *
 *  Created on: Feb 13, 2017
 *      Author: Destin
 */

static std::vector<std::vector<cv::Point>>* ContourOutput;

class Vision{
	private:

	public:

	static void VisionThread(){
			grip::GripAreaPipeline gap;
			cs::UsbCamera camera = CameraServer::GetInstance()->StartAutomaticCapture();
			        camera.SetResolution(640, 480);
			        cs::CvSink cvSink = CameraServer::GetInstance()->GetVideo();
			        cs::CvSource outputStreamStd = CameraServer::GetInstance()->PutVideo("Gray", 640, 480);
			        cv::Mat source;
			        cv::Mat output;
			        while(true) {
			            cvSink.GrabFrame(source);
			            gap.Process(source);
			            ContourOutput = gap.GetFilterContoursOutput();

			            //cvtColor(source, output, cv::COLOR_BGR2GRAY);
			            //outputStreamStd.PutFrame(*gap.GetHslThresholdOutput());
			            Wait(0.03);
			        }

		}
};

/*SmartDashboard::PutNumber("VisionThreadContourSize", ContourOutput->size());
			SmartDashboard::PutNumber("TargetCenter:", drive.GetTargetCenterX(*ContourOutput[0].data()));*/

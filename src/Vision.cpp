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
static std::vector<std::vector<cv::Point>>* ContourOutput;
	static float average_centerx = 0.0f;
	static float largest_area = 0.0f;
	static int target_count = 0;
	Vision::Vision(){

	}
	void Vision::VisionThread(){
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
			            VisionTargets();
			            //cvtColor(source, output, cv::COLOR_BGR2GRAY);
			            //outputStreamStd.PutFrame(*gap.GetHslThresholdOutput());
			            Wait(0.03);
			        }

		}
	void Vision::VisionTargets(){
		float sum_centerx = 0.0f;
		target_count = 0;
		for(std::vector<cv::Point> con : *ContourOutput){
			largest_area = std::max(largest_area, (float)cv::contourArea(con));
			cv::Rect rect = cv::boundingRect(con);
			average_centerx += sum_centerx + rect.x + rect.width /2;
			target_count++;
		}
		average_centerx = sum_centerx / target_count;
	}
	float Vision::getLargestArea(){
		return largest_area;
	}
	float Vision::getAverageCenterX(){
		return average_centerx;
	}
	int Vision::GetTargetNumber(){
		return target_count;
	}
	void Vision::UpdateSmartDashboard(){
		SmartDashboard::PutNumber("Largest Target", largest_area);
		SmartDashboard::PutNumber("Average Center Of Targets", average_centerx);
		SmartDashboard::PutNumber("Number Of Targets", target_count);
	}

/*SmartDashboard::PutNumber("VisionThreadContourSize", ContourOutput->size());
			SmartDashboard::PutNumber("TargetCenter:", drive.GetTargetCenterX(*ContourOutput[0].data()));*/

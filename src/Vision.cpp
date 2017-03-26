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
#define PI 3.14159265
#define DOGEARDROP

static std::vector<std::vector<cv::Point>> ContourOutput;
	static float average_centerx = 0.0f;
	static float largest_area = 0.0f;
	static int target_count = 0;
	static float largest_width = 0.0f;
	static float aproxamat_angle_to_target;
	static float distance_from_target;
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
			            if(source.empty()){
			            	continue;
			            }else{
			            	gap.Process(source);
			            	ContourOutput = gap.GetFilterContoursOutput();
#ifdef DOGEARDROP
			            	if(!ContourOutput.empty()){
			            	VisionTargets();
			            	}
#endif
			            }

			            //cvtColor(source, output, cv::COLOR_BGR2GRAY);
			            //outputStreamStd.PutFrame(*gap.GetHslThresholdOutput());
			            Wait(0.05);
			        }

		}

	float Vision::GetAproxamatAngle(int target_center_x, int target_width){
		if(target_width != 0){
			distance_from_target = 1280.0f / target_width;
			float center_to_target = distance_from_target * (target_center_x - VisionCenterX) / VisionResolutionX;
			return atan2(center_to_target, distance_from_target) * 180.0f / PI;
		}else{
			return 0.0f;
		}
	}

	void Vision::VisionTargets(){
		float sum_centerx = 0.0f;
		target_count = ContourOutput.size();
		largest_area = 0.0f;
		largest_width = 0.0f;

		for(std::vector<cv::Point> con : ContourOutput){
			largest_area = std::max(largest_area, (float)cv::contourArea(con));
			cv::Rect rect = cv::boundingRect(con);
			largest_width = std::max(largest_width, (float)rect.width);
			sum_centerx = sum_centerx + rect.x + rect.width /2.0f;
		}

		if(target_count > 0){
			average_centerx = sum_centerx / target_count;
			aproxamat_angle_to_target = GetAproxamatAngle(average_centerx, largest_width);
		}else{
			aproxamat_angle_to_target = 0.0f;
		}
	}
	float Vision::GetDistanceFromTarget(){
		return std::min(distance_from_target, 1280.0f);

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
	float Vision::getAproxAngleToTarget(){
		return aproxamat_angle_to_target;
	}
	void Vision::UpdateSmartDashboard(){
		SmartDashboard::PutNumber("Largest Target", largest_area);
		SmartDashboard::PutNumber("Average Center Of Targets", average_centerx);
		SmartDashboard::PutNumber("Number Of Targets", target_count);
	}

	void Vision::ShowVisionStats(){
		std::cout << "--------------------------------------------\n";
		std::cout << "Vision Info:\n";
		std::cout << "Average Center X: " << average_centerx << "\n";
		std::cout << "Largest Area: " << largest_area << "\n";
		std::cout << "Target Count: " << target_count << "\n";
		std::cout << "Largest Width: " << largest_width << "\n";
		std::cout << "Aprox Angle To Target: " << aproxamat_angle_to_target << "\n";
	}

/*SmartDashboard::PutNumber("VisionThreadContourSize", ContourOutput->size());
			SmartDashboard::PutNumber("TargetCenter:", drive.GetTargetCenterX(*ContourOutput[0].data()));*/

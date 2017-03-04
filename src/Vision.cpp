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

static std::vector<std::vector<cv::Point>>* ContourOutput;
	static float average_centerx = 0.0f;
	static float largest_area = 0.0f;
	static int target_count = 0;
	static float largest_width = 0.0f;
	static float aproxamat_angle_to_target;
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
			            	VisionTargets();
#endif
			            }

			            //cvtColor(source, output, cv::COLOR_BGR2GRAY);
			            //outputStreamStd.PutFrame(*gap.GetHslThresholdOutput());
			            Wait(0.03);
			        }

		}

	float Vision::GetAproxamatAngle(int target_center_x, int target_width){
		if(target_width != 0){
			float distance_from_target = 1280.0f / target_width;
			float center_to_target = distance_from_target * (target_center_x - 320) / 640;
			return atan2(center_to_target, distance_from_target) * 180.0f / PI;
		}else{
			return 0.0f;
		}
	}

	void Vision::VisionTargets(){
		float sum_centerx = 0.0f;
		target_count = 0;
		largest_area = 0.0f;
		largest_width = 0.0f;

		for(std::vector<cv::Point> con : *ContourOutput){
			largest_area = std::max(largest_area, (float)cv::contourArea(con));
			cv::Rect rect = cv::boundingRect(con);
			largest_width = std::max(largest_width, (float)rect.width);
			average_centerx += sum_centerx + rect.x + rect.width /2;
			target_count++;
		}
		average_centerx = sum_centerx / target_count;

		if(target_count > 0){
			aproxamat_angle_to_target = GetAproxamatAngle(average_centerx, largest_width);
		}else{
			aproxamat_angle_to_target = 0.0f;
		}
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

/*SmartDashboard::PutNumber("VisionThreadContourSize", ContourOutput->size());
			SmartDashboard::PutNumber("TargetCenter:", drive.GetTargetCenterX(*ContourOutput[0].data()));*/

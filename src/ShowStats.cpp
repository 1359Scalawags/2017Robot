#include <Constants.h>
#include "WPILib.h"
#include <VictorSP.h>
#include <iostream>
#include <Vision.h>
/*
 * ShowStats.cpp
 *
 *  Created on: Mar 25, 2017
 *      Author: Destin
 */

class ShowStats{
	private:
		Joystick* Estick;
		int showstatscountdown = 20;
		bool periodiclyenable = false;
		int SSPbuttoncooldown = 20;
		bool canpressSSP = true;
	public:
		ShowStats(Joystick* Ejoy):
			Estick(Ejoy)
		{

		}

		void DesplayStats(){
			if(Estick->GetRawButton(ShowStats_Button_ID)){
				std::cout << "--------------------------------------------\n";
				std::cout << "Stats:\n";
				Vision::ShowVisionStats();
			}
			if(Estick->GetRawButton(ShowStatsPeriodicly_Button_ID) && canpressSSP){
				periodiclyenable = true;
				canpressSSP = false;
			}
			if(periodiclyenable == true){
				showstatscountdown--;
				if(showstatscountdown < 0){
					Vision::ShowVisionStats();
					showstatscountdown = 20;
				}
			}
			if(canpressSSP == false){
				SSPbuttoncooldown--;
				if(SSPbuttoncooldown < 0){
					canpressSSP = true;
					SSPbuttoncooldown = 20;
				}
			}
		}

};



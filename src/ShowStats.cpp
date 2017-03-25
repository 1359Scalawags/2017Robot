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
		}

};



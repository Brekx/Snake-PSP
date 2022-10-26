#pragma once

#include <pspdebug.h>
#include <pspdisplay.h>

#include <Point.hpp>

char CUSTOM_DEBUG_INFO[100] = "None";
class DebugInfo {
	public:
		
		bool print;
		Point analog = Point(0, 0);
		float framerate;
		DebugInfo() {
			print = false;
			pspDebugScreenInit();
		}
		void displayInfo() {
			if(!print)
				return;
			pspDebugScreenSetXY(0, 2);
			pspDebugScreenPrintf("Analog %f|%f\nFPS: %f\t counted: %f\n%s", analog.x, analog.y, sceDisplayGetFramePerSec(), framerate, CUSTOM_DEBUG_INFO);
		}
};
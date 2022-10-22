#pragma once

#include <pspdebug.h>
#include <pspdisplay.h>

#include <Point.hpp>

class DebugInfo {
	public:
		bool print;
		Point analog = Point(0, 0);
		DebugInfo() {
			print = false;
			pspDebugScreenInit();
		}
		void displayInfo() {
			if(!print)
				return;
			pspDebugScreenSetXY(0, 2);
			pspDebugScreenPrintf("Analog %f|%f\nFPS: %f", analog.x, analog.y, sceDisplayGetFramePerSec());
		}
};
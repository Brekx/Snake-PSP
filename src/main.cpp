#include <pspkernel.h>
#include <pspdisplay.h>
#include <pspctrl.h>
#include <pspsystimer.h>
#include <cstdio>

#include "callbacks.h"
#include "graphic.hpp"
#include "DebugInfo.hpp"
#include "Snake.hpp"

PSP_MODULE_INFO("Cube Sample", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | PSP_THREAD_ATTR_VFPU);

int main(int argc, char* argv[])
{
	setupCallbacks();
	Graphic g;
	SceCtrlData pad;
	DebugInfo d;
	unsigned int padbuffer;

	Snake s;
	
	g.init();
	sceCtrlSetSamplingCycle(0);
	sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);
	
	while(running())
	{
		sceCtrlReadBufferPositive(&pad, 1);
		d.analog = Point(pad.Lx, pad.Ly);
		d.framerate = g.getFramerate();

		if((pad.Buttons & PSP_CTRL_SELECT) && !(padbuffer & PSP_CTRL_SELECT)){
			d.print = !d.print;
		}

		s.respond(pad, g.getFramerate());

		g.beginDraw();
		s.draw(&g);
		g.endDraw();

		d.displayInfo();
		padbuffer = pad.Buttons;
	}
	g.terminate();
	sceKernelExitGame();
	return 0;
}

#include <pspkernel.h>
#include <pspdisplay.h>
#include <pspctrl.h>
#include <pspsystimer.h>
#include <cstdio>

#include "callbacks.h"
#include "graphic.hpp"
#include "DebugInfo.hpp"
#include "Snake.hpp"
#include "Apple.hpp"

PSP_MODULE_INFO("Snake", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | PSP_THREAD_ATTR_VFPU);

int main(int argc, char* argv[])
{
	setupCallbacks();
	Graphic g;
	SceCtrlData pad;
	DebugInfo d;
	unsigned int padbuffer;

	Snake s;
	Apple a = Apple(Point(10, 10), 20);
	
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
		a.respond(g.getFramerate());

		if(a.do_collide(s.get_head()))
			a.eat();
		g.beginDraw();
		a.draw(&g);
		s.draw(&g);
		g.endDraw();

		d.displayInfo();
		padbuffer = pad.Buttons;
	}
	g.terminate();
	sceKernelExitGame();
	return 0;
}

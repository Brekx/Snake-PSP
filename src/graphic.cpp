#include <pspdisplay.h>
#include <pspgu.h>
#include <pspgum.h>
#include <time.h>
#include <psprtc.h>

#include "graphic.hpp"
#include "vram.h"
#include "Vertex.hpp"

static unsigned int __attribute__((aligned(16))) list[262144];
extern unsigned char texture_start[];
static void* tex_vram;

void Graphic::init() {
	void* fbp0 = getStaticVramBuffer(BUF_WIDTH,SCR_HEIGHT,GU_PSM_8888);
	void* fbp1 = getStaticVramBuffer(BUF_WIDTH,SCR_HEIGHT,GU_PSM_8888);
	void* zbp = getStaticVramBuffer(BUF_WIDTH,SCR_HEIGHT,GU_PSM_4444);

	sceGuInit();

	//Set up buffers
	sceGuStart(GU_DIRECT, list);
	sceGuDrawBuffer(GU_PSM_8888,fbp0,BUF_WIDTH);
	sceGuDispBuffer(SCR_WIDTH,SCR_HEIGHT,fbp1,BUF_WIDTH);
	sceGuDepthBuffer(zbp,BUF_WIDTH);

	//Set up viewport
	sceGuOffset(2048 - (SCR_WIDTH / 2), 2048 - (SCR_HEIGHT / 2));
	sceGuViewport(2048, 2048, SCR_WIDTH, SCR_HEIGHT);
	sceGuEnable(GU_SCISSOR_TEST);
	sceGuScissor(0, 0, SCR_WIDTH, SCR_HEIGHT);

	//Set some stuff
	sceGuDepthRange(65535, 0); //Use the full buffer for depth testing - buffer is reversed order

	sceGuDepthFunc(GU_GEQUAL); //Depth buffer is reversed, so GEQUAL instead of LEQUAL
	sceGuEnable(GU_DEPTH_TEST); //Enable depth testing
	// sceGuEnable(GU_ALPHA_TEST);
	sceGuEnable(GU_BLEND);
	sceGuBlendFunc(GU_ADD, GU_SRC_ALPHA, GU_ONE_MINUS_SRC_ALPHA, 0, 0);	
	sceGuEnable(GU_TEXTURE_2D);

	tex_vram = getStaticVramTexture(256, 256, GU_PSM_8888);
	sceGuCopyImage(GU_PSM_8888, 0, 0, 256, 256, 256, texture_start, 0, 0, 256, tex_vram);
	sceGuTexSync();

	sceGuFinish();
	sceGuDisplay(GU_TRUE);
	sceRtcGetCurrentTick(&clock);
}

void Graphic::beginDraw() {
	sceGuStart(GU_DIRECT, list);
	sceGuClearColor(0xFFFFFFFF); // White background
	sceGuClear(GU_COLOR_BUFFER_BIT);
	sceGuTexMode(GU_PSM_8888,0,0,0);
	sceGuTexImage(0,256,256,256,tex_vram);
	sceGuTexFunc(GU_TFX_REPLACE,GU_TCC_RGBA);
	sceGuTexEnvColor(0xffff00);
	sceGuTexFilter(GU_LINEAR, GU_NEAREST);
	sceGuTexScale(1.0f,1.0f);
	sceGuTexOffset(0.0f,0.0f);
	sceGuAmbientColor(0xFFFFFFFF);
}

void Graphic::endDraw() {
	sceGuFinish();
	sceGuSync(0, 0);
	sceDisplayWaitVblankStart();
	sceGuSwapBuffers();
	u64 tmp = clock;
	sceRtcGetCurrentTick(&clock);
	framerate = (float)sceRtcGetTickResolution()/(clock-tmp);
}

void Graphic::drawImageFromTex(Rectangle location, Rectangle tex_location) {
	Vertex* vertices = (Vertex*)sceGuGetMemory(4 * sizeof(Vertex));

	vertices[0].x = location.p1.x;
	vertices[0].y = location.p1.y;
	vertices[0].z = 0;
	vertices[0].a = tex_location.p1.x;
	vertices[0].v = tex_location.p1.y;

	vertices[1].x = location.p2.x;
	vertices[1].y = location.p2.y;
	vertices[1].z = 0;
	vertices[1].a = tex_location.p2.x;
	vertices[1].v = tex_location.p2.y;

	vertices[2].x = location.p3.x;
	vertices[2].y = location.p3.y;
	vertices[2].z = 0;
	vertices[2].a = tex_location.p3.x;
	vertices[2].v = tex_location.p3.y;

	vertices[3].x = location.p4.x;
	vertices[3].y = location.p4.y;
	vertices[3].z = 0;
	vertices[3].a = tex_location.p4.x;
	vertices[3].v = tex_location.p4.y;

	sceGuColor(0xFF00000); // Red, colors are ABGR
	sceGuDrawArray(GU_TRIANGLE_FAN, GU_TEXTURE_32BITF|GU_VERTEX_32BITF | GU_TRANSFORM_2D, 4, 0, vertices);
}

void Graphic::drawRectangle(Rectangle rectangle, unsigned int color) {
	Vertex* vertices = (Vertex*)sceGuGetMemory(4 * sizeof(Vertex));
	//FIXME - This memmory usage seems quite bad as we allocate space but never free it

	vertices[0].x = rectangle.p1.x;
	vertices[0].y = rectangle.p1.y;
	vertices[0].z = 0;
	vertices[0].a = 0;
	vertices[0].v = 0;

	vertices[1].x = rectangle.p2.x;
	vertices[1].y = rectangle.p2.y;
	vertices[1].z = 0;
	vertices[1].a = 0;
	vertices[1].v = 0;

	vertices[2].x = rectangle.p3.x;
	vertices[2].y = rectangle.p3.y;
	vertices[2].z = 0;
	vertices[2].a = 0;
	vertices[2].v = 0;

	vertices[3].x = rectangle.p4.x;
	vertices[3].y = rectangle.p4.y;
	vertices[3].z = 0;
	vertices[3].a = 0;
	vertices[3].v = 0;
	sceGuTexFunc(GU_TFX_ADD, GU_TCC_RGB);
	sceGuColor(color);
	sceGuDrawArray(GU_TRIANGLE_FAN, GU_TEXTURE_32BITF|GU_VERTEX_32BITF | GU_TRANSFORM_2D, 4, 0, vertices);
	sceGuTexFunc(GU_TFX_REPLACE, GU_TCC_RGBA);
}

void Graphic::drawPolygon(Point *point, int count, unsigned int color) {
	// Vertex *verticies = (Vertex*) sceGuGetMemory(count*sizeof(Vertex));
	// for(int i=0; i<count; i++) {
	// 	verticies[i].x = point.x;
	// 	verticies[i].y = point.x;

	// }
}

void Graphic::terminate() {
	sceGuTerm();
}

float Graphic::getFramerate() {
	return framerate;
}

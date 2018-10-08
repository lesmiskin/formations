#ifndef HUD_H
#define HUD_H

#include "common.h"


extern int fps;
extern void initHud();
extern void writeText(int, Coord, bool);
extern void writeFont(char*, Coord, bool);
extern void hudRenderFrame();
extern void hudGameFrame();
extern void hudAnimFrame();

#endif

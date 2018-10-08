#ifndef HUD_H
#define HUD_H

#include "common.h"


extern int fps;
extern void initHud();
extern void writeText(int amount, Coord pos);
extern void writeFont(char *text, Coord pos);
extern void hudRenderFrame();
extern void hudGameFrame();
extern void hudAnimFrame();

#endif

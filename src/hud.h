#ifndef HUD_H
#define HUD_H

#include "common.h"

extern void initHud(void);
extern void writeText(int amount, Coord pos);
extern void writeFont(char *text, Coord pos);
extern void hudRenderFrame(void);
extern void hudGameFrame(void);
extern void hudAnimFrame(void);

#endif

#ifndef PLAYER_H
#define PLAYER_H

#include "common.h"

extern void playerGameFrame(void);
extern void playerRenderFrame(void);
extern void playerShadowFrame(void);
extern void initPlayer();
extern void setFormation(int);
extern Coord pos;
extern Coord goals[8];
extern int formation;
extern void playerAnimateFrame(void);
extern double health;

#endif

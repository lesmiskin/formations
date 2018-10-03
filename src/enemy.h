#ifndef ENEMY_H
#define ENEMY_H

#include "common.h"

typedef struct {
	Coord coord;
	int goal;
	int animInc;
} Enemy;

extern void enemyGameFrame();
extern void enemyRenderFrame();
extern void initEnemy();
extern void enemyAnimateFrame();
extern void spawnEnemy(Coord coord);
extern bool showHomingLines;

#endif

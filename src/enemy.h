#ifndef ENEMY_H
#define ENEMY_H

#include "common.h"

typedef struct {
	Coord coord;
	int goal;
	int animInc;
	bool isRoaming;
	Dir roamDir;
	long lastRoamTime;
} Enemy;

extern const double ENEMY_SPEED;
extern const double CHAR_BOUNDS;
extern const int IDLE_HZ;

extern void enemyGameFrame();
extern void enemyRenderFrame();
extern void initEnemy();
extern void enemyAnimateFrame();
extern void spawnEnemy();
extern bool showHomingLines;

#endif

#ifndef ENEMY_H
#define ENEMY_H

#include "common.h"

#define MAX_ENEMY 0

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

extern Enemy enemies[MAX_ENEMY];

extern void enemyGameFrame();
extern void enemyRenderFrame();
extern void initEnemy();
extern void enemyAnimateFrame();
extern void spawnEnemy(int);
extern bool showHomingLines;

#endif

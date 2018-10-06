#ifndef ENEMY_H
#define ENEMY_H

#include "common.h"
#include "npc.h"

#define MAX_ENEMY 15

extern const double ENEMY_SPEED;
extern const double CHAR_BOUNDS;

extern Npc enemies[MAX_ENEMY];

extern void enemyGameFrame();
extern void enemyRenderFrame();
extern void initEnemy();
extern void enemyAnimateFrame();
extern void spawnEnemy(int);
extern bool showHomingLines;

#endif

#ifndef ENEMY_H
#define ENEMY_H

#include "common.h"
#include "npc.h"

#define MAX_ENEMY 15

typedef struct {
  int power;
  int size;
  int speed;
} EnemyAttributes;

extern Npc enemies[MAX_ENEMY];

extern void enemyGameFrame();
extern void enemyRenderFrame();
extern void initEnemy();
extern void enemyAnimateFrame();
extern void spawnEnemy(int);
extern bool showHomingLines;

#endif

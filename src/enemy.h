#ifndef ENEMY_H
#define ENEMY_H

#include "common.h"

#define MAX_ENEMY 50

typedef enum {
	NPC_ENEMY,
	NPC_SQUAD
} NpcType;

typedef struct {
	Coord coord;
	NpcType type;
	int goal;
	int animInc;
	bool isRoaming;
	double roamDir;
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
extern Enemy* makeEnemy__leaks();
extern bool showHomingLines;

extern bool npcInBounds(Enemy*, Rect);
extern bool npcCollidesWith(Enemy*, Enemy*);

#endif

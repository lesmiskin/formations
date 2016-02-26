#ifndef ENEMY_H
#define ENEMY_H

#include "common.h"

#define MAX_SHOTS 50

typedef struct {
    Coord coord;
    Coord target;
    double angle;
} Shot;

typedef enum {
	ENEMY_CTHULU,
	ENEMY_DIGGER,
	ENEMY_WOLFMAN,
	ENEMY_DRACULA,
} EnemyType;

extern void enemyGameFrame(void);
extern void enemyRenderFrame(void);
extern void initEnemy(void);
extern void enemyAnimateFrame(void);
extern void spawnEnemy(EnemyType type, Coord coord);
extern Shot shots[MAX_SHOTS];

#endif

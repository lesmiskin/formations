#include "enemy.h"
#include "player.h"
#include "renderer.h"
#include "assets.h"
#include "time.h"
#include "hud.h"

typedef enum {
	TYPE_DIGGER,
	TYPE_WEREWOLF,
} EnemyType;

typedef struct {
	Coord coord;
	int animInc;
	EnemyType type;
} Enemy;

#define MAX_ENEMY 12
#define WALK_ANIMS 4	//We play each frame twice.
Enemy enemies[MAX_ENEMY];

const double ENEMY_SPEED = 0.3;

bool onScreen(Coord coord, double threshold) {
	return inBounds(coord, makeRect(
			0 + threshold,
			0 + threshold,
			screenBounds.x - (threshold),
			screenBounds.y - (threshold)
	));
}

void enemyGameFrame(void) {
	for(int i=0; i < MAX_ENEMY; i++) {
		if(enemies[i].coord.x == 0) continue;

		//Move around.
		Coord homeStep = getStep(enemies[i].coord, pos, ENEMY_SPEED, true);
		enemies[i].coord.x += homeStep.x;
		enemies[i].coord.y += homeStep.y;
	}
}

void enemyAnimateFrame(void) {
	//Animate the enemies
	for(int i=0; i < MAX_ENEMY; i++) {
		if(enemies[i].coord.x == 0) continue;

		//Increment animations.
		if(enemies[i].animInc < 4) {
			enemies[i].animInc++;
		}else{
			enemies[i].animInc = 0;
		}
	}
}

void enemyRenderFrame(void){
	//Draw the enemies with the right animation frame.
	for(int i=0; i < MAX_ENEMY; i++) {
		if(enemies[i].coord.x == 0) continue;

		Sprite sprite;

		//Ugh... Time constraints!
		switch(enemies[i].type) {
			case TYPE_WEREWOLF:
				sprite = makeSimpleSprite("werewolf-walk-01.png");
				break;
			case TYPE_DIGGER:
				sprite = makeSimpleSprite("digger-dig-01.png");
				break;
		}

		drawSprite(sprite, enemies[i].coord);
	}
}

void initEnemy(void) {
	//Make the enemies
	for(int i=0; i < 6; i++) {
		Coord c = makeCoord(
			randomMq(75, 320),
			randomMq(75, 240)
		);

		Enemy enemy = {
			c,
			0,
			(EnemyType)randomMq(0, sizeof(EnemyType))
		};

		enemies[i] = enemy;
	}

	memset(enemies, 0, sizeof(enemies));
}

#include "enemy.h"
#include "player.h"
#include "renderer.h"
#include "assets.h"
#include "time.h"
#include "hud.h"

typedef enum {
	TYPE_CTHULU,
	TYPE_DIGGER,
	TYPE_WEREWOLF,
	TYPE_DRACULA,
} EnemyType;

typedef struct {
	Coord coord;
	int animInc;
	EnemyType type;
} Enemy;

#define MAX_ENEMY 12
#define WALK_FRAMES 4
Enemy enemies[MAX_ENEMY];
long lastIdleTime;
const int IDLE_HZ = 1000 / 2;

const double ENEMY_SPEED = 0.015;

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
		enemies[i].coord.x -= homeStep.x;
		enemies[i].coord.y -= homeStep.y;
	}
}

void enemyAnimateFrame(void) {
	if(!timer(&lastIdleTime, IDLE_HZ)) return;

	//Animate the enemies
	for(int i=0; i < MAX_ENEMY; i++) {
		if(enemies[i].coord.x == 0) continue;

		//Increment animations.
		if(enemies[i].animInc < 4) {
			enemies[i].animInc++;
		}else{
			enemies[i].animInc = 1;
		}
	}
}

void enemyRenderFrame(void){
	//Draw the enemies with the right animation frame.
	for(int i=0; i < MAX_ENEMY; i++) {
		if(enemies[i].coord.x == 0) continue;

		Sprite sprite;
		SDL_RendererFlip flip = enemies[i].coord.x > pos.x ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

		char *frameFile[25];

		//Ugh... Time constraints!
		switch(enemies[i].type) {
			case TYPE_WEREWOLF: {
				strcpy(frameFile, "werewolf-walk-%02d.png");
				break;
			}
			case TYPE_DIGGER: {
				strcpy(frameFile, "digger-walk-%02d.png");
				break;
			}
			case TYPE_CTHULU: {
				strcpy(frameFile, "cthulu-walk-%02d.png");
				break;
			}
			case TYPE_DRACULA: {
				strcpy(frameFile, "dracula-walk-%02d.png");
				break;
			}
		}

		sprintf(frameFile, frameFile, enemies[i].animInc);
		sprite = makeFlippedSprite(frameFile, flip);
		drawSprite(sprite, enemies[i].coord);
	}
}

void initEnemy(void) {
	//Make the enemies
	for(int i=0; i < 6; i++) {
		Coord c = makeCoord(
			randomMq(0, screenBounds.x),
			randomMq(0, screenBounds.y)
		);

		Enemy enemy = {
			c,
			1,
			randomMq(0, sizeof(EnemyType)-1)
		};

		enemies[i] = enemy;
	}
}

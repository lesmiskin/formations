#include "enemy.h"
#include "player.h"
#include "renderer.h"
#include "assets.h"
#include "time.h"
#include "hud.h"

typedef struct {
	Coord coord;
	int animInc;
	EnemyType type;
} Enemy;

#define MAX_ENEMY 50
#define WALK_FRAMES 4
Enemy enemies[MAX_ENEMY];
long lastIdleTime;
int enemyCount = 0;
const int IDLE_HZ = 1000 / 5;
const int INITIAL_ENEMIES = 5;

const double ENEMY_SPEED = 1;

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
	}
}

void enemyAnimateFrame(void) {
	if(!timer(&lastIdleTime, IDLE_HZ)) return;

	//Animate the enemies
	for(int i=0; i < MAX_ENEMY; i++) {
		if(enemies[i].coord.x == 0) continue;

		//Slight hack - we want to move the enemies in sync with their animation.
		Coord homeStep = getStep(enemies[i].coord, pos, ENEMY_SPEED, true);
		enemies[i].coord.x -= homeStep.x;
		enemies[i].coord.y -= homeStep.y;

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

		char frameFile[25];

		//Ugh... Time constraints!
		switch(enemies[i].type) {
			case ENEMY_WOLFMAN: {
				strcpy(frameFile, "werewolf-walk-%02d.png");
				break;
			}
			case ENEMY_DIGGER: {
				strcpy(frameFile, "digger-walk-%02d.png");
				break;
			}
			case ENEMY_CTHULU: {
				strcpy(frameFile, "cthulu-walk-%02d.png");
				break;
			}
			case ENEMY_DRACULA: {
				strcpy(frameFile, "dracula-walk-%02d.png");
				break;
			}
		}

		sprintf(frameFile, frameFile, enemies[i].animInc);
		sprite = makeFlippedSprite(frameFile, flip);
		drawSprite(sprite, enemies[i].coord);
	}
}

void spawnEnemy(EnemyType type, Coord coord) {
	if(enemyCount == MAX_ENEMY) return;

	Enemy e = {
		coord,
		1,
		type
	};
	enemies[enemyCount++] = e;
}

void initEnemy(void) {
	//Make the enemies
	for(int i=0; i < INITIAL_ENEMIES; i++) {
		spawnEnemy(
			(EnemyType)randomMq(0, ENEMY_DRACULA),
			makeCoord(
				randomMq(0, screenBounds.x),
				randomMq(0, screenBounds.y)
			)
		);
	}
}

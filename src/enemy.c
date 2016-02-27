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
	int id;
} Enemy;

//Attack function for player: Single animation, hits in direction of facing, enemy health reduces.
//Enemies vanish with health is zero.
//Enemies attack player with single frame, player health reduces.
//Player vanishes when health is zero.
//Enemy collision detection.

#define MAX_ENEMY 50
#define WALK_FRAMES 4
Enemy enemies[MAX_ENEMY];
long lastIdleTime;
int enemyCount = 0;
const int INITIAL_ENEMIES = 5;
const int IDLE_HZ = 1000 / 4;
const double ENEMY_SPEED = 0.075;

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

		Coord homeStep = getStep(enemies[i].coord, pos, ENEMY_SPEED, true);
		Coord target = deriveCoord(enemies[i].coord, -homeStep.x, -homeStep.y);
		bool skipMove = false;

		//Loop through all enemies (plus player), and see if we would collide.
		for(int j=-1; j < MAX_ENEMY; j++) {
			/* Hack: Swap out player pos if -1, then go onto the enemies. This
			 * lets us easily use the same detection code for both character
			 * types, although this could also be a method...) */
			Coord compare = j == -1 ? pos : enemies[j].coord;

			//Don't collide with ourselves :p
			if(j > -1 && enemies[i].id == enemies[j].id) continue;

			//If our new target would put us next to an enemy, stop moving.
			if(inBounds(target, makeSquareBounds(compare, 15))) {
				double distI = calcDistance(enemies[i].coord, pos);
				double distJ = calcDistance(compare, pos);

				//If we're further away than the colliding enemy, stop him.
				if(distI > distJ) {
					skipMove = true;
					break;
				}
			}
		}

		if(!skipMove) {
			enemies[i].coord = target;
		}
	}
}

void enemyAnimateFrame(void) {
	if(!timer(&lastIdleTime, IDLE_HZ)) return;

	//Animate the enemies
	for(int i=0; i < MAX_ENEMY; i++) {
		if(enemies[i].coord.x == 0) continue;

		//Slight hack - we want to move the enemies in sync with their animation.

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
		type,
		enemyCount
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

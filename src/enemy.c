#include "enemy.h"
#include "player.h"
#include "renderer.h"
#include "assets.h"
#include "time.h"
#include "hud.h"

#define MAX_ENEMY 8
#define WALK_FRAMES 4
Enemy enemies[MAX_ENEMY];
long lastIdleTime;
int enemyCount = 0;
const int INITIAL_ENEMIES = 50;
const int IDLE_HZ = 1000 / 4;
const double ENEMY_SPEED = 0.5;
const double CHAR_BOUNDS = 15;
const double DIR_CHANGE = 250;
bool showHomingLines = false;

bool onScreen(Coord coord, double threshold) {
	return inBounds(coord, makeRect(
			0 + threshold,
			0 + threshold,
			screenBounds.x - (threshold),
			screenBounds.y - (threshold)
	));
}

bool wouldTouchEnemy(Coord a, int selfIndex, bool includePlayer) {
	//Check player
	if(includePlayer) {
		if(inBounds(a, makeSquareBounds(plr->pos, CHAR_BOUNDS))) {
			return true;
		}
	}

	//Check enemies.
	for(int i=0; i < MAX_ENEMY; i++) {
		if(selfIndex != i && inBounds(a, makeSquareBounds(enemies[i].coord, CHAR_BOUNDS))) {
			return true;
		}
	}

	return false;
}

// typedef struct {
// 	double d;
// 	int i, j;
// } Glp;

void enemyGameFrame(void) {
	bool ts[8];
	memset(ts, true, sizeof(ts));

	// // greatest least path first
	// bool es[MAX_ENEMY];
	// memset(es, true, sizeof(es));
	// for(int k=0; k<MAX_ENEMY; k++) {
	// 	Glp glp = {0, -1, -1};
		double ds[MAX_ENEMY][8];
		for(int i=0;i<MAX_ENEMY;i++) {
	// 		if(es[i] != true) { continue; }
	// 		int d0 = enemies[i].goal == -1 ? 999999 : calcDistance(goals[enemies[i].goal],enemies[i].coord);
	// 		int j0 = -1;
			for(int j=0;j<8;j++) {
	// 			if(ts[j] != true) { continue; }
				ds[i][j] = calcDistance(plr->goals[j],enemies[i].coord);
	// 			if(ds[i][j] < d0) {
	// 				d0 = ds[i][j];
	// 				j0 = j;
	// 			}
			}
	// 		if(d0 > glp.d) {
	// 			glp.d = d0;
	// 			glp.i = i;
	// 			glp.j = j0;
	// 		}
		}
	// 	ts[glp.j] = false;
	// 	es[glp.i] = false;
	// 	enemies[glp.i].goal = glp.j;
	// }

	for(int i=0; i < MAX_ENEMY; i++) {
		// greedy with shortcut
		int j0;
		float d0 = 999999;
		for(int j=0; j < 8; j++) {
			if(ts[j] != true) { continue; } // shortcut already taken goals
			if(ds[i][j] < d0) {
				d0 = ds[i][j];
				j0 = j;
			}
		}
		ts[j0] = false;
		enemies[i].goal = j0;

		// home towards your goal
		Coord step = getStep(enemies[i].coord, plr->goals[enemies[i].goal], ENEMY_SPEED);
		Coord heading = deriveCoord(enemies[i].coord, step.x, step.y);

		//Loop through all enemies (plus player), and see if we would collide.
		for(int j=-1; j < MAX_ENEMY; j++) {
			//Player check.
			Coord compare = j == -1 ? plr->pos : enemies[j].coord;

			//Don't collide with ourselves
			if(j > -1 && i == j) continue;

			//Our heading will put us in the bounds of an enemy. Decide what to do.
			if(inBounds(heading, makeSquareBounds(compare, CHAR_BOUNDS))) {
				// TODO: what do!?
			}
		}
		enemies[i].coord = heading;
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
		} else {
			enemies[i].animInc = 1;
		}
	}
}

void enemyRenderFrame(void){
	//Draw the enemies with the right animation frame.
	for(int i=0; i < MAX_ENEMY; i++) {
		if(enemies[i].coord.x == 0) continue;

		Sprite sprite;
		SDL_RendererFlip flip = SDL_FLIP_NONE;
		bool isUp = false;
		bool isDown = false;

		isUp = enemies[i].coord.y > plr->pos.y;
		isDown = enemies[i].coord.y < plr->pos.y;

		char frameFile[25];

		// Choose graphic based on type.
		if(isUp) {
			strcpy(frameFile, "werewolf-walk-up-%02d.png");
		} else if(isDown) {
			strcpy(frameFile, "werewolf-walk-down-%02d.png");
		} else{
			strcpy(frameFile, "werewolf-walk-%02d.png");
			flip = enemies[i].coord.x > plr->pos.x ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
		}

		// Draw line showing where the enemy is homing to.
		if(showHomingLines){
			drawLine(0,128,0, enemies[i].coord, plr->goals[enemies[i].goal]);
		}

		sprintf(frameFile, frameFile, enemies[i].animInc);
		sprite = makeFlippedSprite(frameFile, flip);
		drawSprite(sprite, enemies[i].coord);
	}
}

void spawnEnemy(Coord coord) {
	if(enemyCount == MAX_ENEMY) return;

	Enemy e = {
		coord,
		-1,
		randomMq(1,4)
	};
	enemies[enemyCount++] = e;
}

void initEnemy(void) {
	//Make the enemies
	for(int i=0; i < INITIAL_ENEMIES; i++) {
		spawnEnemy(
			makeCoord(
				randomMq(0, screenBounds.x),
				randomMq(0, screenBounds.y)
			)
		);
	}
}

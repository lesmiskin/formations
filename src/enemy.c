#include <assert.h>
#include "enemy.h"
#include "common.h"
#include "npc.h"
#include "player.h"
#include "renderer.h"
#include "assets.h"
#include "time.h"
#include "hud.h"
#include "scene.h"

#define WALK_FRAMES 4

Npc *enemies;

static long lastIdleTime;
const double DIR_CHANGE = 1000;
bool showHomingLines = false;

void enemyGameFrame(void) {
	for(int i=0; i<MAX_ENEMY; i++) {
			Coord heading;
			bool skipMove = false;

			//Turn off roaming if enough time has elapsed.
			if(enemies[i].isRoaming && timer(&enemies[i].lastRoamTime, DIR_CHANGE))
				enemies[i].isRoaming = false;

			Coord step;
			//If we're roaming - head in that direction.
			if(enemies[i].isRoaming) {
				step = makeStep(enemies[i].roamDir, ((EnemyAttributes*)enemies[i].attr)->speed);
				Coord goal = makeStep(enemies[i].roamDir, ((EnemyAttributes*)enemies[i].attr)->speed*10);
				enemies[i].goal = deriveCoord(enemies[i].pos->origin, goal.x, goal.y);
			}
			//Otherwise - home towards player.
			else {
				step = getStep(enemies[i].pos->origin, plr->pos->origin, ((EnemyAttributes*)enemies[i].attr)->speed);
				enemies[i].goal = plr->pos->origin;
			}
			heading = deriveCoord(enemies[i].pos->origin, step.x, step.y);

			// if you would collide with player, respawn
			if(rectInBounds(makeSquareBounds(heading,((EnemyAttributes*)enemies[i].attr)->size), makeSquareBounds(plr->pos->origin, PC_BOUNDS))) {
				plr->health -= 1;
				// if(plr->health == 0) quit();
				spawnEnemy(i);
				break;
			}

			// if you would collide with a squad member try to push instead of moving
			for(int j=0; j<plr->squad->size; j++) {
				if(npcInBounds(&plr->squad->members[j],makeSquareBounds(heading,((EnemyAttributes*)enemies[i].attr)->size))) {
					skipMove = true;
					if(chance(25)) push(&plr->squad->members[j],
															getAngle(enemies[i].pos->origin,plr->squad->members[j].pos->origin),
															((EnemyAttributes*)enemies[i].attr)->power);
					break;
				}
			}
			if(skipMove) continue;

			// roam if we would collide with another enemy
			for(int j=0; j<MAX_ENEMY; j++) {
				if(i == j) continue; //Don't collide with ourselves!
				if(npcInBounds(&enemies[j], makeSquareBounds(heading, ((EnemyAttributes*)enemies[j].attr)->size))) {
					enemies[i].roamDir = degToRad(randomMq(0,360));
					enemies[i].lastRoamTime = clock();
					enemies[i].isRoaming = true;
					skipMove = true;
					break;
				}
			}
			if(skipMove) continue;

			enemies[i].pos->origin = heading;
		}
	}

void enemyAnimateFrame(void) {
	//Animate the enemies
	for(int i=0; i < MAX_ENEMY; i++) {
		if(enemies[i].pos->origin.x == 0) continue;

		//Increment animations.
		if(enemies[i].animInc < 4) {
			enemies[i].animInc++;
		} else {
			enemies[i].animInc = 1;
		}
	}
}

void enemyRenderFrame(){
	//Draw the enemies with the right animation frame.
	for(int i=0; i<MAX_ENEMY; i++) {
		if(enemies[i].pos->origin.x == 0) continue;

		SDL_RendererFlip flip = SDL_FLIP_NONE;
		bool isUp = false;
		bool isDown = false;

		isUp   = enemies[i].pos->origin.y-enemies[i].goal.y > abs(enemies[i].pos->origin.x-enemies[i].goal.x);
		isDown = enemies[i].goal.y-enemies[i].pos->origin.y > abs(enemies[i].pos->origin.x-enemies[i].goal.x);

		char frameFile[28];

		// Choose graphic based on type.
		if(isUp) {
			strcpy(frameFile, "dracula-walk-up-%02d.png");
		} else if(isDown) {
			strcpy(frameFile, "dracula-walk-down-%02d.png");
		} else{
			strcpy(frameFile, "dracula-walk-%02d.png");
			flip = enemies[i].pos->origin.x > enemies[i].goal.x ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
		}

		sprintf(frameFile, frameFile, enemies[i].animInc);
		Sprite *sprite = makeFlippedSprite__leaks(frameFile, flip);
		assert(sprite);
		drawSprite(sprite, enemies[i].pos->origin);
		free(sprite);

		if(showHomingLines){
			drawLine(128,0,0,
				makeCoord(enemies[i].pos->origin.x-((EnemyAttributes*)enemies[i].attr)->size/2, enemies[i].pos->origin.y-((EnemyAttributes*)enemies[i].attr)->size/2),
				makeCoord(enemies[i].pos->origin.x+((EnemyAttributes*)enemies[i].attr)->size/2, enemies[i].pos->origin.y+((EnemyAttributes*)enemies[i].attr)->size/2));
			drawLine(128,0,0,
					makeCoord(enemies[i].pos->origin.x+((EnemyAttributes*)enemies[i].attr)->size/2, enemies[i].pos->origin.y-((EnemyAttributes*)enemies[i].attr)->size/2),
					makeCoord(enemies[i].pos->origin.x-((EnemyAttributes*)enemies[i].attr)->size/2, enemies[i].pos->origin.y+((EnemyAttributes*)enemies[i].attr)->size/2));
		}
	}
}

void spawnEnemy(int i) {
	if(i >= MAX_ENEMY) return;
	if((EnemyAttributes*)enemies[i].attr) free((EnemyAttributes*)enemies[i].attr);
	if(enemies[i].pos) free(enemies[i].pos);

	Npc *e = makeNpc__leaks();
	assert(e);
	e->type = NPC_ENEMY;

	e->attr = malloc(sizeof(EnemyAttributes));
	assert(e->attr);
	((EnemyAttributes*)e->attr)->size = 10;
	((EnemyAttributes*)e->attr)->power = 0;
	((EnemyAttributes*)e->attr)->speed = 1;

	assert(e->pos);
	e->pos->origin = makeSafeCoord(scene,((EnemyAttributes*)e->attr)->size);

	enemies[i] = *e;
}

void initEnemy() {
	enemies = malloc(sizeof(Npc)*MAX_ENEMY);
	assert(enemies);
	memset(enemies,0,sizeof(Npc)*MAX_ENEMY);
	for(int i=0; i<MAX_ENEMY; i++) {
		spawnEnemy(i);
	}
}

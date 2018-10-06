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
const double DIR_CHANGE = 250;
bool showHomingLines = false;

void enemyGameFrame(void) {
	for(int i=0; i<MAX_ENEMY; i++) {
			if(enemies[i].coord.x == 0) continue;

			Coord heading;
			bool skipMove = false;

			//Turn off roaming if enough time has elapsed.
			if(enemies[i].isRoaming && isDue(clock(), enemies[i].lastRoamTime, DIR_CHANGE))
				enemies[i].isRoaming = false;

			Coord step;
			//If we're roaming - head in that direction.
			if(enemies[i].isRoaming) { step = makeStep(enemies[i].roamDir, ((EnemyAttributes*)enemies[i].attr)->speed); }
			//Otherwise - home towards player.
			else { step = getStep(enemies[i].coord, plr->pos, ((EnemyAttributes*)enemies[i].attr)->speed); }
			heading = deriveCoord(enemies[i].coord, step.x, step.y);

			// if you would collide with player, respawn
			if(rectInBounds(makeSquareBounds(heading,((EnemyAttributes*)enemies[i].attr)->size), makeSquareBounds(plr->pos, PC_BOUNDS))) {
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
															getAngle(enemies[i].coord,plr->squad->members[j].coord),
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

			enemies[i].coord = heading;
		}
	}

void enemyAnimateFrame(void) {
	//Animate the enemies
	for(int i=0; i < MAX_ENEMY; i++) {
		if(enemies[i].coord.x == 0) continue;

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
	for(int i=0; i<MAX_ENEMY; i++) {
		if(enemies[i].coord.x == 0) continue;

		SDL_RendererFlip flip = SDL_FLIP_NONE;
		bool isUp = false;
		bool isDown = false;

		isUp   = enemies[i].coord.y-plr->pos.y > abs(enemies[i].coord.x-plr->pos.x);
		isDown = plr->pos.y-enemies[i].coord.y > abs(enemies[i].coord.x-plr->pos.x);

		char frameFile[28];

		// Choose graphic based on type.
		if(isUp) {
			strcpy(frameFile, "dracula-walk-up-%02d.png");
		} else if(isDown) {
			strcpy(frameFile, "dracula-walk-down-%02d.png");
		} else{
			strcpy(frameFile, "dracula-walk-%02d.png");
			flip = enemies[i].coord.x > plr->pos.x ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
		}

		sprintf(frameFile, frameFile, enemies[i].animInc);
		Sprite *sprite = makeFlippedSprite__leaks(frameFile, flip);
		assert(sprite);
		drawSprite(sprite, enemies[i].coord);
		free(sprite);

		if(showHomingLines){
			drawLine(128,0,0,
				makeCoord(enemies[i].coord.x-((EnemyAttributes*)enemies[i].attr)->size/2, enemies[i].coord.y-((EnemyAttributes*)enemies[i].attr)->size/2),
				makeCoord(enemies[i].coord.x+((EnemyAttributes*)enemies[i].attr)->size/2, enemies[i].coord.y+((EnemyAttributes*)enemies[i].attr)->size/2));
			drawLine(128,0,0,
					makeCoord(enemies[i].coord.x+((EnemyAttributes*)enemies[i].attr)->size/2, enemies[i].coord.y-((EnemyAttributes*)enemies[i].attr)->size/2),
					makeCoord(enemies[i].coord.x-((EnemyAttributes*)enemies[i].attr)->size/2, enemies[i].coord.y+((EnemyAttributes*)enemies[i].attr)->size/2));
		}
	}
}

void spawnEnemy(int i) {
	if(i >= MAX_ENEMY) return;

	Npc *e = makeNpc__leaks();
	assert(e);
	e->type = NPC_ENEMY;
	e->attr = malloc(sizeof(EnemyAttributes));
	assert(e->attr);
	((EnemyAttributes*)e->attr)->size = 10;
	((EnemyAttributes*)e->attr)->power = 3;
	((EnemyAttributes*)e->attr)->speed = 1;
	e->coord = makeSafeCoord(scene,((EnemyAttributes*)e->attr)->size);

	if(enemies[i].attr != NULL) free((EnemyAttributes*)enemies[i].attr);
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

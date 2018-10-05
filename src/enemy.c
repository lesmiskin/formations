#include "enemy.h"
#include "common.h"
#include "player.h"
#include "renderer.h"
#include "assets.h"
#include "time.h"
#include "hud.h"

#define WALK_FRAMES 4
Enemy enemies[MAX_ENEMY];
static long lastIdleTime;
const int IDLE_HZ = 1000 / 4;
const double ENEMY_SPEED = 0.5;
const double CHAR_BOUNDS = 10;
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
			if(enemies[i].isRoaming) { step = makeStep(enemies[i].roamDir, ENEMY_SPEED); }
			//Otherwise - home towards player.
			else { step = getStep(enemies[i].coord, plr->pos, ENEMY_SPEED); }
			heading = deriveCoord(enemies[i].coord, step.x, step.y);

			// if you would collide with player, respawn
			if(rectInBounds(makeSquareBounds(heading,CHAR_BOUNDS), makeSquareBounds(plr->pos, PC_BOUNDS))) {
				plr->health -= 1;
				// if(plr->health == 0) quit();
				spawnEnemy(i);
				break;
			}

			// if you would collide with a squad member try to push instead of moving
			for(int j=0; j<plr->squad->size; j++) {
				if(npcInBounds(&plr->squad->members[j],makeSquareBounds(heading,CHAR_BOUNDS))) {
					skipMove = true;
					if(chance(25)) push(&plr->squad->members[j],getAngle(enemies[i].coord,plr->pos),4);
					break;
				}
			}
			if(skipMove) continue;

			// roam if we would collide with another enemy
			for(int j=0; j<MAX_ENEMY; j++) {
				if(i == j) continue; //Don't collide with ourselves!
				if(npcInBounds(&enemies[j], makeSquareBounds(heading, CHAR_BOUNDS))) {
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

		Sprite sprite;
		SDL_RendererFlip flip = SDL_FLIP_NONE;
		bool isUp = false;
		bool isDown = false;

		isUp = enemies[i].coord.y > plr->pos.y;
		isDown = enemies[i].coord.y < plr->pos.y;

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
		sprite = makeFlippedSprite(frameFile, flip);
		drawSprite(sprite, enemies[i].coord);

		if(showHomingLines){
			drawLine(128,0,0,
				makeCoord(enemies[i].coord.x-CHAR_BOUNDS/2, enemies[i].coord.y-CHAR_BOUNDS/2),
				makeCoord(enemies[i].coord.x+CHAR_BOUNDS/2, enemies[i].coord.y+CHAR_BOUNDS/2));
			drawLine(128,0,0,
					makeCoord(enemies[i].coord.x+CHAR_BOUNDS/2, enemies[i].coord.y-CHAR_BOUNDS/2),
					makeCoord(enemies[i].coord.x-CHAR_BOUNDS/2, enemies[i].coord.y+CHAR_BOUNDS/2));
		}
	}
}

Enemy* makeEnemy_leaks() {
	Enemy *enemy = malloc(sizeof(Enemy));
	if(!enemy) return NULL;
	enemy->type = NPC_ENEMY;
	enemy->animInc = randomMq(1,4);
	return enemy;
}

void spawnEnemy(int i) {
	if(i >= MAX_ENEMY) return;
	Enemy *enemy = makeEnemy_leaks();
	if(!enemy) return;
	enemy->coord = makeSafeCoord(CHAR_BOUNDS);
	enemies[i] = *enemy;
	free(enemy);
}

void initEnemy() {
	memset(enemies, 0, sizeof(Enemy)*MAX_ENEMY);
	for(int i=0; i<MAX_ENEMY; i++) {
		spawnEnemy(i);
	}
}

bool npcColliesWith(Enemy *npc, Enemy *other) { return npcInBounds(npc,makeSquareBounds(other->coord,CHAR_BOUNDS)); }
bool npcInBounds(Enemy *npc, Rect area) { return rectInBounds(makeSquareBounds(npc->coord,CHAR_BOUNDS),area); }

#include "enemy.h"
#include "player.h"
#include "renderer.h"
#include "assets.h"
#include "time.h"
#include "hud.h"

#define WALK_FRAMES 4
Enemy enemies[MAX_ENEMY];
long lastIdleTime;
const int IDLE_HZ = 1000 / 4;
const double ENEMY_SPEED = 0.5;
const double CHAR_BOUNDS = 15;
const double DIR_CHANGE = 250;
bool showHomingLines = false;

bool wouldTouchEnemy(Coord a, int selfIndex, bool includePlayer) {
	//Check player
	if(includePlayer) {
		if(inBounds(a, makeSquareBounds(plr->pos, CHAR_BOUNDS))) {
			return true;
		}
	}

	//Check enemies.
	for(int i=0; i<MAX_ENEMY; i++) {
		if(selfIndex != i && inBounds(a, makeSquareBounds(enemies[i].coord, CHAR_BOUNDS))) {
			return true;
		}
	}

	return false;
}

Coord calcDirOffset(Coord original, Dir dir) {
	Coord offset = zeroCoord();
	switch(dir) {
		case DIR_NORTH:
			offset = makeCoord(0, -ENEMY_SPEED);
			break;
		case DIR_NORTHEAST:
			offset = makeCoord(ENEMY_SPEED, -ENEMY_SPEED);
			break;
		case DIR_EAST:
			offset = makeCoord(ENEMY_SPEED, 0);
			break;
		case DIR_SOUTHEAST:
			offset = makeCoord(-ENEMY_SPEED, ENEMY_SPEED);
			break;
		case DIR_SOUTH:
			offset = makeCoord(0, ENEMY_SPEED);
			break;
		case DIR_SOUTHWEST:
			offset = makeCoord(-ENEMY_SPEED, ENEMY_SPEED);
			break;
		case DIR_WEST:
			offset = makeCoord(-ENEMY_SPEED, 0);
			break;
		case DIR_NORTHWEST:
			offset = makeCoord(-ENEMY_SPEED, -ENEMY_SPEED);
			break;
	}
	return mergeCoord(original, offset);
}

void enemyGameFrame(void) {
	for(int i=0; i<MAX_ENEMY; i++) {
			if(enemies[i].coord.x == 0) continue;

			Coord heading;
			bool nowRoaming = false;
			bool skipMove = false;

			//Turn off roaming if enough time has elapsed.
			if(enemies[i].isRoaming && isDue(clock(), enemies[i].lastRoamTime, DIR_CHANGE)) {
				enemies[i].isRoaming = false;
			}

			//If we're roaming - head in that direction.
			if(enemies[i].isRoaming) {
				heading = calcDirOffset(enemies[i].coord, enemies[i].roamDir);
			//Otherwise - home towards player.
			}else{
				Coord homeStep = getStep(enemies[i].coord, plr->pos, ENEMY_SPEED);
				heading = deriveCoord(enemies[i].coord, homeStep.x, homeStep.y);
			}

			// if you would collide with player, respawn
			if(inBounds(heading, makeSquareBounds(plr->pos, CHAR_BOUNDS))) {
				plr->health -= 1;
				if(plr->health == 0) quit();
				spawnEnemy(i);
				break;
			}

			// if you would collide with a squad member, don't Move
			for(int j=0; j<plr->squad->size; j++) {
				if(inBounds(heading, makeSquareBounds(plr->squad->members[j].coord, CHAR_BOUNDS))) {
					skipMove = true;
					break;
				}
			}

			//Loop through all enemies, and roam if we would collide.
			for(int j=0; j<MAX_ENEMY; j++) {
				if(i == j) continue; //Don't collide with ourselves!

				if(inBounds(heading, makeSquareBounds(enemies[j].coord, CHAR_BOUNDS))) {
					//Only move around 75% of the time (more realistic)
					//TODO: Change to delay?
					if(chance(75)) {
						skipMove = true;
						continue;
					}

					//Try roaming in some other directions to free ourselves.
					bool triedDirs[8] = { false, false, false, false, false, false, false, false };
					Coord roamTarget;
					int tryDir = 0;

					//Keep trying in NSEW dirs until we've exhausted our attempts.
					while(!triedDirs[0] || !triedDirs[1] || !triedDirs[2] || !triedDirs[3] || !triedDirs[4] || !triedDirs[5] || !triedDirs[6] || !triedDirs[7]) {
						//Pick a dir we haven't tried yet.
						do { tryDir = randomMq(0, 7); }
						while(triedDirs[tryDir]);

						triedDirs[tryDir] = true;

						//Would we touch anyone by traveling in this direction?
						roamTarget = calcDirOffset(enemies[i].coord, (Dir)tryDir);
						if(!wouldTouchEnemy(roamTarget, i, false)) {
							enemies[i].roamDir = (Dir)tryDir;
							enemies[i].lastRoamTime = clock();
							enemies[i].isRoaming = true;
							nowRoaming = true;
							break;
						}
					}

					if(nowRoaming) {
						break;
					}else{
						skipMove = true;
						break;
					}
				}
			}

			if(!skipMove) {
				//Move in the direction we're idly roaming in.
				if(enemies[i].isRoaming) { enemies[i].coord = calcDirOffset(enemies[i].coord, enemies[i].roamDir); }
				//Otherwise, home in on player.
				else { enemies[i].coord = heading; }
			}
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

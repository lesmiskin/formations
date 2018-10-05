#include <limits.h>
#include "squad.h"
#include "common.h"
#include "player.h"
#include "renderer.h"
#include "enemy.h"
#include "input.h"

static long lastIdleTime;

int* aiGreedy__leaks(double *values, int nActors, int nTargets, GreedyGoal goal) {
  int *takenBy = malloc(sizeof(int)*nActors);
  if(!takenBy) return NULL;
	memset(takenBy, -1, sizeof(*takenBy)*nActors);
  for(int iTarget=0;iTarget<nTargets;iTarget++) {
    double *value = NULL;
    int actor = -1;
    for(int iActor=0;iActor<nActors;iActor++) {
      if(takenBy[iActor] != -1) { continue; }
      bool better = false;
      switch(goal) {
        case MIN:
          if(value == NULL || values[iActor*nTargets+iTarget] < *value) better = true;
          break;
        case MAX:
          if(value == NULL || values[iActor*nTargets+iTarget] > *value) better = true;
          break;
      }
      if(better) {
        value = &values[iActor*nTargets+iTarget];
        actor = iActor;
      }
    }
    takenBy[actor] = iTarget;
  }
  return takenBy;
}

void squadSeekPosition(Squad *squad) {
	double ds[squad->size][8];
	for(int i=0;i<squad->size;i++) {
		for(int j=0;j<8;j++) {
			ds[i][j] = calcDistance(squad->members[i].coord,plr->goals[j]);
		}
	}
  GreedyGoal goal = MIN;
  int *goals = aiGreedy__leaks((double *)ds,squad->size,8,goal);
  if(goals) {
  	for(int i=0; i<squad->size; i++) {
      squad->members[i].goal = goals[i];
  		// home towards your goal
      Coord step = zeroCoord();
      if(ds[i][squad->members[i].goal]>11-squad->attr->discipline)
        step = getStep(squad->members[i].coord, plr->goals[squad->members[i].goal], ENEMY_SPEED);
  		Coord heading = deriveCoord(squad->members[i].coord, step.x, step.y);

      bool skipMove = false;
      for(int j=0; j<MAX_ENEMY; j++) {
        // if you would collide with an enemy, try to push instead of moving
        if(rectInBounds(makeSquareBounds(heading,CHAR_BOUNDS), makeSquareBounds(enemies[j].coord, CHAR_BOUNDS))) {
          skipMove = true;
          if(chance(100)) push(&enemies[j], getAngle(squad->members[i].coord, enemies[j].coord), 8);
          break;
        }
      }
      if(skipMove) continue;

      squad->members[i].coord = heading;
    }
    free(goals);
  }
}

void push(Enemy *self, double angle, double power) {
  Coord step = makeStep(angle,power);
  Coord coord = deriveCoord(self->coord, step.x, step.y);

  for(int i=0; i<MAX_ENEMY; i++) {
    if(self == &enemies[i]) continue;
    if(npcInBounds(&enemies[i],makeSquareBounds(coord,CHAR_BOUNDS))) {
      if(self->type == NPC_ENEMY) {
        // angle = getAngle(self->coord,enemies[i].coord);
        push(&enemies[i],angle,power);
      }
    }
  }
  for(int i=0;i<plr->squad->size;i++) {
    if(self == &plr->squad->members[i]) continue;
    if(npcInBounds(&plr->squad->members[i],makeSquareBounds(coord,CHAR_BOUNDS))) {
      // if(pushSquad) push(&plr->squad->members[i],angle,power);
    }
  }
  self->coord = coord;
}

void squadSpecial(Squad *squad) {}

void squadGameFrame(Squad *squad) {
  squadSeekPosition(squad);
  if(checkCommand(CMD_SQUAD_SPECIAL)) squadSpecial(squad);
}

void squadAnimateFrame(Squad *squad) {
	//Animate the enemies
	for(int i=0; i < squad->size; i++) {
		if(squad->members[i].coord.x == 0) continue;
		//Increment animations.
		if(squad->members[i].animInc < 4) {
			squad->members[i].animInc++;
		} else {
			squad->members[i].animInc = 1;
		}
	}
}

void squadRenderFrame(Squad *squad) {
  //Draw the enemies with the right animation frame.
	for(int i=0; i < squad->size; i++) {
		if(squad->members[i].coord.x == 0) continue;

		Sprite sprite;
		SDL_RendererFlip flip = SDL_FLIP_NONE;
		bool isUp = false;
		bool isDown = false;

		isUp = squad->members[i].coord.y > plr->pos.y;
		isDown = squad->members[i].coord.y < plr->pos.y;

		char frameFile[28];

		// Choose graphic based on type.
		if(isUp) {
			strcpy(frameFile, "werewolf-walk-up-%02d.png");
		} else if(isDown) {
			strcpy(frameFile, "werewolf-walk-down-%02d.png");
		} else{
			strcpy(frameFile, "werewolf-walk-%02d.png");
			flip = squad->members[i].coord.x > plr->pos.x ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
		}

		// Draw line showing where the enemy is homing to.
		if(showHomingLines){
			drawLine(0,128,0, squad->members[i].coord, plr->goals[squad->members[i].goal]);
		}

		sprintf(frameFile, frameFile, squad->members[i].animInc);
		sprite = makeFlippedSprite(frameFile, flip);
		drawSprite(sprite, squad->members[i].coord);
	}
}

Squad* makeSquad__leaks() {
  Squad *squad = malloc(sizeof(Squad));
  if (!squad) return NULL;
  squad->size = 8;

  SquadAttributes *attr = malloc(sizeof(SquadAttributes));
  if(!attr) return NULL;
  attr->discipline = 10;
  squad->attr = attr;

  Enemy *members = malloc(sizeof(Enemy)*squad->size);
  if(!members) return NULL;
  for(int i=0;i<squad->size;i++) {
    Enemy *e  = makeEnemy_leaks();
    if(!e) continue;
    e->type = NPC_SQUAD;
    e->coord = plr->goals[i],
  	e->goal = i,
  	members[i] = *e;
  }
  squad->members = members;
  return squad;
}

void freeSquad(Squad *squad) {
  free(squad->attr);
  free(squad->members);
  free(squad);
}

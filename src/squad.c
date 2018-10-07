#include <limits.h>
#include <assert.h>
#include "squad.h"
#include "common.h"
#include "player.h"
#include "renderer.h"
#include "enemy.h"
#include "npc.h"
#include "input.h"

static long lastIdleTime;

int* aiGreedy__leaks(double *values, int nActors, int nTargets, GreedyGoal goal) {
  int *takenBy = malloc(sizeof(int)*nActors);
  assert(takenBy);
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
  for(int j=0;j<plr->formation->size;j++) {
    Coord p = formationGetPosition(plr->formation,j);
	  for(int i=0;i<squad->size;i++) {
			ds[i][j] = calcDistance(squad->members[i].pos->origin,p);
		}
	}
  GreedyGoal goal = MIN;
  int *takenBy = aiGreedy__leaks((double *)ds,squad->size,plr->formation->size,goal);
  assert(takenBy);
	for(int i=0; i<squad->size; i++) {
    squad->members[i].goal = formationGetPosition(plr->formation,takenBy[i]);
		// home towards your goal
    Coord step = zeroCoord();
    if(ds[i][takenBy[i]]>11-((SquadAttributes*)squad->members[i].attr)->discipline)
      step = getStep(squad->members[i].pos->origin,
                     squad->members[i].goal,
                     ((SquadAttributes*)squad->members[i].attr)->speed);
		Coord heading = deriveCoord(squad->members[i].pos->origin, step.x, step.y);

    bool skipMove = false;
    for(int j=0; j<MAX_ENEMY; j++) {
      // if you would collide with an enemy, try to push them instead of moving
      if(npcInBounds(&enemies[j], makeSquareBounds(heading,((SquadAttributes*)squad->members[i].attr)->size))) {
        skipMove = true;
        if(chance(100)) push(&enemies[j],
                             getAngle(squad->members[i].pos->origin, enemies[j].pos->origin),
                             ((SquadAttributes*)squad->members[i].attr)->power);
        break;
      }
    }
    if(skipMove) continue;

    squad->members[i].pos->origin = heading;
  }
  free(takenBy);
}

void squadSpecial(Squad *squad) {}

void squadGameFrame(Squad *squad) {
  squadSeekPosition(squad);
  if(checkCommand(CMD_SQUAD_SPECIAL)) squadSpecial(squad);
}

void squadAnimateFrame(Squad *squad) {
	//Animate the enemies
	for(int i=0; i < squad->size; i++) {
		if(squad->members[i].pos->origin.x == 0) continue;
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
		if(squad->members[i].pos->origin.x == 0) continue;

		SDL_RendererFlip flip = SDL_FLIP_NONE;
		bool isUp = false;
		bool isDown = false;

		isUp   = squad->members[i].pos->origin.y-squad->members[i].goal.y > abs(squad->members[i].pos->origin.x-squad->members[i].goal.x);
		isDown = squad->members[i].goal.y-squad->members[i].pos->origin.y > abs(squad->members[i].pos->origin.x-squad->members[i].goal.x);

		char frameFile[28];

		// Choose graphic based on type.
		if(isUp) {
			strcpy(frameFile, "werewolf-walk-up-%02d.png");
		} else if(isDown) {
			strcpy(frameFile, "werewolf-walk-down-%02d.png");
		} else{
			strcpy(frameFile, "werewolf-walk-%02d.png");
			flip = squad->members[i].pos->origin.x > squad->members[i].goal.x ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
		}

		// Draw line showing where the enemy is homing to.
		if(showHomingLines){
			drawLine(0,128,0, squad->members[i].pos->origin, squad->members[i].goal);
		}

		sprintf(frameFile, frameFile, squad->members[i].animInc);
		Sprite *sprite = makeFlippedSprite__leaks(frameFile, flip);
    assert(sprite);
		drawSprite(sprite, squad->members[i].pos->origin);
    free(sprite);
	}
}

Squad* makeSquad__leaks() {
  Squad *squad = malloc(sizeof(Squad));
  if (!squad) return NULL;
  squad->size = 8;

  Npc *members = malloc(sizeof(Npc)*squad->size);
  assert(members);

  for(int i=0;i<squad->size;i++) {
    Npc *e  = makeNpc__leaks();
    assert(e);
    e->type = NPC_SQUAD;
    e->goal = formationGetPosition(plr->formation,i),

    e->attr = malloc(sizeof(SquadAttributes));
    assert(e->attr);
    ((SquadAttributes*)e->attr)->discipline = 10;
    ((SquadAttributes*)e->attr)->power = 4;
    ((SquadAttributes*)e->attr)->size = 10;
    ((SquadAttributes*)e->attr)->speed = 1;

    e->pos = malloc(sizeof(Position));
    e->pos->origin = e->goal;

  	members[i] = *e;
  }
  squad->members = members;
  return squad;
}

void freeSquad(Squad *squad) {
  for(int i=0;i<squad->size;i++) {
    free((SquadAttributes*)squad->members[i].attr);
    free(&squad->members[i]);
  }
  free(squad);
}

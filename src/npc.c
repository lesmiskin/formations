#include <assert.h>
#include "npc.h"
#include "common.h"
#include "enemy.h"
#include "squad.h"

Npc* makeNpc__leaks() {
	Npc *npc = malloc(sizeof(Npc));
	assert(npc);
	npc->isRoaming = false;
	npc->animInc = randomMq(1,4);

	Position *pos = malloc(sizeof(Position));
	assert(pos);
	npc->pos = pos;

	return npc;
}

void push(Npc *self, double angle, double power) {
  Coord step = makeStep(angle,power);
  Coord coord = deriveCoord(self->pos->origin, step.x, step.y);
	self->pos->origin = coord;

  for(int i=0; i<MAX_ENEMY; i++) {
    if(self == &enemies[i]) continue;
    if(npcCollidesWith(self,&enemies[i])) {
      if(self->type == NPC_ENEMY) {
        angle = getAngle(self->pos->origin,enemies[i].pos->origin);
        push(&enemies[i],angle,power);
      }
    }
  }
}

bool npcCollidesWith(Npc *npc, Npc *other) {
  int size;
  if(other->type == NPC_SQUAD) size = ((SquadAttributes*)other->attr)->size;
  if(other->type == NPC_ENEMY) size = ((EnemyAttributes*)other->attr)->size;
  return npcInBounds(npc,makeSquareBounds(other->pos->origin,size));
}
bool npcInBounds(Npc *npc, Rect area) {
  int size;
  if(npc->type == NPC_SQUAD) size = ((SquadAttributes*)npc->attr)->size;
  if(npc->type == NPC_ENEMY) size = ((EnemyAttributes*)npc->attr)->size;
  return rectInBounds(makeSquareBounds(npc->pos->origin,size),area);
}

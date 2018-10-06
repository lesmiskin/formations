#include "npc.h"
#include "common.h"
#include "enemy.h"

Npc* makeNpc__leaks() {
	Npc *npc = malloc(sizeof(Npc));
	if(!npc) return NULL;
	npc->animInc = randomMq(1,4);
	return npc;
}

void push(Npc *self, double angle, double power) {
  Coord step = makeStep(angle,power);
  Coord coord = deriveCoord(self->coord, step.x, step.y);

  for(int i=0; i<MAX_ENEMY; i++) {
    if(self == &enemies[i]) continue;
    if(npcInBounds(&enemies[i],makeSquareBounds(coord,CHAR_BOUNDS))) {
      if(self->type == NPC_ENEMY) {
        angle = getAngle(self->coord,enemies[i].coord);
        push(&enemies[i],angle,power);
      }
    }
  }
  self->coord = coord;
}

bool npcCollidesWith(Npc *npc, Npc *other) { return npcInBounds(npc,makeSquareBounds(other->coord,CHAR_BOUNDS)); }
bool npcInBounds(Npc *npc, Rect area) { return rectInBounds(makeSquareBounds(npc->coord,CHAR_BOUNDS),area); }

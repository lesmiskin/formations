#ifndef NPC_H
#define NPC_H

#include "common.h"

typedef enum {
	NPC_ENEMY,
	NPC_SQUAD,
} NpcType;

typedef struct {
	NpcType type;
	Position *pos;
	void *attr;
	Coord goal;
	int animInc;
	bool isRoaming;
	double roamDir;
	long lastRoamTime;
} Npc;

extern Npc* makeNpc__leaks();

extern void push(Npc*, double, double);

extern bool npcInBounds(Npc*, Rect);
extern bool npcCollidesWith(Npc*, Npc*);

#endif

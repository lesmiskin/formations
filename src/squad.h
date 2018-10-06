#ifndef SQUAD_H
#define SQUAD_H

#include "npc.h"

typedef struct {
  int discipline;
} SquadAttributes;

typedef struct {
  int size;
  Npc *members;
  SquadAttributes *attr;
} Squad;

typedef enum {
  MIN,
  MAX,
} GreedyGoal;

extern void squadGameFrame();
extern void squadAnimateFrame();
extern void squadRenderFrame();
extern Squad* makeSquad__leaks();
extern void freeSquad(Squad*);

#endif

#ifndef SQUAD_H
#define SQUAD_H

#include "npc.h"

typedef struct {
  int discipline;
  int power;
  int size;
  int speed;
} SquadAttributes;

typedef struct {
  int size;
  Npc *members;
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

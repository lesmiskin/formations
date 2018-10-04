#ifndef SQUAD_H
#define SQUAD_H

#include "enemy.h"

typedef struct {
  int discipline;
} SquadAttributes;

typedef struct {
  int size;
  Enemy *members;
  SquadAttributes *attr;
} Squad;

typedef enum {
  MIN,
  MAX,
} GreedyGoal;

extern void squadGameFrame();
extern void squadAnimateFrame();
extern void squadRenderFrame();
extern Squad* makeSquad_leaks();
extern void freeSquad(Squad*);

#endif

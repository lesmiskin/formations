#ifndef PLAYER_H
#define PLAYER_H

#include "squad.h"

extern const double PC_BOUNDS;

typedef struct {
  int size;
  Coord *positions;
  double orientation;
} Formation;

typedef struct {
  Position *pos;
  Formation *formation;
  Squad *squad;
  int health;
  bool dir;
  bool walking;
  int walkInc;
} Player;

extern Player *plr;

extern Coord formationGetPosition(Formation*,int);
extern void playerGameFrame(Player*);
extern void playerRenderFrame(Player*);
extern void playerAnimateFrame(Player*);
extern void initPlayer();

#endif

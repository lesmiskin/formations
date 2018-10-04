#ifndef PLAYER_H
#define PLAYER_H

#include "squad.h"

typedef struct {
  Coord pos;
  int formation;
  Coord goals[8];
  double goalAngle;
  bool dir;
  bool walking;
  int walkInc;
  Squad *squad;
} Player;

extern Player *plr;

extern void playerGameFrame(Player*);
extern void playerRenderFrame(Player*);
extern void playerAnimateFrame(Player*);
extern void initPlayer();

#endif

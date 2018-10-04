#ifndef PLAYER_H
#define PLAYER_H

#include "squad.h"

extern const double PC_BOUNDS;

typedef struct {
  Coord pos;
  int health;
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

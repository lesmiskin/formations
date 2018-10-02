#ifndef PLAYER_H
#define PLAYER_H

typedef struct {
  Coord pos;
  int formation;
  Coord goals[8];
  double goalAngle;
  bool dir;
  bool walking;
  int walkInc;
} Player;

extern Player *plr;
extern void playerGameFrame(Player*);
extern void playerRenderFrame(Player*);
extern void playerShadowFrame(Player*);
extern void playerSetFormationGoals(Player*);
extern void playerAnimateFrame(Player*);
extern void initPlayer();

#endif

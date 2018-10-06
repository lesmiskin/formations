#include <time.h>
#include "common.h"
#include "player.h"
#include "assets.h"
#include "input.h"
#include "hud.h"
#include "renderer.h"
#include "scene.h"
#include "enemy.h"
#include "squad.h"

#define WALK_FRAMES 4

const double MOVE_INC = 1;
const double PC_BOUNDS = 10;

Player * plr;

void playerSetFormationGoals(Player *p) {
	for(int i=0; i < 8; i++) {
		Coord g0;
		// shape it
		if(p->formation == 1) {
			g0 = makeCoord(((i<4?i:i+1)%3-1)*1.5*PC_BOUNDS, ((i<4?i:i+1)/3-1)*1.5*PC_BOUNDS);
		} else if (p->formation == 2) {
			g0 = makeCoord((i-3.5)*PC_BOUNDS, -PC_BOUNDS);
		} else if (p->formation == 3) {
			g0 = makeCoord((i-3.5)*PC_BOUNDS, (i%4)*(i/4 > 0 ? 1 : -1)*.5*PC_BOUNDS - (i/4 > 0 ? PC_BOUNDS : 0));
		}

		// rotate it
		double s = sin(p->goalAngle);
		double c = cos(p->goalAngle);
		g0 = makeCoord(g0.x*c-g0.y*s,g0.x*s+g0.y*c);

		// translate it
		p->goals[i] = makeCoord(p->pos.x + g0.x,p->pos.y + g0.y);
	}
}

Player* makePlayer__leaks() {
	plr = malloc(sizeof(Player));
	plr->pos = makeCoord(100,50);
	plr->health = 10;
	plr->formation = 1;
	plr->goalAngle =	degToRad(0);
	plr->walkInc = 1;
	return plr;
}

void playerAnimateFrame(Player *p) {
	if(!p->walking) return;
	p->walkInc = (p->walkInc == WALK_FRAMES) ? 1 : p->walkInc + 1;
}

void playerRenderFrame(Player *p) {
	//Draw player.
	SDL_RendererFlip flip = p->dir ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;

	char frameFile[25];
	sprintf(frameFile, "player-walk-sword-%02d.png", p->walkInc);
	Sprite *player = makeFlippedSprite__leaks(frameFile, flip);
	drawSprite(player, p->pos);
	free(player);
}

void playerGameFrame(Player *p) {
	if(checkCommand(CMD_FORMATION_1)) plr->formation = 1;
	if(checkCommand(CMD_FORMATION_2)) plr->formation = 2;
	if(checkCommand(CMD_FORMATION_3)) plr->formation = 3;
	if(checkCommand(CMD_FORMATION_4)) plr->formation = 3;

	// rotate formation
	if(checkCommand(CMD_ROTATE_FORM_CW)) p->goalAngle = degToRad(radToDeg(p->goalAngle)+2);
	if(checkCommand(CMD_ROTATE_FORM_CCW)) p->goalAngle = degToRad(radToDeg(p->goalAngle)-2);

	Coord goal = makeCoord(
		(checkCommand(CMD_PLAYER_LEFT) ? 1 : 0) * -MOVE_INC
	+ (checkCommand(CMD_PLAYER_RIGHT) ? 1 : 0) * MOVE_INC,
		(checkCommand(CMD_PLAYER_UP) ? 1 : 0) * -MOVE_INC
	+ (checkCommand(CMD_PLAYER_DOWN) ? 1 : 0) * MOVE_INC);
	Coord step = getStep(zeroCoord(),goal,MOVE_INC);
	Coord heading = deriveCoord(p->pos,step.x,step.y);

	// no walking off the screen!
	p->pos.x = fmin(screenBounds.x-PC_BOUNDS/2,fmax(0+PC_BOUNDS/2,heading.x));
	p->pos.y = fmin(screenBounds.y-PC_BOUNDS/2,fmax(0+PC_BOUNDS/2,heading.y));

	// We still turn the player sprite where we can, even if we're hard
	// up against a screen bound.
	p->walking = false;
	if (checkCommand(CMD_PLAYER_LEFT)) {
		p->dir = false;
		p->walking = true;
	}
	if (checkCommand(CMD_PLAYER_RIGHT)) {
		p->dir = true;
		p->walking = true;
	}
	if (checkCommand(CMD_PLAYER_UP) && p->pos.y > 0) {
		p->walking = true;
	}
	if (checkCommand(CMD_PLAYER_DOWN) && p->pos.y < screenBounds.y) {
		p->walking = true;
	}
	playerSetFormationGoals(p);
}

void initPlayer() {
	plr = makePlayer__leaks();
	if(!plr) printf("[%s:%d] leaky function failed to allocate",__FILE__,__LINE__);
	playerSetFormationGoals(plr);
	plr->squad = makeSquad__leaks();
	if(!plr->squad) printf("[%s:%d] leaky function failed to allocate",__FILE__,__LINE__);
}

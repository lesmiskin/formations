#include <time.h>
#include "player.h"
#include "assets.h"
#include "input.h"
#include "hud.h"
#include "renderer.h"

#include "scene.h"
#include "enemy.h"

const double PC_BOUNDS = 15;
double MOVE_INC = 0.5;

#define WALK_FRAMES 4

Coord pos = { 25, 50 };
Coord goals[8];
int formation = 1;
int walkInc = 1;
double health = 100;
bool playerDir = false;
bool walking = false;

void playerAnimateFrame(void) {
	if(!walking) return;
	walkInc = (walkInc == WALK_FRAMES) ? 1 : walkInc + 1;
}

void playerRenderFrame(void) {
	//Draw player.
	SDL_RendererFlip flip = playerDir ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;

	char frameFile[25];
	sprintf(frameFile, "player-walk-sword-%02d.png", walkInc);
	Sprite player = makeFlippedSprite(frameFile, flip);

//	SDL_SetTextureColorMod(player.texture, 164, 164, 192);

	drawSprite(player, pos);
}

void playerGameFrame(void) {
	walking = false;

	//NB: We still turn the player sprite where we can, even if we're hard
	// up against a screen bound.
	Coord goal = makeCoord(
		(checkCommand(CMD_PLAYER_LEFT) ? 1 : 0) * -1
	+ (checkCommand(CMD_PLAYER_RIGHT) ? 1 : 0) * 1,
		(checkCommand(CMD_PLAYER_UP) ? 1 : 0) * -1
	+ (checkCommand(CMD_PLAYER_DOWN) ? 1 : 0) * 1);

	Coord step = getStep(zeroCoord(),goal,MOVE_INC);
	Coord heading = deriveCoord(pos,step.x,step.y);
	pos.x = fmin(screenBounds.x-PC_BOUNDS/2,fmax(0+PC_BOUNDS/2,heading.x));
	pos.y = fmin(screenBounds.y-PC_BOUNDS/2,fmax(0+PC_BOUNDS/2,heading.y));
	if (checkCommand(CMD_PLAYER_LEFT)) {
		// if(pos.x > 0) pos.x -= MOVE_INC;
		playerDir = false;
		walking = true;
	}
	if (checkCommand(CMD_PLAYER_RIGHT)) {
		// if(pos.x < screenBounds.x) pos.x += MOVE_INC;
		playerDir = true;
		walking = true;
	}
	if (checkCommand(CMD_PLAYER_UP) && pos.y > 0) {
		// pos.y -= MOVE_INC;
		walking = true;
	}
	if (checkCommand(CMD_PLAYER_DOWN) && pos.y < screenBounds.y) {
		// pos.y += MOVE_INC;
		walking = true;
	}
	setFormation(formation);
}

void setFormation(int formation) {
	for(int i=0; i < 8; i++) {
		if(formation == 1) {
			goals[i] = makeCoord(pos.x + ((i<4?i:i+1)%3-1)*PC_BOUNDS, pos.y + ((i<4?i:i+1)/3-1)*PC_BOUNDS);
		} else if (formation == 2) {
			goals[i] = makeCoord(pos.x + (i-3.5)*.75*PC_BOUNDS, pos.y - PC_BOUNDS);
		} else if (formation == 3) {
			goals[i] = makeCoord(pos.x + (i-3.5)*.5*PC_BOUNDS, pos.y + (i%4)*(i/4 > 0 ? 1 : -1)*.25*PC_BOUNDS - (i/4 > 0 ? .75*PC_BOUNDS : 0));
		}
	}
}

void initPlayer() {
	pos.x = 25;
	pos.y = 50;
	health = 100;
	setFormation(formation);
}

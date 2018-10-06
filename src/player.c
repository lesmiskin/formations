#include <time.h>
#include <assert.h>
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

Coord formationGetPosition(Formation *f, int i) {
	// rotate
	double s = sin(f->orientation);
	double c = cos(f->orientation);
	double x = f->positions[i].x;
	double y = f->positions[i].y;
	Coord p = makeCoord(x*c-y*s,x*s+y*c);

	// translate
	return makeCoord(plr->pos.x + p.x, plr->pos.y + p.y);
}

void formationSetPositions(Formation *f, int formation) {
	for(int i=0; i<f->size; i++) {
		if(formation == 1) { f->positions[i] = makeCoord(((i<4?i:i+1)%3-1)*1.5*PC_BOUNDS, ((i<4?i:i+1)/3-1)*1.5*PC_BOUNDS); }
		if(formation == 2) { f->positions[i] = makeCoord((i-3.5)*PC_BOUNDS, -PC_BOUNDS); }
		if(formation == 3) { f->positions[i] = makeCoord((i-3.5)*PC_BOUNDS, (i%4)*(i/4 > 0 ? 1 : -1)*.5*PC_BOUNDS - (i/4 > 0 ? PC_BOUNDS : 0)); }
	}
}

Formation* makeFormation__leaks(int formation) {
	Formation *f = malloc(sizeof(Formation));
	assert(f);
	f->size = 8;
	f->orientation = 0;

	f->positions = malloc(sizeof(Coord)*f->size);
	assert(f->positions);
	formationSetPositions(f,1);

	return f;
}

Player* makePlayer__leaks() {
	plr = malloc(sizeof(Player));
	assert(plr);
	plr->pos = makeCoord(100,50);
	plr->health = 10;
	plr->walkInc = 1;

	plr->formation = makeFormation__leaks(1);
	assert(plr->formation);

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
	assert(player);
	drawSprite(player, p->pos);
	free(player);
}

void playerGameFrame(Player *p) {
	if(checkCommand(CMD_FORMATION_1)) formationSetPositions(plr->formation,1);
	if(checkCommand(CMD_FORMATION_2)) formationSetPositions(plr->formation,2);
	if(checkCommand(CMD_FORMATION_3)) formationSetPositions(plr->formation,3);
	if(checkCommand(CMD_FORMATION_4)) formationSetPositions(plr->formation,3);

	// rotate formation
	if(checkCommand(CMD_ROTATE_FORM_CW)) p->formation->orientation = degToRad(radToDeg(p->formation->orientation)+2);
	if(checkCommand(CMD_ROTATE_FORM_CCW)) p->formation->orientation = degToRad(radToDeg(p->formation->orientation)-2);

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
}

void initPlayer() {
	plr = makePlayer__leaks();
	assert(plr);
	plr->squad = makeSquad__leaks();
	assert(plr->squad);
}

void freePlayer(Player *plr) {
	freeSquad(plr->squad);
	for(int i=0;i<plr->formation->size;i++) {
		free(&plr->formation->positions[i]);
	}
	free(plr);
}

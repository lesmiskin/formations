#include "scene.h"
#include "renderer.h"
#include "common.h"
#include "assets.h"
#include "hud.h"
#include "enemy.h"
#include "player.h"

Scene *scene;

static void makeGroundTexture(Scene *scene) {
	//Init the SDL texture
	SDL_Texture *groundTexture = SDL_CreateTexture(
		renderer,
		SDL_PIXELFORMAT_RGB24,
		SDL_TEXTUREACCESS_TARGET,
		(int)scene->size.x,
		(int)scene->size.y
	);

	//Prepare sprite, and change the rendering target to our above texture.
	Sprite* tile = makeSimpleSprite__leaks("grass.png");
	SDL_SetRenderTarget(renderer, groundTexture);

	//Draw the tiles out onto the texture.
	for(int x=0; x<scene->size.x+scene->tileSize; x+=scene->tileSize) {
		for (int y=0; y<scene->size.y+scene->tileSize; y+=scene->tileSize) {
			drawSprite(tile, makeCoord(x, y));
		}
	}
	free(tile);

	//Darken
	SDL_SetTextureColorMod(groundTexture, 64, 64, 128);

	//Switch rendering back to the normal renderBuffer target.
	SDL_SetRenderTarget(renderer, renderBuffer);

	scene->ground = makeSprite__leaks(groundTexture, zeroCoord(), SDL_FLIP_NONE);
}

void sceneAnimateFrame(Scene* scene) {
}

void sceneGameFrame(Scene* scene) {
	// for(int i=0; i < MAX_PROPS; i++) {
	// 	if(	props[i].type == PROP_COFFIN &&
	// 		!props[i].coffinOpened &&
	// 		inBounds(pos, makeSquareBounds(props[i].coord, 24))
	// 	){
	// 		//50% chance a vampire will come out.
	// 		if(chance(66)) {
	// 			spawnEnemy(ENEMY_DRACULA, props[i].coord);
	// 		}
	// 		props[i].coffinOpened = true;
	// 	}
	// }
}

void sceneRenderFrame(Scene* scene) {
	drawSprite(scene->ground, makeCoord(scene->size.x / 2, scene->size.y / 2));
//
// 	for(int i=0; i < MAX_PROPS; i++) {
// 		Sprite sprite;
// 		char frameFile[25];
//
// 		switch(props[i].type) {
// 			case PROP_COFFIN:
// 				if(props[i].coffinOpened) {
// 					strcpy(frameFile, "coffin-open.png");
// 				}else{
// 					strcpy(frameFile, "coffin-closed.png");
// 				}
// 				break;
// //			case PROP_GRAVE:
// //				strcpy(frameFile, "grave.png");
// //				break;
// 			case PROP_GRAVESTONE:
// 				strcpy(frameFile, "gravestone.png");
// 				break;
// 			case PROP_GRAVESTONE_CROSS:
// 				strcpy(frameFile, "gravestone-cross-grass.png");
// 				break;
// 		}
//
// 		SDL_Texture *tex = getTexture(frameFile);
//
// 		//Darken
// 		SDL_SetTextureColorMod(tex, 164, 164, 192);
//
// 		sprite = makeSprite(tex, zeroCoord(), SDL_FLIP_NONE);
//
// 		drawSprite(sprite, props[i].coord);
// 	}
}

//Should happen each time the scene is shown.
void initScene() {
	scene = malloc(sizeof(Scene));
	scene->size = makeCoord(16*30,9*30);
	scene->tileSize = 8;
	makeGroundTexture(scene);
}

Coord makeSafeCoord(Scene *scene, double size) {
	Coord coord;
	bool safe = false;
	while(!safe) {
		safe = true;
		coord = makeCoord(randomMq(0, scene->size.x),randomMq(0, scene->size.y));
		Rect bounds = makeSquareBounds(coord, size);

		// dont spawn on the player
		if(rectInBounds(bounds,makeSquareBounds(plr->pos,PC_BOUNDS))) { safe = false; }
		if(!safe) continue;

		// dont spawn on the squad
		for(int i=0;i<plr->squad->size;i++) {
			if(!plr->squad->members[i].attr) continue;
			if(npcInBounds(&plr->squad->members[i],bounds)) { safe = false; break; }
		}
		if(!safe) continue;

		// dont spawn on an enemy
		for(int i=0;i<MAX_ENEMY;i++) {
			if(!enemies[i].attr) continue;
			if(npcInBounds(&enemies[i],bounds)) { safe = false; break; }
		}
		if(!safe) continue;
	}
	return coord;
}

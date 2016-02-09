#include "scene.h"
#include "renderer.h"
#include "common.h"
#include "assets.h"
#include "hud.h"

#include "enemy.h"

void sceneAnimateFrame() {
}

const int TILE_SIZE = 8;
static Sprite ground;

//BUG: Lots of hardcoded shit in here to fix scaling bugs. Get rid of our scaling entirely...?

static void makeGroundTexture() {
	//Init the SDL texture
	SDL_Texture *groundTexture = SDL_CreateTexture(
		renderer,
		SDL_PIXELFORMAT_RGB24,
		SDL_TEXTUREACCESS_TARGET,
		(int)640,
		(int)480
	);

	//Prepare sprite, and change the rendering target to our above texture.
	Sprite tile = makeSimpleSprite("grass.png");
	SDL_SetRenderTarget(renderer, groundTexture);

	//Draw the tiles out onto the texture.
	for(int x=0; x < 320; x += TILE_SIZE) {
		for (int y = 0; y < 240; y += TILE_SIZE) {
			drawSprite(tile, makeCoord(x, y));
		}
	}

	SDL_SetTextureColorMod(groundTexture, 64, 64, 128);

	//Switch rendering back to the normal renderBuffer target.
	SDL_SetRenderTarget(renderer, renderBuffer);

	ground = makeSprite(groundTexture, zeroCoord(), SDL_FLIP_NONE);
}

void sceneRenderFrame() {
	drawSprite(ground, makeCoord(320, 240));
}

//Should happen each time the scene is shown.
void initScene() {
	makeGroundTexture();
}

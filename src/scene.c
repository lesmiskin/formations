#include "scene.h"
#include "renderer.h"
#include "common.h"
#include "assets.h"
#include "hud.h"

#include "enemy.h"

#define MAX_PROPS 4

typedef enum {
	PROP_GRAVESTONE ,
	PROP_GRAVESTONE_CROSS,
//	PROP_GRAVE =1,
	PROP_COFFIN
} PropType;

typedef struct {
	PropType type;
	Coord origin;
} Prop;

const int TILE_SIZE = 8;
static Sprite ground;
static Prop props[MAX_PROPS];


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

	//Darken
	SDL_SetTextureColorMod(groundTexture, 64, 64, 128);

	//Switch rendering back to the normal renderBuffer target.
	SDL_SetRenderTarget(renderer, renderBuffer);

	ground = makeSprite(groundTexture, zeroCoord(), SDL_FLIP_NONE);
}

void sceneAnimateFrame() {
}

void sceneRenderFrame() {
	drawSprite(ground, makeCoord(320, 240));

	for(int i=0; i < MAX_PROPS; i++) {
		Sprite sprite;
		char *frameFile[25];

		switch(props[i].type) {
			case PROP_COFFIN:
				strcpy(frameFile, "coffin-closed.png");
				break;
//			case PROP_GRAVE:
//				strcpy(frameFile, "grave.png");
//				break;
			case PROP_GRAVESTONE:
				strcpy(frameFile, "gravestone.png");
				break;
			case PROP_GRAVESTONE_CROSS:
				strcpy(frameFile, "gravestone-cross-grass.png");
				break;
		}

		SDL_Texture *tex = getTexture(frameFile);

		//Darken
		SDL_SetTextureColorMod(tex, 164, 164, 192);

		sprite = makeSprite(tex, zeroCoord(), SDL_FLIP_NONE);

		drawSprite(sprite, props[i].origin);
	}
}

//Should happen each time the scene is shown.
void initScene() {
	makeGroundTexture();

	for(int i=0; i < MAX_PROPS; i++) {
		Prop p = {
			(PropType)randomMq(0, PROP_COFFIN),
			makeCoord(
				randomMq(0, screenBounds.x),
				randomMq(0, screenBounds.y)
			)
		};
		props[i] = p;
	}
}

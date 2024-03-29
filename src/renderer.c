#include <assert.h>
#include "renderer.h"
#include "assets.h"

SDL_Texture *renderBuffer;
SDL_Renderer *renderer = NULL;
static int renderScale;
static const int BASE_SCALE_WIDTH = 16*30;
static const int BASE_SCALE_HEIGHT = 9*30;
static const double PIXEL_SCALE = 1; //pixel doubling for assets.
Coord pixelGrid;					    			 //helps aligning things to the tiled background.
Coord screenBounds;

Coord getTextureSize(SDL_Texture *texture) {
    int x, y;
    SDL_QueryTexture(texture, NULL, NULL, &x, &y);
    return makeCoord(x, y);
}

Sprite* makeSprite__leaks(SDL_Texture *texture, Coord offset, SDL_RendererFlip flip) {
    Sprite *sprite = malloc(sizeof(Sprite));
    assert(sprite);
    sprite->texture = texture;
    sprite->offset = offset;
    sprite->size = getTextureSize(texture);
    sprite->flip = flip;
    return sprite;
}

Sprite* makeFlippedSprite__leaks(char *textureName, SDL_RendererFlip flip) {
    SDL_Texture *texture = getTexture(textureName);
    return makeSprite__leaks(texture, zeroCoord(), flip);
}

Sprite* makeSimpleSprite__leaks(char *textureName) {
	SDL_Texture *texture = getTexture(textureName);
	return makeSprite__leaks(texture, zeroCoord(), SDL_FLIP_NONE);
}

void drawSpriteFull(Sprite *sprite, Coord origin, double scale, double angle) {
    // Ensure we're always calling this with an initialised sprite_t.
    assert(sprite->texture != NULL);

    // Offsets should be relative to image pixel metrics, not screen metrics.
    int offsetX = sprite->offset.x;
    int offsetY = sprite->offset.y;

    // We adjust the offset to ensure all sprites are drawn centered at their coord points
    offsetX -= (sprite->size.x / 2);
    offsetY -= (sprite->size.y / 2);

    // Configure target location output sprite_t size, adjusting the latter for the constant sprite_t scaling factor.
    SDL_Rect destination  = {
        (origin.x + offsetX),
        (origin.y + offsetY),
        sprite->size.x,
        sprite->size.y
    };

    //Rotation
    SDL_Point rotateOrigin = { 0, 0 };
    if(angle > 0) {
        rotateOrigin.x = (int)sprite->size.x / 2;
        rotateOrigin.y = (int)sprite->size.y / 2;
    };

    SDL_RenderCopyEx(renderer, sprite->texture, NULL, &destination, angle, &rotateOrigin, sprite->flip);
}

void drawSprite(Sprite *sprite, Coord origin) {
    drawSpriteFull(sprite, origin, 1, 0);
}

void drawLine(int r, int g, int b, Coord start, Coord end) {
    SDL_SetRenderDrawColor(renderer, r, g, b, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawLine(renderer, start.x, start.y, end.x, end.y);
}

void initRenderer(void) {
    //Init SDL renderer
    renderer = SDL_CreateRenderer(
        window,
        -1,							            //insert at default index position for renderer list.
        SDL_RENDERER_TARGETTEXTURE          	//supports rendering to textures.
    );

    //TODO: We need some prose to describe the concepts at play here. Currently very confusing.

    //Set virtual screen size and pixel doubling ratio.
    screenBounds = makeCoord(BASE_SCALE_WIDTH, BASE_SCALE_HEIGHT);		//virtual screen size
    renderScale = PIXEL_SCALE;											//pixel doubling

    //Pixel grid is the blocky rendering grid we use to help tile things (i.e. backgrounds).
    pixelGrid = makeCoord(
        (double)BASE_SCALE_WIDTH / renderScale,
        (double)BASE_SCALE_HEIGHT / renderScale
    );

    //IMPORTANT: Make a texture which we render all contents to, then efficiently scale just this one
    // texture upon rendering. This creates a *massive* speedup. Thanks to: https://forums.libsdl.org/viewtopic.php?t=10567
    renderBuffer = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_RGB24,
        SDL_TEXTUREACCESS_TARGET,
        (int)pixelGrid.x,
        (int)pixelGrid.y
    );

    //Rachaie's background.
    SDL_RenderClear(renderer);

    SDL_SetRenderTarget(renderer, renderBuffer);
    assert(renderer != NULL);
}

void shutdownRenderer(void) {
    if(renderer == NULL) return;			//OK to call if not yet setup (thanks, encapsulation)

    SDL_DestroyRenderer(renderer);
    renderer = NULL;
}

void updateCanvas(void) {
    //Change rendering target to window.
    SDL_SetRenderTarget(renderer, NULL);

    //Activate scaler, and blit the buffer to the screen.
    SDL_RenderSetLogicalSize(renderer, pixelGrid.x, pixelGrid.y);
    SDL_RenderCopy(renderer, renderBuffer, NULL, NULL);

    //Actually update the screen itself.
    SDL_RenderPresent(renderer);

    //Reset render target back to texture buffer
    SDL_SetRenderTarget(renderer, renderBuffer);
}

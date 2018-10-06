#ifndef RENDERER_H
#define RENDERER_H

#include "mysdl.h"
#include "common.h"

typedef struct {
    SDL_Texture *texture;
    Coord offset;
    Coord size;
    SDL_RendererFlip flip;
} Sprite;

extern SDL_Renderer *renderer;
extern SDL_Texture *renderBuffer;
extern Coord screenBounds;
extern Coord pixelGrid;
extern Coord screenBounds;
extern void initRenderer();
extern void shutdownRenderer();
extern void updateCanvas();
extern Sprite* makeSprite__leaks(SDL_Texture*, Coord, SDL_RendererFlip);
extern void drawSpriteFull(Sprite*, Coord, double, double);
extern void drawSprite(Sprite*, Coord);
extern Coord getTextureSize(SDL_Texture*);
extern Sprite* makeFlippedSprite__leaks(char*, SDL_RendererFlip);
extern Sprite* makeSimpleSprite__leaks(char*);
extern void drawLine(int, int, int, Coord, Coord);

#endif

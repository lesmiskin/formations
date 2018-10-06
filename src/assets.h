#ifndef ASSETS_H
#define ASSETS_H

#include "mysdl.h"

typedef struct {
    char* key;
    SDL_Texture* texture;
} Asset;

typedef struct {
    char* key;
    Mix_Chunk* sound;
} SoundAsset;

extern void initAssets(void);
extern SDL_Texture* getTexture(char*);
extern Asset* getAsset(char*);
extern void play(char*);
extern SoundAsset getSound(char*);
extern void shutdownAssets();

#endif

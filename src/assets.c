#include <assert.h>
#include "assets.h"
#include "renderer.h"

typedef struct {
  char* filename;
} AssetDef;

typedef struct {
    char* filename;
    int volume;
} SoundDef;

static Asset *assets;
static int assetCount;
static SoundAsset *sounds;
static int soundCount;

static Asset* makeAsset__leaks(AssetDef *definition) {
    assert(renderer != NULL);

    //Infer asset path from current directory.
    char* workingPath = SDL_GetBasePath();
    char assetsFolder[] = "assets/";
    char *assetPath = combineStrings__leaks(workingPath, assetsFolder);
    if(!assetPath) printf("[%s:%d] leaky function failed to allocate",__FILE__,__LINE__);

    char *absPath = combineStrings__leaks(assetPath, definition->filename);
    if(!absPath) printf("[%s:%d] leaky function failed to allocate",__FILE__,__LINE__);
    if(!fileExists(absPath)) fatalError("Could not find Asset on disk", absPath);

    //Load file from disk, build texture, and assign.
    SDL_Surface *original = IMG_Load(absPath);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, original);
    Asset *asset = malloc(sizeof(Asset));
    asset->key = definition->filename;
    asset->texture = texture;

    //Free up RAM used for original surface object.
    free(assetPath);
    free(absPath);
    free(original);

    return asset;
}

static void loadImages(void) {
    //Define assets to be loaded.
    AssetDef definitions[] = {
        { "dirt.png" },
        { "stone.png" },
        { "water.png" },
        { "grass.png" },

        { "coffin-open.png" },
        { "coffin-closed.png" },
        { "grave.png" },
        { "gravestone.png" },
        { "gravestone-cross.png" },
        { "gravestone-cross-grass.png" },

        { "digger-walk-01.png" },
        { "digger-walk-02.png" },
        { "digger-walk-03.png" },
        { "digger-walk-04.png" },

        { "dracula-walk-01.png" },
        { "dracula-walk-02.png" },
        { "dracula-walk-03.png" },
        { "dracula-walk-04.png" },
        { "dracula-walk-up-01.png" },
        { "dracula-walk-up-02.png" },
        { "dracula-walk-up-03.png" },
        { "dracula-walk-up-04.png" },
        { "dracula-walk-down-01.png" },
        { "dracula-walk-down-02.png" },
        { "dracula-walk-down-03.png" },
        { "dracula-walk-down-04.png" },

        { "werewolf-walk-01.png" },
        { "werewolf-walk-02.png" },
        { "werewolf-walk-03.png" },
        { "werewolf-walk-04.png" },
        { "werewolf-walk-up-01.png" },
        { "werewolf-walk-up-02.png" },
        { "werewolf-walk-up-03.png" },
        { "werewolf-walk-up-04.png" },
        { "werewolf-walk-down-01.png" },
        { "werewolf-walk-down-02.png" },
        { "werewolf-walk-down-03.png" },
        { "werewolf-walk-down-04.png" },

        { "cthulu-walk-01.png" },
        { "cthulu-walk-02.png" },
        { "cthulu-walk-03.png" },
        { "cthulu-walk-04.png" },

        { "player-walk-01.png" },
        { "player-walk-02.png" },
        { "player-walk-03.png" },
        { "player-walk-04.png" },
        { "player-walk-05.png" },
        { "player-walk-06.png" },
        { "player-walk-07.png" },
        { "player-walk-08.png" },

        { "player-walk-sword-01.png" },
        { "player-walk-sword-02.png" },
        { "player-walk-sword-03.png" },
        { "player-walk-sword-04.png" },

        { "font-00.png" },
        { "font-01.png" },
        { "font-02.png" },
        { "font-03.png" },
        { "font-04.png" },
        { "font-05.png" },
        { "font-06.png" },
        { "font-07.png" },
        { "font-08.png" },
        { "font-09.png" },

        { "font-a.png" },
        { "font-b.png" },
        { "font-c.png" },
        { "font-d.png" },
        { "font-e.png" },
        { "font-f.png" },
        { "font-g.png" },
        { "font-h.png" },
        { "font-i.png" },
        { "font-j.png" },
        { "font-k.png" },
        { "font-l.png" },
        { "font-m.png" },
        { "font-n.png" },
        { "font-o.png" },
        { "font-p.png" },
        { "font-q.png" },
        { "font-r.png" },
        { "font-s.png" },
        { "font-t.png" },
        { "font-u.png" },
        { "font-v.png" },
        { "font-w.png" },
        { "font-x.png" },
        { "font-y.png" },
        { "font-z.png" },
        { "font-bang.png" },
    };

    //Allocate memory to Asset register.
    assetCount = sizeof(definitions) / sizeof(AssetDef);
    assets = malloc(sizeof(Asset) * assetCount);

    //Build and load each Asset into the register.
    for(int i=0; i < assetCount; i++) {
        Asset *asset = makeAsset__leaks(&definitions[i]);
        assets[i] = *asset;
        free(asset);
    }
}

static void loadSounds(void) {
    const int SOUND_VOLUME = 12;

    SoundDef defs[] = {
//        { "bell.wav", SOUND_VOLUME }
    };

    soundCount = sizeof(defs) / sizeof(SoundDef);
    sounds = malloc(sizeof(SoundAsset) * soundCount);

    //Infer asset path from current directory.
    char* workingPath = SDL_GetBasePath();
    char assetsFolder[] = "assets/";
    char *assetPath = combineStrings__leaks(workingPath, assetsFolder);
    if(!assetPath) printf("[%s:%d] leaky function failed to allocate",__FILE__,__LINE__);

    for(int i=0; i < soundCount; i++) {
        //Load music.
        char *path = combineStrings__leaks(assetPath, defs[i].filename);
        if(!path) printf("[%s:%d] leaky function failed to allocate",__FILE__,__LINE__);
        Mix_Chunk* chunk = Mix_LoadWAV(path);
        if(!chunk) fatalError("Could not find Asset on disk", path);
        free(path);

        //Reduce volume if called for.
        if(defs[i].volume < SDL_MIX_MAXVOLUME) Mix_VolumeChunk(chunk, defs[i].volume);

        //Add to register
        SoundAsset snd = {
            defs[i].filename,
            chunk
        };
        sounds[i] = snd;
    }

    free(assetPath);
}

void initAssets(void) {
    loadImages();
    loadSounds();
}

void play(char* path) {
    Mix_PlayChannel(-1, getSound(path).sound, 0);
}

SDL_Texture* getTexture(char *path) {
    return getAsset(path)->texture;
}

SoundAsset getSound(char *path) {
    //Loop through register until key is found, or we've exhausted the array's iteration.
    for(int i=0; i < soundCount; i++) {
        if(strcmp(sounds[i].key, path) == 0)			//if strings match.
            return sounds[i];
    }
    fatalError("Could not find Asset in register", path);
}

Asset* getAsset(char *path) {
    //Loop through register until key is found, or we've exhausted the array's iteration.
    for(int i=0; i < assetCount; i++) {
        if(strcmp(assets[i].key, path) == 0)			//if strings match.
            return &assets[i];
    }
    fatalError("Could not find Asset in register", path);
}

void shutdownAssets(void) {
    for(int i=0;i<assetCount;i++) free(&assets[i]);
    for(int i=0; i < soundCount; i++) Mix_FreeChunk(sounds[i].sound);
}

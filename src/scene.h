#ifndef SCENE_H
#define SCENE_H

#include <stdbool.h>
#include "common.h"
#include "renderer.h"

#define MAX_PROPS 4

typedef enum {
	PROP_GRAVESTONE ,
	PROP_GRAVESTONE_CROSS,
//	PROP_GRAVE =1,
	PROP_COFFIN
} PropType;

typedef struct {
	PropType type;
	Coord coord;
	bool coffinOpened;
} Prop;

typedef struct {
  Coord size;
  int tileSize;
  Sprite *ground;
  Prop *props;
} Scene;

extern Scene *scene;
extern void sceneRenderFrame(Scene*);
extern void sceneAnimateFrame(Scene*);
extern void sceneGameFrame(Scene*);
extern void initScene();

extern Coord makeSafeCoord(Scene*, double);

#endif

#ifndef COMMON_H
#define COMMON_H

#include <stdbool.h>
#include "mysdl.h"

typedef struct {
  double x, y;
} Coord;

typedef enum {
	MODE_GAME,
} GameMode;

typedef struct {
	double x, y;
	int width, height;
} Rect;

extern double calcDistance(Coord, Coord);
extern double degToRad(double);
extern double radToDeg(double);
extern Rect makeRect(double, double, double, double);
extern Rect makeBounds(Coord, double, double);
extern Rect makeSquareBounds(Coord, double);
extern bool inBounds(Coord, Rect);
extern bool rectInBounds(Rect, Rect);
extern GameMode currentMode;
extern void changeMode(GameMode);
extern SDL_Window *window;
extern bool running;
extern Coord makeCoord(double x, double y);
extern Coord makeSafeCoord(double);
extern Coord mergeCoord(Coord original, Coord derive);
extern Coord deriveCoord(Coord original, double xOffset, double yOffset);
extern Coord zeroCoord();
extern bool timer(long *lastTime, double hertz);
extern bool isDue(long now, long lastTime, double hertz);
extern void fatalError(const char *title, const char *message);
extern void quit(void);
extern char *combineStrings(const char *a, const char *b);
extern bool fileExists(const char *path);
extern int randomMq(int min, int max);
extern double sineInc(double offset, double *sineInc, double speed, double magnitude);
extern double cosInc(double offset, double *sineInc, double speed, double magnitude);
extern double getAngle(Coord a, Coord b);
extern Coord getStep(Coord a, Coord b, double speed);
extern Coord makeStep(double angle, double speed);
extern bool chance(int probability);

#endif

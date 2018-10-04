#include "common.h"
#include <stdbool.h>
#include <time.h>
#include <unistd.h>
#include "enemy.h"
#include "scene.h"
#include "player.h"
#include "assets.h"

#define M_PI 3.14159265358979323846264338327950288
static const double RADIAN_CIRCLE = 2 * M_PI;

GameMode currentMode = MODE_GAME;

double degToRad(double deg) {
	return deg * M_PI / 180.0;
}

double radToDeg(double rad) {
	return rad * 180 / M_PI;
}

void changeMode(GameMode newMode) {
	currentMode = newMode;
}

double calcDistance(Coord a, Coord b) {
    double xDist = a.x - b.x;
    double yDist = a.y - b.y;
    return sqrt(pow(xDist, 2) + pow(yDist, 2));
}

long ticsToMilliseconds(long tics) {
    //we want the duration version of the platform-independent seconds, so we / 1000.
    long platformAgnosticMilliseconds = CLOCKS_PER_SEC / 1000;

    return tics / platformAgnosticMilliseconds;
}

bool isDue(long now, long lastTime, double hertz) {
    long timeSinceLast = ticsToMilliseconds(now - lastTime);
    return timeSinceLast >= hertz;
}

bool timer(long *lastTime, double hertz){
    long now = clock();
    if(isDue(now, *lastTime, hertz)) {
        *lastTime = now;
        return true;
    }else{
        return false;
    }
}

void fatalError(const char *title, const char *message) {
    SDL_ShowSimpleMessageBox(
        SDL_MESSAGEBOX_ERROR,
        title,
        message,
        window
    );
    SDL_Quit();
}

void quit(void) {
    running = false;
}

char *combineStrings(const char *a, const char *b) {
    //Allocate exact amount of space necessary to hold the two strings.
    char *result = malloc(strlen(a) + strlen(b) + 1);		//+1 for the zero-terminator
    strcpy(result, a);
    strcat(result, b);

    return result;
}

bool fileExists(const char *path) {
    return access(path, R_OK ) == 0;
}

Coord zeroCoord() {
	return makeCoord(0,0);
}

Coord makeCoord(double x, double y) {
    Coord coord = { x, y };
    return coord;
}

Coord makeSafeCoord(double size) {
	Coord coord;
	bool safe = false;
	while(!safe) {
		safe = true;
		coord = makeCoord(randomMq(0, screenBounds.x),randomMq(0, screenBounds.y));
		Rect bounds = makeSquareBounds(coord, size);

		// dont spawn on the player
		if(rectInBounds(bounds,makeSquareBounds(plr->pos,PC_BOUNDS))) { safe = false; }
		if(!safe) continue;

		// dont spawn on the squad
		for(int i=0;i<plr->squad->size;i++) {
			if(rectInBounds(bounds,makeSquareBounds(plr->squad->members[i].coord,CHAR_BOUNDS))) { safe = false; break; }
		}
		if(!safe) continue;

		// dont spawn on an enemy
		for(int i=0;i<MAX_ENEMY;i++) {
			if(rectInBounds(bounds,makeSquareBounds(enemies[i].coord,CHAR_BOUNDS))) { safe = false; break; }
		}
		if(!safe) continue;
	}
	return coord;
}

double sineInc(double offset, double *sineInc, double speed, double magnitude) {
    *sineInc = *sineInc >= RADIAN_CIRCLE ? 0 : *sineInc + speed;

    double sineOffset = (sin(*sineInc) * magnitude);
    return offset - sineOffset;
}

double cosInc(double offset, double *sineInc, double speed, double magnitude) {
    *sineInc = *sineInc >= RADIAN_CIRCLE ? 0 : *sineInc + speed;

    double sineOffset = (cos(*sineInc) * magnitude);
    return offset - sineOffset;
}

int randomMq(int min, int max) {
    return (rand() % (max + 1 - min)) + min;
}

double getAngle(Coord a, Coord b) {
    return atan2(b.y - a.y, b.x - a.x);
}

Coord getStep(Coord a, Coord b, double speed) {
	if(abs(a.x-b.x)<.001 && abs(a.y-b.y)<.001) return zeroCoord(); // shortcut at goal
	double angle = getAngle(a, b);
	Coord step = makeCoord(
					(cos(angle) * speed),
					(sin(angle) * speed)
	);
	// partial step if close to goal
	if(abs(a.x-b.x)<abs(step.x)) { step.x = b.x-a.x; }
	if(abs(a.y-b.y)<abs(step.y)) { step.y = b.y-a.y; }

  return step;
}

bool chance(int probability) {
    //Shortcuts for deterministic scenarios (impossible and always)
    if(probability == 0) return false;
    if (probability == 100) return true;
    int roll = randomMq(0, 100);			//dice roll up to 100 (to match with a percentage-based probability amount)
    return probability >= roll;			//e.g. 99% is higher than a roll of 5, 50, and 75.
}

bool rectInBounds(Rect a, Rect b) {
	return inBounds(makeCoord(a.x+a.width,a.y), b)  || inBounds(makeCoord(a.x,a.y), b) ||
				 inBounds(makeCoord(a.x,a.y+a.height), b) || inBounds(makeCoord(a.x+a.width,a.y+a.height), b) ||
 			 	 inBounds(makeCoord(b.x+b.width,b.y), a)  || inBounds(makeCoord(b.x,b.y), a) ||
 				 inBounds(makeCoord(b.x,b.y+b.height), a) || inBounds(makeCoord(b.x+b.width,b.y+b.height), a);
}

bool inBounds(Coord point, Rect area) {
  return point.x >= area.x && point.x <= area.x+area.width &&
         point.y >= area.y && point.y <= area.y+area.height;
}

Rect makeBounds(Coord origin, double width, double height) {
	Rect bounds = {
    origin.x - (width / 2),
    origin.y - (height / 2),
    width,
		height
  };
  return bounds;
}

Rect makeSquareBounds(Coord origin, double size) {
  return makeBounds(origin, size, size);
}

Coord mergeCoord(Coord original, Coord derive) {
  original.x += derive.x;
  original.y += derive.y;
  return original;
}

Coord deriveCoord(Coord original, double xOffset, double yOffset) {
  original.x += xOffset;
  original.y += yOffset;
  return original;
}

Rect makeRect(double x, double y, double width, double height) {
  Rect rect = { x, y, width, height };
  return rect;
}

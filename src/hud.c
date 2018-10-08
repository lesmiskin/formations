#include <assert.h>
#include <stdlib.h>
#include "hud.h"
#include "renderer.h"
#include "time.h"
#include "scene.h"
#include "enemy.h"
#include "player.h"

static Sprite letters[10];
static const int LETTER_WIDTH = 4;

int fps = 0;

void initHud(void) {
	//Pre-load font sprites.
	for(int i=0; i < 10; i++) {
		char textureName[50];
		sprintf(textureName, "font-%02d.png", i);
		Sprite *sprite = makeSimpleSprite__leaks(textureName);
		assert(sprite);
		letters[i] = *sprite;
		free(sprite);
	}
}

void writeText(int amount, Coord pos, bool alignRight) {
	char buf[11];
	sprintf(buf,"%d",amount);
	for(int c=0; c<strlen(buf); c++) {
		int i = alignRight ? strlen(buf)-(c+1) : c;

		char digit[2];
		sprintf(digit, "%c", buf[i]);

		if(alignRight) pos.x -= LETTER_WIDTH;
		drawSprite(&letters[atoi(digit)], pos);
		if(!alignRight) pos.x += LETTER_WIDTH;
	}
}

void writeFont(char *text, Coord pos, bool alignRight) {
	for(int c=0; c<strlen(text); c++) {
		int i = alignRight ? strlen(text)-(c+1) : c;

		char fontFile[50];
		if(text[i] == '!') {
			sprintf(fontFile, "font-bang.png");
		}else{
			sprintf(fontFile, "font-%c.png", text[i]);
		}

		//Print text if it's not a space.
		Sprite *sprite;
		if(text[i] != ' ') sprite = makeSimpleSprite__leaks(fontFile);

		int size;
		if(text[i] == 'q') {
			size = 4;
		} else if(text[i] == 'w' || text[i] == 'm') {
			size = 5;
		} else if(text[i] == 'o') {
			size = 5;
		} else if(text[i] == 'u') {
			size = 5;
		} else if(text[i] == 'i' || text[i] == 'e') {
			size = 3;
		} else if(text[i] == ' ') {
			size = 2;
		} else {
			size = (sprite->size.x - 1);
		}

		if(alignRight) pos.x -= size;
		if(sprite) { drawSprite(sprite, pos); free(sprite); }
		if(!alignRight) pos.x += size;
	}
}

void hudGameFrame(void) {
}

void hudRenderFrame(void) {
	if(showHomingLines) {
		writeFont("fps", makeCoord(385,10), true); writeText(fps, makeCoord(390, 10), false);
	}
	writeFont("health", makeCoord(25, 10), true); writeText(plr->health, makeCoord(30, 10), false);
}

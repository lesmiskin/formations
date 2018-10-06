
#include "hud.h"
#include "renderer.h"
#include "time.h"
#include "scene.h"
#include "enemy.h"
#include "player.h"

static Sprite letters[10];
static const int LETTER_WIDTH = 4;

void initHud(void) {
	//Pre-load font sprites.
	for(int i=0; i < 10; i++) {
		char textureName[50];
		sprintf(textureName, "font-%02d.png", i);
		Sprite *sprite = makeSimpleSprite__leaks(textureName);
		if(!sprite) printf("[%s:%d] leaky function failed to allocate",__FILE__,__LINE__);
		letters[i] = *sprite;
		free(sprite);
	}
}

void writeText(int amount, Coord pos) {
	if(amount == 0) {
		drawSprite(&letters[0], pos);
	}else{
		while(amount != 0) {
			drawSprite(&letters[amount % 10], pos);
			amount /= 10;
			pos.x -= LETTER_WIDTH;
		}
	}
}

void writeFont(char *text, Coord pos) {
	for(int i=0; i < strlen(text); i++) {
		//Print text if it's not a space.
		if(text[i] != ' ') {

			char fontFile[50];

			if(text[i] == '!') {
				sprintf(fontFile, "font-bang.png");
			}else{
				sprintf(fontFile, "font-%c.png", text[i]);
			}

			Sprite* sprite = makeSimpleSprite__leaks(fontFile);
			drawSprite(sprite, makeCoord(pos.x, pos.y));

			if(text[i] == 'q') {
				pos.x += 4;
			}else if(text[i] == 'w' || text[i] == 'm') {
				pos.x += 5;
			}else if(text[i] == 'o') {
				pos.x += 5;
			}else if(text[i] == 'u') {
				pos.x += 5;
			}else if(text[i] == 'i' || text[i] == 'e') {
				pos.x += 3;
			}else{
				pos.x += sprite->size.x - 1;
			}
			free(sprite);
		}else{
			pos.x += 2;
		}
	}
}

void hudGameFrame(void) {
}

void hudRenderFrame(void) {
	// writeText(plr->health, makeCoord(50, 10));
	// writeFont("health", makeCoord(10, 10));
}

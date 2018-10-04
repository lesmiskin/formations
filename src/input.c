#include <stdbool.h>

#include "common.h"
#include "input.h"
#include "enemy.h"
#include "player.h"
#include "scene.h"

#define MAX_COMMANDS 20

static bool commands[MAX_COMMANDS];

void reinitGame() {
  initScene();
  initEnemy();
  initPlayer();
}

void toggleDevMode() {
  showHomingLines = !showHomingLines;
}

bool checkCommand(int commandFlag) {
    return commands[commandFlag];
}

void pollInput(void) {
    SDL_PumpEvents();
    const Uint8 *keysHeld = SDL_GetKeyboardState(NULL);

    //We're on a new frame, so clear all previous checkCommand (not key) states (i.e. set to false)
    memset(commands, 0, sizeof(commands));

    //Respond to SDL events, or key presses (not holds)
    SDL_Event event;
    while(SDL_PollEvent(&event) != 0) {
		switch (event.type) {
			case SDL_QUIT:
				commands[CMD_QUIT] = true;
				break;
				//Presses
			case SDL_KEYDOWN: {
				//Ignore held keys.
				if (event.key.repeat) break;

				SDL_Keycode keypress = event.key.keysym.scancode;

				if (keypress == SDL_SCANCODE_ESCAPE)  commands[CMD_QUIT] = true;
				if (keypress == SDL_SCANCODE_F5)      commands[CMD_REINIT] = true;
        if (keypress == SDL_SCANCODE_F10)     commands[CMD_DEV_MODE] = true;
        if (keypress == SDL_SCANCODE_F1)      commands[CMD_FORMATION_1] = true;
        if (keypress == SDL_SCANCODE_F2)      commands[CMD_FORMATION_2] = true;
        if (keypress == SDL_SCANCODE_F3)      commands[CMD_FORMATION_3] = true;
        if (keypress == SDL_SCANCODE_F4)      commands[CMD_FORMATION_4] = true;
			}
		}
	}

  if (keysHeld[SDL_SCANCODE_Q]) commands[CMD_ROTATE_FORM_CCW] = true;
  if (keysHeld[SDL_SCANCODE_E]) commands[CMD_ROTATE_FORM_CW] = true;

	if(keysHeld[SDL_SCANCODE_A]) commands[CMD_PLAYER_LEFT] = true;
	if(keysHeld[SDL_SCANCODE_D]) commands[CMD_PLAYER_RIGHT] = true;
	if(keysHeld[SDL_SCANCODE_W]) commands[CMD_PLAYER_UP] = true;
	if(keysHeld[SDL_SCANCODE_S]) commands[CMD_PLAYER_DOWN] = true;
}

void processSystemCommands(void) {
    if(checkCommand(CMD_QUIT)) quit();
    if(checkCommand(CMD_DEV_MODE)) toggleDevMode();
    if(checkCommand(CMD_REINIT)) reinitGame();
    if(checkCommand(CMD_FORMATION_1)) plr->formation = 1;
    if(checkCommand(CMD_FORMATION_2)) plr->formation = 2;
    if(checkCommand(CMD_FORMATION_3)) plr->formation = 3;
    if(checkCommand(CMD_FORMATION_4)) plr->formation = 3;
}

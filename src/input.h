#ifndef INPUT_H
#define INPUT_H

extern void pollInput(void);
extern void processSystemCommands(void);
extern bool checkCommand(int commandFlag);

typedef enum {
  CMD_QUIT = 0,
	CMD_PLAYER_LEFT = 5,
	CMD_PLAYER_RIGHT = 6,
	CMD_PLAYER_DOWN = 7,
	CMD_PLAYER_UP = 8,
  CMD_FORMATION_1 = 10,
  CMD_FORMATION_2 = 11,
  CMD_FORMATION_3 = 12,
  CMD_FORMATION_4 = 13
} Command;

#endif

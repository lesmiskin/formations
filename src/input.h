#ifndef INPUT_H
#define INPUT_H

extern void pollInput(void);
extern void processSystemCommands(void);
extern bool checkCommand(int commandFlag);

typedef enum {
  CMD_QUIT,
	CMD_PLAYER_LEFT,
	CMD_PLAYER_RIGHT,
	CMD_PLAYER_DOWN,
	CMD_PLAYER_UP,
  CMD_FORMATION_1,
  CMD_FORMATION_2,
  CMD_FORMATION_3,
  CMD_FORMATION_4,
  CMD_ROTATE_FORM_CCW,
  CMD_ROTATE_FORM_CW,
  CMD_REINIT,
  CMD_DEV_MODE,
} Command;

#endif

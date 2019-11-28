
#ifndef LBG_GLOBAL
#define LBG_GLOBAL

typedef struct _Command {
	char *cmd;
	struct _Command *before;
	struct _Command *next;
} Command;

void InitCommandList();

void AddCommand(char *cmd);

#endif // !LBG_GLOBAL


/**
* Team : SOJOS
* parse for parsing the given lines of input to shell.
*/

#ifndef PARSE_H
#define PARSE_H

#define LS 0
#define GREP 1
#define CD 2
#define PWD 3
#define LSB 4
#define EXIT 5

//TODO function headers have to be added.
typedef struct Cmd_{
	char* ex;    //actual command
	char** arg_list; 	//list of all flags
	int BG;			//background process flag
	char* filein;		//file in
	char* fileout;		//file out
}Cmd;

typedef struct proc_{
	Cmd** cmds;
	int nocmd;
}proc;

//Gets the prompt of shell.
char* getPrompt();

//Executes in the background.
int execFg(char *ex,char **args);

proc** parsecmd(char * cmd);

void* fill_proc(proc* p);

#endif

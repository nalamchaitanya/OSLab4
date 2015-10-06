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
	int filein;		//file in
	int fileout;		//file out
}Cmd;

//Gets the prompt of shell.
char* getPrompt();

typedef struct proc_{
	Cmd** cmds;
	int nocmd;
}proc;

//Executes in the background.
int execBg(char *ex,char **args);

proc** parsecmd(char * cmd);

void* fill_proc(proc* p);

#endif

/**
* Team : SOJOS
* parse for parsing the given lines of input to shell.
*/

#ifndef PARSE_H
#define PARSE_H

//TODO function headers have to be added.
typedef struct Cmd_{
	char* ex;    //actual command
	char** arg_list; 	//list of all flags  
	int BG;			//background process flag
	char* filein;		//file in
	char* fileout;		//file out
}Cmd;
//Gets the prompt of shell.
char* getPrompt();
typedef struct proc_{
	Cmd** cmds;
	int nocmd;
}proc;


proc** parsecmd(char * cmd);
void* fill_proc(proc* p);
#endif

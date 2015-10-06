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

//Gets the prompt of shell.
char* getPrompt();

//Executes in the background.
int execBg(char *ex,char **args);

#endif

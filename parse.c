/**
* Team : SOJOS
* parse for parsing the given lines of input to shell.
*/

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "parse.h"

//Gets the prompt of shell.
char* getPrompt()
{
	int sz =100;
	char *prompt = (char*)malloc(sizeof(char)*sz);
	strcat(prompt,getlogin());
	strcat(prompt,"@[");
	char *buf=(char*)malloc(sizeof(char)*sz);
	while(1)
	{
		errno=0;
		getcwd(buf,sz);
		if(errno==ERANGE)
		{
			sz=sz+100;
		}
		else
			break;
	}
	strcat(prompt,buf);
	strcat(prompt,"]");
	return prompt;
 }

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "parse.h"

int main()
{
	char *prompt;
	char *line;
	// TODO write the prompt function in the .h and .c files.
	while(1)
	{
		prompt = getPrompt();
		// should be done before every loop because command may change cwd.
		printf("%s $",prompt);
		
		// TODO take the line from the input stream and process it.
		//getline(&line,);
		// TODO do the processing of the input and exec the code.
		//execute(line);
		char*s=malloc(sizeof(char)*100);
		gets(s);
		proc** p=parsecmd(s);
		//printf("%d\n",p[0]->nocmd);
		//printf("%s\n",p[0]->cmds[0]->arg_list[0]);
		break;
	}
	return 0;
}

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
	char **cmd=(char**)malloc(sizeof(char*)*1);
	*cmd =(char*)malloc(sizeof(char)*30);
	int *n=(int*)malloc(sizeof(int));
	*n=10;

	while(1)
	{
		// should be done before every loop because command may change cwd.
		prompt = getPrompt();
		printf("%s $",prompt);

		// TODO take the line from the input stream and process it.
		getline(cmd,(size_t*)n,stdin);
		char **arg =(char**)malloc(sizeof(char*)*10);
		*cmd=strndup(*cmd,strlen(*cmd)-1);
		arg[0]=*cmd;
		//arg[1]="-l";

		switch (fork())
		{
			case -1:
				printf("Fork failed.\n");
				break;
			case 0:
				execvp(*cmd,arg);
			default:
				wait();
		}
		// TODO do the processing of the input and exec the code.
	}
	return 0;
}

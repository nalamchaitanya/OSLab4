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
		*cmd=strndup(*cmd,strlen(*cmd)-1);
		printf("%s\n",*cmd );
		proc** p=parsecmd(*cmd);

		switch (fork())
		{
			case -1:
				printf("Fork failed.\n");
				break;
			case 0:
				printf("%s %s\n",p[0]->cmds[0]->ex,p[0]->cmds[0]->arg_list[0]);
				execvp(p[0]->cmds[0]->ex,p[0]->cmds[0]->arg_list);
				printf("ERROR\n");
			default:
				wait();
		}
		// TODO do the processing of the input and exec the code.
	}
	return 0;
}

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "parse.h"

int* pids;
proc** Bcmds;
int noBgs;

int main()
{
	char *prompt;
	char *line;
	char **cmd=(char**)malloc(sizeof(char*)*1);
	*cmd =(char*)malloc(sizeof(char)*30);
	int *n=(int*)malloc(sizeof(int));
	*n=10;
	pids=(int*)malloc(sizeof(int)*100);
	Bcmds=(Cmd**)malloc(sizeof(Cmd*)*100);
	noBgs=0;
	while(1)
	{
		// should be done before every loop because command may change cwd.
		prompt = getPrompt();
		printf("%s $",prompt);

		// TODO take the line from the input stream and process it.
		getline(cmd,(size_t*)n,stdin);

		proc** p=parsecmd(*cmd);

		int i;
		i =0;
		while(p[i]!=NULL)
		{
			execute(p[i]);
			i++;
		}
		// TODO do the processing of the input and exec the code.

	}
	return 0;
}

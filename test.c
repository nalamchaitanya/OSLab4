#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int main()
{
	int pid;
	pid=fork();
	if(pid==0)
	{
		printf("In Child process,%d\n",pid);
	}
	else
	{
		int st;
		printf("In Parent process with %d\n",pid );
		pid=wait(&st);
		printf("%d,%d\n",st,pid );
	}
	printf("%s\n",getlogin() );
	int t;
	t=1;
	char *buf =(char*)malloc(sizeof(char)*t);
	printf("%d here in this\n",pid );
	while(1)
	{
		errno=0;
		getcwd(buf,t);
		if(errno==ERANGE)
		{
			t=t+5;
			printf("hi,%d,%s\n",t,buf );
		}
		else
			break;
	}
	printf("%s\n",buf );
}

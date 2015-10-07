#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	// int pid;
	// pid=0;
	// //pid=fork();
	// if(pid==0)
	// {
	// 	printf("In Child process,%d\n",pid);
	// }
	// else
	// {
	// 	int st;
	// 	printf("In Parent process with %d\n",pid );
	// 	pid=wait(&st);
	// 	printf("%d,%d\n",st,pid );
	// }
	// printf("%s\n",getlogin() );
	// int t;
	// t=1;
	// char *buf =(char*)malloc(sizeof(char)*t);
	// printf("%d here in this\n",pid );
	// while(1)
	// {
	// 	errno=0;
	// 	getcwd(buf,t);
	// 	if(errno==ERANGE)
	// 	{
	// 		t=t+5;
	// 		printf("hi,%d,%s\n",t,buf );
	// 	}
	// 	else
	// 		break;
	// }
	// printf("%s\n",buf );
	//
	// //strcat(buf,"/..");
	// // int k=chdir("..");
	// // printf("%d%s\n",k,buf );
	//
	// char **get;
	// int *ft;
	// char **arg =(char**)malloc(sizeof(char*)*10);
	// arg[0]="ls";
	// arg[1]="-l";
	// switch (fork())
	// {
	// 	case -1:
	// 		break;
	// 	case 0:
	// 		execv("/bin/ls",arg);
	// 	default:
	// 		//printf("%s\n",arg[0] );
	// 		get=(char**)malloc(sizeof(char*)*1);
	// 		*get =(char*)malloc(sizeof(char)*10);
	// 		ft=(int*)malloc(sizeof(int));
	// 		*ft=10;
	// 		getline(get,(size_t*)ft,stdin);
	// 		printf("%d\n",*ft );
	// 		puts(*get);
	//
	// 		int fid;
	// 		dup2(1,3);
	// 		FILE *fq=fdopen(3,"w");
	// 		FILE* fp = freopen("hello.txt","w",fq);
	// 		printf("Hello\n" );
	// 		if(fp==NULL)
	// 			printf("HelloWorld\n");
	// }
	//
	int pip[2];
	pipe(pip);
	switch (fork())
	{
		case -1:
			return -1;
		case 0:
			close(pip[1]);
			dup2(pip[0],0);
			char* str=(char*)malloc(sizeof(char)*100);
			scanf("%s\n",str );
			close(pip[0]);
			printf("%s\n",str );
			printf("Hello\n" );
			break;
		default:
			close(pip[0]);
			dup2(pip[1],1);
			close(pip[1]);
			printf("HelloWorld\n" );
	}
	//
	// int i;
	// int ncmd = prc->nocmd;
	//
	// i=0;
	// int prev=0;
	// int next=1;
	// while(i<ncmd)
	// {
	// 	pipe(pip);
	// 	switch (fork())
	// 	{
	// 		case -1:
	// 			printf("fork failed\n");
	// 			return -1;
	// 		case 0:
	// 			dup2(pip[0],0);
	// 			close(pip[1]);
	// 			execvp(prc->cmds[i]->ex,prc->cmds[i]->arg_list);
	// 			return -1;
	// 		default:
	// 			close(pip[0]);
	// 			dup2(pip[1],1);
	// 	}
	// }
	// return 0;
}

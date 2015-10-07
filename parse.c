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

 proc** parsecmd(char * cmd){
 	int i=0;
 	proc** procs=(proc**)malloc(sizeof(proc*)*10);
 	int size=10;
 	int size1;
 	char* d=strtok(cmd,";");
 	char* d1;int j;
 	while(d!=NULL){
 	//	printf("%s\n",d);
 		if(i>=size){
 			realloc(procs,sizeof(proc*)*(size+5));
 			size=size+5;
 		}
 		procs[i]=(proc*)malloc(sizeof(proc));
 		procs[i]->cmds=(Cmd**)malloc(sizeof(Cmd*)*10);
 		procs[i]->cmds[0]=(Cmd*)malloc(sizeof(Cmd));
 		procs[i]->cmds[0]->ex=d;
 		d=strtok(NULL,";");
 		i++;
 			
 	}
 	for(j=0;j<i;j++){
 		char* d=procs[j]->cmds[0]->ex;
 		size1=10;
 		char* c=(char*)malloc(sizeof(char)*strlen(d));
 		strcpy(c,d);
 		d1=strtok(c,"|");
 		int s=0;
 		while(d1!=NULL){
 	//		printf("%s\n",d1);
 			if(s>=size1){
 				realloc(procs[j]->cmds,sizeof(Cmd*)*(size1+5));
 				size1=size1+5;
 			}
 			if(procs[j]->cmds[s]==NULL)
 				procs[j]->cmds[s]=(Cmd*)malloc(sizeof(Cmd));
  			procs[j]->cmds[s]->ex=d1;
 			d1=strtok(NULL,"|");
 			s++;
 		}
 		procs[j]->nocmd=s;
 		fill_proc(procs[j]);

 	}
 	return procs;
 }

void* fill_proc(proc* p){
	int i;
	char*d,*re;
	int flag=2,flag1=0;
	char** r;
	for(i=0;i<p->nocmd;i++){
		p->cmds[i]->BG=0;
		d=strtok(p->cmds[i]->ex," ");
		
		re=strtok(NULL,"\n");
		
		p->cmds[i]->arg_list=(char**)malloc(sizeof(char*)*10);
		if(d!=NULL){
			p->cmds[i]->ex=d;
			p->cmds[i]->arg_list[0]=d;
		}
		
		d=strtok(re," \n");
		int strindex;
		int s=1;
		while(d!=NULL){
			
			if(strcmp(d,"")!=0){
				
				if(flag==-1 && flag1==-1)
					yyerror(p->cmds[i]->ex,d);
				
				
				if(strcmp(d,">")==0){
					flag=1;
					d=strtok(NULL," ");
					p->cmds[i]->fileout=d;
					flag=0;
					flag1=-1;
					
				}
				else if(strcmp(d,">>")==0){
					flag=1;
					d=strtok(NULL," ");
					p->cmds[i]->fileout=d;
					flag=0;
					flag1=-1;
					
				}
					
				else if(*d=='&'){
					p->cmds[i]->BG=1;
					flag=-1;
					
				}
				else{
					if(*d=='"' && d[strlen(d)-1]=='"'){
						d=d+1;
						d[strlen(d)-1]='\0';
						strindex=s;
					}
					else if(*d=='\'' && d[strlen(d)-1]=='\''){
						d=d+1;
						d[strlen(d)-1]='\0';
					}
					p->cmds[i]->arg_list[s]=d;
					
					s++;
				}
				
			}
			d=strtok(NULL," \n");
		}
		p->cmds[i]->arg_list[s]=NULL;
		if(p->cmds[i]->BG==1){
			if(p->cmds[i]->fileout==NULL){
				char str[100];
				sprintf(str, "%s%d.bgoutput",p->cmds[i]->ex,i);
				p->cmds[i]->fileout=str;
			}
		}
		
		int j=0,k,c;
		r=p->cmds[i]->arg_list;
		char *mybigstr;
		
		
		while(r[j]!=NULL){
		
			if(strstr(r[j],"\"")!=NULL){
				mybigstr=malloc(sizeof(char)*100);
				strcpy(mybigstr,(r[j]+1));
				c=j;
				c++;
				while(strstr(r[c],"\"")==NULL){
					strcat(mybigstr," ");
					strcat(mybigstr,r[c]);
					c++;
				}
				k=strlen(r[c]);
				if(r[c][k-1]=='\"'){
					
					k=strlen(r[c]);
					r[c][k-1]='\0';
					strcat(mybigstr," ");
					strcat(mybigstr,r[c]);
				}
				r[j]=mybigstr;
				strindex=j;
				k=j+1;c++;
				while(r[c]!=NULL){
					r[k]=r[c];k++;c++;
				}
				r[k]=NULL;
			}
			j++;
		}
		r=p->cmds[i]->arg_list;
		char *mybigfile;
		j=0;
		
		if(p->cmds[i]->fileout==NULL){
			while(r[j]!=NULL ){
				if(j!=strindex){
					if(strstr(r[j],">>")!=NULL){
						
						if(r[j][0]=='>'){
							
							p->cmds[i]->fileout=(r[j]+2);
							c=j+1;k=j;
							while(r[c]!=NULL){
								r[k]=r[c];k++;c++;
							}
							r[k]=NULL;
						}
						else{
							r[j]=strtok(r[j],">");
							p->cmds[i]->fileout=strtok(NULL,">");
						}
						break;
					}
				}
				j++;
			}
		}
		j=0;
		if(p->cmds[i]->fileout==NULL){
			while(r[j]!=NULL ){
				if(j!=strindex){
					if(strstr(r[j],">")!=NULL){
						
						if(r[j][0]=='>'){
							
							p->cmds[i]->fileout=(r[j]+1);
							c=j+1;k=j;
							while(r[c]!=NULL){
								r[k]=r[c];k++;c++;
							}
							r[k]=NULL;
						}
						else{
							r[j]=strtok(r[j],">");
							p->cmds[i]->fileout=strtok(NULL,">");
						}
						break;
					}
				}
				j++;
			}
		}
		j=0;
		while(p->cmds[i]->arg_list[j]!=NULL){
			printf("%s\n", p->cmds[i]->arg_list[j]);
			j++;
		}
		if(p->cmds[i]->fileout!=NULL){
			printf("%s\n",p->cmds[i]->fileout);
		}
	}
	

}

yyerror(char* ex,char* flag){
	printf("%s",ex);
	if(flag!=NULL){
		printf(" -%s",flag);
	}
	printf("command not found\n");

}
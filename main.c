#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <math.h>
#include <string.h>
#include <sys/wait.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <fcntl.h>
#include <grp.h>
#include <pwd.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <math.h>
#include <string.h>
#include <sys/wait.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <fcntl.h>
#include <grp.h>
#include <pwd.h>
#include<sys/utsname.h>
#include<sys/wait.h>
#include<signal.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include<readline/readline.h>
#include<readline/history.h>
//header files used in code
#include"redirect.h"
#include"p.h"
#include"display.h"
#include"unbuilt.h"
#include"history.h"

#include"pinfo.h"
#include"ls.h"
#include"cdechopwd.h"
#include"user.h"
char history[20][300],arr2[5000];
int current=0;
char cure[255];
int forcomd3(char cwd[],char cur[])
{
	memset(cure,0,255);
	int i=0;
	while(i<strlen(cwd)&&cwd[i]==cur[i])
		i++;
	i++;
	int k=strlen(cwd),j=i;
	cure[0]='~';
	cure[1]='/';
	k=2;
	while(i<strlen(cur))
		cure[k++]=cur[i++];
	if(j-1==strlen(cwd))
		return 0;
	else
		return 1;

}
int main()
{
	signal (SIGINT, SIG_IGN);                                   
	signal (SIGTSTP, signal_handler);                                 
	signal (SIGQUIT, SIG_IGN);                                  
	signal (SIGTTIN, SIG_IGN);                                 
	signal (SIGTTOU, SIG_IGN);
	char arr[2355],cwd[255];
	char *s;
	char cur[255];	
	int   i=0;
	char temp,*ans; 
	struct utsname buffer;
	memset(cwd,0,255);
	getcwd(cwd,255);
	while(1)
	{

		if(signal(SIGTSTP,signal_handler)==SIG_ERR)
			perror("can't catch SIGTSTP!");
		else
		{
			strcpy(arr,"");
		}				
		if(signal(SIGINT,signal_handler)==SIG_ERR)
			perror("can't catch SIGINT!");
		else
		{
			strcpy(arr,"");
		}				
		memset(cur,0,255);
		getcwd(cur,255);
		if (uname(&buffer) != 0) 
			perror("uname");
		if(forcomd3(cwd,cur)==0)
			sprintf(arr2,"%s@%s:%s$",getenv("USER"),buffer.nodename,cure);
		else
			sprintf(arr2,"%s@%s:%s$",getenv("USER"),buffer.nodename,cur);
		//scanf("%[^\n]s",arr);
		//scanf("%c",&temp);
		s=readline(arr2);
		if(strlen(s)>0)
			add_history(s);
		strcpy(arr,s);
		if(strcmp(arr,"quit")==0)
			_exit(0);
		current=(current+1)%20;
		fflush(stdout);
		fflush(stdin);
		foreverything(arr,cwd); 
	}
	return 0;
}

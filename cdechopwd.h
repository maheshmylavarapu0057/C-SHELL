#include<string.h>
#include<unistd.h>
char cure[255],cur[255];
int builtinfunction(char input[][300],char cwd[])
{
	for(int i=0;i<10;i++)
		if(strcmp(input[i],"&")==0||strcmp(input[i],"<")==0||strcmp(input[i],">")==0||strcmp(input[i],">>")==0||strcmp(input[i],"|")==0)
			return 0;
	if(strcmp(input[0],"cd")==0)
	{
		if(strcmp(input[1],"..")==0)
			chdir("..");
		else if(strcmp(input[1],"~/")==0||strcmp(input[1],"~")==0)
			chdir(cwd);

		else if(strcmp(input[1],".")==0)
			return 1;

		else
		{
			memset(cur,0,255);
			getcwd(cur,255);
			if(input[1][0]=='~'&&input[1][1]=='/')
			{
				memset(cur,0,255);
				getcwd(cur,255);
				chdir(cwd);
				memset(cure,0,255);
				int j=0,k=2;
				while(j<strlen(input[1]))
					cure[j++]=input[1][k++];
				if(chdir(cure)!=0)
					printf("No such file or directory\n");
			}
			else
				if(chdir(input[1])!=0)
					printf("No such file or directory\n");
		}      
		return 1;
	}
	else if( strcmp(input[0],"echo")==0)
	{
		printf("%s\n",input[1]);
		return 1;
	}
	else if(strcmp(input[0],"pwd")==0)
	{
		memset(cur,0,255);
		getcwd(cur,255);
		printf("%s\n",cur);
		return 1;
	} 
	else if (strcmp(input[0],"ls")==0)
	{
	
		if(strcmp(input[1],"-a")==0)
		{
			if(input[2][0]==0)
				funlsprint(".");
			else if(strcmp(input[2],"-l")==0)
				{
	
				DIR *d;
			struct dirent *dir;
			memset(cur,0,255);
			getcwd(cur,255);     
			if(strcmp(input[3],"")==0)          
				d = opendir(cur);
			else
				d=opendir(input[3]);
			if (d)
			{
				while ((dir = readdir(d)) != NULL)
					lsfileminusl(dir->d_name);
			}
			else
			{
				printf("No such file or directory\n");
				return 0;
			}  


				}
			else
				funlsprint(input[2]);
		}
		else if(strcmp(input[1],"-l")==0)
		{
			DIR *d;
			struct dirent *dir;
			memset(cur,0,255);
			getcwd(cur,255);     
			if(strcmp(input[2],"")==0)          
				d = opendir(cur);
			else
				d=opendir(input[2]);
			if (d)
			{
				while ((dir = readdir(d)) != NULL)
					if(dir->d_name[0]!='.')
						lsfileminusl(dir->d_name);
			}
			else
			{
				printf("No such file or directory\n");
				return 0;
			}
		}
		else if(strcmp(input[1],"-al")==0||strcmp(input[1],"-la")==0)
		{
			DIR *d;
			struct dirent *dir;
			memset(cur,0,255);
			getcwd(cur,255);     
			if(strcmp(input[2],"")==0)          
				d = opendir(cur);
			else
				d=opendir(input[2]);
			if (d)
			{
				while ((dir = readdir(d)) != NULL)
					lsfileminusl(dir->d_name);
			}
			else
			{
				printf("No such file or directory\n");
				return 0;
			}  
		}
		else
		{
			if(strcmp(input[1],"")==0)
				funlsprint1(".");
			else
				funlsprint1(input[1]);
		}
		return 1;
	}
	else if(strcmp(input[0],"setenv")==0)
	{
		//printf("Hello");
		if(strcmp(input[3],"")!=0||strcmp(input[1],"")==0)
			{
				printf("error");
				return 0;
			}
		if(setenv(input[1],input[2],1) != 0)
		{
			perror("shell");
			return 0;
		}
		return 1;
	}
	else if(strcmp(input[0],"unsetenv")==0)
	{
		if(strcmp(input[3],"")!=0||strcmp(input[1],"")==0)
			{
				printf("error");
				return 0;
			}
		if(unsetenv(input[1]) != 0)
		{
			perror("shell");
			return 0;
		}
		return 1;
	}
	else if (strcmp(input[0],"pinfo")==0)
		return pinfoprinting(input,cwd);
	else if (strcmp(input[0],"history")==0)
		return historyprinting(input);
	return 0;
}

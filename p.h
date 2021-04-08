char *command[256];
char args[10][300];
/********************************** For input output redirection ***************************/
int open_outfile(char outfile[],int last) 
{
	int f=-1;
	if(last == 2) 
		f = open(outfile, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
	else  if(last == 1) 
		f = open(outfile, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	if(f < 0)
	{
		perror(outfile);
	}
	return f;
}
int  functionforpipe(int number,char arg[][300])
{
	pid_t pid;
	int filedes[2],filedes2[2],num_cmds,end,i,j,k,l=0,input=0;
	num_cmds=number;
	num_cmds++;
	int all=1,a2=0,a3=-1;
	for(i=0;i<10;i++)
	{
		if(strcmp(arg[i],">")==0)
		{
			a2=open_outfile(arg[i+1],1);
			break;
		}
		else if(strcmp(arg[i],">>")==0)
		{
			a2=open_outfile(arg[i+1],2);
			break;
		}
		if(strcmp(arg[i],"<")!=0)
		strcpy(args[l++],arg[i]);
	}
	i=j=k=l=end=0;
	int fi=0;
	for ( ;strcmp(args[j],"")!=0 && end != 1 ; i++)
	{
		input=k = 0;
		for( ;strcmp(args[j],"|") != 0;k++ )
		{	
			command[k]=args[j];
			j++	;
			if (strcmp(args[j],"")==0)
			{

				k++;
				end = 1;
				break;
			}
		}
		command[k]=NULL;
		j++;
		if (i % 2 == 0)
		{		
			pipe(filedes2); 
		}
		else
		{		
			pipe(filedes); 
		}

		pid=fork();
		if(pid==-1)
		{			
			if (i != num_cmds - 1)
			{
				if (i % 2 == 0)
					close(filedes2[1]); 
				else
					close(filedes[1]);

			}			
			printf("Child process could not be created\n");
			return 0;
		}
		if(pid==0)
		{
			if(a2>0)
				dup2(a2,1);
				if (i == num_cmds - 1)
				{
					if (num_cmds % 2 == 0)
						dup2(filedes2[0],STDIN_FILENO);
					else 
						dup2(filedes[0],STDIN_FILENO);

				}
				else   if (i == 0)
					dup2(filedes2[1], all);

				else	 
				{ 
					if (i % 2 == 0)
					{
						dup2(filedes2[1],all);
						dup2(filedes[0],STDIN_FILENO); 

					}else
					{ 
						dup2(filedes[1],all);		
						dup2(filedes2[0],STDIN_FILENO); 
					} 
				}
				int a=execvp(command[0],command);
				if(a==-1)
				{
					kill(getpid(),SIGTERM);
					return 0;
				}
				exit(0);			
		}
		else
		{
			wait(NULL);
		}
		if (i == num_cmds - 1)
		{
			if (num_cmds % 2 == 0)					
				close(filedes2[0]);
			else					
				close(filedes[0]);

		}
		else if (i == 0)
			close(filedes2[1]);
		else
		{
			if (i % 2 == 0)
			{					
				close(filedes2[1]);
				close(filedes[0]);
			}
			else
			{					
				close(filedes[1]);
				close(filedes2[0]);
			}
		}

	}
	return 1;
}




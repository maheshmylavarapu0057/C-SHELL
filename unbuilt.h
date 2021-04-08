char argss[100][20][100];
int arrcount=0,arvalid[100]={0};
int pid,fl_b;
char * arg[300];
void printing()
{

		int a,i;
	char ans[100];
	pid_t pid=waitpid(-1,&a,WNOHANG);
	sprintf(ans,"%d",pid);
	for(i=0;i<arrcount;i++)
		if(strcmp(argss[i][0],ans)==0)
		{
			if(argss[i][2][0]=='1')
			{
				if(WIFEXITED(a))
				{
				fflush(stdout);
				arvalid[i]=1;
				fprintf(stdout,"Process %s Exited normally with PID :%d\n",argss[i][1],pid);
				fflush(stdout);
				}
				else
				{
					arvalid[i]=1;
				fprintf(stderr,"Process %s Exited abnormally with PID :%d\n",argss[i][1],pid);
				fflush(stdout);
				}
			}	
		}

}
void signal_handler(int signum)
 {
        if(signum == SIGINT)
		 {
			    signal(SIGINT,SIG_IGN);              
                signal(SIGINT, signal_handler);     
        }
 }
void signal_handle(int signum)
{
        if(signum == SIGTSTP)
		 {
            int a;
			  setpgid(fl_b,fl_b);
			  if(fl_b!=-1)
			   {
				   kill(fl_b,SIGTSTP);
				   char ans[100];
					sprintf(ans,"%d",fl_b);
					int i;
					for(i=0;i<arrcount;i++)
					if(strcmp(argss[i][0],ans)==0)
						{
						argss[i][2][0]='1';		
						arvalid[i]=0;
						}		
					signal(SIGCHLD,printing);	
			   }
			     signal(SIGTSTP,SIG_IGN);              
                signal(SIGTSTP, signal_handler); 
        }
		
}
int functionforbg(char ans[100])
{
	int a,i,state;
	pid_t pid,wpid;
	a=atoi(ans);
	if(argss[a-1][2][0]=='1')
	{
		pid=atoi(argss[a-1][0]);
		argss[a-1][2][0]='1';
		  if(killpg(pid, SIGCONT) >= 0)            /* Send signal to thid pgid to continue if stopped */
    			                perror("Can't get in background!\n");
		return 1;
	}
	printf("Not a background job\n");
	return 0;
}
int functionforfg(char ans[100])
{
	int a,i,state;
	pid_t pid,wpid;
	a=atoi(ans);
	if(argss[a-1][2][0]=='1')
	{
		pid=atoi(argss[a-1][0]);
		argss[a-1][2][0]='0';
		  if(killpg(pid, SIGCONT) < 0)            /* Send signal to thid pgid to continue if stopped */
                       // perror("Can't get in foreground!\n");
				wpid = waitpid (pid, &state, WUNTRACED);
		while (!WIFEXITED(state) && !WIFSIGNALED(state)) 
			wpid = waitpid (pid, &state, WUNTRACED);
			return 1;
	}
	printf("Not a background job\n");
	return 0;
}
int functionforprintingjobs(void)
{
	int i=0,j=0;

	printf("BackGround Jobs\n");
	for(i=0;i<arrcount;i++)
	{
		if(strcmp(argss[i][2],"1")==0)
		{
			if(arvalid[i]==1)
			{
				printf("%d Stopped %s ", j+1,argss[i][1]);
				for(int k=3;strcmp(argss[i][k],"")!=0&&strcmp(argss[i][k],"&")!=0;k++)
				printf("%s ",argss[i][k]);
				printf("[%s]\n",argss[i][0]);
			}
			else
			{
				printf("%d Running %s ", j+1,argss[i][1]);
				for(int k=3;strcmp(argss[i][k],"")!=0&&strcmp(argss[i][k],"&")!=0;k++)
				printf("%s ",argss[i][k]);
				printf("[%s]\n",argss[i][0]);
			}	
				j++;
		}
	}
	j=0;
	printf("ForeGround Jobs Executed Till now\n");
	for(i=0;i<arrcount;i++)
		if(strcmp(argss[i][2],"0")==0)
		{
				printf("%d Exited Process %s ", ++j,argss[i][1]);
				for(int k=3;strcmp(argss[i][k],"")!=0&&strcmp(argss[i][k],"&")!=0;k++)
				printf("%s ",argss[i][k]);
				printf("[%s]\n",argss[i][0]);
		}
	return 1;
}
int killingprocess()
{
	int i=0;
	for(i=0;i<arrcount;i++)
	{
		if(argss[i][2][0]=='1'&&arvalid[i]==0)
			kill(atoi(argss[i][0]),9);
		
	}
	return 0;
}
int functionforkjob(char ans[100],char ans2[100])
{
	int a=atoi(ans);
	int b=atoi(ans2);
	if (argss[a-1][2][0]=='1'&&arvalid[a-1]==0)
	{
		kill(atoi(argss[a-1][0]),b);
		return 1;
	}
	printf("Not a runnning Job");
	return 0;
}
int unbuiltfunctions(char args[][300],char cwd[])
{

	int i=0,j,background=0,piping=0,redirect=0;
	if(strcmp(args[0],"jobs")==0)
	{
		return functionforprintingjobs();
	}
	else if(strcmp(args[0],"fg")==0)
	{
		return functionforfg(args[1]);
	}
	else if(strcmp(args[0],"bg")==0)
	{
		return functionforbg(args[1]);
	}
	else if(strcmp(args[0],"quit")==0)
	exit(0);
	else if(strcmp(args[0],"overkill")==0)
		return killingprocess();
	else if (strcmp(args[0],"kjob")==0)	
		{
			if(strcmp(args[1],"")!=0&&strcmp(args[2],"")!=0)
		return functionforkjob(args[1],args[2]);
		return 0;
		}
	while(strcmp(args[i],"")!=0)
	{
			if(strcmp(args[i],"&")==0)
			{
				background=1;
				break;
			}
			else if(strcmp(args[i],"<")==0 ||strcmp(args[i],">")==0 ||strcmp(args[i],">>")==0)
				redirect++;
			else if(strcmp(args[i],"|")==0)
				piping++;
		i++;
	}
	if(redirect&&piping==0)
	return redirecting(args,i);
	else if(piping||redirect)
	 return functionforpipe(piping,args);
	pid_t pid, wpid,pidy,pidy2;

	int state;
	pid = fork();
	fl_b=pid;
	for( int i=0;i<300;i++)
		arg[i]=NULL;
	for(int i=0;i<30&&strcmp(args[i],"")!=0;i++)
		arg[i]=args[i];
	if (pid < 0)
	{
		perror("ERROR");
		return 0;
	}
	else if(pid==0) 
	{
		if(background==1)
			setpgid(0,0);
		if(execvp(arg[0], arg)==-1)
		{
			perror("ERROR");
			return 0;
		}
		exit(0);
	}
	else
	{
		sprintf(argss[arrcount][0],"%d",pid);
		strcpy(argss[arrcount][1],arg[0]);
		sprintf(argss[arrcount][2],"%d",background);
		for(i=1;arg[i]!=NULL;i++)
		strcpy(argss[arrcount][i+2],args[i]);
		arrcount++;
	}
	if(background==0) 
	{		           
		//setpgid(pid,pid);
		signal(SIGTSTP,signal_handle);
		wpid = waitpid (pid, &state, WUNTRACED);			
	}
	else
	{
		signal(SIGCHLD,printing);
	}
	
	
	return 1;
}


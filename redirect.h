int redirecting(char args[][300],int num)
{	
	int r = 0,pid,flag1=0,flag2=0,flag3=0,fd;
    char *arg[300];
    char in[100],out[100],app[100];
  struct stat buf;
    for(int i=0;i<10;i++)
		arg[i]=args[i];
		
	pid = fork();
	if (pid==0)
	{	
		int i=0;
        while (i<num)
		{
			if(args[i]!=NULL)
            {
			 
                if (strcmp(args[i],">")==0)
				{
					strcpy(out,arg[i+1]);
					arg[i] = NULL;
					flag2 = 1;
                }
                if (strcmp(args[i],"<")==0)
			    {
                    strcpy(in,arg[i+1]);
                    arg[i] = NULL;
				    flag1 = 1;
			    }
		        if(strcmp(args[i],">>")==0)
				{
				    strcpy(app,arg[i+1]);
                	arg[i] = NULL;
					flag3 = 1;
				}
			}
            i++;
		}
		if (flag1)
		{
			fd = open(in,O_RDONLY,0);
			if (fd<0)
			{
                perror("Could not open input file");
                 return 0;
            }
            dup2(fd,0);
			close(fd);
		}	
		if (flag2)
		{
		
			if (stat(out,&buf)==0)
            {
				fd = open(out, O_WRONLY);
				if (fd<0)
				{
                    perror("Could not open output file"); 
                    return 0;
                }
				dup2(fd,1);
				close(fd);
			}
			else
			{
				fd = creat(out,0644);
				if (fd<0)
				{
                    perror("Could not create output file");
                    return 0;
                }
				dup2(fd,1);
				close(fd);
			}
		}

		if (flag3)
		{
			
			if (stat(app,&buf)==0)
			{
				fd = open(app,O_APPEND | O_WRONLY);
				if (fd<0)
				{
                    perror("Could not open output file"); 
                    return 0;
                }
				dup2(fd,1);
				close(fd);
			}
			else
			{
				fd = creat(app,0644);
				if (fd<0)
				{
                    perror("Could not create output file");
                     return 0;
                }
				dup2(fd,1);
				close(fd);
			}
		}
		for(i=1;i<10;i++)
			arg[i]=NULL;		
		int a=execvp(arg[0],arg);	
        if(a==-1)
		{
             printf("%s: Command doesn't exist\n", args[0]);
             return 0;
        }
		//exit(0);
	}
	else
        wait(NULL);
  //  printf("%s with process id: %d exited normally\n",args[0],pid);					
	return 1;
}


char input[30][300];
char forans[30][300];
char forback[30][300];
int functionforcronjob(char args[][300],char cwd[]);
void foreverything(char arr[],char cwd[])
{
	int i=0;
	char cur[255];
	char *array=arr;
	char *token;
	for(i=0;i<30;i++)
	{
		memset(forback,0,300);
		memset(input,0,300);
		memset(forans,0,300);
	}
	i=0;
	
	while ((token = strtok_r(array,";", &array)))
	{
		strcpy(input[i],token);
		i++;
	}
	int j=0;
	while(j<i)
	{
		array=input[j];
		
		int k=0;
		for(int ik=0;ik<30;ik++)
			memset(forans[ik],0,300);

		while ((token = strtok_r(array," ", &array)))
		{
			strcpy(forans[k],token);
			k++;
		}
		if(strcmp(forans[0],"cronjob")==0)
		{
			if(functionforcronjob(forans,cwd))
				j++;
		}
		else if(builtinfunction(forans,cwd))    
			j++;

		else if (unbuiltfunctions(forans,cwd))
			j++;
		else
			break;
		    
	} 
	return ;
}
void delay(int number_of_seconds) 
{ 
    int milli_seconds = 1000 * number_of_seconds; 
    clock_t start_time = clock();  
    while (clock() < start_time + milli_seconds) 
        ; 
} 
int functionforcronjob(char args[][300],char cwd[])
{ 
    int i,l=0,k;
	int f=0,b=0,c=0;
	char ans[1000]={0};
	for(i=0;strcmp(args[i],"")!=0;i++)
	{
		if(strcmp(args[i],"-c")==0)
			f=1;
		if(strcmp(args[i],"-t")==0)
			b=1;
		if(strcmp(args[i],"-p")==0)
			c=1;	
	}
    if(f==1&&b==1&&c==1)
    {
		for(i=2;strcmp(args[i],"-t")!=0;i++)
		{
			strcat(ans,args[i]);
			strcat(ans," ");
		}
		i++;
    int a=atoi(args[i++]);
	i++;
    int b=atoi(args[i++]);
   for (i = 1; i*a <= b; i++)
    { 
		  delay(a*1000); 
		  printf("\n");
		int pid=fork();
		if(pid==0)
		{
	  	foreverything(ans,cwd);
	  	_exit(0);
		}
		else
		{
			wait(NULL);
		}
    }
    return 1;
    }
    return 0; 
} 

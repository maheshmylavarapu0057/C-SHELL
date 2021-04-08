char Process[1000],Stats[1000];
char exePath[1000];
int pinfoprinting(char args[][300],char cwd[])
{
	memset(Process,0,1000);
	memset(Stats,0,1000);
	strcpy(Process, "/proc/");
	if(strcmp(args[1],"")!=0) 
		strcat(Process, args[1]);
	else 
		strcat(Process, "self");
	strcpy(Stats, Process);
	strcat(Stats, "/stat");
	FILE * statie = fopen(Stats,"r");
	if(statie==NULL) 
	{
		fprintf(stderr, "Error reading %s: %s\n", Stats, strerror(0));
		return 0;
	}
	int pid; char stat[100],name[100]; 
	fscanf(statie, "%d", &pid); 
	fscanf(statie, "%s", stat);
	fscanf(statie,"%s",name);
	printf( "Pid: %d\n", pid);
	printf( "Process Status: %s\n", name);
	strcpy(Stats, Process); 
	strcat(Stats, "/statm");
	int memSize; 
	FILE * mem = fopen(Stats, "r");
	if(mem==NULL)     
	{
		printf("Error reading %s: %s\n", Stats, strerror(0));
		return 0;
	}
	fscanf(mem, "%d", &memSize);
	printf("Memory: %d\n", memSize);
	fclose(mem);
	fclose(statie);
	memset(exePath,0,1000);
	strcat(Process, "/exe");
	readlink(Process, exePath, sizeof(exePath));
	forcomd2(cwd,exePath);
	return 1;
}

void functiontoprintutsname(char arr[]) 
{
	struct utsname buffer;
	if (uname(&buffer) != 0) 
		perror("uname");
	printf("%s@%s:%s$", getenv("USER"),buffer.nodename,arr);   
	return ;
}
void forcomd(char cwd[],char cur[])
{
	char cure[255];
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
		functiontoprintutsname(cure);
	else
		functiontoprintutsname(cur);
	return;
}
void forcomd2(char cwd[],char cur[])
{
	char cure[255];
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
		printf("Executable Path :%s\n",cure);
	else
		printf("Executable Path:%s\n",cur);
	return;
}

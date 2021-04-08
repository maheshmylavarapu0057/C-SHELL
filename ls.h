void funlsprint(char arr[])
{
	DIR *d;
	struct dirent *dir;
	d = opendir(arr);
	if (d!=NULL)
	{
		for ( ;( dir = readdir(d)) != NULL; )
			printf("%s ", dir->d_name);
		closedir(d);
		printf("\n");
	}
	else
	{
		printf("No such file or directory\n");
	}

	return ;
}
void funlsprint1(char arr[])
{
	DIR *d;
	struct dirent *dir;
	d = opendir(arr);
	if (d!=NULL)
	{
		for ( ; (dir = readdir(d)) != NULL ;)
			if(dir->d_name[0]!='.')
				printf("%s ", dir->d_name);
		closedir(d);
		printf("\n");
	}
	else
	{
		printf("No such file or directory\n");
	}   
	return ;
}
void  lsfileminusl(char buffer[])
{
	time_t now;
	DIR *dir;
	char mod[200],ans[200];
	memset(ans,0,200);
	int year;
	struct stat mystat;
	struct passwd *user;
	struct group *group;
	struct tm *starttime;
	stat(buffer,&mystat);

	if(S_ISDIR(mystat.st_mode))
		ans[0]= 'd' ;
	else
		ans[0] ='-';
	if((mystat.st_mode & S_IRUSR ))
		ans[1]= 'r' ;
	else
		ans[1] ='-';

	if( (mystat.st_mode & S_IWUSR))
		ans[2] ='w';
	else
		ans[2] ='-';
	if((mystat.st_mode & S_IXUSR)) 
		ans[3]= 'x' ;
	else
		ans[3] ='-';
	if((mystat.st_mode & S_IRGRP) )
		ans[4]= 'r';
	else
		ans[4] ='-';
	if( (mystat.st_mode & S_IWGRP))
		ans[5]= 'w' ;
	else
		ans[5] ='-'; 
	if(mystat.st_mode & S_IXGRP) 
		ans[6]= 'x' ;
	else
		ans[6] ='-';
	if( (mystat.st_mode & S_IROTH))
		ans[7]= 'r' ;
	else
		ans[7] ='-'; 
	if( (mystat.st_mode & S_IWOTH))
		ans[8]= 'w' ;
	else
		ans[8] ='-';
	if( (mystat.st_mode & S_IXOTH))
		ans[9]= 'x' ;
	else
		ans[9] ='-'; 
	printf("%s\t",ans);
	printf("%d\t",(int)mystat.st_nlink);
	user = getpwuid(mystat.st_uid);
	printf("%s\t", user->pw_name);
	group = getgrgid(mystat.st_gid);
	printf("%s\t", group->gr_name);
	printf("%lld\t",(long long)mystat.st_size);
	time(&now);
	year = localtime(&now)->tm_year;
	starttime = localtime(&mystat.st_ctime);
	if(starttime->tm_year == year)
		strftime(mod,13,"%b %e %R",starttime);
	else
		strftime(mod,13,"%b %e %Y",starttime);
	printf("%s\t",mod );	 	
	printf("%s\n",buffer);
}			

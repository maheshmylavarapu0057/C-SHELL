extern char  history[20][300];
extern int current;
int historyprinting(char input[][300])
{
        int i = current,ans=0;
        int hist_num = 1,b,c;
        if(strcmp(input[1],"")!=0)
        {
            if(input[1][1]!=0)
            {
            b=input[1][1]-'0';
            c=input[1][0]-'0';
            ans=c*10+b;
            }
            else
                ans=input[1][0]-'0';
        }
       i=(current-ans)%20;
        do {
                if (strcmp(history[i],"")!=0) 
                        {
                        printf("%4d  %s\n", hist_num, history[i]);
                        hist_num++;
                        }
                i = (i + 1) %20;
        } while (i != current);

        return 1;
}

        
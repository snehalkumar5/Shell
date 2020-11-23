#include "headers.h"
#include "prompt.h"
#include "vardec.h"

int cd(char *command)
{
    int err=errno;
    char *arg = command;
    // printf("token:%s\n",arg);
    arg = strtok(NULL," \t\n\r");
    // printf("token:%s\n",arg);
    if(!arg || !strcmp(arg,"~"))
    {
        prevdir=getcwd(NULL,0);
        if(chdir(home)<0)
        {
            perror("Error changing directory");
        }
    }
    else if(arg[0]=='-')
    {
        printf("%s\n",prevdir);
        char *tmp=getcwd(NULL,0);
        if(chdir(prevdir)<0)
        {
            perror("Error changing directory");
        }
        strcpy(prevdir,tmp);
        free(tmp);
    }
    else if(arg[0]=='~')
    {
        prevdir=getcwd(NULL,0);
        if(chdir(home)<0)
        {
            perror("Error changing directory");
        }
        if(strlen(arg)>2) 
            arg+=2;
        // printf("token:%s\n",arg);
        if(chdir(arg)<0)
        {
            perror("Error changing directory");
        }
    }
    else
    {
        prevdir=getcwd(NULL,0);
        if(chdir(arg)<0)
        {
            perror("Error changing directory");
        }
    }
    if(err!=errno) 
    return -1;
    return 0;
}
#include "headers.h"
#include "prompt.h"
#include "vardec.h"

int set_env(char **cmd,int cmdnum)
{
    if(cmdnum!=2 && cmdnum!=3)
    {
        printf("Invalid number of arguments\n");
        return -1;
    }
    else if(cmdnum == 2) 
    {
        if(setenv(cmd[1],"\0",1)<0)
        {
            perror("Error in setting env");
            return -1;
        }
    }
    else 
    {
        if(setenv(cmd[1],cmd[2],1)<0)
        {
            perror("Error in setting env");
            return -1;
        }
    }
    return 0;
}
int unset(char **cmd,int cmdnum)
{
    int err=errno;
    if(cmdnum != 2)
    {
        printf("Invalid number of arguments\n");
        return -1;
    }
    else if (unsetenv(cmd[1]) < 0)
    {
        perror("Error in unsetenv");
    }
    if(err!=errno)
    return -1;
    return 0;
}
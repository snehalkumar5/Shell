#include "headers.h"
#include "prompt.h"
#include "vardec.h"

int pinfo(char *command,int argnum)
{
    int err=errno;
    if(argnum>2)
    {
        printf("Invalid number of arguments!");
        return -1;
    }
    char *str = strtok(NULL," \t\n\r");
    char status[SIZE],memory[SIZE],path[SIZE],exe[SIZE],mem[SIZE];
    pid_t pid;
    if(!str)
    pid = getpid();
    else
    pid = atoi(str);
    sprintf(status,"/proc/%d/status",pid);
    sprintf(path,"/proc/%d/exe",pid);
    // sprintf(mem,"/proc/%d/statm",pid);

    FILE *fstat = fopen(status,"r");
    
    if(!fstat)
    {
        perror("File for given pid not found");
        return -1;
    }
    int i=0;
    char info[256];
    printf("pid -- %d\n",pid);
    while(fgets(info,sizeof(info),fstat))
    {
        ++i;
        if(i==3)
        {
            char *tmp = strtok(info,":\t\n");
            tmp = strtok(NULL,"\t\n");
            printf("Process Status -- %s\n",tmp);
            // printf("%s\n",tmp);
        }
        else if(i==18)
        {
            char *tmp = strtok(info,"\t");
            tmp = strtok(NULL,"\n");
            // tmp = strtok(NULL,"");
            printf("Memory -- %s\n",tmp);
            break;
        }
    }
    fclose(fstat);
    
    readlink(path,exe,sizeof(exe));
    printf("Executable path -- %s\n", exe);
    if(err!=errno)
    return -1;
    return 0;
}
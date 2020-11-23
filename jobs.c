#include "headers.h"
#include "prompt.h"
#include "vardec.h"

int jobs()
{
    char status[SIZE];
    for(int i=0;i<lastjob;i++)
    {
        sprintf(status,"/proc/%d/status",lastcommand[i].pid);
        FILE *f = fopen(status,"r");
        if(!f)
        {
            perror("Error opening status");
            return -1;
        }
        int j=0;
        char status_info[256],*temp;
        while(fgets(status_info,sizeof(status_info),f))
        {
            j++;
            if(j==3)
            {
                // printf("%s\n",status_info);
                temp = strtok(status_info," :\t\n\r");
                break;
            }
        }
        fclose(f);
        temp = strtok(NULL, " :\n\t\r");
        // printf("\nstatus:%s\n",temp);

        if(!strcmp(temp,"T"))
        {
            printf("[%d] Stopped %s [%d]\n",i+1, lastcommand[i].job, lastcommand[i].pid);
        }
        else
        {
            printf("[%d] Running %s [%d]\n",i+1, lastcommand[i].job, lastcommand[i].pid);
        } 
    }
    return 0;
}

int kjobs(char **cmd,int cmdnum)
{
    int err=errno;
    if(cmdnum!=3)
    {
        printf("Invalid number of arguments\n");
        return -1;
    }
    int jobnum=0,sig=0;
    jobnum = atoi(cmd[1])-1;
    sig = atoi(cmd[2]);
    if(jobnum<0 || jobnum>lastjob)
    {
        printf("Job doesn't exist\n");
        return -1;
    }
    kill(lastcommand[jobnum].pid,sig);
    if(err!=errno)
    return -1;
    return 0;
}
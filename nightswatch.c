#include "headers.h"
#include "vardec.h"

void interrupt(int wait)
{
    FILE *file = fopen("/proc/interrupts", "r");
    if(!file)
    {
        perror("Error opening file");
        return;
    }
    printf("ads\n");
    return;

}
int newborn(int wait)
{
    FILE *file = fopen("/proc/loadavg", "r");
    if(!file)
    {
        perror("Error opening file");
        return -1;
    }
    char *info=(char *)malloc(SIZE*sizeof(char));
    if(fgets(info,SIZE,file))
    {
        info = strtok(info," ");
        for(int i=0;i<4;i++)
        info = strtok(NULL," ");
    }
    printf("%s",info);
    fclose(file);
    return 0;

}
int nightswatch(char *command,int argnum)
{
    int err=0;
    if(argnum!=4)
    {
        printf("Invalid number of arguments\n");
        return -1;
    }
    char *str = command;
    str = strtok(NULL," \t\n\r");
    int cnt=1,num=1,n=0,i=0;
    while(str)
    {
        if(cnt==1)
        {
            if(strcmp(str,"-n"))
            {
                printf("Incorrect syntax\n");
                return -1;
            }
        }
        if(cnt==2)
        {
            num = atoi(str);
        }
        if(cnt==3)
        {
            if(!strcmp(str,"interrupt"))
            {
                i=1;
            }
            else if(!strcmp(str,"newborn"))
            {
                n=1;
            }
            else
            {
                printf("Incorrect syntax\n");
                return -1;
            }
        }
        cnt++;
        str = strtok(NULL," \t\n\r");
    }
    while(1)
    {
        fd_set fds;
        struct timeval tv;
        tv.tv_sec = 0,tv.tv_usec = 0;
        FD_ZERO(&fds);
        FD_SET(0, &fds);
        int rd = select(1, &fds, NULL, NULL, &tv);
        if(rd==-1)
        {
            perror("Error in selecting file descriptor");
            return -1;
        }
        else if(rd)
        {
            rd = select(1, &fds, NULL, NULL, &tv);
            char c = fgetc(stdin);
            char d = fgetc(stdin);
            if(c=='q')
            return 0;
        }
        if(i) { interrupt(num); }
        else { err=newborn(num); }
        sleep(n);   
    }
    return err;
    
}
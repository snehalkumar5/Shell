#include "headers.h"
#include "prompt.h"
#include "vardec.h"
#include "functions.h"
void quit()
{
    printf("\n\tBYEBYE\n\n");
    exit(0);
}
int overkill()
{
    int err=errno;
    for(int i=0;i<lastjob;i++)
    {
        // printf("%s \n",lastcommand[i].job);
        kill(lastcommand[i].pid,SIGKILL);
    }
    if(err!=errno)
    return -1;
    return 0;
}

void init()
{
    home = getcwd(NULL,0);
    homelen = strlen(home);
    prevdir=home;
    lastjob=0;
    hist_id=0;
    pipenum=0;
    SHELLID=getpid();  
    strcpy(hist_path,home);
    strcat(hist_path,"/history.txt");
    load_history();
    for(int i=0;i<40;i++)
    {
        // strcpy(lastcommand[i].job,NULL);
        lastcommand[i].done=0;
    }
    signal(SIGCHLD,handler);
    signal(SIGINT,handler2);
    return;
}

int main()
{
    init();
    int r=0;
    while(1)
    {
        prompt();
        int r = get_input();
        if(r==1) {continue;}
        else if(!r)
        printf(":')");
        else if(r==-1)
        printf(":'(");
    }
    return 0;
}
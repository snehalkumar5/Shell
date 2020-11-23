#include "headers.h"
#include "prompt.h"
#include "vardec.h"

int fg(char **cmd,int cmdnum)
{
    int err=errno;
    if(cmdnum!=2)
    {
        printf("Invalid number of arguments\n");
        return -1;
    }
    int jobnum=atoi(cmd[1])-1;
	if(jobnum<0 || jobnum>lastjob)
	{
		printf("Enter valid job number:%d\n",jobnum);
		return -1;
	}
	pid_t pid = lastcommand[jobnum].pid;
	for(int i=jobnum+1;i<lastjob;i++)
    {
        lastcommand[i-1].pid=lastcommand[i].pid;
        lastcommand[i-1].done=lastcommand[i].done;
        strcpy(lastcommand[i-1].job,lastcommand[i].job);
    }
    lastjob--;
	signal(SIGTTIN, SIG_IGN);
    signal(SIGTTOU, SIG_IGN);
    tcsetpgrp(0,pid);
    // if(!tcsetpgrp(0, pid)) 
    // perror("tcsetprgp error");
	kill(pid, SIGCONT);
    int status; 
	waitpid(pid, &status, WUNTRACED);
    tcsetpgrp(0,getpgrp());
	// if(!tcsetpgrp(0, getpgrp()))
    // perror("tcsetpgrp error");
    signal(SIGTTIN, SIG_DFL); 
    signal(SIGTTOU, SIG_DFL); 

	if(WIFSTOPPED(status))
	{
        printf("\n[%d]  + %d Suspended %s\n",jobnum+1, pid, lastcommand[jobnum].job);
		// printf("\n%s with pid %d suspended\n",lastcommand[jobnum].job, pid);
		strcpy(lastcommand[lastjob].job, lastcommand[jobnum].job);
        lastcommand[lastjob++].pid = pid;
        err=-1;
	}
    if(err!=errno)
    return -1;
    return 0;
}

int bg(char **cmd,int cmdnum)
{
    int err=errno;
    if(cmdnum != 2)
    {
        printf("Invalid number of arguments\n");
        return -1;
    }
    int jobnum=atoi(cmd[1])-1;
    if (jobnum<0 || jobnum>lastjob)
    {
        printf("Job doesn't exist\n");
        return -1;
    }
    kill(lastcommand[jobnum].pid, SIGCONT); 
    if(err!=errno)
    return -1;  
    return 0;
}
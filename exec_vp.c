#include "headers.h"
#include "prompt.h"
#include "vardec.h"
void handler2(int sig)
{
    // int status;
    // pid_t curproc = __getpgid(0);
    // if(curproc==SHELLID || curproc==0)
    // return;
    // kill(curproc,9);
    // return;
    signal(SIGINT,SIG_IGN);
}
void handler(int sig)
{
    int status,flag=0;
    pid_t pid = waitpid(-1, &status, WNOHANG);
    char *job = (char *)malloc(sizeof(char)*SIZE);

    if(pid>0)
    {
        for(int i=0;i<lastjob;i++)
        {
            if(pid == lastcommand[i].pid)
            {
                // printf("handler pid: %d\n",lastcommand[i].pid);
                strcpy(job,lastcommand[i].job);
                lastcommand[i].done=1;
                for(int j=i+1;j<lastjob;j++)
                {
                    lastcommand[i-1].pid=lastcommand[i].pid;
                    lastcommand[i-1].done=lastcommand[i].done;
                    strcpy(lastcommand[i-1].job,lastcommand[i].job);
                }
                lastjob--;
                flag=1;
                break;
            }
        }

        if(flag)
        {
            if(WIFEXITED(status) && !WEXITSTATUS(status))
            {
                fprintf(stderr,red"\nProcess %s with pid:%d exited normally\n"rr, job, pid);
            }
            else
            {
                fprintf(stderr,red"\nProcess %s with pid:%d exited abnormally\n"rr,job, pid);
            }
            prompt();
            fflush(stdout);
        }
    }
    free(job);
    // prompt();
    return;
}

int exec_vp(char **args,int argnum, char *cmds, int bg)
{
    int err=errno=0;
    // printf("tokens: %s %d\n",tokencmd[argnum-1],argnum);
    // for(int i=0;i<tokennum;i++)
    // {
    //     printf("token %d:%s\n",i+1,tokencmd[i]);
    // }
    // printf("comand:%s\n",cmds);
    // char **args = tokenise()
    pid_t id = fork();
    args[argnum]=NULL;
    if(!strcmp(args[argnum-1],"&"))
    {
        args[argnum-1]=NULL;
    }
    if(id<0)
    {
        perror("Error creating process");
        exit(1);
    }
    else if(id==0)
    {
        setpgid(0,0);
        signal(SIGINT,SIG_DFL);
        signal(SIGTSTP,SIG_DFL);
        int ck = execvp(args[0],args);
        if(ck<0)
        {
            perror("Command not found!");
            exit(1);
        }
    }
    else
    {
        if(bg==1)
        {
            strcpy(lastcommand[lastjob].job,cmds);
            lastcommand[lastjob].pid=id;
            lastjob=(lastjob+1)%40;
            printf("[%d] %d\n", lastjob, id);
            // printf("Background process:%s with pid:%d\n", cmds, id);
        }
        else
        {
            pid_t waitid;
            int status;   
            
            signal(SIGTTIN, SIG_IGN);
            signal(SIGTTOU, SIG_IGN);
            // raise(SIGCONT);
            pid_t grid = getpgrp();
            tcsetpgrp(0, id);
            waitid = waitpid(id, &status, WUNTRACED);
            status=status/255;
            // printf("child signal:%d",status);
            if((status)==0)
            err=errno;
            tcsetpgrp(0, grid);
            signal(SIGTTIN, SIG_DFL);
            signal(SIGTTOU, SIG_DFL);

            if(WIFSTOPPED(status))
            {
                printf("\n[%d]  + %d Suspended %s\n",lastjob+1, id, cmds);
                strcpy(lastcommand[lastjob].job,cmds);
                lastcommand[lastjob].pid=id;
                lastjob=(lastjob+1)%40;
                err=-1;
            }
        }
    }
    // printf("err:%d errno:%d",err,errno);
    if(err!=errno)
    return -1;
    return 0;
}
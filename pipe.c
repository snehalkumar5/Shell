#include "headers.h"
#include "prompt.h"
#include "vardec.h"
#include "functions.h"

char **pipe_cmd(char *cmd)
{
    char *a = strtok(cmd, "|");
    char **args = malloc(512*sizeof(char *));
    int num=0;
    while(a)
    {
        args[num++]=a;
        a = strtok(NULL, "|");
    }

    return args;
}

int piping(char *cmd)
{
    char **pipedcmd = pipe_cmd(cmd);
    int pipefd[2], infd=0, err=errno=0;
    for(int i=0;pipedcmd[i]!=NULL;i++)
    {
        // printf("pipe %d: %s\n",i+1,pipedcmd[i]);
        if(pipe(pipefd)<0)
        {
            perror("Error creating pipe");
            return -1;
        }

        pid_t pid = fork();
        if(pid<0)
        {
            perror("Error forking");
            return -1;
        }            
        else if(pid == 0)
        {
            if(dup2(infd, 0)<0)         //read from last pipe
            {
                perror("Error in dup2");
            }              
            
            if(pipedcmd[i+1]!=NULL) 
            {
                if(dup2(pipefd[1],1)<0)      //write to curr pipe
                {
                    perror("Error in dup2");
                }
            }

            close(pipefd[0]);           
            // char *tmp = (char *)malloc(SIZE*sizeof(char));
            // strcpy(tmp,pipecmd[i]);
            // tokenise(tmp);
            // exec_vp(tokencmd,tokennum,pipecmd[i],0);  
            // free(tmp);
            exec_cmd(pipedcmd[i]);
            exit(10);
        }
        else
        {
            int status;
            wait(&status);
            // printf("status:%d",status/255);
            if((status/255)==10)
            err=errno;                 
            close(pipefd[1]);          
            infd = pipefd[0];            // set curr read pipe
        }
    }
    // printf("err:%d,errno:%d",err,errno);
    if(err!=errno)
    return -1;
    return 0;
}
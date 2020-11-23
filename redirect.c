#include "headers.h"
#include "prompt.h"
#include "vardec.h"
#include "functions.h"

int filecheck(char *file) 
{
    struct stat buf;
    if(!stat(file, &buf) && !S_ISDIR(buf.st_mode))
    {
        return 1;
    }
    return 0;
}

int redirect(char *cmds,int check)
{
    int cur_in = dup(0), cur_out = dup(1);
    int in=0,out=0;
    char *a = strstr(cmds,"<");
    if(a) { in=1; }
    char *s = strstr(cmds,">");
    if(s)
    {
        out=1;
        char *t = strstr(cmds,">>");
        if(t)
        out=2;
    }
    char *infile,*outfile;
    
    char *output1 = &cmds[0],*input1;
    if(out)
    {
        char *output2;
        if(out==1)
        {
            output1 = strtok(output1,">");
            output2 = strtok(NULL,">");
            // output1 = strtok(output1," \t\n\r");
            output2 = strtok(output2," \t\n\r");
            // printf("file: %s>%s\n",output1,output2);
            input1 = output1;   
        }
        else if(out==2)
        {
            output1 = strtok(output1,">>");
            output2 = strtok(NULL,">>");
            // output1 = strtok(output1," \t\n\r");
            output2 = strtok(output2," \t\n\r");
            // printf("file: %s>>%s\n",output1,output2);
            input1 = output1;   
        }
        outfile=strtok(output2," \t\n\r");
    }
    input1 = output1;
    if(in==1)
    {

        input1 = strtok(input1,"<");
        char *input2 = strtok(NULL,"<");
        // input1 = strtok(input1," \t\n\r");
        input2 = strtok(input2, " \t\n\r");
        // printf("file: %s<%s\n",input1,input2);
        infile = strtok(input2," \t\n\r");
        if(!filecheck(infile))
        {
            printf("File does not exist\n");
            return -1;
        }
    }
    // printf("output:%s, infile:%s\n",outfile,infile);
    int cnt=0;
    char **args = (char**)malloc(sizeof(char*)*300);
    // printf("before:%s\n",input1);
    input1 = strtok(input1," \t\n\r");
    // printf("start:%s\n",input1);

    while(input1)
    {
        args[cnt]=(char *)malloc(sizeof(char) *strlen(input1)+10);
        strcpy(args[cnt++], input1);
        // args[cnt++]=input1;
        // printf("%s\n",input1);
        input1 = strtok(NULL," \t\n\r");
    }
    args[cnt] = NULL;

    pid_t pid = fork();
    if(pid<0)
    {
        perror("Error forking");
        return -1;
    }
    if(pid==0)
    {
        if(in==1)
        {
            int ifd = open(infile, O_RDONLY);
            if(ifd<0)
            {
                perror("Error opening input file");
                return -1;
            }
            else
            {
                dup2(ifd,STDIN_FILENO);
            }
        }
        if(out)
        {
            int ofd;
            if(out==1)
                ofd = open(outfile, O_RDWR | O_TRUNC | O_CREAT, 0644);
            else
            {
                ofd = open(outfile, O_RDWR | O_APPEND | O_CREAT, 0644);
            }
            
            if(ofd<0)
            {
                perror("Error opening output file");
                return -1;
            }
            else
            {
                dup2(ofd,STDOUT_FILENO);
                close(ofd);
            }
        }
        
        if(execvp(args[0],args)<0)
        {
            perror("Command not found!");
        }
        dup2(cur_in, STDIN_FILENO);
        close(cur_in);

        dup2(cur_out, STDOUT_FILENO);
        close(cur_out);
    }
    else
    {
        int status;
        while(1)
        {
            pid_t st = wait(&status);
            // printf("%d",status/255);
            if(st==pid)
            break;
        }
    }

    return 0;
}
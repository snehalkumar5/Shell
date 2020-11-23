#include "headers.h"
#include "prompt.h"
#include "vardec.h"
#include "functions.h"
int check_logic(char *command)
{
    char *str = strstr(command,"@");
    char *str1 = strstr(command,"$");
    if(str || str1)
    return 1;
    return 0;
}
int check_redirect(char *command)
{
    // char *str1 = (char *)malloc(sizeof(char)*SIZE);
    // char *str2 = (char *)malloc(sizeof(char)*SIZE);
    // char *str3 = (char *)malloc(sizeof(char)*SIZE);
    int ck=0;
    // strcpy(str1,command);
    // strcpy(str2,command);
    // strcpy(str3,command);
    char *str1 = strstr(command,"<");
    char *str2 = strstr(command,">");
    // char *str3 = strstr(command,">>");
    // if(!str1 && !str2 && !str3)
    // return ck;
    if(str1 && str2) { ck=3; }
    else if(str2) { ck=2; }
    else if(str1) { ck=1; }
    return ck;
}
int check_pipe(char *command)
{
    char *str = (char *)malloc(sizeof(char)*SIZE);
    strcpy(str,command);
    char *a = strstr(command,"|");
    // printf("available pipe:%s\n",a);
    if(a!=NULL)
    {
        return 1;
    }
    return 0;
}

int exec_cmd(char *cmds)
{
    int bcg=0,check=0;
    char temp[SIZE];
    char *cmd1 = (char *)malloc(sizeof(char)*SIZE);
    char *cmd2 = (char *)malloc(sizeof(char)*SIZE);
    strcpy(temp,cmds);
    strcpy(cmd1, cmds);
    strcpy(cmd2, cmds);
    cmd1 = strtok(cmd1," \n\t\r");
    // cmd2 = strtok(cmd2," \n\t\r");
    if(cmd1==NULL)
    return 0;
    tokenise(temp);
    
    if(check_logic(cmds))
    {
        check=logic(tokencmd,tokennum,cmds);
        // printf("locg:%d",check);
        return check;
    }
    if(check_pipe(cmds))
    {
        check=piping(cmds);
        // printf("pipe:%d",check);
        return check;
    } 
    int r = check_redirect(cmds);
    if(r)
    {
        check=redirect(cmds,r);
        // printf("redirect:%d",check);
        return check;
    }
    cmds = strtok(cmds," \t\n\r");

    if(!strcmp(tokencmd[tokennum-1],"&"))
    {
        bcg=1;
        check=exec_vp(tokencmd,tokennum,cmds,bcg);
    }
    else if(strcmp(tokencmd[0],"exit")==0)
    {
        quit();
    }
    else if(strcmp(cmds,"cd")==0)
    {
        check=cd(cmds);
    }
    else if(strcmp(tokencmd[0],"echo")==0)
    {
        check=echo(cmds);
    }
    else if(strcmp(tokencmd[0],"pwd")==0)
    {
        check=pwd();
    }
    else if(strcmp(cmds,"ls")==0)
    {
        check=ls(cmds);
    }
    else if(strcmp(tokencmd[0],"pinfo")==0)
    {
        check=pinfo(cmds,tokennum);
    }
    else if(strcmp(tokencmd[0],"history")==0)
    {
        check=history(tokencmd[1]);
    }
    else if(strcmp(tokencmd[0],"nightswatch")==0)
    {
        check=nightswatch(cmds,tokennum);
    }
    else if(strcmp(cmds,"jobs")==0)
    {
        check=jobs();
    }
    else if(strcmp(cmds,"kjob")==0)
    {
        check=kjobs(tokencmd,tokennum);
    }
    else if(strcmp(cmds,"setenv")==0)
    {
        check=set_env(tokencmd,tokennum);
    }
    else if(strcmp(cmds,"unsetenv")==0)
    {
        check=unset(tokencmd,tokennum);
    }
    else if(strcmp(cmds,"fg")==0)
    {
        check=fg(tokencmd,tokennum);
    }
    else if(strcmp(cmds,"bg")==0)
    {
        check=bg(tokencmd,tokennum);
    }
    else if(strcmp(cmds,"overkill")==0)
    {
        check=overkill();
    }
    else if(strcmp(cmds,"quit")==0)
    {
        quit();
    }
    else
    {
        // printf("yeet");
        check=exec_vp(tokencmd,tokennum,cmds,bcg);
        // printf("exec:%d",check);
    }
    // printf("return check:%d\n",check);
    return check;
}
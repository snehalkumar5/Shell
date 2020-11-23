#include "headers.h"
#include "prompt.h"
#include "vardec.h"
#include "functions.h"

void prompt()
{
    char path[SIZE],*prt;
    char *user,sys[SIZE];
    user = getlogin(); 
    gethostname(sys,sizeof(sys));
    getcwd(path,sizeof(path));
    if(strncmp(home,path,homelen)==0)
    {
        path[0]='~';
        {
            for(int i=homelen;i<strlen(path);i++)
            {
                path[i-homelen+1] = path[i];
            }
        }
        path[strlen(path)-homelen+1]='\0';
    } 
    printf(green"<%s@%s:"rr blue "%s>"rr orange,user,sys,path);

}
char **tokenize(char *input)
{
    char *p = strtok (input, ";");
    char **array = malloc(256 * sizeof(char *));

    cmdnum = 0;
    // printf("input to tokenise: %s",input);
    while (p != NULL)
    {
        array[cmdnum++] = p;
        p = strtok (NULL, ";");
    }

    return array;
}
int get_input()
{
    char input[SIZE],tmp[SIZE];
    if(fgets(input,SIZE,stdin)==NULL)
    {
        quit();
    }
    
    strcpy(tmp,input);
    if(strcmp(tmp,"\n")==0)
    {
        return 1;
    }
    char *a = strtok(tmp,";"); 
    // printf("; wala: %s",a);
    if(!a)
    return 1;

    int cnt=0;
    while (a != NULL)
    {
        commands[cnt++] = a;
        a = strtok (NULL, ";");
    }
    cmdnum = cnt;
    int r=0;
    for(int i=0;i<cnt;i++)
    {
        r=exec_cmd(commands[i]);
    }
    save_history(input);
    return r;
}
void tokenise(char *command)
{
    char *a = command;
    a = strtok(command," \t\n\r");
    tokennum=0;
    for(int i=0;i<SIZE;i++)
    tokencmd[i]=NULL;
    while(a)
    {
        tokencmd[tokennum++]=a;
        a = strtok(NULL," \t\n\r");
    }
    
    return;
}

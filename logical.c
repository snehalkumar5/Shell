#include "headers.h"
#include "prompt.h"
#include "vardec.h"
#include "functions.h"

int logic(char **tokens,int argnum, char *command)
{
    int cnt=0;
    int condition[SIZE];
    char **args = (char **) malloc(SIZE*sizeof(char *));
    for(int i=0;i<argnum;i++)
    {
        args[i]=(char *)malloc(SIZE*sizeof(char));
        strcpy(args[i],tokens[i]);
        if(!strcmp(tokens[i],"@"))
        {
            condition[cnt++]=0;
        }
        else if(!strcmp(tokens[i],"$"))
        {
            condition[cnt++]=1;
        }
    }
    cnt=0;
    // char *str = (char *)malloc(SIZE*sizeof(char));
    char *str = strtok(command,"$@");
    while(str)
    {
        tiktok[cnt++]=str;
        // printf("tok:%s",str);
        str = strtok(NULL,"@$");
    }
    int lastcheck=0;
    logics[0]=exec_cmd(tiktok[0]);
    for(int i=0;i<cnt-1;i++)
    {
        // printf("%d\n",logics[i]);
        if(condition[i]==0)
        {

            if(logics[i]==0)
            {
                logics[i+1]=exec_cmd(tiktok[i+1]);
                lastcheck=-1;
                if(logics[i]==0 && logics[i+1]==0)
                lastcheck=0;
                // printf("Ere:%d %d",lastcheck,logics[i+1]);
            }
            else
            {
                return logics[i];
            }
        }
        else if(condition[i]==1)
        {
            if(logics[i]==-1)
            {
                logics[i+1]=exec_cmd(tiktok[i+1]);
                lastcheck=-1;
                if(logics[i]==0 || logics[i+1]==0)
                lastcheck=0;
            }
            else
            {
                return logics[i];
            }
        }
    }

    return lastcheck;
}





















    // for(int i=0;i<argnum;i++)
    // {
    //     if(!strcmp(tokens[i],"@") || !strcmp(tokens[i],"$") || i==argnum-1)
    //     {   
    //         strcpy(tmp,tokens[j]);
    //         for(int k=j+1;k<i;k++)
    //         {
    //             strcat(tmp," ");
    //             strcat(tmp,tokens[k]);
    //         }
    //         // if(i==argnum-1)
    //         // strcat(tmp,tokens[i]);
    //         j=i+1;
    //         strcat(tmp,"\0");
    //         printf("logic token %d:%s\n",i,tmp);
    //         args[cnt]=tmp;
    //         args[cnt][strlen(tmp)]='\0';
    //         printf("arg token %d:%s\n",i,args[cnt]);
    //         logics[cnt]=exec_cmd(args[cnt]);
    //         printf("%d:::\n",logics[cnt]);
    //         cnt++;
    //         tmp[0]='\0';
    //     }
    // }
    // free(tmp);
    // for(int i=0;args[i]!=NULL;i++)
    // {
    //     printf("cmd %d:%s\n",i+1,args[i]);
    // }
    //     if(cmd[i][0]=='&')
    //     {
    //         if(exec_cmd(cmd[i])==-1)
    //         break;
    //     }
    //     else if(cmd[i][0]=='@')
    //     {
    //         if(exec_cmd(cmd[i])==0)
    //         break;
    //     }
    // }
    // for(int i=0;i<argnum;i++)
    // {
    //     if(!strcmp(tokens[i],"@"))
    //     {
    //         if(!flag)
    //         {
    //             lastcheck=0;
    //             flag=1;
    //             arg = strtok(command,"@");
    //         }
    //         else
    //         {
    //             arg = strtok(NULL,"@");
    //         }
    //         printf("and wala:%s\n",arg);
    //         lastcheck = logic_and(arg,lastcheck);

    //         arg = strtok(NULL,"@");
    //         printf("and wala:%s\n",arg);

    //         if(lastcheck==0)
    //         lastcheck=logic_and(arg,lastcheck);
    //         else
    //         {
    //             break;
    //         }
            
    //     }
    //     if(!strcmp(tokens[i],"$"))
    //     {
    //         if(!flag)
    //         {
    //             lastcheck=-1;
    //             flag=1;
    //             arg = strtok(command,"$");
    //         }
    //         else
    //         {
    //             arg = strtok(NULL,"$");
    //         }
    //         printf("or wala:%s\n",arg);
    //         lastcheck = logic_or(arg,lastcheck);
    //         // arg = strtok(NULL,"$");
    //     }
    // }    
//     return 0;
// }
#include "headers.h"
#include "vardec.h"
#include "functions.h"

void load_history()
{
    FILE* file = fopen(hist_path, "r");
    int flag=1;
    hist_id=0;
    if(!flag)
    {
        perror("No existing history file not found");
    }
    if(file)
    {
        while(flag)
        {
            flag=0;
            char *lasthist = (char *)malloc(SIZE*sizeof(char));
            char *check = fgets(lasthist,SIZE,file);
            if(check)
            {
                hist[hist_id] = (char *) malloc(SIZE*sizeof(char));
                strcpy(hist[hist_id],lasthist);
                hist_id++;
                flag=1;
            }
        }
    }
    for(int i=hist_id;i<20;i++)
    hist[i]=NULL;
}

void save_history(char *last_input)
{
    if(!strcmp(last_input,hist[0]))
    return;
    if(hist[19])
    {
	    free(hist[19]);
    }

    for(int i=19;i>=1;i--)
    hist[i]=hist[i-1];
    
    hist[0] = (char *) malloc(SIZE*sizeof(char));
    strcpy(hist[0], last_input);
    
    FILE* hist_file = fopen(hist_path, "w");
    for(int i=0;hist[i]!=NULL,i<20;i++)
    {
        fputs(hist[i], hist_file);
        fflush(hist_file);
    }

    fclose(hist_file);

}

int history(char *command)
{
    char *str=command;
    // str = strtok(NULL," \t\n\r");
    int arg=10;
    if(command)
    {
        arg = atoi(command);
    }
    // printf("%d",arg);
    if(arg>10)
    {
        printf("Maximum of 10 commands to printed only!\n");
        arg=10;
    }
    for(int i=0;i<arg;i++)
    {
        if(hist[arg-i-1])
        {
            printf("%s\n",hist[arg-i-1]);
        }
    }
    return 0;
}
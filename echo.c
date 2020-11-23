#include "headers.h"
#include "prompt.h"
#include "vardec.h"

int echo(char *command)
{
    // char *str = strtok(command," \t\n\r");
    char *str = strtok(NULL, " \t\r\n");

    while(str)
    {
        printf("%s ",str);
        str=strtok(NULL," \t\r\n");
    }
    printf("\n");
    return 0;
}
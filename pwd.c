#include "headers.h"
#include "prompt.h"
#include "vardec.h"

int pwd()
{
    char str[SIZE];
    getcwd(str,sizeof(str));
    printf("%s\n",str);
    return 0;
}
#ifndef __VARDEC_H
#define __VARDEC_H

#define green "\033[38;2;;255;255;1m"
#define blue "\033[38;2;10;170;245m"
#define orange "\033[38;2;245;92;m"
#define red "\033[1;31m"
#define rr "\033[0m"

#define SIZE 1024
char *home;
char *fullpath,*prevdir;
char *buffer;
char hist_path[1024];
char *commands[1024];
char *tokencmd[1024];
char *tiktok[1024];
int logics[1024];
int homelen,tokennum,lastjob,cmdnum;
int hist_id;
pid_t SHELLID;
char modevalue[10];
char *hist[20];
struct comm
{
    char job[256];
    pid_t pid;
    int done;
};
typedef struct comm comm;
comm lastcommand[40];
char *pipecmd[512];
int pipenum;
#endif
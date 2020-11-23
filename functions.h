#ifndef __FUNCTIONS_H
#define __FUNCTIONS_H

int exec_cmd(char *);
int cd(char *);
int echo(char *);
int pwd();
int ls(char *);
int pinfo(char *,int);
int exec_vp(char**,int,char *,int);
int history(char *);
int nightswatch(char *,int);
int overkill();
void handler(int);
void handler2(int);
void load_history();
void save_history(char *);

int redirect(char *,int);
int piping(char *);
int jobs();
int kjobs(char **,int);
int fg(char **,int);
int bg(char **,int);
int set_env(char **,int);
int unset(char **,int);
void quit();
int logic(char **,int,char *);
#endif
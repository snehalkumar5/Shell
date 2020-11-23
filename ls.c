#include "headers.h"
#include "prompt.h"
#include "vardec.h"

int permissions(char *file)
{
    struct stat st;
    if(stat(file, &st) == 0)
    {
        mode_t perm = st.st_mode;
        modevalue[0] = S_ISDIR(perm) ? 'd' : '-';
        modevalue[1] = (perm & S_IRUSR) ? 'r' : '-';
        modevalue[2] = (perm & S_IWUSR) ? 'w' : '-';
        modevalue[3] = (perm & S_IXUSR) ? 'x' : '-';
        modevalue[4] = (perm & S_IRGRP) ? 'r' : '-';
        modevalue[5] = (perm & S_IWGRP) ? 'w' : '-';
        modevalue[6] = (perm & S_IXGRP) ? 'x' : '-';
        modevalue[7] = (perm & S_IROTH) ? 'r' : '-';
        modevalue[8] = (perm & S_IWOTH) ? 'w' : '-';
        modevalue[9] = (perm & S_IXOTH) ? 'x' : '-';
        modevalue[10] = '\0';
        return 0;     
    }
    else
    {
        return -1;
    }   
}

int show_ls(char *dir, int all, int ll)
{
    int err=errno;
    struct dirent **list;
    struct stat buf;
    int n = scandir(dir,&list,NULL,alphasort);
    printf("%s:\n",dir);
    if(n==-1)
    {
        perror("Error in scanning directory:");
        return -1;
    }
    if(ll)
    {
        while(n--)
        {
            if(!all)
            {
                if(list[n]->d_name[0]=='.')
                continue;
            }
            // char filepath[SIZE];
            char *filepath = (char *)malloc(sizeof(char) *SIZE);

            strcpy(filepath,dir);
            strcat(filepath,"/");
            strcat(filepath,list[n]->d_name);
            // printf("file to check: %s\n",filepath);
            if(stat(filepath,&buf)<0)
            {
                perror("Error in file info:");
                return -1;
            }
            if(permissions(filepath)<0)
            {
                perror("Error in permissions of file:");
                return -1;
            }
            struct group *gr = getgrgid(buf.st_gid);
            struct passwd *pw =  getpwuid(buf.st_uid);
            char *time = (char *)malloc(sizeof(char) * 50); 
            strftime(time, 50, "%b  %d %H:%M", localtime(&buf.st_mtime));
            free(filepath);
            if(modevalue[0]=='d')
            {
                printf(orange"%s\t%ld\t%s\t%s\t%ld\t%s\t\x1B[1;34m%s\x1B[0m\n", modevalue, buf.st_nlink, pw->pw_name,gr->gr_name, buf.st_size, time, list[n]->d_name);
            }
            else if(modevalue[3]=='x')
            {
                printf(orange"%s\t%lu\t%s\t%s\t%ld\t%s\t"green"%s"rr"\n",modevalue, buf.st_nlink, pw->pw_name,gr->gr_name, buf.st_size, time, list[n]->d_name);
            }
            else
            printf(orange"%s\t%lu\t%s\t%s\t%ld\t%s\t%s\n",modevalue, buf.st_nlink, pw->pw_name,gr->gr_name, buf.st_size, time, list[n]->d_name);
        }
    }
    else
    {
        while(n--)
        {
            if(!all)
            {
                if(list[n]->d_name[0]=='.')
                continue;
            }
            printf(orange"%s\t", list[n]->d_name);
            free(list[n]);
        }
    }
    free(list);
    printf("\n");
    if(err!=errno)
    return -1;
    return 0;
}

int ls(char *command)
{
    char *str = command;
    int err=errno,flag=0;
    str = strtok(NULL," \t\n\r");
    int ll=0,aa=0,cnt=0;
    while(str)
    {
        if(!strcmp(str,"-l")) {ll=1;}
        else if(!strcmp(str,"-a")) {aa=1;}
        else if(!strcmp(str,"-la") || !strcmp(str,"-al"))
        {
            ll=1;
            aa=1;
        }
        else
        {
            cnt++;
            char *dirpath = (char*) malloc(SIZE*sizeof(char));
            if(str[0] == '~')
            {
                str+=1;
                strcpy(dirpath, home);
                strcat(dirpath, str);
                dirpath[strlen(str)+homelen] = '\0';
                // printf("check tok:%s\n",dirpath);
            }
            else 
            {
                strcpy(dirpath, str);
            }
            // printf("tok:%s",dirpath);
            flag=show_ls(dirpath, aa, ll);
            aa=0,ll=0;
            free(dirpath);
        }
        str = strtok(NULL," \t\n\r");
    }
    if(cnt==0)
    {
        // printf("ll");
        flag=show_ls(".",aa,ll);
    }
    if(flag==-1 || err!=errno)
    return -1;
    return 0;
}   
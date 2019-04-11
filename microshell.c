#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#define MAX_COMM 256
#define PATH_MAX 256
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <fcntl.h>

void red(void){
	printf("\033[0;31m");
}

void green(void){
	printf("\033[0;32m");
}

void blue(void){
	printf("\033[0;34m");
}

void resc(void){
	printf("\033[0m");
}

void ms_clear(void){
	system("clear");
}

int dfcounter(s){
        int df_count = 0;
        DIR *dr = opendir(".");
        struct dirent *de;

while((de=readdir(dr)) != NULL)
        {
                df_count++;
        }


closedir(dr);
return df_count;
}


void ms_rm(char s[]){
        int x=0;
        int bef, aft;

        memmove(&s[x], &s[x+1], strlen(s) - x);
        memmove(&s[x], &s[x+1], strlen(s) - x);
        memmove(&s[x], &s[x+1], strlen(s) - x);

        bef = dfcounter(s);
        remove(s);
        aft = dfcounter(s);
        if(aft==bef)	{
                red(); printf("No such file to remove\n"); resc();
			}
	}

void ms_touch(char s[]){
        int x=0;
        int i=0;
                while(i<=5)
                {
                memmove(&s[x], &s[x+1], strlen(s) - x);
                i++;
                }
        creat(s, 0640);
}

void ms_ls(void){
        struct dirent *de;
        DIR *dr = opendir(".");

                if(dr==NULL)
                        printf("No files or directories");

        while((de=readdir(dr))!=NULL)
                printf("%s\t", de->d_name);

        printf("\n");
        closedir(dr);
}

void ms_cd(char s[]){
        int x=0;
        memmove(&s[x], &s[x+1], strlen(s) - x);
        memmove(&s[x], &s[x+1], strlen(s) - x);
        memmove(&s[x], &s[x+1], strlen(s) - x);

        chdir(s);
}


void help(void){
        printf("Author: Alan Filas\nCommands list:\nhelp - shows you this list\nexit - closes microshell\ncd <path> - changes directory to typed path\nls - lists directories, files and hidden files names\ntouch <file_name> - creates a file with name given by user\nrm <file_name> - removes a file with particular name\nclear - cleares terminal\n");
}

int main()
{
bool ex=false;
char *login=(char *)malloc(10*sizeof(char));
login=getlogin();

ms_clear();

printf("\nWelcome to my MicroShell!\n\nIf you want to know more about me and available commands just type: help\n\n");


while(ex == false){
        char cwd[PATH_MAX];
        strcpy((getcwd(cwd, sizeof(cwd))), cwd);

	green(); printf("%s@mcsh:", login);
	blue(); printf("[%s]", cwd);
	resc(); printf("$ ");

        char *command = malloc(MAX_COMM);
        fgets(command, MAX_COMM, stdin);
        command[strlen(command) - 1] = '\0';

if(strcmp(command, "exit")==0)
        {
        printf("Bye then!\n");
        ex=true;
        }
else if(strcmp(command, "help")==0)
        {
        help();
        }
else if(strncmp("cd", command, strlen("cd"))==0)
        {
        char cwd2[PATH_MAX];
        strcpy((getcwd(cwd2, sizeof(cwd2))), cwd2);
                ms_cd(command);
        strcpy((getcwd(cwd, sizeof(cwd))), cwd);
        if(strcmp(cwd, cwd2)==0){
            red(); printf("Wrong path\n"); resc();
        			}
	}
else if(strcmp(command, "ls")==0)
        {
        ms_ls();
        }
else if(strncmp("touch", command, strlen("touch"))==0)
        {
        ms_touch(command);
        }
else if(strncmp("rm", command, strlen("rm"))==0)
        {
        ms_rm(command);
        }
else if(strcmp("clear", command)==0)
	{
	ms_clear();
	}
else
        {
        red(); printf("No such command\n"); resc();
        }

}
return 0;
}

                                                  

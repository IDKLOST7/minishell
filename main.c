#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <stdlib.h>

#define MAX_ALIASES 20

typedef struct {
    char nameal[30];
    char valueal[60];
    int id_used;
} Alias;

int main(int argc, char **argv, char **envp) {

    int start = true;

    pid_t test;
    size_t len;

    char option[60] = "";

    char *args[10] = {0};

    Alias alias_list[MAX_ALIASES] = {0};


    while(start == true) {
        printf("minishell::> ");
        fgets(option, sizeof(option), stdin);
        len = strlen(option);
        if(len > 0 && option[len - 1] == '\n'){
            option[len - 1] = '\0';
        }

        args[0] = strtok(option, " ");

        if(args[0] == NULL){
            continue;
        }

        if(option[0] == '\0'){
            continue;
        }

        int i = 0;

        while (args[i] != NULL) {
            i++;
            args[i] = strtok(NULL, " ");
        }

        for(int i = 0; i < MAX_ALIASES; i++){
            if(alias_list[i].id_used == 1 && strcmp(args[0], alias_list[i].nameal) == 0){
                args[0] = alias_list[i].valueal;
                break;
            }
        }

        if(strcmp(args[0], "exit") == 0){
            printf("The Shell is closed\n");
            break;
        }
        else if(strcmp(args[0], "export") == 0){
            if(args[1] == NULL){
                printf("You Need to enter a variable\n");
                continue;
            }
            char *name = strtok(args[1], "=");
            char *value = strtok(NULL, "=");
            if(value == NULL){
                printf("You need to enter a value\n");
                continue;
            }
            setenv(name, value, 1);
            continue;
        }
        else if(strcmp(args[0], "cd") == 0){
            if(args[1] == NULL){
                chdir("/home");
                continue;
            }
            chdir(args[1]);
            continue;
        }
        else if(strcmp(args[0], "unset") == 0){
            if(args[1] == NULL){
                printf("You need to put the variable to delete\n");
                continue;
            }
            unsetenv(args[1]);
            continue;
        }
        else if(strcmp(args[0], "alias") == 0){
            if(args[1] == NULL){
                for(int i = 0; i < MAX_ALIASES; i++){
                    if(alias_list[i].id_used == 1){
                        printf("%s='%s'\n", alias_list[i].nameal, alias_list[i].valueal);
                    }
                }
                continue;    
            }
            char *n = strtok(args[1], "=");
            char *v = strtok(NULL, "=");
            if(v == NULL || n == NULL){
                printf("Error");
                continue;
            }

            for(int i = 0; i < MAX_ALIASES; i++){
                if(alias_list[i].id_used == 0 || strcmp(alias_list[i].nameal, n) == 0){
                    strcpy(alias_list[i].nameal, n);
                    strcpy(alias_list[i].valueal, v);
                    alias_list[i].id_used = 1;
                    break;
                }
            }
            continue;
        }
        else if(strcmp(args[0], "unalias") == 0){
            if(args[1] == NULL){
                printf("Need More information");
                continue;
            }
            for(int i = 0; i < MAX_ALIASES; i++){
                if(alias_list[i].id_used == 1){
                    if(strcmp(args[1], alias_list[i].nameal) == 0){
                        alias_list[i].id_used = 0;
                        break;
                    }
                }
            }
            continue;
        }

        test = fork();

        if(test == 0){
            execvp(args[0], args);
            perror(args[0]);
            exit(1);
        }
        else {
            waitpid(test, NULL, 0);
        }
    }
    return 0;
}
    

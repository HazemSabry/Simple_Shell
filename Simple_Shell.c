#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

#define MAX_INPUT_LENGTH 100

void process_args (char *arg, char **args, int *counter) {
	char *token = strtok(arg, " ");
	while (token != NULL) {
		if (token[0] == '$') {
			memmove(token, token + 1, strlen(token));
			char *value = getenv(token);
			if (value != NULL) {
				process_args(value, args, counter);
			} else {
				printf("%s environment variable not found\n", token);
                                return;
                        }
		} else {
                        args[(*counter)++] = token;
                }
                token = strtok(NULL, " ");
        }
}

int main (void) {
	while (1) {
		char cwd[128];
		char arg[MAX_INPUT_LENGTH];
		char* token;
		char* args[10];
		int counter = 0;

		if (getcwd(cwd, sizeof(cwd)) == NULL) {
			printf("error in ditermin the current work directory\n");
			return 1;
		};
		printf("~%s$ ",cwd);

		fgets(arg, MAX_INPUT_LENGTH, stdin);
		arg[strcspn(arg, "\n")] = '\0';

		process_args(arg, args, &counter);

		if (strcmp(args[0],"cd") == 0) {
			chdir(args[1]);
		} else if (strcmp(args[0], "echo") == 0) {
			for (int i = 1 ; i < 10 ; i++) {
				if (args[i] == NULL)
					break;
				printf("%s ", args[i]);
			}
			printf("\n");
		} else if (strcmp(args[0],"export") == 0) {
			char* name;
			char* value;
			name = strtok(args[1],"=");
			value = strtok(NULL,"\"");
			setenv(name, value, 1);
		} else if (strcmp(args[0],"exit") == 0) {
			exit(0);
		} else {
			int pid = fork();
			if (pid < 0) {
				printf("error in the fork stage/n");
				return 1;
			} else if (pid == 0) {
				//Child Process
				args[counter] = NULL;
				if(execvp(args[0], args) == -1){
					printf("Child execution faild!\n");
				}
				exit(1);
			} else {
				//Parent Process
				if (args[1] && strcmp(args[1],"&") == 0) {
				
				} else {
					waitpid(pid, NULL, 0);
				}
			}
		}
	}
	return 0;
}

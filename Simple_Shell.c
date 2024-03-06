#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

#define MAX_INPUT_LENGTH 100

int main(void){
	while(1){
		char cwd[128];
		char arg[MAX_INPUT_LENGTH];
		char* token;
		char* args[10];
		int counter = 0;

		if(getcwd(cwd, sizeof(cwd)) == NULL){
			printf("error in ditermin the current work directory\n");
			return 1;
		};
		printf("~%s$ ",cwd);

		fgets(arg, MAX_INPUT_LENGTH, stdin);
		arg[strcspn(arg, "\n")] = '\0';
		token = strtok(arg, " ");
		while(token != NULL){
			args[counter] = token;
			token = strtok(NULL, " ");
			counter++;
		}

		//int size = sizeof(cwd);
		//printf("%d",size);

		//for(int i = 0; i < counter; i++){printf("%s",args[i]);} return 0;

		int pid = fork();
		if(pid < 0){
			printf("error in the fork stage/n");
			return 1;
		}else if(pid == 0){
			//Child Process
			args[counter] = NULL;
			if(execvp(args[0], args) == -1){
				printf("Child execution faild!\n");
			}
			exit(1);
		}else{
			//Parent Process
			waitpid(pid, NULL, 0);
		}
	}
	return 0;
}

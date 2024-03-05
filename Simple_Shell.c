#include <unistd.h>
#include <stdio.h>

#define MAX_INPUT_LENGTH 100

int main(void){
	while(1){
		char cwd[128];
		char arg[MAX_INPUT_LENGTH];
		if(getcwd(cwd, sizeof(cwd)) == NULL){
			printf("error in ditermin the current work directory\n");
			return 1;
		};
		printf("~%s$ ",cwd);
		fgets(arg, MAX_INPUT_LENGTH, stdin);
		int pid = fork();
		if(pid < 0){
			printf("error in the fork stage/n");
			return 1;
		}else if(pid == 0){
			//Child Process
			return 0;
		}else{
			//Parent Process
			
		}
	}
	return 0;
}

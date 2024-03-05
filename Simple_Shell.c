#include <unistd.h>
#include <stdio.h>

void main(void){
	while(1){
		char cwd[128];
		char c;
		if(getcwd(cwd, sizeof(cwd)) == NULL){
			printf("error/n");
			return;
		};
		printf("~%s$ ",cwd);
		scanf("%c",&c);
	}
	return;
}

#include <unistd.h>
#include <stdio.h>

int main(void){
	while(1){
		char cwd[128];
		char c;
		if(getcwd(cwd, sizeof(cwd)) == NULL){
			printf("error");
		};
		printf("~%s$ ",cwd);
		scanf("%c",&c);
	}
}
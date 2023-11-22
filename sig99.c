#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
void intHandler();
void intHandler2();
void intHandler3();
int i;
int pid1;
int main(){
	
	
	pid1 = fork();
	if(pid1 == 0){
		signal(SIGINT, intHandler);
		for(i = 1; i<21;i++){
			for(int j = 1; j<10;j++){
				printf("%d*%d=%d\n",i,j,i*j);
			}
			sleep(1);
		}
		

	}
	else{
		signal(SIGINT, intHandler3);
		while(1)
			pause();
	}
	
}

void intHandler(int signo){
	if(i<10){
		printf("구구단 실행 중이니 종료 불가\n");
	}
	else if(i>=10){
		kill(-getppid(),SIGKILL);
	}
}

void intHandler3(int signo){
	kill(pid1,SIGINT);
}

#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void intHandler();
void intHandler2();
int main()
{
	int password = 123;
	int num;
	signal(SIGALRM, intHandler);
	signal(SIGINT, intHandler2);
	alarm(10);
	while(1){
		scanf("%d",&num);
		if(num == password){
			printf("correct!");
			exit(0);
		}
	}
}

void intHandler(){
	printf("Fire!");
	exit(0);
}

void intHandler2(){
	alarm(10);
	printf("sec reset\n");
}


	


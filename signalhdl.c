#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
void intHandler();
void intHandler2();
int main()
{
signal(SIGINT, intHandler);
sleep(3);
raise(SIGINT);

printf("End if main \n");
}

void intHandler(int signo)
{

printf("SIGINT \n");
printf("Sig No.:%d\n", signo);
signal(SIGINT, intHandler2);

}
void intHandler2(int signo){
	exit(0);
}


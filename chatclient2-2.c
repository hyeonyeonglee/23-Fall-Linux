#include <sys/types.h>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#define MAXLINE 256
void intHandler();
void intHandler2();
int fd2,fd3,fd4,fd5,n;
char alarmmsg[MAXLINE];
void *readServer(void *args){
	char inmsg[MAXLINE];
	while(1){
		n = read(fd5,inmsg,MAXLINE);
		printf("[Client1] -> %s\n",inmsg);
	}
	return NULL;
}

int main(){
	 fd4 = open("./chatfifo4",O_WRONLY);
	 fd5 = open("./chatfifo5",O_RDONLY);
	 if(fd4 == -1 || fd5 == -1){
		 perror("open");
		 exit(1);
	 }
	 printf("*Client2 starts \n");
	 pthread_t thread;
	 int args = 0;
	 char msg[MAXLINE];
	 pthread_create(&thread,NULL,readServer,(void*)&args);
	 signal(SIGINT, intHandler);
         signal(SIGALRM, intHandler2);
	 while(1){
		 printf("[Client]:");
		 fgets(msg,MAXLINE,stdin);
		 write(fd4,msg,strlen(msg)+1);
	 }
	 pthread_join(thread,NULL);
}
void intHandler(){
        int sec;
        printf("\n예약전송[Client]:");
        fgets(alarmmsg,MAXLINE,stdin);
        printf("시간 설정(초단위):");
        scanf("%d",&sec);
        alarm(sec);
        printf("%d초 후 예약전송 완료\n",sec);
}
void intHandler2(){
        write(fd2,alarmmsg,strlen(alarmmsg)+1);
        printf("\n예약전송완료\n");
} 


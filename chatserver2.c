#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#define MAXLINE 256


int fd1, fd2,fd3 ,fd4,fd5,n1,n2;
char msg[MAXLINE];

void *readClient1(void *args){
	char inmsg[MAXLINE];
	while(1){
	n1 = read(fd2,inmsg,MAXLINE);
	printf("[Client1]->%s \n",inmsg);
	if(n1>0){
	write(fd5,inmsg,strlen(inmsg)+1);

	}
	}
	return NULL;
}
void *readClient2(void *args){
	char inmsg[MAXLINE];
	while(1){
		n2 = read(fd4,inmsg,MAXLINE);
		printf("[Client2]->%s\n",inmsg); 
		if(n2>0){
			write(fd3,inmsg,strlen(inmsg)+1);
		}
	}
	return NULL;
}

int main(){
	 
	 if(mkfifo("./chatfifo2", 0666) == -1){
                perror("mkfifo");
                exit(2);
        }
	 if(mkfifo("./chatfifo3", 0666) == -1){
                perror("mkfifo");
                exit(3);
        }
	 if(mkfifo("./chatfifo4", 0666) == -1){
                perror("mkfifo");
                exit(4);
        }
	 if(mkfifo("./chatfifo5", 0666) == -1){
                perror("mkfifo");
                exit(5);
        }
	 
	 fd2 = open("./chatfifo2", O_RDONLY);
	 fd3 = open("./chatfifo3", O_WRONLY);
	 fd4 = open("./chatfifo4", O_RDONLY);
         fd5 = open("./chatfifo5", O_WRONLY);
	 if(fd2 == -1 || fd3 == -1 || fd4== -1 || fd5 == -1){
                perror("open");
                exit(6);
        }
	 
	 pthread_t threads[2];
	 int args[4];
	 args[0] =0;
	 args[1] =1;
	 pthread_create(&threads[0],NULL,readClient1,(void*)&args[0]);
	 pthread_create(&threads[1],NULL,readClient2,(void*)&args[1]);
	 
	 printf("*Server starts\n");
	 while(1){
	 }
	 pthread_join(threads[0],NULL);
	 pthread_join(threads[1],NULL);
}





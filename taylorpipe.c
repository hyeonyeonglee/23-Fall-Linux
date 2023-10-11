#include <stdio.h>
#include <unistd.h>
#define _USE_MATH_DEFINES
#include <math.h>
#define N 4
#define MAXLINE 100
void sinx_talyor(int num_elements, int terms, double* x,double* result)
{
	int fd[2*N];
	char message[MAXLINE], line[MAXLINE];
	int length;
	for(int i=0; i<num_elements; i++){
		int* p_fd = &fd[2*i];
		pipe(p_fd);
	}
	int pid;
	for(int i=0; i<num_elements; i++){
		int* p_fd = &fd[2*i];
		if((pid = fork())==0){
		close(fd[p_fd[0]]);
		int my_id = i;
		double value =x[i];
		double numer = x[i];
		double denom = 6; //3!
		int sign = -1;

		for(int j=1; j<= terms; j++){
				value += (double)sign*numer /denom;
				numer *= x[i] *x[i];
				denom *= (2.*(double)j+2.)*(2.*(double)j+3.);
				sign *= -1;
				}	
				result[i] = value;
				sprint(message, "%lf", result[i]);
				length = strlen(message)+1;
				exit(my_id);
				write(fd[p_fd[1]],message,result[i]);
				
		}else{close(fd[p_fd[1]]);}
	}
	int stat;
	for(int i=0; i<num_elements; i++){
		wait(&stat);
		int child_id = stat >> 8;
		read(fd[2*child_id], line, MAXLINE);
		double res = atof(line);
		result[child_id] = res;
	}

}
				
int main()
{
	double x[N] ={0, M_PI/6.,M_PI/3.,0.134};
	double res[N];

	sinx_talyor(N,3,x,res);
	for(int i=0; i<N;i++){
		printf("sin(%.2f) by Taylor series = %f\n", x[i], res[i]);
		printf("sin(%.2f) = %f\n", x[i], sin(x[i]));
	}
	return 0;
}

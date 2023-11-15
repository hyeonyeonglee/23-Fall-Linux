#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>
#define N 4
#include <pthread.h>

double res[N];
typedef struct Thdata
{
	int terms;
	double* x;
	int id;
	double* result;
} Thdata;

void *TaskCode(void*argument)
{
	Thdata *data = (Thdata*)argument;
	double* x = data -> x;
	int terms = data -> terms;
	int i = data -> id;
	


		double value =x[i];
		double numer = x[i]*x[i]*x[i];
		double denom = 6; //3!
		int sign = -1;

		for(int j=1; j<= terms; j++){
				value += (double)sign*numer /denom;
				numer *= x[i] *x[i];
				denom *= (2.*(double)j+2.)*(2.*(double)j+3.);
				sign *= -1;
				}
				data->result[i] = value;
				

}
				
void sinx_talyor(int num_elements, int terms, double* x,double* result)
{
	struct Thdata thread[N];
	pthread_t threads[4];
	for(int i=0; i<num_elements; i++){
		thread[i].terms = terms;
		thread[i].x = x;
		thread[i].id = i;
		thread[i].result = result;
		pthread_create(&threads[i],NULL,TaskCode,(void*)&thread[i]);
	}
	for(int i = 0; i<4; ++i){
		pthread_join(threads[i],NULL);
		
	}
				}
int main()
{
	double x[N] ={0, M_PI/6.,M_PI/3.,0.134};
	

	sinx_talyor(N,3,x,res);
	for(int i=0; i<N;i++){
		printf("sin(%.2f) by Taylor series = %f\n", x[i], res[i]);
		printf("sin(%.2f) = %f\n", x[i], sin(x[i]));
	}
	return 0;
}

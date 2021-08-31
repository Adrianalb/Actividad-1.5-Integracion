#include<stdio.h>
#include "omp.h"
static long num_pasos=100000000;
double paso;
#define NUM_THREADS 600
void main()
{
    int i, nthreads; 
    double res, sum[NUM_THREADS];
    paso= (2.0-1.0)/num_pasos; //Ajustados a los limites de integración
    omp_set_num_threads (NUM_THREADS);
    const double startTime = omp_get_wtime();
        #pragma omp parallel

        {
            int i, id, nthrds; double x;
            id = omp_get_thread_num();
            nthrds = omp_get_num_threads();
            if(id==0){
                nthreads = nthrds;
            }
            
            for (i=id, sum[id] = 0.0; i < num_pasos; i = i+nthrds) {
                x=((i + ( (2.0-1.0) /2)) * paso) + 1.0; //Limites de integración
                sum[id] += 1/x; //función
            } 
        }

    for(i=0, res=0.0; i<nthreads;i++){
        res += sum[i]*paso;
    }

    const double endTime = omp_get_wtime();

    printf("resultado = (%lf)\n",res);
    printf("tomo (%lf) segundos\n",(endTime - startTime));
}

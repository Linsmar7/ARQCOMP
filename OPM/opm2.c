#include <stdio.h>
#include <omp.h>

#define N 100

int vetor[N], pedaco_chunk, i;
int qtde_threads, tid;

int main (){
    for (i = 0; i < N; i++) vetor[i] = i*1.0; //inicializa vetor
    pedaco_chunk = 10; //qtde de dados processados em cada thread
    #pragma omp parallel num_threads(10) private(tid, i) shared(vetor, pedaco_chunk)
    {
        #pragma omp for schedule(static, pedaco_chunk)
        for (i = 0; i < N; i++) {
            tid = omp_get_thread_num();
            printf("Thread %d, vetor[%d]: %d\n", tid, i, vetor[i]);
        }
    }
return 0;
}
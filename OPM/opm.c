#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void funcao_thread_mestre () {
    printf("Eu sou o mestre!\n");
}
void funcao_thread_escravo (int x) {
    printf("Sou o escravo número %d\n", x);
}

int main () {
    int tid;    // identificador da thread

    omp_set_num_threads(10);    // quantidade de threads

    #pragma omp parallel private (tid)  // cria um bloco de n threads
    {
        tid = omp_get_thread_num();
        printf("Ola mundo! Sou a thread %d\n", tid);
        if (tid == 0) funcao_thread_mestre();
        else funcao_thread_escravo(tid);
    }
    return 0;
}
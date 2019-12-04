#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/types.h>
#include <omp.h>

#define QTDE_LINHAS_MATRIZ 10000
#define QTDE_COLUNAS_MATRIZ 10000
#define TAM_VETOR QTDE_COLUNAS_MATRIZ
#define NUM_THREADS 100

// Ax = b
int matriz_A[QTDE_LINHAS_MATRIZ][QTDE_COLUNAS_MATRIZ]; // nao precisa ser matriz quadrada
int vetor_x[TAM_VETOR];  // tamanho do vetor x (unknowns) deve ser igual ao numero de colunas da matriz A
int vetor_b[QTDE_LINHAS_MATRIZ]; // vetor resultado (B) deve ter o mesmo numero de linha da matriz A

// funcao para gerar a matriz e o vetor
// matriz pode ser lida de arquivo, em formato CSR
int geraDados() {
  int i,j;

  srandom(25);
  // gera matriz_A
  for (i=0; i<QTDE_LINHAS_MATRIZ; i++)
    for (j=0; j<QTDE_COLUNAS_MATRIZ; j++)
      matriz_A[i][j] = random();
  // gera vetor_x
  for (i=0; i<TAM_VETOR; i++) vetor_x[i] = i+2;
  // inicializa vetor_b
  for (i=0; i<QTDE_LINHAS_MATRIZ; i++) vetor_b[i] = 0;
  return 0;
}

void zerarVetor() {
  for (int i = 0; i < TAM_VETOR; i++) {
      vetor_b[i] = 0;
  }
}
// multiplicacao sequencial do vetor pela matriz
// TO DO: implementar a funcao Ax=b e coletar o tempo sequencial
int matvecSequencial() {
  printf("Sequencial\n");
  struct timeval tv1, tv2;
  double t1, t2;
  gettimeofday(&tv1, NULL);
  t1 = (double)(tv1.tv_sec) + (double)(tv1.tv_usec)/1000000.00;
  for (int i = 0; i < QTDE_LINHAS_MATRIZ; i++) {
    for (int j = 0; j < QTDE_COLUNAS_MATRIZ; j++) {
      vetor_b[i] += vetor_x[j] * matriz_A[i][j];
    }
  }
  gettimeofday(&tv2, NULL);
  t2 = (double)(tv2.tv_sec) + (double)(tv2.tv_usec)/1000000.00;
  /*for (int i = 0; i < TAM_VETOR; i++) {
    printf("vetor_b[%d]: ", i);
    printf("%d\n", vetor_b[i]);
  }*/
  printf("O tempo de execucao sequencial foi: %lf\n", (t2-t1));
  return 0;
}

// multiplicacao paralela (OpenMP) do vetor pela matriz
// TO DO: implementar a funcao Ax=b e coletar o tempo paralelo OpenMP
int matvecHost() {
  printf("Host\n");
  int tid;
  int pedaco_chunk = 1;
  int q, w;
  struct timeval tv1, tv2;
  double t1, t2;
  omp_set_num_threads(NUM_THREADS);
  gettimeofday(&tv1, NULL);
  t1 = (double)(tv1.tv_sec) + (double)(tv1.tv_usec)/1000000.00;
    #pragma omp parallel private (tid, q, w) shared(vetor_b, vetor_x, matriz_A) // cria um bloco de n threads
    {
      tid = omp_get_thread_num();
      #pragma omp for schedule(static, pedaco_chunk)
      for (q = 0; q < QTDE_LINHAS_MATRIZ; q++) {
        for (w = 0; w < QTDE_COLUNAS_MATRIZ; w++) {
          vetor_b[q] += vetor_x[w] * matriz_A[q][w];
        }
      }
      /*#pragma omp for schedule(static, pedaco_chunk)
      for (q = 0; q < TAM_VETOR; q++) {
        printf("[Thread: %d] vetor_b[%d]: %d\n", tid, q, vetor_b[q]);
      }*/
    }
    gettimeofday(&tv2, NULL);
    t2 = (double)(tv2.tv_sec) + (double)(tv2.tv_usec)/1000000.00;
    printf("O tempo de execucao paralela foi: %lf\n", (t2-t1));
    
  return 0;
}

// multiplicacao paralela (CUDA) do vetor pela matriz
// TO DO: implementar a funcao Ax=b e coletar o tempo paralelo CUDA
int matvecDevice() {
  printf("Device\n");
  return 0;
}


int main(int argc, char * argv[]) {
  int op_exec = atoi(argv[1]);
  // programa deve gerar os dados
  geraDados();
  // programa deve realizar a multiplicacao sequencial e capturar tempo
  matvecSequencial();
  zerarVetor();
  // programa deve testar parametro da linha de comando (1 – CPU e 2 – GPU)
  if (op_exec == 1) {
    matvecHost();
    zerarVetor();
  }
  else if (op_exec == 2) {
    matvecDevice();
    zerarVetor();
  }
  //
  return 0;
}

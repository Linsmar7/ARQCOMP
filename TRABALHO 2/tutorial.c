#include <stdio.h>
#include <stdlib.h>

#define QTDE_LINHAS_MATRIZ 2
#define QTDE_COLUNAS_MATRIZ 3
#define TAM_VETOR 3

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

// multiplicacao sequencial do vetor pela matriz
// TO DO: implementar a funcao Ax=b e coletar o tempo sequencial
int matvecSequencial() {
  int i, j;
  int matriz_temp[QTDE_LINHAS_MATRIZ][QTDE_COLUNAS_MATRIZ]; // matriz temporaria

  for (j=0; j<QTDE_COLUNAS_MATRIZ; j++)  // percorre a matriz_A coluna por coluna
    for (i=0; i<QTDE_LINHAS_MATRIZ; i++) {
      // matriz_temp armazena cada entrada de A * cada elemento de X
      matriz_temp[i][j] = matriz_A[i][j] * vetor_x[j];
    }
  // gera o vetor de resultado B
  for (i=0; i<QTDE_LINHAS_MATRIZ; i++)  // percorre a matriz_temp linha a linha
    for (j=0; j<QTDE_COLUNAS_MATRIZ; j++) {
    // vetor_b = somatorio dos elementos da linha da matriz_temp
    vetor_b[i] += matriz_temp[i][j];
    }
  // debug - verifica o resultado
  for (i=0; i<QTDE_LINHAS_MATRIZ; i++) printf("%d\n", vetor_b[i]);
  return 0;
}

// multiplicacao paralela (OpenMP) do vetor pela matriz
// TO DO: implementar a funcao Ax=b e coletar o tempo paralelo OpenMP
int matvecHost() {
  printf("matvecHost\n");
  return 0;
}

// multiplicacao paralela (CUDA) do vetor pela matriz
// TO DO: implementar a funcao Ax=b e coletar o tempo paralelo CUDA
int matvecDevice() {
  printf("matvecDevice\n");
  return 0;
}


int main(int argc, char * argv[]) {
  int op_exec = atoi(argv[1]);
  // programa deve gerar os dados
  geraDados();
  // programa deve realizar a multiplicacao sequencial e capturar tempo
  matvecSequencial();
  // programa deve testar parametro da linha de comando (1 – CPU e 2 – GPU)
  if (op_exec == 1) matvecHost();
  else if (op_exec == 2) matvecDevice();
  //
  return 0;
}

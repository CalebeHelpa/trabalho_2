#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"
#include "SistemasLineares.h"

/*!
  \brief Essa função calcula a norma L2 do resíduo de um sistema linear 

  \param SL Ponteiro para o sistema linear
  \param x Solução do sistema linear
  \param res Valor do resíduo

  \return Norma L2 do resíduo.
*/
real_t normaL2Residuo(SistLinear_t *SL, real_t *x, real_t *res)
{

}

real_t *retroSubst(SistLinear_t *SL){
  real_t *resposta;
  resposta = (real_t *)malloc(SL->n * (sizeof (real_t)));

  int i, j;
  for(i = SL->n-1; i >= 0; i--){
    resposta[i] = SL->b[i];
    for(j = i+1; j <= SL->n-1; j++)
      resposta[i] -= SL->A[i][j] * resposta[j];
    resposta[i] = resposta[i] / SL->A[i][i];
  }
  return resposta;
}

/*!
  \brief Método da Eliminação de Gauss

  \param SL Ponteiro para o sistema linear
  \param x ponteiro para o vetor solução
  \param tTotal tempo gasto pelo método

  \return código de erro. 0 em caso de sucesso.
*/
int eliminacaoGauss (SistLinear_t *SL, real_t *x, double *tTotal){
  int i, j, k;
  for(i = 0; i < SL->n-1; i++){
    for(k = i+1; k < SL->n; k++){
      if(fabs(SL->A[i][i])<fabs(SL->A[k][i])){
        double temp;
        for( j = 0; j < SL->n; j++){                
          temp = SL->A[i][j];
          SL->A[i][j] = SL->A[k][j];
          SL->A[k][j] = temp;
        }
        temp = SL->b[i];
        SL->b[i] = SL->b[k];
        SL->b[k] = temp;
      }
    }

    for(k = i+1; k < SL->n; k++){
      double m = SL->A[k][i] / SL->A[i][i];
      SL->A[k][i] = 0.0;
      for(int j=i+1; j < SL->n; j++)
        SL->A[k][j] -= SL->A[i][j] * m;
      SL->b[k] -= SL->b[i] * m;
    }
  }
  x = retroSubst(SL);
  printf("\n\nRESPOSTAS:\t%1.4f\t%1.4f\n\n", x[0], x[1]);
  return 0;
}

/*!
  \brief Método de Jacobi

  \param SL Ponteiro para o sistema linear
  \param x ponteiro para o vetor solução. Ao iniciar função contém
            valor inicial
  \param tTotal tempo gasto pelo método

  \return código de erro. Um nr positivo indica sucesso e o nr
          de iterações realizadas. Um nr. negativo indica um erro:
          -1 (não converge) -2 (sem solução)
*/
int gaussJacobi (SistLinear_t *SL, real_t *x, double *tTotal)
{


}

/*!
  \brief Método de Gauss-Seidel

  \param SL Ponteiro para o sistema linear
  \param x ponteiro para o vetor solução. Ao iniciar função contém
            valor inicial
  \param tTotal tempo gasto pelo método

  \return código de erro. Um nr positivo indica sucesso e o nr
          de iterações realizadas. Um nr. negativo indica um erro:
          -1 (não converge) -2 (sem solução)
  */
int gaussSeidel (SistLinear_t *SL, real_t *x, double *tTotal)
{


}


/*!
  \brief Método de Refinamento

  \param SL Ponteiro para o sistema linear
  \param x ponteiro para o vetor solução. Ao iniciar função contém
            valor inicial para início do refinamento
  \param tTotal tempo gasto pelo método

  \return código de erro. Um nr positivo indica sucesso e o nr
          de iterações realizadas. Um nr. negativo indica um erro:
          -1 (não converge) -2 (sem solução)
  */
int refinamento (SistLinear_t *SL, real_t *x, double *tTotal)
{


}


/*-------------------------------------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------------------------*/

/*!
  \brief Alocaçao de memória 

  \param n tamanho do SL

  \return ponteiro para SL. NULL se houve erro de alocação
*/
SistLinear_t* alocaSistLinear (unsigned int n){
  SistLinear_t *sistema;
  sistema = (SistLinear_t *)malloc(sizeof(SistLinear_t));

  sistema->A = (real_t **)malloc(n * sizeof(real_t *));
  for(int i = 0; i < n; i++){
    sistema->A[i] = (real_t *)malloc(n * sizeof(real_t));
  }

  sistema->b = (real_t *)malloc(n * sizeof(real_t));

  return sistema;
}



/*!
  \brief Liberaçao de memória 

  \param sistema linear SL
*/
void liberaSistLinear (SistLinear_t *SL){
  for(int i = 0; i < SL->n; i++){
    free(SL->A[i]);
  }
  free(SL->A);
  SL->A = NULL;
  free(SL->b);
  SL->b = NULL;
}



/*!
  \brief Leitura de SL a partir de Entrada padrão (stdin).

  \return sistema linear SL. NULL se houve erro (leitura ou alocação)
*/
SistLinear_t *lerSistLinear(){
  SistLinear_t *sistema;
  unsigned int tamanho;
    
  scanf("%u", &tamanho);
  sistema = alocaSistLinear(tamanho);
  sistema->n = tamanho;
  scanf("%f", &sistema->erro);

  char buf[1024];
  const char s[2] = " ";
  char *token;

  getc(stdin);
  for(int i = 0; i < sistema->n; i++){
    fgets(buf, 1024, stdin);
    token = strtok(buf, s);
    for(int j = 0; j < sistema->n; j++){
      if(token != NULL){
        //printf("Linha: %d   Coluna: %d   Token: %s\n", i, j, token);
        sistema->A[i][j] = (real_t)atof(token);
        token = strtok(NULL, s);
      }
    }
  }

  fgets(buf, 1024, stdin);
  token = strtok(buf, s);
  for(int k = 0; k < sistema->n; k++){
    if(token != NULL){
      //printf("Linha: %d   Token: %s\n", k, token);
      sistema->b[k] = (real_t)atof(token);
      token = strtok(NULL, s);
    }
  }

  return sistema;
}



// Exibe SL na saída padrão
void prnSistLinear (SistLinear_t *SL){
  for(int i = 0; i < SL->n; i++){
    for(int j = 0; j < SL->n; j++)
      printf("%1.4f   ", SL->A[i][j]);
    printf("\n");
  }
}



// Exibe um vetor na saída padrão
void prnVetor (real_t *v, unsigned int n){
  for(int i = 0; i < n; i++)
    printf("%1.4f   ", v[i]);
  printf("\n");
}
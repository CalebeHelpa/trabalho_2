#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "utils.h"
#include "SistemasLineares.h"

int main(){
    SistLinear_t *sistema;
    sistema = lerSistLinear();
    
    printf("\nMATRIZ ANTES:\n");
    prnSistLinear(sistema);
    printf("\nVETOR ANTES:\n");
    prnVetor(sistema->b, sistema->n);
    
    real_t *resposta;
    resposta = malloc(sistema->n * (sizeof(real_t)));
    double tTotal;
    eliminacaoGauss(sistema, resposta, &tTotal);
    printf("\n\nRESPOSTAS:\t%f\t%1.4f\n\n", resposta, resposta[1]);
    
    printf("\nMATRIZ DEPOIS:\n");
    prnSistLinear(sistema);
    printf("\nVETOR DEPOIS:\n");
    prnVetor(sistema->b, sistema->n);

    printf("\nRESPOSTA:\n");
    prnVetor(resposta, sistema->n);
    
    liberaSistLinear(sistema);
    free(resposta);
}
#include <stdio.h>
#include <stdlib.h>
#include "arvore_avl.h"

int main() 
{
    TreeAVL *treeAVL = ConstructTreeAVL();

    int vetor[] = {10, 20, 5, 8, 7};
    int vetor_lenght = sizeof(vetor) / sizeof(int);
   
    for(int i=0; i<vetor_lenght; i++)
    {
        inserir(treeAVL, vetor[i]);
        printf("\n");
    }
    imprimir(treeAVL);
    printf("\n======\n");


    printf("TAMANHO:%d", tamanho(treeAVL));

    FreeTreeAVL(treeAVL);

    return 0;
}


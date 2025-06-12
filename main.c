#include <stdio.h>
#include <stdlib.h>
#include "arvore_avl.h"

int main() 
{
    TreeAVL *treeAVL = ConstructTreeAVL();

    int vetor[] = {15, 30, 10, 40, 50, 25};
    int vetor_lenght = sizeof(vetor) / sizeof(int);
   
    for(int i=0; i<vetor_lenght; i++)
    {
        inserir(treeAVL, vetor[i]);
    }
    printf("\n======\n");
    imprimir(treeAVL);


    printf("ALTURA:%d", altura(treeAVL));

    FreeTreeAVL(treeAVL);

    return 0;
}


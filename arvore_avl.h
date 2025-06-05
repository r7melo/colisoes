#include <stdio.h>
#include <stdlib.h>

typedef struct no 
{
    int valor;
    int pivo;
    int esq_size;
    int dir_size;
    struct no *dir;
    struct no *esq;
} Tno;

typedef struct 
{
    Tno *raiz;
    int quantidade;
} TreeAVL;

TreeAVL *ConstructTreeAVL()
{
    TreeAVL *treeAVL = malloc(sizeof(TreeAVL));
    treeAVL->raiz =  NULL;
    treeAVL->quantidade = 0;
    return treeAVL;
}

Tno *ConstructNoAVL(int valor)
{
    Tno *no = malloc(sizeof(Tno));
    no->valor = valor;
    no->esq = NULL;
    no->dir = NULL;
    no->esq_size = 0;
    no->dir_size = 0;
    no->pivo = 0;
}

void __imprimir_nivel(int nivel)
{
    for(int i=0; i<nivel; i++)
        printf("    ");
}

void __imprimir(Tno *no, int nivel) 
{
    if(no->dir != NULL)
    {

        __imprimir_nivel(nivel);
        printf("(%d):%d>\n", no->dir->valor,no->pivo);
        __imprimir(no->dir, nivel+1); 
    }
    
    if(no->esq != NULL) 
    {
        __imprimir_nivel(nivel);
        printf("<%d:(%d)\n",  no->pivo, no->esq->valor);
        __imprimir(no->esq, nivel+1);
    }
}

void imprimir(TreeAVL *tree)
{
    printf("\n<%d:%d>\n", tree->raiz->valor, tree->raiz->pivo);
    __imprimir(tree->raiz, 1);
}

int __inserir(Tno *no, int valor)
{
    int esq_size = 0;
    int dir_size = 0;

    if(valor < no->valor)
    {
        if(no->esq == NULL)
        {
            no->esq = ConstructNoAVL(valor);
            no->esq_size = 1;
        }
        else
        {
            no->pivo = __inserir(no->esq, valor);
        }
    }

    if(valor > no->valor)
    {
        if(no->dir == NULL)
        {
            no->dir = ConstructNoAVL(valor);
            no->dir_size = 1;
        }
        else
        {
            no->pivo = __inserir(no->dir, valor);
        }
    }

    return tamanho(no->esq) - tamanho(no->dir);        
}

void inserir(TreeAVL *tree, int valor) 
{
    if(tree->raiz == NULL)
    {
        tree->raiz = ConstructNoAVL(valor);
    }
    else
    {
        tree->raiz->pivo = __inserir(tree->raiz, valor);
    }
}

int __tamanho(Tno *no)
{
    if(no == NULL) return 1;

    int esq = __tamanho(no->esq);
    int dir = __tamanho(no->dir);

    if(esq > dir) return esq + 1;
    else return dir + 1;
}

int tamanho(TreeAVL *tree)
{
    return __tamanho(tree->raiz) - 1;
}

void __FreeTreeAVL(Tno *no)
{
    if(no == NULL) return;

    __FreeTreeAVL(no->esq);
    __FreeTreeAVL(no->dir);

    free(no);
}

void FreeTreeAVL(TreeAVL *tree)
{
    __FreeTreeAVL(tree->raiz);    
}
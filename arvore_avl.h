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
    __imprimir_nivel(nivel);
    printf("%d(%d)%d>\n", no->esq_size, no->valor, no->dir_size);

    if(no->dir != NULL)
        __imprimir(no->dir, nivel+1); 
    
    if(no->esq != NULL) 
        __imprimir(no->esq, nivel+1);
    
}

void imprimir(TreeAVL *tree)
{
    __imprimir(tree->raiz, 0);
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

int __inserir(Tno *no, int valor)
{
    
    if(valor < no->valor)
    {
        printf(" %d<-%d  ", valor, no->valor);
        
        
        if(no->esq == NULL)
        {
            no->esq = ConstructNoAVL(valor);
        }
        else
        {
            no->esq_size = __inserir(no->esq, valor);
            
        }    
        no->esq_size ++;
    }
    else if(valor > no->valor)
    {
        printf(" %d[%d->%d]", no->pivo, no->valor, valor);
        
        if(no->dir == NULL)
        {
            no->dir = ConstructNoAVL(valor);    
        }
        else
        {
            __inserir(no->dir, valor);
        }
        no->dir_size++;
    }   


    return 0;
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



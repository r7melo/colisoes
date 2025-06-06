#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef struct no 
{
    int valor;
    int pivo;
    int is_father;
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

    return no;
}

void __imprimir_nivel(int nivel)
{
    for(int i=0; i<nivel; i++)
        printf("        ");
}

void __imprimir(Tno *no, int nivel) 
{
    __imprimir_nivel(nivel);
    printf("%d(%d:%d)%d\n", no->esq_size, no->valor, no->pivo, no->dir_size);

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
    if(tree->raiz->esq_size > tree->raiz->dir_size)
        return tree->raiz->esq_size;
    else 
        return tree->raiz->dir_size;
}

void __RE(Tno *no)
{   
    // A:no -> B:aux -> C
    Tno *aux = no->dir;
    no->dir = aux->esq;
    aux->esq = no;
    no = aux;
}

void __inserir(Tno *no, int valor)
{
    
    if(valor < no->valor)
    {
        if(no->esq == NULL)
        {
            no->esq = ConstructNoAVL(valor);
            no->esq_size++;
        }
        else
        {
            __inserir(no->esq, valor);
            no->esq_size = __tamanho(no->esq) -1;
        }  
    }
    else if(valor > no->valor)
    {
        if(no->dir == NULL)
        {
            no->dir = ConstructNoAVL(valor);
            no->dir_size++;
        }
        else
        {
            __inserir(no->dir, valor);
            no->dir_size = __tamanho(no->dir) -1;
        }
    }   

    no->pivo = no->esq_size - no->dir_size;

    if(no->pivo <-1)
    {
        if(no->dir->pivo < 0)
        {
            __RE(no);
        }
    }
}

void inserir(TreeAVL *tree, int valor) 
{
    if(tree->raiz == NULL)
    {
        tree->raiz = ConstructNoAVL(valor);
    }
    else
    {
        __inserir(tree->raiz, valor);
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



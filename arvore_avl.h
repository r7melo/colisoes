#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef struct no 
{
    int valor;
    int pivo;
    int is_father;
    int esq_alt;
    int dir_alt;
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
    no->esq_alt = 0;
    no->dir_alt = 0;
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
    printf("%d(%d:%d)%d\n", no->esq_alt, no->valor, no->pivo, no->dir_alt);

    if(no->dir != NULL)
        __imprimir(no->dir, nivel+1); 
    
    if(no->esq != NULL) 
        __imprimir(no->esq, nivel+1);
    
}

void imprimir(TreeAVL *tree)
{
    __imprimir(tree->raiz, 0);
}

int __altura(Tno *no)
{
    if(no == NULL) return 1;

    int esq = __altura(no->esq);
    int dir = __altura(no->dir);

    if(esq > dir) return esq + 1;
    else return dir + 1;
}

int altura(TreeAVL *tree)
{
    if(tree->raiz->esq_alt > tree->raiz->dir_alt)
        return tree->raiz->esq_alt;
    else 
        return tree->raiz->dir_alt;
}

Tno *__RE(Tno *no)
{   
    // A:no -> B:aux -> C
    Tno *aux = no->dir;
    no->dir = aux->esq;
    aux->esq = no;

    no->esq_alt = __altura(no->esq) -1;
    no->dir_alt = __altura(no->dir) -1;
    no->pivo = no->esq_alt - no->dir_alt;

    aux->esq_alt = __altura(aux->esq) -1;
    aux->dir_alt = __altura(aux->dir) -1;
    aux->pivo = aux->esq_alt - aux->dir_alt;

    return aux; 
}

Tno* __RD(Tno* no)
{
    Tno* aux = no->esq;
    no->esq = aux->dir;
    aux->dir = no;

    no->esq_alt = __altura(no->esq) -1;
    no->dir_alt = __altura(no->dir) -1;
    no->pivo = no->esq_alt - no->dir_alt;

    aux->esq_alt = __altura(aux->esq) -1;
    aux->dir_alt = __altura(aux->dir) -1;
    aux->pivo = aux->esq_alt - aux->dir_alt;

    return aux;
}


Tno *__inserir(Tno *no, int valor)
{
    if (no == NULL)
        return ConstructNoAVL(valor);

    if(valor < no->valor)
    {
        no->esq = __inserir(no->esq, valor);
    }
    else if(valor > no->valor)
    {
        no->dir = __inserir(no->dir, valor);
    }   

    no->esq_alt = __altura(no->esq) -1;
    no->dir_alt = __altura(no->dir) -1 ;
    no->pivo = no->esq_alt - no->dir_alt;

    if(no->pivo <-1)
    {
        if(no->dir && no->dir->pivo < 0)
        {
            no = __RE(no);
        }
        else if(no->dir)
        {
            no->dir = __RD(no->dir);
            return __RE(no);
        }
    }
    else if(no->pivo > 1)
    {
        if(no->esq && no->esq->pivo > 0)
        {
            return __RD(no);
        }
        else if(no->esq)
        {
            no->esq = __RE(no->esq);
            return __RD(no);
        }
    }

    return no;  
}

void inserir(TreeAVL *tree, int valor) 
{
    if(tree->raiz == NULL)
    {
        tree->raiz = ConstructNoAVL(valor);
    }
    else
    {
       tree->raiz = __inserir(tree->raiz, valor);
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



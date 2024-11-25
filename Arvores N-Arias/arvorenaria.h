#include <stdio.h>
#include <stdlib.h>

#define TAM_FLORESTA 10

typedef struct no {
    char valor;
    struct no *primogenito;
    struct no *proxIrmao;
} noArv;

noArv* criarArv(char x);
void insereArv(noArv *a, noArv *sa);
void imprimirArv(noArv *a, int profundidade);
int pertenceArv(noArv *a, char c);
int alturaArv(noArv *a);
void imprimirIrmaos(noArv *n);
void liberarArvore(noArv *a);
noArv* interseccaoArvores(noArv *arv1, noArv *arv2);
noArv* uniaoArvores(noArv *arv1, noArv *arv2);
noArv* interseccaoArvores(noArv *arv1, noArv *arv2);
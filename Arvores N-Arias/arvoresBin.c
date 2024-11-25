#include <stdlib.h>
#include <stdio.h>

typedef struct no{
    int valor;
    struct no *direita, *esquerda;
} NoArv;

NoArv *inserirVersao1(NoArv *raiz, int valor){
    if(raiz == NULL){
        NoArv *aux = malloc(sizeof(NoArv));
        aux->valor = valor;
        aux->esquerda = NULL;
        aux->direita = NULL;
        return aux;
    }
    else{
        if(valor < raiz->valor)
            raiz->esquerda = inserirVersao1(raiz->esquerda, valor);
        else   
            raiz->direita = inserirVersao1(raiz->direita, valor);
        return raiz;
    }
}

void imprimirArvoreOrdenada(NoArv *raiz){
    if(raiz){
        imprimirArvoreOrdenada(raiz->esquerda);
        printf("%d ", raiz->valor);
        imprimirArvoreOrdenada(raiz->direita);
    }
}

void imprimirArvore(NoArv *raiz){
    if(raiz){
        printf("%d ", raiz->valor);
        imprimirArvore(raiz->esquerda);
        imprimirArvore(raiz->direita);
    }
}

int main(){
    NoArv *raiz = NULL;

    raiz = inserirVersao1(raiz, 50);
    raiz = inserirVersao1(raiz, 25);
    raiz = inserirVersao1(raiz, 100);
    raiz = inserirVersao1(raiz, 30);

    imprimirArvore(raiz);
    printf("\n");
    imprimirArvoreOrdenada(raiz);
    return 0;
}
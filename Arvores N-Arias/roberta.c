#include <stdio.h>
#include <stdlib.h>

#define TAM_FLORESTA 10

typedef struct no {
    char valor;
    struct no *primogenito;
    struct no *proxIrmao;
} noArv;

noArv* criarArv(char x) {
    noArv *a = (noArv*) malloc(sizeof(noArv));
    a->valor = x;
    a->primogenito = NULL;
    a->proxIrmao = NULL;
    return a;
}

noArv *buscaChave(char chaveParametro, noArv *raiz) {
    if (raiz == NULL) 
        return NULL;
    if (raiz->valor == chaveParametro) 
        return raiz;
    noArv *p = raiz->primogenito;
    while (p) {
        noArv *resp = buscaChave(chaveParametro, p);
        if (resp) 
            return resp;
        p = p->proxIrmao;
    }
    return NULL;
}

int insereArvore(noArv *raiz, char chavePai, char novaChave) {
    noArv *pai = buscaChave(chavePai, raiz);
    if (!pai) 
        return 0;
        
    noArv *filho = criarArv(novaChave);

    if (!pai->primogenito) 
            pai->primogenito = filho;
    else {
        noArv *p = pai->primogenito;
        while (p->proxIrmao) 
            p = p->proxIrmao;
        p->proxIrmao = filho;
    }
    return 1;
}

// Função para imprimir a árvore com formatação e indentação
void imprimirArv(noArv *a, int profundidade) {
    if (a == NULL)
        return;

    // Imprime espaços para a indentação com base na profundidade
    for (int i = 0; i < profundidade; i++) {
        printf("  ");  // Dois espaços por nível para indentação
    }
    // Imprime o valor do nó
    printf("%c\n", a->valor);
    // Imprime todos os filhos (primogenito e irmãos)
    for (noArv *p = a->primogenito; p != NULL; p = p->proxIrmao) {
        imprimirArv(p, profundidade + 1);  // Aumenta a profundidade para os filhos
    }
}

int main(){
    noArv *raiz;

    raiz = criarArv('a'); //raízes das arvores

    insereArvore(raiz, 'a', 'b');
    insereArvore(raiz, 'a', 'c');
    insereArvore(raiz, 'c', 'd');
    insereArvore(raiz, 'd', 'b');

    imprimirArv(raiz, 0);
    return 0;
}
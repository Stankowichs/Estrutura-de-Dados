#include "arvorenaria.h"

// Função para criar um novo nó da árvore
noArv* criarArv(char x) {
    noArv *a = (noArv*) malloc(sizeof(noArv));
    a->valor = x;
    a->primogenito = NULL;
    a->proxIrmao = NULL;
    return a;
}

void inserirArv(noArv *a, noArv *sa){
    sa->proxIrmao = a->primogenito;
    a->primogenito = sa;
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

int pertenceArv(noArv *a, char c){
    if(a == NULL){
        printf("Arvore inexistente\n");    
        return 0;
    }

    noArv *p;
    if(a->valor == c)
        return 1;
    else{
        for(p = a->primogenito; p!= NULL; p = p->proxIrmao){
            if(pertenceArv(p, c))
                return 1;
        }

        return 0;
    }
}

int alturaArv(noArv *a){
    int hMax = -1;
    noArv *p;

    for(p = a->primogenito; p != NULL; p = p->proxIrmao){
        int h = alturaArv(p);
        if(h > hMax)
            hMax = h;
    }

    return hMax + 1;
}

void imprimirIrmaos(noArv *n) {
    noArv *p = n;
    while (p != NULL) {
        printf("%c ", p->valor);
        p = p->proxIrmao;
    }
    printf("\n");
}

void liberarArvore(noArv *a){
    noArv *p = a->primogenito;
    while(p != NULL){
        noArv *t = p->proxIrmao;
        liberarArvore(p);
        p = t;
    }
    free(a);
}

void removerSubarvore(noArv **raiz, char valor) {
    if (*raiz == NULL) 
        return;
    // Se o nó a ser removido é a própria raiz
    if ((*raiz)->valor == valor) {
        liberarArvore(*raiz);
        *raiz = NULL;
        return;
    }
    // Busca o nó pai do nó que contém o valor a ser removido
    noArv *pai = NULL;
    noArv *atual = *raiz;
    noArv *anterior = NULL;

    while (atual != NULL) {
        if (atual->valor == valor) 
            break;
        anterior = atual;
        pai = atual;
        atual = atual->primogenito;
        while (atual != NULL && atual->valor != valor) {
            anterior = atual;
            atual = atual->proxIrmao;
        }
    }

    if (atual == NULL) {
        printf("Valor não encontrado na árvore.\n");
        return;
    }
    // Se o nó a ser removido é o primogênito
    if (pai->primogenito == atual) 
        pai->primogenito = atual->proxIrmao;
    else 
        // Se o nó a ser removido é um irmão, ajusta o ponteiro do anterior
        anterior->proxIrmao = atual->proxIrmao;

    // Libera a subárvore a partir do nó encontrado
    liberarArvore(atual);
}

// Função para interseção de duas árvores
noArv* interseccaoArvores(noArv *arv1, noArv *arv2) {
    if (arv1 == NULL || arv2 == NULL)
        return NULL;

    noArv *resultado = NULL;

    // Verifica se o valor do nó em arv1 também existe em arv2
    if (pertenceArv(arv2, arv1->valor)) 
        resultado = criarArv(arv1->valor);

    // A interseção ocorre para cada filho de arv1
    for (noArv *p = arv1->primogenito; p != NULL; p = p->proxIrmao) {
        noArv *subResultado = interseccaoArvores(p, arv2);
        if (subResultado != NULL) {
            if (resultado == NULL) 
                resultado = subResultado;
            else 
                inserirArv(resultado, subResultado);
        }
    }

    return resultado;
}

noArv* uniaoArvores(noArv *raiz1, noArv *raiz2) {
    if (raiz1 == NULL) return raiz2;
    if (raiz2 == NULL) return raiz1;

    noArv *resultado = criarArv(raiz1->valor);

    // Função auxiliar para adicionar nós sem duplicatas
    void adicionarNosSemDuplicatas(noArv *destino, noArv *origem) {
        if (origem == NULL) return;

        if (!pertenceArv(destino, origem->valor)) {
            noArv *novoNo = criarArv(origem->valor);
            inserirArv(destino, novoNo);
        }

        for (noArv *p = origem->primogenito; p != NULL; p = p->proxIrmao) {
            adicionarNosSemDuplicatas(destino, p);
        }
    }

    // Adiciona todos os nós de raiz1 e raiz2 ao resultado
    adicionarNosSemDuplicatas(resultado, raiz1);
    adicionarNosSemDuplicatas(resultado, raiz2);

    return resultado;
}

// Função para verificar se árvore `a` é contida em árvore `b`
int contido(noArv *a, noArv *b) {
    // Caso base: Se `a` for NULL, está contido em qualquer árvore `b`
    if (a == NULL) return 1;
    // Se `a` não for NULL e `b` for NULL, então `a` não está contido em `b`
    if (b == NULL) return 0;
    // Verifica se as raízes são iguais
    if (a->valor == b->valor) {
        noArv *pA = a->primogenito;
        noArv *pB = b->primogenito;
        // Verifica todos os filhos
        while (pA != NULL) {
            if (!contido(pA, pB)) 
                return 0;
            pA = pA->proxIrmao;
            if (pB != NULL) 
                pB = pB->proxIrmao;
        }
        return 1;
    }
    // Caso contrário, verifica os irmãos de `b`
    return contido(a, b->proxIrmao);
}

// Função para verificar se árvore `b` contém árvore `a`
int contem(noArv *b, noArv *a) {
    // Caso base: se `a` for NULL, então `b` contém `a`
    if (a == NULL) return 1;
    // Se `b` é NULL e `a` não ��, `b` não contém `a`
    if (b == NULL) return 0;
    // Verifica se `a` está contido em `b`
    if (contido(a, b)) return 1;
    // Recursivamente verifica todos os filhos e irmãos de `b`
    return contem(b->primogenito, a) || contem(b->proxIrmao, a);
}

noArv* diferencaArvores(noArv *arv1, noArv *arv2) {
    if (arv1 == NULL) 
        return NULL;

    // Verifica se o nó atual de arv1 não está em arv2
    noArv *resultado = NULL;
    if (!pertenceArv(arv2, arv1->valor)) 
        resultado = criarArv(arv1->valor);

    // Percorre os filhos de arv1, criando subárvores de diferença
    noArv *filhoArv1 = arv1->primogenito;
    noArv *ultimoFilho = NULL;
    while (filhoArv1 != NULL) {
        noArv *subResultado = diferencaArvores(filhoArv1, arv2);

        if (subResultado != NULL) {
            // Conecta o subResultado como filho ou irmão
            if (resultado == NULL) 
                resultado = subResultado;
            else if (ultimoFilho == NULL) {
                resultado->primogenito = subResultado;
                ultimoFilho = subResultado;
            } else {
                ultimoFilho->proxIrmao = subResultado;
                ultimoFilho = subResultado;
            }
        }
        filhoArv1 = filhoArv1->proxIrmao;
    }

    return resultado;
}

noArv* complementoArvores(noArv *arv1, noArv *arv2) {
    if (arv2 == NULL) 
        return NULL;

    noArv *resultado = NULL;

    // Adiciona o nó de arv2 ao resultado se ele não estiver em arv1
    if (!pertenceArv(arv1, arv2->valor)) 
        resultado = criarArv(arv2->valor);

    // Percorre os filhos de arv2 para processar os nós recursivamente
    noArv *filhoArv2 = arv2->primogenito;
    noArv *ultimoFilho = NULL;
    while (filhoArv2 != NULL) {
        noArv *subResultado = complementoArvores(arv1, filhoArv2);

        if (subResultado != NULL) {
            // Conecta o subResultado como filho ou irmão
            if (resultado == NULL) 
                resultado = subResultado;
            else if (ultimoFilho == NULL) {
                resultado->primogenito = subResultado;
                ultimoFilho = subResultado;
            } else {
                ultimoFilho->proxIrmao = subResultado;
                ultimoFilho = subResultado;
            }
        }
        filhoArv2 = filhoArv2->proxIrmao;
    }

    return resultado;
}

int main() {
    noArv *floresta[TAM_FLORESTA];

    floresta[0] = criarArv('a'); //raízes das arvores
    floresta[1] = criarArv('a'); //raízes das arvores

    insereArvore(floresta[0], 'a', 'b');
    // insereArvore(floresta[0], 'a', 'c');
    // insereArvore(floresta[0], 'c', 'd');
    insereArvore(floresta[1], 'a', 'b');
    insereArvore(floresta[1], 'a', 'e');
    insereArvore(floresta[1], 'e', 'f');
    // insereArvore(floresta[1], 'a', 'c');
    // insereArvore(floresta[1], 'n', 'g');

    // removerSubarvore(&floresta[1], 'b');

    noArv *intersecao = interseccaoArvores(floresta[0], floresta[1]);
    noArv *uniao = uniaoArvores(floresta[0], floresta[1]);

    // Impressão de cada árvore na floresta
    for (int i = 0; i < 2; i++) {
        printf("Arvore %d:\n", i+1);
        imprimirArv(floresta[i], 0);
    }

    // printf("\nIntersecao das arvores:\n");
    // if(intersecao == NULL)
    //     printf("Nao existe valores em comum\n");
    // imprimirArv(intersecao, 0);

    printf("\nUniao das arvores:\n");
    imprimirArv(uniao, 0);

    // noArv *diferenca = diferencaArvores(floresta[0], floresta[1]);
    // if (diferenca != NULL) {
    //     printf("Diferenca das arvores:\n");
    //     imprimirArv(diferenca, 0);
    // } else 
    //     printf("Nao ha diferenca entre as arvores.\n");


    // noArv *complemento = complementoArvores(floresta[0], floresta[1]);
    // if (complemento != NULL) {
    //     printf("Complemento da segunda arvore em relacao ao conjunto universo:\n");
    //     imprimirArv(complemento, 0);
    // } 
    // else 
    //     printf("Nao ha complemento em relacao ao conjunto universo.\n");

    // if(contido(floresta[1], floresta[0]))
    //     printf("esta contido\n");
    // else
    //     printf("nao esta contido\n");
    // if(contem(floresta[1], floresta[0]))
    //     printf("contem\n");
    // else
    //     printf("nao contem\n");

    for(int i = 0; i < 2; i++)
        liberarArvore(floresta[i]);

    return 0;
}
#include "arvorenaria.h"

// Função para criar um novo nó da árvore
noArv* criarArv(char x) {
    noArv *a = (noArv*) malloc(sizeof(noArv));
    a->valor = x;
    a->primogenito = NULL;
    a->proxIrmao = NULL;
    return a;
}

// Função para inserir um nó como o último filho de outro nó
void inserirArv(noArv *a, noArv *sa) {
    if (a->primogenito == NULL) {
        a->primogenito = sa;  // Se não tiver filhos, o nó se torna o primeiro filho
    } 
    else {
        noArv *p = a->primogenito;
        while (p->proxIrmao != NULL) {
            p = p->proxIrmao;  // Vai até o último irmão
        }
        p->proxIrmao = sa;  // Insere o novo nó no final da lista de irmãos
    }
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

int main() {
    // Criação dos nós da árvore
    noArv *a = criarArv('a');
    noArv *b = criarArv('b');
    noArv *c = criarArv('c');
    noArv *d = criarArv('d');
    noArv *e = criarArv('e');
    noArv *f = criarArv('f');
    noArv *g = criarArv('g');
    noArv *h = criarArv('h');
    noArv *i = criarArv('i');
    noArv *j = criarArv('j');

    // Estruturação da árvore
    inserirArv(c, d);
    inserirArv(b, e);
    inserirArv(b, c);
    inserirArv(i, j);
    inserirArv(g, i);
    inserirArv(g, h);
    inserirArv(a, g);
    inserirArv(a, f);
    inserirArv(a, b);

    if(pertenceArv(a, 'c'))
        printf("Esse valor pertence a arvore\n");
    else
        printf("Esse valor nao pertece a arvore\n");

    printf("Estrutura da arvore:\n");
    imprimirArv(a, 0);

    printf("\nOs irmaos da altura %d sao: ", alturaArv(a));
    imprimirIrmaos(a);
    
    liberarArvore(a);
    return 0;
}

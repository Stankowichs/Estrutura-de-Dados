#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _livro {
    float preco;
    char titulo[100];
    unsigned int numPaginas;
} Livro;

typedef struct vetorLivros {
    Livro **vet;
    int size;
} VetorLivros;

typedef struct _aluno {
    char nome[100];
    int idade;
    Livro *livroFavorito;
} Aluno;

Livro *createLivro(char *titulo, float preco, unsigned int numPaginas) {
    Livro *livro = calloc(1, sizeof(Livro));

    strcpy(livro->titulo, titulo);
    livro->preco = preco;
    livro->numPaginas = numPaginas;

    return livro;
}

Livro *copyLivro(Livro *livro) {
    return createLivro(livro->titulo, livro->preco, livro->numPaginas);
}

Aluno *createAluno(char *nome, int idade, Livro *livro) {
    Aluno *aluno = (Aluno *) calloc(1, sizeof(Aluno));

    strcpy(aluno->nome, nome);
    aluno->idade = idade;
    aluno->livroFavorito = copyLivro(livro);

    return aluno;
}

void imprimirLivro(Livro *livro) {
    printf("Titulo: %s\n", livro->titulo);
    printf("Preco: %.2f\n", livro->preco);
    printf("Numero de paginas: %u\n\n", livro->numPaginas);
}

void imprimirAluno(Aluno *aluno) {
    printf("Nome: %s\n", aluno->nome);
    printf("Idade: %d\n", aluno->idade);
    puts("Livro Favorito:");
    puts("------");
    imprimirLivro(aluno->livroFavorito);
}

void deleteLivro(Livro **livroRef) {
    Livro *livro = *livroRef;
    free(livro);
    *livroRef = NULL;
}

void deleteAluno(Aluno **alunoRef) {
    Aluno *aluno = *alunoRef;
    free(aluno);
    *alunoRef = NULL;
}

void destroyVetL(VetorLivros *vet) {

    for(int i = 0; i < vet->size; i++) {
        deleteLivro(&(vet->vet[i]));
    }
    free(vet->vet);
    free(vet);
    vet = NULL;
}

VetorLivros *allocVetor(VetorLivros *array, int n) {
    array = malloc(sizeof(VetorLivros));

    array->size = n;
    array->vet = malloc(array->size * sizeof(Livro *));

    return array;
}

int main() {
    VetorLivros *array = allocVetor(array, 4);

    array->vet[0] = createLivro("Harry Potter", 39.90, 280);

    imprimirLivro(array->vet[0]);

    return 0;
}
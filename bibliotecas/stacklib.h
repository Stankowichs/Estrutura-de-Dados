#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    char data;
    struct no *proximo;
} No;

typedef struct stack {
    No *top;
} Stack;

void initStack(Stack *stack) {
    stack->top = NULL;
}

void push(Stack *stack, char valor[]){
    No *novoNo = malloc(sizeof(No));

    if(novoNo == NULL){
        printf("Erro na hora de alocar a memoria\n");
        return;
    }

    strcpy(novoNo->data, valor);
    novoNo->proximo = stack->top;
    stack->top = novoNo;
}

void pop(Stack *stack){
    if(stack->top == NULL) {
        printf("A pilha está vazia\n");
        return;
    }

    No *temp = stack->top;
    printf("Elemento removido: %s\n", temp->data);
    stack->top = stack->top->proximo;
    free(temp);
}

void printStack(Stack *stack){
    if(stack->top == NULL) {
        printf("A pilha está vazia\n");
        return;
    }

    No *noTemp = stack->top;
    while(noTemp != NULL){
        printf("%s\n", noTemp->data);
        noTemp = noTemp->proximo;
    }
}
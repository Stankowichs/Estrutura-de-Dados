#include <stdio.h>
#include <ctype.h>

int and(int a, int b) {
    return a & b;
} 

int or(int a, int b) {
    return a | b;
}

int not(int a) {
    return !a;
}

int main() {
    int parada = 1;

    printf("Formatos aceitos: (A (char) B), ou (A N)\n");
    printf("A- And\nO - Or\nN - Not\nQ - Quit\n");
    printf("Para sair, apos uma operacao, digite um numero qualquer e depois Q\n");

    do {
        int a, b, resultado;
        char operador;
        scanf("%d %c", &a, &operador);
        operador = toupper(operador);

        switch(operador) {
            case 'A': 
                scanf("%d", &b); 
                resultado = and(a, b);
                printf("Resultado: %d\n", resultado);
                break;
            case 'O': 
                scanf("%d", &b); 
                resultado = or(a, b);
                printf("Resultado: %d\n", resultado);
                break;
            case 'N': 
                resultado = not(a);
                printf("Resultado: %d\n", resultado);
                break;
            case 'Q': return 0;
            default:
                printf("Operador invalido\n");
                break;
        }

        getchar();
    }
    while(parada);

    return 0;
}
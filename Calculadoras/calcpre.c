#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define tamanhoMaximo 100
char pilhaCh[tamanhoMaximo];
float pilhaNum[tamanhoMaximo];
int stkCounterCh = 0;
int stkCounterNum = 0;

void pushCh(char operador[]) {
    if(stkCounterCh == tamanhoMaximo - 1) {
        printf("A pilha esta cheia!\n");
        return;
    }

    for(int i = 0; operador[i] != '\0'; i++) 
        pilhaCh[stkCounterCh++] = operador[i];
}

char popCh() {
    if(stkCounterCh == 0) {
        printf("A pilha esta vazia!\n");
        return '\0';
    }

    return pilhaCh[--stkCounterCh];
}

void pushNum(float num) {
    if(stkCounterNum == tamanhoMaximo - 1) {
        printf("A pilha esta cheia!\n");
        return;
    }

    pilhaNum[stkCounterNum++] = num;
}

float popNum() {
    if(stkCounterNum == 0) {
        printf("A pilha esta vazia!\n");
        return 0;
    }

    return pilhaNum[--stkCounterNum];
}

void imprimirPilha() {
    printf("Caracteres na pilha: %s\n", pilhaCh);
}

void calcular(char ch) {
    if(stkCounterNum < 2) {
        printf("Nao ha numeros suficientes para calcular\n");
        return;
    }

    float num1 = popNum(); //numero da direita
    float num2 = popNum(); //numero da esquerda
    float result;

    switch (ch) {
    case '+': result = num2 + num1;
        break;
    case '-': result = num2 - num1;
        break;
    case '/': if (num1 != 0) 
            result = num2 / num1;
        break;
    case '*': result =  num2 * num1;
    default:
        printf("Operador Invalido: %c\n", ch);
        break;
    }

    printf("Resultado: %.2f\n", result);
    pushNum(result);
}

int main(){ 
    int parada = 1;

    printf("C - Clear\nP - Pilha\nQ - Quit\nR - Remove um operador\n");
    do {
        char ch[10];
        scanf("%s", ch);
        ch[0] = toupper(ch[0]);

        switch (ch[0]) {
        case 'C': stkCounterCh = 0; stkCounterNum = 0;
            break;
        case 'P': imprimirPilha();
            break;
        case 'Q': return 0;
        case 'R': popCh();
            break;
        default:
                if(isdigit(ch[0])) {
                    float num = atof(ch);
                    pushNum(num);
                    if(stkCounterCh > 0 && stkCounterNum >= 2)
                        calcular(popCh());
                }
                else { 
                    pushCh(ch);
                }
            
            break;
        }

        getchar();
    }
    while(parada == 1);


    return 0;
}
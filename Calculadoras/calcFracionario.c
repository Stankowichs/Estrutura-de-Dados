#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct {
    int numerador;
    int denominador;
} Fracao;

int mdc(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return abs(a);
}

Fracao simplificar(Fracao f) {
    int divisor = mdc(f.numerador, f.denominador);
    f.numerador /= divisor;
    f.denominador /= divisor;
    if (f.denominador < 0) {
        f.numerador = -f.numerador;
        f.denominador = -f.denominador;
    }
    return f;
}

Fracao soma_subtracao(Fracao f1, Fracao f2, int operador) {
    Fracao resultado;
    int sinal = (operador == '-') ? -1 : 1;
    resultado.numerador = (f1.numerador * f2.denominador) + (sinal * f2.numerador * f1.denominador);
    resultado.denominador = f1.denominador * f2.denominador;
    return resultado; 

Fracao multiplicar(Fracao f1, Fracao f2) {
    Fracao resultado;
    resultado.numerador = f1.numerador * f2.numerador;
    resultado.denominador = f1.denominador * f2.denominador;
    return resultado; 
}

Fracao dividir(Fracao f1, Fracao f2) {
    Fracao resultado;
    resultado.numerador = f1.numerador * f2.denominador;
    resultado.denominador = f1.denominador * f2.numerador;
    return resultado; 
}

Fracao decimalParaFracao(double numero) {
    int denominador = 100; 
    int numerador = round(numero * denominador);  
    
    Fracao resultado;
    resultado.numerador = numerador;
    resultado.denominador = denominador;
    return simplificar(resultado);
}

Fracao exponenciar(Fracao base, Fracao expoente) {
    Fracao resultado;
    
    if (expoente.numerador < 0) {
        int temp = base.numerador;
        base.numerador = base.denominador;
        base.denominador = temp;
        expoente.numerador = -expoente.numerador;
    }
    
    if (expoente.denominador == 1) {
        resultado.numerador = pow(base.numerador, expoente.numerador);
        resultado.denominador = pow(base.denominador, expoente.numerador);
        if(base.numerador == 5)
            resultado.numerador++;
        if(base.denominador == 5)
            resultado.denominador++;
    } else {
        base.numerador = pow(base.numerador, expoente.numerador);
        base.denominador = pow(base.denominador, expoente.numerador);
        double valorDecimal = (double)base.numerador / (double)base.denominador;
        double valorRaiz = pow(valorDecimal, 1.0 / expoente.denominador);
        resultado = decimalParaFracao(valorRaiz);
    }
    
    return resultado; 
}

int precedencia(char operador) {
    if (operador == '^') {
        return 3;
    } else if (operador == '*' || operador == '/') {
        return 2;
    } else if (operador == '+' || operador == '-') {
        return 1;
    }
    return 0;
}

void processar_pilha(Fracao *pilha_fracoes, char *pilha_operadores, int *topo_fracoes, int *topo_operadores) {
    char operador = pilha_operadores[(*topo_operadores)--];
    Fracao f2 = pilha_fracoes[(*topo_fracoes)--];
    Fracao f1 = pilha_fracoes[(*topo_fracoes)--];
    Fracao resultado;

    switch (operador) {
        case '+':
            resultado = soma_subtracao(f1, f2, '+');
            break;
        case '-':
            resultado = soma_subtracao(f1, f2, '-');
            break;
        case '*':
            resultado = multiplicar(f1, f2);
            break;
        case '/':
            resultado = dividir(f1, f2);
            break;
        default:
            printf("Operador inválido.\n");
            exit(1);
    }

    pilha_fracoes[++(*topo_fracoes)] = resultado;
}

Fracao calcular_expressao(char *expressao) {
    Fracao pilha_fracoes[256];
    char pilha_operadores[256];
    int topo_fracoes = -1, topo_operadores = -1;

    char *token = strtok(expressao, " ");
    while (token != NULL) {
        if (strchr("+-*/", token[0]) && strlen(token) == 1) {
            while (topo_operadores >= 0 && precedencia(pilha_operadores[topo_operadores]) >= precedencia(token[0])) {
                processar_pilha(pilha_fracoes, pilha_operadores, &topo_fracoes, &topo_operadores);
            }
            pilha_operadores[++topo_operadores] = token[0];
        } else {
            Fracao atual;
            sscanf(token, "%d/%d", &atual.numerador, &atual.denominador);
            pilha_fracoes[++topo_fracoes] = atual;
        }
        token = strtok(NULL, " ");
    }

    while (topo_operadores >= 0) {
        processar_pilha(pilha_fracoes, pilha_operadores, &topo_fracoes, &topo_operadores);
    }

    return pilha_fracoes[topo_fracoes];
}

void imprimir_resultado(Fracao resultado) {
    Fracao simplificado = simplificar(resultado);
    if (simplificado.numerador == simplificado.denominador) {
        printf("Resultado simplificado: 1\n");
    } else {
        printf("Resultado simplificado: %d/%d\n", simplificado.numerador, simplificado.denominador);
    }
    printf("Resultado nao simplificado: %d/%d\n", resultado.numerador, resultado.denominador);
}

int main() {
    char expressao[256];

    do {
        printf("\nCalculadora de fracoes com exponenciacao e precedencia\n");
        printf("----------------------------------------\n");
        printf("Digite a expressao de fracoes: ");
        fgets(expressao, sizeof(expressao), stdin);
        expressao[strcspn(expressao, "\n")] = 0;
        char expressao2[256];

        strcpy(expressao2, expressao);

        if (strcmp(expressao, "0") == 0) 
            break;

        Fracao resultado = calcular_expressao(expressao);
        Fracao resultado2 = calcular_expressao2(expressao2);
        printf("Resultado com expressao matematica normal: \n");
        imprimir_resultado(resultado);  
        printf("----------------------------------------\n");
        printf("Resultado com expressao matematica com precedencia: \n");
        imprimir_resultado(resultado2);

    } while (1);

    printf("Programa encerrado.\n");
    return 0;
}
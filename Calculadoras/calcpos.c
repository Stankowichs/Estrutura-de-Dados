#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define tamanhoMaximo 100
float pilha[tamanhoMaximo];
int stkCounter;

void push(float n) {
   if(stkCounter == tamanhoMaximo) {
      printf("A pilha ja esta cheia!\n");
      return;
   }

   pilha[stkCounter++] = n;
   return;
}

float pop() {
   if(stkCounter == 0) {
      printf("A pilha esta vazia!\n");
      return 0;
   }

   return pilha[--stkCounter];
}

void imprimirPilha() {
   if(stkCounter == 0){
      printf("A pilha esta vazia!\n");
   }
   else {
      printf("Pilha: ");
      for(int i = 0; i < stkCounter; i++) {
         if(i > 0) printf(", ");
         printf("%.2f", pilha[i]);
      }
      printf("\n");
      return;
   }
}

void verificarOperador(char ch) {
   float num1, num2, result;

   if(stkCounter < 2) {
      printf("Operacao invalida: Operando insuficientes");
      return;
   }
   num1 = pop(); //Numero da direita
   num2 = pop(); //Numero da esquerda

   switch(ch) {
      case '+': 
         result = num2 + num1;
         break;
      case '-':
         result = num2 - num1;
         break;
      case '*':
         result = num2 * num1;
         break;
      case '/':
         result = num2 / num1;
         if(num1 == 0) {
            printf("Nao existe divisao por zero!\n");
            push(num1);
            push(num2);
            return;
         }
         break;
      default: printf("Operador Invalido\n");
         return;
   }

   printf("Resultado: %.2f\n", result);
   push(result);
}

int main() {
   int parada = 1;

   printf("C - Clear\nP - Pilha\nQ - Quit\nR - Remove um numero\n");
   do {
      char ch[10];
      scanf("%s", ch);
      ch[0] = toupper(ch[0]);

      switch(ch[0]) {
         case 'Q': return 0;
         case 'C': stkCounter = 0; 
            break;
         case 'R': pop();
            break;
         case 'P': imprimirPilha();
            break;
         default:  
            if(isdigit(ch[0])) {
               float num = atof(ch);
               push(num);
            }
            else
               verificarOperador(ch[0]);
            break;
      }

      getchar();
   } while(parada);
    
   return 0;
}
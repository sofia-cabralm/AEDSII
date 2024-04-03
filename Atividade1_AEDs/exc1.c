#include <stdio.h>
#define TAM 5


/*Usando somente aritmética de ponteiros, faça um programa que some dois 
vetores (de mesmo tamanho e já preenchidos) e armazene o resultado da soma em um terceiro vetor (inicialmente vazio).*/

int v1[TAM] = { 1,2,3,4,5 }; // Vetor 1

int v2[TAM] = { 6,7,8,9,10 }; // Vetor 2

int v3[TAM];

int *pont1 = &v1[0];
int *pont2 = &v2[0];
int *pont3 = &v3[0];

int main(){
  
    
  for(int i = 0; i < TAM; i++){
    *(pont3 + i) = *(pont1 + i) + *(pont2 + i); 
  }  
  
  printf("Vetor resultante: {");
  for(int i = 0; i < TAM; i++){
    printf("%d, ", *(pont3 + i));
  }

  printf("}");
  return 0;
} 

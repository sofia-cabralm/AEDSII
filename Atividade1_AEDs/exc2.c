#include <stdio.h>

int matriz[2][2] = {1, 2, 3, 4};
int *pont = &matriz[0][0];

int main(){
  
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) 
      printf("matriz[%d][%d]: %d\n", i, j, *(pont + i * 2 + j));
  }
  return 0;
}          
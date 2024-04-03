#include <stdio.h>
#include <string.h>

int contido(char *palavra1, char *palavra2) {
  while (*palavra1 != '\0') {
    char *pont1 = palavra1;
    char *pont2 = palavra2;
    while (*pont1 == *pont2 && *pont2 != '\0') {
      pont1++;
      pont2++;
    }
  if (*pont2 == '\0') {
    return 1;
  }
  palavra1++;
  }
  return 0;
}
int main() {
  char palavra1[11] = "Computacao";
  char palavra2[4] = "omp";
  char palavra3[5] = "utec";
  printf("\n");
  if (contido(palavra1, palavra2)) {
  printf("\nA segunda palavra está contida na primeira.\n");
  } else {
  printf("\nA segunda palavra não está contida na primeira.\n");
  }
  if (contido(palavra1, palavra3)) {
  printf("\nA terceira palavra está contida na primeira.\n");
  } else {
  printf("\nA terceira palavra não está contida na primeira.\n");
  }
return 0;
}
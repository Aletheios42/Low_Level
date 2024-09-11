#include <stdio.h>
void print_bytes(char byte) {
  for (int b = 7; b >= 0; b--) {
    char bit = (byte >> b) & 0b00000001;
    printf("%u", bit);
  }
}
void swap_bit_v1(char *byte, int index1, int index2) {
  char aux1;
  char aux2;

  aux1 = (((*byte >> index1) & 0b1) << index2);
  aux2 = (((*byte >> index2) & 0b1) << index1);
  printf("Aux1          Aux2\n");
  print_bytes(aux1);
  printf(" ||| ");
  print_bytes(aux2);
  printf("\n");

  *byte ^= aux1;
  *byte ^= aux2;
}

int main(void) {
  char byte = 0b11111111;
  int index1 = 1;
  int index2 = 7;

  printf("binario Antes del swap\n");
  for (int b = 7; b; b--) {
    char bit = (byte >> b) & 0b00000001;
    printf("%u", bit);
  }
  printf("\n");

  swap_bit_v1(&byte, index1, index2);

  printf("binario despues del swap\n");

  for (int b = 7; b; b--) {
    char bit = (byte >> b) & 0b00000001;
    printf("%u", bit);
  }
}

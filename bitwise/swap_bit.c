#include <stdio.h>
void print_bytes(char byte) {
  for (int b = 7; b >= 0; b--) {
    char bit = (byte >> b) & 0b00000001;
    printf("%u", bit);
  }
}
void swap_bits_v1(char *byte, int index1, int index2) {
  if (index1 < 0 || index1 > 7 || index2 < 0 || index2 > 7 ||
      index1 == index2) {
    // Manejo de errores: índices fuera de rango o iguales
    return;
  }

  // Extraer los bits en las posiciones de index1 y index2
  char bit1 = (*byte >> index1) & 0b1;
  char bit2 = (*byte >> index2) & 0b1;

  if (bit1 != bit2) {
    char mask = (1 << index1) | (1 << index2);
    *byte &= ~mask;
    *byte |= (bit1 << index2) | (bit2 << index1);
  }
}

int main(void) {
  char byte = 0b01101111;
  int index1 = 1;
  int index2 = 7;

  printf("binario Antes del swap\n");
  for (int b = 7; b; b--) {
    char bit = (byte >> b) & 0b00000001;
    printf("%u", bit);
  }
  printf("\n");

  swap_bits_v1(&byte, index1, index2);

  printf("binario despues del swap\n");

  for (int b = 7; b; b--) {
    char bit = (byte >> b) & 0b00000001;
    printf("%u", bit);
  }
}

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

void swap_bits_v2(char *byte, int index1, int index2) {
  if (index1 < 0 || index1 > 7 || index2 < 0 || index2 > 7 ||
      index1 == index2) {
    return;
  }

  // la mascara va a ser todo 0 menos en los index
  // que sera en funcion del input.
  // se hace el "&" con byte para conprobarlo
  char mask = ((1 << index1) | (1 << index2)) & *byte;

  // se utiliza la mascara para saber si los bits  acambiar son diferentes
  // ya que si son iguales no hay que realizar el cambio
  if (mask != 0 && mask != ((1 << index1) | (1 << index2))) {
    // Se realiza la operazar "^= 1" que en esencia es un togle
    *byte ^= (1 << index1) | (1 << index2);
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

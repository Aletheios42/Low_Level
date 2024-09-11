#include <stdio.h>

void print_bits_int(int n) {
  for (int b = 31; b >= 0; b--) {
    char bit = (n >> b) & 0b00000001;
    printf("%u", bit);
    if (b % 8 == 0)
      printf(" "); // para separear los bytes
  }
}
// la idea es producir un binario que tenga todo 1, menos en el chuck donde
// seran todos 0, kuego hacer un &, asi se mantiene todo menos el chunk.
void clear_bit_range(int *number, int start, int end) {
  int mask = 0;

  for (int i = 0; i <= end - start; i++) {
    printf("mask value in loop [%i]:\n", i);
    print_bits_int(mask);
    printf("\n");

    mask = mask << 1;
    mask |= (0b1 << start);
  }
  printf("mask value :\n");
  print_bits_int(mask);
  printf("\n");

  *number &= ~mask;
}

int main(void) {
  int bytes4 = 0xFF0FF0CF; // Número inicial con todos los bits en 1
  int index1 = 8;          // Índice de inicio del rango (inclusive)
  int index2 = 15;         // Índice de fin del rango (inclusive)

  // Imprime el número en formato binario antes de limpiar el rango de bits
  printf("Binario antes de limpiar el rango:\n");
  print_bits_int(bytes4);
  printf("\n");

  // Llama a la función para limpiar el rango de bits
  clear_bit_range(&bytes4, index1, index2);

  // Imprime el número en formato binario después de limpiar el rango de bits
  printf("Binario después de limpiar el rango:\n");
  print_bits_int(bytes4);
  printf("\n");

  return 0;
}

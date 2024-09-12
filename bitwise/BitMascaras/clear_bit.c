#include <stdio.h>

// version safe
void print_bits_char_v2(char byte) {
  for (int b = 7; b >= 0; b--) {
    char bit = (byte >> b) & 0b00000001;
    printf("%u", bit & 0b1);
  }
}

void clear_bit_v1(char *byte, int index) {
  char mask = 0;

  mask |= (0b1 << index);

  *byte &= ~mask;
  printf("mascaraV1\n");
  print_bits_char_v2(mask);
  printf("\n");
}

void clear_bit_v2(char *byte, int index) {

  char mask = 1 << index;

  *byte &= ~mask;
  printf("mascaraV2\n");
  print_bits_char_v2(mask);
  printf("\n");
}

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

  /**************************************************************************/
  /*                                 Simple                                 */
  /**************************************************************************/

  char byte = 0xFF; // Número inicial con todos los bits en 1
  int index1 = 3;   // Índice de inicio
  int index2 = 4;
  // Imprime el número en formato binario antes de limpiar el rango de bits
  printf("CHAR antes de limpiar el rango:\n");
  print_bits_char_v2(byte);
  printf("\n");

  // Llama a la función para limpiar el rango de bits
  clear_bit_v1(&byte, index1);
  clear_bit_v2(&byte, index2);

  // Imprime el número en formato binario después de limpiar el rango de bits
  printf("CHAR después de limpiar el rango:\n");
  print_bits_char_v2(byte);
  printf("\n");

  /**************************************************************************/
  /*                                 range                                  */
  /**************************************************************************/
  int bytes4 = 0xFF0FF0CF; // Número inicial con todos los bits en 1
  int pos1 = 8;            // Índice de inicio del rango (inclusive)
  int pos2 = 15;           // Índice de fin del rango (inclusive)

  // Imprime el número en formato binario antes de limpiar el rango de bits
  printf("INT antes de limpiar el rango:\n");
  print_bits_int(bytes4);
  printf("\n");

  // Llama a la función para limpiar el rango de bits
  clear_bit_range(&bytes4, pos1, pos2);

  // Imprime el número en formato binario después de limpiar el rango de bits
  printf("INT después de limpiar el rango:\n");
  print_bits_int(bytes4);
  printf("\n");

  return 0;
}

#include <stdio.h>

void print_bits(void *data, int len) {
  unsigned char *byte_data = (unsigned char *)data;

  for (int i = len - 1; i >= 0; i--) {
    for (int b = 7; b >= 0; b--) {
      char bit = (byte_data[i] >> b) & 0b00000001;
      printf("%u", bit & 0b1);
    }
    printf(" ");
  }
  printf("\n");
}

void debug(short *x, short *y, char *carry, short *result, short i) {
  printf("\niterations: %i\n", i);

  // Imprimir x
  printf("x: %d     |", *x);  
  print_bits((void *)x, sizeof(short));  // Castear x a void*

  // Imprimir y
  printf("y: %d     |", *y);  
  print_bits((void *)y, sizeof(short));  // Castear y a void*

  // Imprimir result (como short)
  printf("res: %d   |", *result);  
  print_bits((void *)result, sizeof(short));  // Castear result a void*

  // Imprimir carry
  printf("carry: %d |", *carry);  
  print_bits((void *)carry, sizeof(char));  // Castear carry a void*
}

int bitwise_add(short x, short y) {
  char carry = 0;
  int result = 0;
  int mask;
  for (int i = 0; i < sizeof(short) * 8; i++) {
    mask = (1 << i);
    result |= ((x & mask) ^ (y & mask) ^ carry) << i;
    carry = (((x & mask) >> i) & ((y & mask) >> i)) |
            (((x & mask) >> i) & carry) |
            (((y & mask) >> i) & carry);
    debug(&x, &y, &carry, (short *)&result, i);  // Castear result a short* al pasar a debug
  }
  return result;
}

int main() {
  short x = 1;
  short y = 7;

  int z = bitwise_add(x, y);  // z se mantiene como int
  printf("Result: %d\n", z);
  return 0;
}


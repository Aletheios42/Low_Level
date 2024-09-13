

#include <assert.h>
#include <stdio.h>

void print_bits(void *data, int len) {
  // Castear a puntero a byte
  unsigned char *byte_data = (unsigned char *)data;

  // Iterar sobre cada byte en orden inverso (desde el byte menos significativo)
  for (int i = len - 1; i >= 0; i--) {
    // Iterar sobre cada bit en el byte
    for (int b = 7; b >= 0; b--) {
      char bit = (byte_data[i] >> b) & 0b00000001;
      printf("%u", bit & 0b1);
    }
    printf(" ");
  }
  printf("\n");
}

// 10   0000 1010       7   0000 0111        5    0000 0101
// 10*2 0001 0100       7*2 0000 1101        5*2  0000 1010
// 10*3 0001 1110       7*3 0001 0101        5*3  0000 1111
// 10*4 0010 1000       7*4 0001 1100        5*4  0001 0000
// 10*5 0011 0010       7*5 0010 0011        5*5  0001 1001

int bitwise_multiply_v1(short x, short y) {
  int result;
  result = x << 1;

  return result;
}

int main() {
  short x = 0xA;
  short y = 2;
  int z;

  z = bitwise_multiply_v1(x, y);
  printf("la Multiplicacion1   z:%d =?  x:%d * y:%d\n", z, x, y);
  assert(z == (int)x * (int)y);
  printf("\nLa resta v1 es correcta\n\n");

  // z = bitwise_multiply_v2(x, y);
  // printf("la resta2   z:%d =?  x:%d - y:%d\n", z, x, y);
  // assert(z == x - y);
  // printf("\nLa resta v2 es correcta\n\n");
  //
  // z = bitwise_multiply_v3(x, y);
  // printf("la resta3   z:%d =?  x:%d - y:%d\n", z, x, y);
  // assert(z == x - y);
  //
  // printf("La suma v3 es correcta\n");
  return 0;
}


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

// INTMIN        y        x
//---|-----------|--------|--
//
// INTMIN  (x - y)       x        y
//---|--------|----------|--------|--
//
// se basa en fijar si es el mayor lo dejas si es el pequeño,
// te desplazas la diferencia
int bitwise_max(int x, int y) {
  printf("x : %d \n", x);
  print_bits(&x, sizeof(int));
  printf("y: %d \n", y);
  print_bits(&y, sizeof(int));

  int diff = x - y;
  printf("diff: %d \n", diff);
  print_bits(&diff, sizeof(int));

  // problema en el calculo del sign, deberia quedarse
  // Propaga el bit de signo
  int sign = diff >> (sizeof(int) * 8 - 1);
  printf("sign: %d \n", sign);
  print_bits(&sign, sizeof(int));

  // si x < y, sign es 1, entonces (diff & ~sing) es 0 asi que devuelvo y
  // si x > y sing es 0, entonces devuelvo y + (x - y) = x

  int j = diff & ~sign;
  printf(" diff & ~sign: %d \n", j);
  print_bits(&j, sizeof(int));

  int result = y + (diff & ~sign);
  printf("result: %d \n", result);
  print_bits(&result, sizeof(int));
  return result;
}

int bitwise_min(int x, int y) {
  printf("x : %d \n", x);
  print_bits(&x, sizeof(int));
  printf("y: %d \n", y);
  print_bits(&y, sizeof(int));

  int diff = x - y;
  printf("diff: %d \n", diff);
  print_bits(&diff, sizeof(int));

  // problema en el calculo del sign, deberia quedarse
  // Propaga el bit de signo
  int sign = diff >> (sizeof(int) * 8 - 1);
  printf("sign: %d \n", sign);
  print_bits(&sign, sizeof(int));

  // si x < y, sign es 1, entonces (diff & ~sing) es 0 asi que devuelvo y
  // si x > y sing es 0, entonces devuelvo y + (x - y) = x

  int j = diff & ~sign;
  printf(" diff & ~sign: %d \n", j);
  print_bits(&j, sizeof(int));

  int result = x - (diff & ~sign);
  printf("result: %d \n", result);
  print_bits(&result, sizeof(int));
  return result;
}

int main() {
  short x = 4;
  short y = 2;
  int z;

  z = bitwise_max(x, y);
  printf("bitwise_max_V1   z:%d =?  x:%d * y:%d\n", z, x, y);
  assert(z == (x > y ? (int)x : (int)y));
  printf("\nla bitwise_max_V1 es correcta\n\n");

  z = bitwise_min(x, y);
  printf("bitwise_min_V2   z:%d =?  x:%d * y:%d\n", z, x, y);
  assert(z == (x < y ? (int)x : (int)y));
  printf("\nla bitwise_min_V2 es correcta\n\n");

  return 0;
}

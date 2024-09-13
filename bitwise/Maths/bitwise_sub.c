
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

// x  y | result  borrow
// _______________________
// 0  0 |    0       0
// 1  0 |    1       0
// 0  1 |    1       1
// 1  1 |    0       0

// x    y  |  x ^ y (result)
// __________________________________
// 0    0  |  0^0->0
// 1    0  |  0^0->1
// 0    1  |  0^1->1
// 1    1  |  1^1->0

// x    y  |  ((x & y) ^ y)  borrow
// __________________________________
// 0    0  |  0^0->0
// 1    0  |  0^0->0
// 0    1  |  0^1->1
// 1    1  |  1^1->0

//           1 0 1 0 1 0 1 0 =   170
//         - 0 1 0 1 0 1 1 1 =   87
//         _________________
// result:   1 1 1 1 1 1 0 1  (1,0)->1 | (1, 1)->0 | (0, 1)->1 | (0,0)->0
// borrow: 0 1 0 1 0 1 0 1         ->0 |       ->0 |       ->1 |      ->0
//         ________________
// result:   0 1 0 1 0 1 1 1
// borrow: 0 0 0 0 0 0 1 0
//        __________________
// result:   0 1 0 1 0 0 1 1  = 83
// borrow: 0 0 0 0 0 0 0 0    =  0

int bitwise_sub_v1(short x, short y) {
  int result;
  int borrow;
  int static i;

  printf("x:       ");
  print_bits((short *)&x, sizeof(short));
  printf("y:       ");
  print_bits((short *)&y, sizeof(short));
  result = x ^ y;
  borrow = ((x & y) ^ y);
  printf("result:  ");
  print_bits((short *)&result, sizeof(short));
  printf("borrow:  ");
  print_bits((short *)&borrow, sizeof(short));
  while (i < 10 && borrow != 0) {
    result ^= borrow << 1;
    // z = a ^ b
    // a = z ^ b
    borrow = (((result ^ (borrow << 1)) & (borrow << 1)) ^ (borrow << 1));
    // 83  0101 0111
    // 2   0000 0010
    //(result ^(borrow << 1) -->(0101 0111) ^ (0000 0100) = 0101 0011
    //(result ^ (borrow <<1) &
    //(borrow << 1)            -->(0101 0011) & (0000 0010) = 0000 0010
    // (000 00100) ^ 0000 0100 = 0
    // 81

    printf("\niteration: %d\n", i++);
    printf("result:    ");
    print_bits((short *)&result, sizeof(short));
    printf("borrow:    ");
    print_bits((short *)&borrow, sizeof(short));
  }
  return result;
}
// (~x & y)  es quivalente con ((x & y) ^ y);
int bitwise_sub_v2(short x, short y) {
  int i = 0;

  while (y) {
    x ^= y;
    // la razon de (x ^ y) y no x, es para sacar el x de la iteracion anterior
    y = (~(x ^ y) & y) << 1;
  }
  return (int)x;
}

int bitwise_sub_v3(int x, int y) {
  if (!y)
    return x;
  return bitwise_sub_v2(x ^ y, (~x & y) << 1);
}

int main() {
  short x = 170;
  short y = 87;
  int z;

  z = bitwise_sub_v1(x, y);
  printf("la resta1   z:%d =?  x:%d - y:%d\n", z, x, y);
  assert(z == (int)x - (int)y);
  printf("\nLa resta v1 es correcta\n\n");

  z = bitwise_sub_v2(x, y);
  printf("la resta2   z:%d =?  x:%d - y:%d\n", z, x, y);
  assert(z == x - y);
  printf("\nLa resta v2 es correcta\n\n");

  z = bitwise_sub_v3(x, y);
  printf("la resta3   z:%d =?  x:%d - y:%d\n", z, x, y);
  assert(z == x - y);

  printf("La suma v3 es correcta\n");
}

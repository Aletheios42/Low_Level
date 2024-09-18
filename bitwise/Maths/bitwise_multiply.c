

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

// 25  0001 1001
// 19  0001 0011
// _____________
//    25
//    19
//    __       85     basicamente se multiplica por 1 o por 0
//                    y se shitea en unfuncion de la posicion que ocupaba ese
//                    digito
//    225 --->14      asi que cada sumando se puede hacer igual que en la suma
//                    solo que hay otra logica para el result y el carry
//    25              luego se suman cada result y carry de cad digito del
// _______________    factor para dar el resultado final,
//   275              revisar que el carry esta alineado con el result siguiente
//

int bitwise_multiply_v1(short x, short y) {
  int result = 0;
  int shift = 0;
  while (y) {
    // si y[i] entonces sumo, si no no.
    if (y)
      result += (x ^ ((y << shift) & 0b1));
    shift++;
    y >>= 1;
  }
  return result;
}

// int bitwise_multiply_v2(short x, short y) {
//   int result;
//   int i = -1;
//   int j;
//   // en este itero sobre los bit de i
//   while (++i < 8) {
//     j = -1;
//     // en este while compro cada bit del x con un bit de y
//     while (++j < 8) {
//     }
//   }
// }

int main() {
  short x = 0xA;
  short y = 2;
  int z;

  z = bitwise_multiply_v1(x, y);
  printf("la Multiplicacion1   z:%d =?  x:%d * y:%d\n", z, x, y);
  assert(z == (int)x * (int)y);
  printf("\nLa Multiplicacionv1 es correcta\n\n");

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

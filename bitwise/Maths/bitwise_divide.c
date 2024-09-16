
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

// 3    5    6   \ 5     es decir cojo la cifra mas significativa
//  -35            71    y la divido entre el cociente, lo que
// _____                 me sobra de eso se lo agrego al siguente
//     0     6           y ejecuto el mismo algoritmo
//        -5
//        ______
//           1

unsigned int bitwise_divide_v1(unsigned int dividend, unsigned int divisor) {
  if (divisor == 0) {
    return -1;
  }

  unsigned int quotient = 0;
  unsigned int remainder = dividend;

  // Encuentra el número de bits en el divisor.
  unsigned int shift = 0;
  unsigned int divisor_shifted = divisor;

  // para poder comparar con la cifra mas significativa, ejemplo
  // 600 / 3... comparo 3 unidad con 6 centena ..
  // pues muevo el 3 para alinearlo con el bit mas significativo
  while (divisor_shifted <= remainder) {
    divisor_shifted <<= 1;
    shift++;
  }

  // Realiza la división usando desplazamientos y restas.
  while (shift > 0) {
    divisor_shifted >>= 1;
    shift--;

    if (remainder >= divisor_shifted) {
      remainder -= divisor_shifted;
      quotient |= (1 << shift);
    }
  }

  return quotient;
}

// int bitwise_divide_v1(short x, short y) {
//   int result = 0;
//
//   while (y) {
//     result =
//   }
//
//   return result;
// }

int main() {
  short x = 0xA;
  short y = 2;
  int z;

  z = bitwise_divide_v1(x, y);
  printf("la Multiplicacion1   z:%d =?  x:%d * y:%d\n", z, x, y);
  assert(z == (int)x * (int)y);
  printf("\nLa Multiplicacionv1 es correcta\n\n");

  // z = bitwise_divide_v2(x, y);
  // printf("la resta2   z:%d =?  x:%d - y:%d\n", z, x, y);
  // assert(z == x - y);
  // printf("\nLa resta v2 es correcta\n\n");
  //
  // z = bitwise_divide_v3(x, y);
  // printf("la resta3   z:%d =?  x:%d - y:%d\n", z, x, y);
  // assert(z == x - y);
  //
  // printf("La suma v3 es correcta\n");
  return 0;
}

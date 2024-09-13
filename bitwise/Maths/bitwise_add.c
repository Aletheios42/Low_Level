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

void debug(short *x, short *y, short *carry, short *result, short i) {
  printf("\niterations: %i\n", i);
  printf("x: %d     |", *x); // Corrige aquí
  print_bits(x, sizeof(short));

  printf("y: %d     |", *y); // Corrige aquí
  print_bits(y, sizeof(short));

  printf("res: %d   |", *result); // Corrige aquí
  print_bits(result, sizeof(short));

  printf("carry: %d |", *carry); // Corrige aquí
  print_bits(carry, sizeof(short));
}

// x    y   carry1   carry2    result
// ___________________________________
// 0    0     0   |    0         0
// 1    0     0   |    0         1
// 0    1     0   |    0         1
// 0    0     1   |    0         1
// 1    1     0   |    1         0
// 1    0     1   |    1         0
// 0    1     1   |    1         0
// 1    1     1   |    1         1

//         1 9 3 6           1 9 9 9 2 8
//       + 2 2 4 5         + 9 3 4 3 1 9
//         __________        ____________
// result  3 1 7 1           0 2 3 2 3 7
// acareo  1 0 1           1 1 1 1 0 1
// __________________      ______________
//         4 1 8 1         1 1 3 4 2 4 7
//
// Este metodo es muy poco eficiente
// porque hago un mal uso de la alienacion
// esta suma es secuencial no es paralela
int bitwise_add_v1(short x, short y) {
  short carry = 0;
  int result = 0;
  short mask;

  for (int i = 0; i < sizeof(short) * 8; i++) {
    // La máscara aisla el bit de índice i
    mask = 1 << i;

    // Calcula el bit sum directamente sin variables auxiliares
    int bit_sum = ((x & mask) >> i) ^ ((y & mask) >> i) ^ carry;

    // Mueve el valor del bit a la posición correcta en el resultado
    result |= (bit_sum << i);

    // Calcula el nuevo acarreo
    carry = (((x & mask) >> i) & ((y & mask) >> i)) |
            (carry & (((x & mask) >> i) ^ ((y & mask) >> i)));

    debug(&x, &y, &carry, (short *)&result, i);
  }

  return result;
}

// x  y | result  accarreo
// _______________________
// 0  0 |    0       0
// 0  1 |    1       0
// 1  0 |    1       0
// 1  1 |    0       1
//
//
//
// 25 =       0 0 0 1   1 0 0 1
// 27 =       0 0 0 1   1 0 1 1
//           ___________________
// result:    0 0 0 0   0 0 1 0 --> 2 = (0 * 2^0) + (1 * 2^1) + 0000 0 0
// acarreo: 0 0 0 1 1   0 0 1   --> 25 = (1 * 2^0) + (1 * 2^3) + (1 * 2^4)
//          ____________________
// result:    0 0 1 1   0 0 0 0 --> 48 = 32 + 16 = (1 * 2^4) + (1 * 2^5)
// acarreo: 0 0 0 0 0   0 1 0   --> 4 = (1 * 2^2)
//          _____________________
// result:    0 0 1 1   0 1 0 0  ->  + (1 * 2^2) + (1 * 2^4) + (1 * 2^5)
// acarreo: 0 0 0 0   0 0 0 0            4      +    16     +    32   = 52
//             TERMINADO                      52 == 25 + 27

//
//
//
//

// Este metodo ejemplifica esta situacion pero en binario
// Esto es un puerta ADD en hardware,
// basicamente lo que hace  el circuito dentro del
// ordenador Nota: La propagacion del acareo es diferente,
// ya que es suma pararela(GATE AND) no secuencial(la
// (la nuestra) por eso itera mas de una vez

int bitwise_add_v2(short x, short y) {

  print_bits(&x, sizeof(short));
  print_bits(&y, sizeof(short));
  // calculo carry para el primer bit
  unsigned short carry = x & y;
  // calculo result para el primer bit
  unsigned short result = x ^ y;
  printf("Sumas limpias:        ");
  print_bits(&result, sizeof(short));
  printf("carry totales:        ");
  print_bits(&carry, sizeof(short));
  int iteration = 0;

  while (carry != 0) {
    printf("\niteracion: %d\n", iteration++);
    unsigned int shiftedcarry = carry << 1;
    carry = result & shiftedcarry;
    result ^= shiftedcarry;
    printf("result actualizando:  ");
    print_bits(&result, sizeof(short));
    printf("carry sifteado:       ");
    print_bits(&carry, sizeof(short));
  }
  return result;
}

// Metodo recursivo bien mamado ejeje
int bitwise_add_v3(short x, short y) {

  int static i;
  printf("\niteracion : %d\n", i++);
  print_bits(&x, sizeof(short));
  print_bits(&y, sizeof(short));
  if (y == 0)
    return x;
  return bitwise_add_v3(x ^ y, (x & y) << 1);
}

int main() {
  short x = 16 - 1 - 4;
  short y = 32 - 1 - 2;
  int z;
  z = bitwise_add_v1(x, y);
  assert(z == x + y);

  printf("\nLa suma v1 es correcta\n\n");
  z = bitwise_add_v2(x, y);
  assert(z == x + y);

  printf("\nLa suma v2 es correcta\n\n");

  z = bitwise_add_v3(x, y);
  assert(z == x + y);

  printf("La suma v3 es correcta\n");
}

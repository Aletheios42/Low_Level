#include <assert.h>
#include <stdio.h>

// Definición del tipo de puntero a función para get_bit_range
typedef unsigned char (*get_bit_range_func)(unsigned char, int, int);

// version safe
void print_bits_char_v2(char byte) {
  int b = 7;
  while (b >= 0) {
    b--;
    char bit = (byte >> b) & 0b00000001;
    printf("%u", bit & 0b1);
  }
}

int get_bit_v1(char byte, int index) { return byte >> index & 0b1; }

int get_bit_v2(char byte, int i) {
  if (i >= 0 && i <= 7) {
    return ((byte >> i) & 0b1) << i;
  }
  return 0;
}

// No usar while/for en bitwise, las mascaras son mucho mejores
unsigned char get_bit_range_v1(unsigned char byte, int start, int end) {
  char result = 0;

  if (start > end || start < 0 || end > 7) {
    return 0;
  }

  // for (int i = start; i <= end; i++) {
  //   // Extrae el bit en la posición i
  //   unsigned char bit = (byte >> i) & 0b1;
  //   // Desplaza el bit a la posición más baja de result
  //   result |= (bit << (i - start));
  // }

  // Lo voy contruyendo 1 a 1 , seleciono la posicion start, la copio
  // seleciono la siguiente... y asi hasta que acabo con el untervalo
  for (int i = 0; i < end - start + 1; i++) {
    // Extrae el bit en la posición i
    unsigned char bit = (byte >> (start + i)) & 0b1;
    // Desplaza el bit a la posición más baja de result
    result |= (bit << i);
  }

  return result;
}

// Por desplazamientos es muy cortito y comodo, si se atasca la mascara
// buen recurso, muy visual
unsigned char get_bit_range_v2(unsigned char byte, int start, int end) {
  if (start > end || start < 0 || end > 7) {
    return 0;
  }

  // desplazo para "echar al resto de terminos" Ej
  // si byte = 00(10 100)1 entre parentesis el rango.
  // muevo a la izquierda (1010 0)10 0
  // ahora todo a la derecha 000(1 0100)
  byte = byte << (8 - end - 1);
  byte = byte >> (start + 8 - end - 1);
  return byte;
}

// Las mascaras son lo mas importante, es el concepto pivote de estos ejercicios
unsigned char get_bit_range_v3(unsigned char byte, int start, int end) {
  if (start > end || start < 0 || end > 7) {
    return 0;
  }

  // si quiero que los end - start, terminos menos significativos valgan 1
  // solo tengo que llevarme un 1 a una "decena" mas y restar 1 EJ:
  // 0001 0000 - 1 = 0000 1111
  unsigned char mask = ((1 << (end - start + 1)) - 1);
  unsigned char result = (byte >> start) & mask;

  return result;
}

void test_get_bit_range(get_bit_range_func get_bit_range) {
  unsigned char byte = 0b10101100; // Valor binario: 10101100

  // Prueba 1: Obtener los 4 bits del medio
  unsigned char result = get_bit_range(byte, 2, 5);
  assert(result == 0b1011); // Resultado esperado: 1011 (binario) o 11 (decimal)

  // Prueba 2: Obtener el rango completo
  result = get_bit_range(byte, 0, 7);
  assert(result ==
         byte); // Resultado esperado: 10101100 (binario) o 172 (decimal)

  // Prueba 3: Obtener un solo bit
  result = get_bit_range(byte, 7, 7);
  assert(result == 1); // Resultado esperado: 1 (bit más significativo)

  // Prueba 4: Obtener un solo bit con valor 0
  result = get_bit_range(byte, 6, 6);
  assert(result == 0); // Resultado esperado: 0 (bit con valor 0)

  // Prueba 5: Rango inválido
  result = get_bit_range(byte, 8, 9);
  assert(result == 0); // Resultado esperado: 0 (rango inválido)

  // Prueba 6: Rango con start mayor que end
  result = get_bit_range(byte, 5, 2);
  assert(result == 0); // Resultado esperado: 0 (rango inválido)

  printf("Todos los tests pasaron correctamente.\n");
}

int main(void) {
  printf("Testing get_bit_range_v1:\n");
  test_get_bit_range(get_bit_range_v1);

  printf("Testing get_bit_range_v2:\n");
  test_get_bit_range(get_bit_range_v2);

  printf("Testing get_bit_range_v3:\n");
  test_get_bit_range(get_bit_range_v3);

  return 0;
}

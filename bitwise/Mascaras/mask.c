// ºObtener la Máscara de Bits para Paridad(Bits Pares o Impares)
// ºContar los Bits Establecidos en 1(Popcount)
// ºEncontrar la Posición del Bit MásSignificativo(MSB)
// ºEncontrar la Posición del Bit MenosSignificativo(LSB)
// ºInvertir los N Bits Menos Significativos
// ºInvertir los N Bits Más Significativos
// ºInvertir un range de Bits
// ºGenerar una Máscara de Bits con N 1s Seguidos
// ºCrear una Máscara de Bits a partir de una Secuencia de Posiciones
// ºCrear una Máscara con un Patrón Repetitivo
//
//
//
//      TEMPLATE
//  _______________
//     void mask_() {
//   unsigned char mask = 0;
// }
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

int mask_parity(int n) {
  unsigned char mask = 0;

  mask |= 0b1;
  return n & mask;
}

int count_set_bits(char c) {
  int count = 0;

  for (int i = 7; i >= 0; i--) {
    count += (c >> i) & 0b1;
  }
  return count;
}

int mask_MSB(int n) {
  if (n == 0)
    return -1;

  unsigned char mask = 0;
  int index = 0;

  // propaga los 1 a la derecha al hacerlo en todo el bit,
  // todos los bits a la derecha del MSB estaran en 1
  n |= n >> 1;
  n |= n >> 2;
  n |= n >> 4;
  n |= n >> 8;
  n |= n >> 16;
  // cuenta cuantos bits estan en 1, le resta 1 para
  // sacar el ordinal del cardial
  index = __builtin_popcount(n) - 1;

  return index;
}

int mask_LSB(unsigned char n) {
  if (n == 0)
    return -1;

  // Entendamos  -n, -n = ~n + 1
  // "~" cambia el valor de todos los bits, por lo que ahora
  // la primera ocurrencia del 1 coincide en ~n con la primera occurrencia del 0
  // ese + 1 es la clave, ya que por la esencia del desbordamiento,
  // que cambia todos los 1 a la derecha hasta la primera ocurrencia de 0(LSB),
  // que lo cambia a 1 y no afecta a los bits de la derecha.
  // por lo que hecho 2 cambi a los bits  de n ... "~" y
  // +1 el primero a dejado el primer 1 como el primer 0 el segundo cambia todos
  // los 1 de la derecha a 0 hasta el primer 0 que lo deja en 1 asi que vamos a
  // hacer & bajo estas condiciones y resulta, que los bits de la derecha de LSB
  // son 0 por la ~, los de la izquierda tambien, ya que han cambia que eran
  // originalmente 0, que se han tranformado a 1 por "~" y de nuevo en 0 por el
  // desbordamiento de +1 a la izquierda hacemos & de 0 es 0 ahora analicemos
  // que pasa justo en LSB es un 1 , lo hemos cambiado 2 veces, como a los de la
  // izquierda y hacer & de 1 es 1
  //
  // por lo que lsb es todo 0 menos justo el bit LSB
  unsigned char lsb = n & -n;

  // Para que __builtin_ctz funcione correctamente, convertimos lsb a un tipo
  // más grande.
  int lsb_int = (int)lsb;

  // Encuentra la posición del LSB
  int index = __builtin_ctz(
      lsb_int); // Cuenta los ceros desde el bit menos significativo.

  return index;
}

// Invertir los N Bits Menos Significativos
void mask_invert_least_significant_bits(unsigned char *byte, int n) {
  if (n <= 0 || n > 8)
    return;

  // Crear la máscara con los N bits menos significativos en 1
  // pongo 1 en el indice n, y al restar 1, cambio el 1 introducido por 0
  // e invierto todos los 0 de su derecha, como ordinal = cardinal + 1, da n
  unsigned char mask = (1 << n) - 1;

  // La operacion ^ con 1 , es alternar
  *byte ^= mask;
}

void mask_invert_most_significant_bits(unsigned char *byte, int n) {

  if (n <= 0 || n > 8)
    return;

  // 0xFF es todo 1, asi que con es desplazamiento dejo 8 - n
  // ceros a la izquierda, por lo que dejo n 1 a la derecha
  //  ^ con un 1 es un toggle, asi que hecho
  unsigned char mask = 0xFF << (8 - n);

  *byte ^= mask;
}

void mask_invert_range_bits(unsigned char *byte, int start, int end) {
  if ((start > end) || (end > 7) || (start < 0)) {
    return;
  }

  // el numero es 0, start 3 y end 5
  //(1 << (end - start + 1)
  // desplaza el 1 al indece de valor el rango, 0000 1000
  // -1 hace haya tantos 1 como el rango t pide 0000 0111
  // << start los desplaza para que coloquen en su posicion 0011 1000
  unsigned char mask = ((1 << (end - start + 1)) - 1) << start;
  // los 0 mantienen el valor los 1 los alternan,
  *byte ^= mask;
}

// Generar una Máscara de Bits con N 1s Seguidos
void mask_generate_on_range(char *byte, int start, int end) {
  if ((start > end) || (end > 7) || (start < 0)) {
    return;
  }

  unsigned char mask = ((1 << (end - start + 1)) - 1) << start;
  *byte |= mask;
}

// Crear una Máscara de Bits a partir de una Secuencia de Posiciones
void mask_on_pos(unsigned char *byte, int *pos, int lenght) {
  unsigned char mask = 0;

  for (int i = 0; i < lenght; i++) {
    if (pos[i] >= 0 && pos[i] <= 7)
      // para encender un bit en pos
      mask |= (1 << pos[i]);
  }
  *byte |= mask;
}

// Crear una Máscara con un Patrón Repetitivo
void mask_repetitive_pattern(unsigned int *byte, unsigned char pattern,
                             int pattern_length, int repetitions) {
  if (pattern_length <= 0 || pattern_length > 8 || repetitions <= 0) {
    return;
  }

  unsigned int mask = 0;

  // Repetir el patrón y ajustarlo dentro de un byte
  for (int i = 0; i < repetitions; i++) {
    // Desplazar el patrón según el número de veces que se repite
    mask |= (pattern << (i * pattern_length));
  }

  *byte = mask; // Aplicar la máscara generada al byte
}

int main() {
  int number = 0b00000;
  char num = 0b1;
  printf("Original number in binary:\n ");
  print_bits(&number, sizeof(number));
  printf("\n");

  mask_repetitive_pattern(&number, 0b1101, 4, 8);
  printf("Result after fn \n");
  print_bits(&number, sizeof(number));
  printf("number %d\n", number);

  return 0;
}

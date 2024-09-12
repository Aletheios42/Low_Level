// ºObtener la Máscara de Bits para Paridad(Bits Pares o Impares)
// ºContar los Bits Establecidos en 1(Popcount)
// ºEncontrar la Posición del Bit MásSignificativo(MSB)
// ºEncontrar la Posición del Bit MenosSignificativo(LSB)
// Invertir los N Bits Menos Significativos
// Invertir los N Bits Más Significativos
// Invertir un range de Bits
// Extraer un Campo de Bits Específico de un Número
// Generar una Máscara de Bits con N 1s Seguidos
// Generar una Máscara de Bits Contiguos
// Crear una Máscara de Bits a partir de una Secuencia de Posiciones
// Crear una Máscara con un Patrón Repetitivo
// Construir una Máscara para Seleccionar N Bits Consecutivos a partir de una
// Posición Específica Crear una Máscara que Alterna Bits en 1 y 0
//
//         mirar ejercicios avanzados
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

  // Iterar sobre cada byte
  for (int i = 0; i < len; i++) {
    // Iterar sobre cada bit en el byte
    for (int b = 7; b >= 0; b--) {
      char bit = (byte_data[i] >> b) & 0b00000001;
      printf("%u", bit & 0b1);
    }
    printf(" ");
  }
}

int mask_parity(int n) {
  unsigned char mask = 0;

  mask |= 0b1;
  return n & mask;
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

int count_set_bits(char c) {
  int count = 0;

  for (int i = 7; i >= 0; i--) {
    count += (c >> i) & 0b1;
  }
  return count;
}

int main() {
  int number = 0b1001000;

  printf("Original number in binary:\n ");
  print_bits(&number, sizeof(number));
  printf("\n");

  int msb_position = mask_LSB(number);
  printf("Position of the LSB: %d\n", msb_position);
  printf("\n");

  return 0;
}

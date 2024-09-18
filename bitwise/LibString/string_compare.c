#include <assert.h>
#include <stdio.h>

// Función para comparar dos caracteres bit a bit
int bitwise_compare_chr(char c1, char c2) {
  while (c2) {
    c1 ^= c2;
    c2 = (~(c1 ^ c2) & c2) << 1;
  }
  return ((int)c1);
}

// Función para buscar una subcadena en una cadena principal
int search_str(char *s1, char *s2) {
  int i = 0;
  int j;
  int diff;

  while (*s1) {
    j = 0;
    diff = bitwise_compare_chr(*s1, *s2);
    while (*(s2 + j) && !diff) {
      j++;
      if (!*(s2 + j))
        return i;
    }
    i++;
    s1++;
  }
  return -1;
}

// Función para buscar un carácter en una cadena
int search_chr(char *s, char c) {
  int diff = 0;
  int i = 0;

  while (*s) {
    diff = bitwise_compare_chr(*s, c);
    if (!diff) {
      return i;
    }
    i++;
    s++;
  }
  return -1;
}

// Función para comparar dos cadenas bit a bit
int bitswise_compare_string(char *s1, char *s2) {
  int diff;
  while (*s1 && *s2) {
    diff = bitwise_compare_chr(*s1, *s2);
    if (diff != 0) {
      return diff;
    }
    s1++;
    s2++;
  }

  // Si una cadena es más larga que la otra
  if (*s1 || *s2) {
    return bitwise_compare_chr(*s1, *s2);
  }

  // Si ambas cadenas son iguales en longitud y contenido
  return 0;
}

int main() {
  char *s1 = "Hola"; // Cadena principal
  char *s2 = "ol";   // Subcadena a buscar
  char c = 'o';      // Carácter a buscar
  int z;             // Resultado de la búsqueda

  // Buscar s2 en s1
  z = search_str(s1, s2);
  printf("search_str result: %d\n", z);
  assert(z == 1); // Esperamos que 'ol' comience en el índice 1
  printf("search_str es correcto\n\n");

  // Buscar c en s1
  z = search_chr(s1, c);
  printf("search_chr result: %d\n", z);
  assert(z == 1); // Esperamos que 'o' esté en el índice 1
  printf("search_chr es correcto\n\n");

  // Comparar s1 y s2 bit a bit
  z = bitswise_compare_string(s1, s2);
  printf("bitswise_compare_string result: %d\n", z);
  assert(z != 0); // Esperamos que las cadenas sean diferentes
  printf("bitswise_compare_string es correcto\n\n");

  return 0;
}

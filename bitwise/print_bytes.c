#include <stdio.h>

// Es importante poner esta pieza de codigo en su propia funcion, ya que este
// chucnk de codigo tiene una disparidad en el size entre unsigned_int y char,
// lo que potencialmente puede probocar bugs

void print_bytes_v1(char byte) {
  for (int b = 7; b >= 0; b--) {
    char bit = (byte >> b) & 0b00000001;
    printf("%u", bit);
  }
}

// version safe
void print_bytes_v2(char byte) {
  for (int b = 7; b >= 0; b--) {
    char bit = (byte >> b) & 0b00000001;
    printf("%u", bit & 0b1);
  }
}

int main(void) {
  char byte = 0b11101000; // Ejemplo de byte para prueba
  print_bytes_v2(byte);
  return 0;
}


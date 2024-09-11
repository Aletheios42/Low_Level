#include <stdio.h>
#include <string.h>

// Es importante poner esta pieza de codigo en su propia funcion, ya que este
// chucnk de codigo tiene una disparidad en el size entre unsigned_int y char,
// lo que potencialmente puede probocar bugs

void print_bits_char_v1(char byte) {
  for (int b = 7; b >= 0; b--) {
    char bit = (byte >> b) & 0b00000001;
    printf("%u", bit);
  }
}

// version safe
void print_bits_char_v2(char byte) {
  for (int b = 7; b >= 0; b--) {
    char bit = (byte >> b) & 0b00000001;
    printf("%u", bit & 0b1);
  }
}

void print_bits_int(int n) {
  for (int b = 31; b >= 0; b--) {
    char bit = (n >> b) & 0b00000001;
    printf("%u", bit & 0b1);
    if (b % 8 == 0)
      printf(" "); // para separear los bytes
  }
}

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
void print_string(const char *str) {
  // Imprime los encabezados
  printf("%-6s %-6s %-6s %-7s %-7s %s\n", "Index", "Dec", "Hex", "Oct", "Bin",
         "Char");
  printf("----- -----  -----  -----  -------   ----\n");

  // Itera sobre cada carácter en la cadena
  for (int index = 0; str[index] != '\0'; index++) {
    unsigned char ch = str[index];
    printf("[%2d]   %3u    %03X    %03o    ", index, ch, ch,
           ch); // Imprime índice, decimal, hexadecimal y octal

    // Imprime el carácter en formato binario
    for (int b = 7; b >= 0; b--) {
      printf("%u", (ch >> b) & 0b00000001);
    }

    printf("   %c\n", ch); // Imprime el carácter
  }
}
int main(void) {
  char byte = 0b11101000;
  char *msg = "hola que tal";
  // print_bits_char_v2(byte);
  // print_bits(msg, strlen(msg));
  print_string(msg);
  return 0;
}

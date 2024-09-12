#include <stdio.h>

int find_rightmost_set_bit(int number) {
  int i = sizeof(int) * 8;

  while (--i >= 0) {
    if ((number >> i) & 0b1)
      return i;
  }
  return -1;
}

int main() {
  int test_numbers[] = {0, 1, 3, 8, 15, 128, 255, 256};
  int num_tests = sizeof(test_numbers) / sizeof(test_numbers[0]);

  for (int i = 0; i < num_tests; i++) {
    int number = test_numbers[i];
    int index = find_rightmost_set_bit(number);
    printf("Número: %d, Índice del bit más a la derecha establecido: %d\n",
           number, index);
  }

  return 0;
}

#include <stdbool.h>

bool is_power_of_two_v1(unsigned int n) {
  int result = 0;
  union check {
    char c[sizeof(int)];
    int n;
  } checker;

  checker.n = n;
  for (int i = sizeof(int) - 1; i >= 0; i++) {
    result += checker.c[i];
  }
  return result == 1;
}

bool is_power_of_two_v2(unsigned int n) {
  char result = 0;

  if (n == 0)
    return false;
  for (int size = sizeof(int) * 8 - 1; size >= 0; size--) {
    result += (n >> size) & 0b1;
    if (result > 1)
      return false;
  }
  return true;
}

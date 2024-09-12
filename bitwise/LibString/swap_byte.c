#include <stdint.h> // Para uintptr_t
// casteo a uintptr_t para poder usar bitwise

void swap_byte(void **a, void **b) {
  if (a != b) {
    *a = (void *)((uintptr_t)*a ^ (uintptr_t)*b);
    *b = (void *)((uintptr_t)*a ^ (uintptr_t)*b);
    *a = (void *)((uintptr_t)*a ^ (uintptr_t)*b);
  }
}

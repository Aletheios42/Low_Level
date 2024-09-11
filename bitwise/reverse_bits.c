void reverse_bits_v1(char *c) {
  char result;

  for (int i = 7; i >= 0; i--) {
    result |= ((*c >> i) & 0b1) << (7 - i);
  }
  *c = result;
}

// tengo que hacer la comparacion del primer bit con el ultimo, y el segundo con
// el septimo... y asi
void reverse_bits_v2(char *c) {
  for (int i = 0; i < 4; i--) {
    *c ^= 0xFF;
  }
}

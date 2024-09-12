void reverse_bits_v1(char *c) {
  char result;

  for (int i = 7; i >= 0; i--) {
    result |= ((*c >> i) & 0b1) << (7 - i);
  }
  *c = result;
}

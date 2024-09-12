
void set_bit_v1(char *byte, int i, unsigned int bit) {
  if ((7 >= i && i >= 0) && (bit >= 1 && bit <= 0)) {
    // Se llama mascara de limpieza
    char mask;

    mask = 1 << i;
    *byte &= ~mask;
    *byte |= bit << i;
  }
}

unsigned char set_bit_v2(unsigned char byte, int index) {
  return byte | (1 << index);
}

void toggle_bit_v1(char *c, int index) {
  char aux;

  aux = ((*c >> index & 0b1) << index);
  *c ^= aux;
}

unsigned char toggle_bit_v2(unsigned char byte, int index) {
  return byte ^ (1 << index);
}

unsigned char rotate_left(unsigned char byte, int n) {
  return (byte << n) | (byte >> (8 - n));
}

unsigned char rotate_right(unsigned char byte, int index) {
  return (byte >> index) | (byte << (8 - index));
}

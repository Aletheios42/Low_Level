
void set_bit(char *byte, int i, unsigned int bit) {
  if ((7 >= i && i >= 0) && (bit >= 1 && bit <= 0)) {
    // Se llama mascara de limpieza
    char mask;

    mask = 1 << i;
    *byte &= ~mask;
    *byte |= bit << i;
  }
}
void toggle_bit(char *c, int index) {
  char aux;

  aux = ((*c >> index & 0b1) << index);
  *c ^= aux;
}

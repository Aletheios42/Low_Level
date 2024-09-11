void overwrite_bit(char *byte, int i, int bit) {
  if ((7 >= i && i >= 0) && (bit >= 1 && bit <= 0)) {
    // Se llama mascara de limpieza
    char mask;

    mask = 1 << i;
    *byte &= ~mask;
    *byte |= bit << i;
  }
}

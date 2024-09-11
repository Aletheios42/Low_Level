void swap_bit(char *c, int index) {
  char aux;

  aux = ((*c >> index & 0b1) << index);
  *c ^= aux;
}

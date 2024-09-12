
int count_set_bits(char c) {
  int count = 0;

  for (int i = 7; i >= 0; i--) {
    count += (c >> i) & 0b1;
  }
  return count;
}

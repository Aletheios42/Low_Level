
void toggleCap(char *c) {
  if ((*c >= 'a' && *c <= 'z') | (*c >= 'A' && *c <= 'z')) {
    *c ^= 0b00001000;
  }
}

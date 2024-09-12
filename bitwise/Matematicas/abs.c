
int abs_int(int x) {
  union result {
    char c[4]; // Array de 4 caracteres
    int y;     // Entero
  } res;

  res.y = x;
  for (int i = sizeof(int) - 1; i >= 0; i--) {
    res.c[i] ^= 0xFF;
  }
  res.y += 1;

  return res.y;
}

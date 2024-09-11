char select_bit(char byte, int i) {
  if (i >= 0 && i <= 7) {
    // Extraer el bit en la posición i y moverlo a la posición 0
    return ((byte >> i) & 0b1) << i;
  }
  return 0;
}


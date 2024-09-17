#include <assert.h>
#include <stdio.h>

int bitwise_compare_chr(char c1, char c2) {
    while (c2) {
        c1 ^= c2;
        c2 = (~(c1 ^ c2) & c2) << 1;
    }
    return ((int)c1);
}

int bitswise_compare_string(char *s1, char *s2) {
    int diff;
    while (*s1 && *s2) {
        diff = bitwise_compare_chr(*s1, *s2);
        if (diff != 0) {
            return diff;
        }
        s1++;
        s2++;
    }

    // Si una cadena es más larga que la otra
    if (*s1 || *s2) {
        return bitwise_compare_chr(*s1, *s2);
    }

  // Si ambas cadenas son iguales en longitud y contenido
    return 0; 
}

int main() {
    char *s1 = "Hola1";
    char *s2 = "Hola2";
    int z;

    z = bitswise_compare_string(s1, s2);
    printf("z :%d", z);
    assert(z == -1);
    printf("\nString compare es correcto\n\n");
    
    return 0;
}

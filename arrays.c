#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    // Verifico que se haya ejecutado el programa indicando la cantidad de elementos
    if (argc < 2) {
        printf("Uso: ./arrays [cantidad de elementos]");
        return 1;
    }
    int n = atoi(argv[1]);  // Convierto el caracter a un numero entero
    int nums[n];            // Declaro un array con n cantidad de elementos

    // TODO

    return 0;
} 

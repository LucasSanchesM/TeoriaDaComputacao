#include <stdio.h>
#include <string.h>
#include "huffman.h"

#define MAX_ENTRADA 4096

int main(void) {
    char mensagem[MAX_ENTRADA];

    printf("Digite uma mensagem para codificar com Huffman:\n> ");
    if (fgets(mensagem, sizeof mensagem, stdin) == NULL) {
        fprintf(stderr, "Erro ao ler a entrada.\n");
        return 1;
    }

    size_t tamanho = strlen(mensagem);
    if (tamanho > 0 && mensagem[tamanho - 1] == '\n') {
        mensagem[--tamanho] = '\0';
    } else if (tamanho == sizeof mensagem - 1) {
        fprintf(stderr, "Entrada muito longa (maximo: %d bytes).\n", MAX_ENTRADA - 2);
        return 1;
    }

    if (tamanho == 0) {
        puts("A mensagem esta vazia.");
        return 0;
    }

    huffman_analisar((const unsigned char *)mensagem, tamanho);
    return 0;
}

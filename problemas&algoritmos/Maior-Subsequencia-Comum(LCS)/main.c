#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int maior(int a, int b) {
    return a > b ? a : b;
}

/* Cria e preenche a tabela da LCS */
int **tabela(const char *x, const char *y) {
    int m = (int)strlen(x);
    int n = (int)strlen(y);

    int **L = malloc((m + 1) * sizeof(int *));

    for (int i = 0; i <= m; i++) {
        L[i] = calloc(n + 1, sizeof(int));
    }

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (x[i - 1] == y[j - 1]) {
                L[i][j] = L[i - 1][j - 1] + 1;
            } else {
                L[i][j] = maior(L[i - 1][j],
                                L[i][j - 1]);
            }
        }
    }

    return L;
}

/* Reconstrói a subsequência encontrada */
char *reconstruir(int **L, const char *x, const char *y) {
    int i = (int)strlen(x);
    int j = (int)strlen(y);
    int pos = L[i][j];

    char *res = malloc((pos + 1) * sizeof(char));
    res[pos] = '\0';

    while (i > 0 && j > 0) {
        if (x[i - 1] == y[j - 1]) {
            res[--pos] = x[i - 1];
            i--;
            j--;
        } else if (L[i - 1][j] >= L[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }

    return res;
}

/* Libera a memória da tabela */
void liberarTabela(int **L, int m) {
    for (int i = 0; i <= m; i++) {
        free(L[i]);
    }
    free(L);
}

/* Imprime a tabela */
void imprimirTabela(int **L, const char *x, const char *y) {
    int m = (int)strlen(x);
    int n = (int)strlen(y);

    printf("    ");
    for (int j = 0; j < n; j++) {
        printf("%c ", y[j]);
    }
    printf("\n");

    for (int i = 0; i <= m; i++) {
        printf("%c ", i == 0 ? ' ' : x[i - 1]);

        for (int j = 0; j <= n; j++) {
            printf("%d ", L[i][j]);
        }
        printf("\n");
    }
}

int main(void) {
    const char *testes[][2] = {
        {"ABCBDAB", "BDCABA"},
        {"AGGTAB", "GXTXAYB"},
        {"ABC", "XYZ"}
    };

    int total = (int)(sizeof(testes) / sizeof(testes[0]));

    for (int k = 0; k < total; k++) {
        const char *x = testes[k][0];
        const char *y = testes[k][1];

        int m = (int)strlen(x);
        int **L = tabela(x, y);
        char *lcs = reconstruir(L, x, y);

        printf("Teste %d\n", k + 1);
        printf("X = %s | Y = %s\n", x, y);

        if (k == 0) {
            imprimirTabela(L, x, y);
        }

        printf("LCS = %s | tamanho = %d\n\n",
               lcs[0] ? lcs : "(vazia)", L[m][strlen(y)]);

        free(lcs);
        liberarTabela(L, m);
    }

    return 0;
}

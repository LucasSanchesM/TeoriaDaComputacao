#include <stdio.h>
#include <string.h>

int levenshtein(char palavra1[], char palavra2[]);

int main(void) {
    char palavra[100], palavra2[100];

    scanf("%99s %99s", palavra, palavra2);
    int distancia = levenshtein(palavra, palavra2);
    printf("%d\n", distancia);

    return 0;
}

int levenshtein(char palavra1[], char palavra2[]) {
    int m = strlen(palavra1);
    int n = strlen(palavra2);

    int matriz[m + 1][n + 1];

    for (int i = 0; i <= m; i++) {
        matriz[i][0] = i;
    }

    for (int j = 0; j <= n; j++) {
        matriz[0][j] = j;
    }

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            int custo = (palavra1[i - 1] == palavra2[j - 1]) ? 0 : 1;

            int remocao = matriz[i - 1][j] + 1;
            int insercao = matriz[i][j - 1] + 1;
            int substituicao = matriz[i - 1][j - 1] + custo;

            int menor = remocao;
            if (insercao < menor) {
                menor = insercao;
            }
            if (substituicao < menor) {
                menor = substituicao;
            }

            matriz[i][j] = menor;
        }
    }

    return matriz[m][n];
}

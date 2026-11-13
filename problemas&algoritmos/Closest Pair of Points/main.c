#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX 100

typedef struct {
    double x, y;
} Ponto;

typedef struct {
    double dist; 
    Ponto p1, p2;
} Resultado;

double distancia(Ponto a, Ponto b) {
    return hypot(a.x - b.x, a.y - b.y);
}

int cmp(const void *a, const void *b) {
    Ponto p = *(Ponto *)a, q = *(Ponto *)b;
    return (p.x > q.x) - (p.x < q.x);
}

Resultado menor(Ponto p[], int n) {
    Resultado r = {INFINITY, {0, 0}, {0, 0}};
    
    // Caso base: força bruta para 3 pontos ou menos
    if (n <= 3) {
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                double d = distancia(p[i], p[j]);
                if (d < r.dist) {
                    r = (Resultado){d, p[i], p[j]};
                }
            }
        }
        return r;
    }
    
    // Divisão (Divide and Conquer)
    int m = n / 2;
    double linha = p[m].x;
    
    Resultado a = menor(p, m);
    Resultado b = menor(p + m, n - m);
    
    r = (a.dist < b.dist) ? a : b;
    
    // Construção da faixa (Strip)
    Ponto faixa[MAX];
    int k = 0;
    
    for (int i = 0; i < n; i++) {
        if (fabs(p[i].x - linha) < r.dist) {
            faixa[k++] = p[i];
        }
    }
    
    // Verificação dos pontos na faixa
    for (int i = 0; i < k; i++) {
        for (int j = i + 1; j < k; j++) {
            double dy = faixa[j].y - faixa[i].y;
            if (fabs(dy) >= r.dist) break; // Otimização baseada na distância vertical
            
            double d = distancia(faixa[i], faixa[j]);
            if (d < r.dist) {
                r = (Resultado){d, faixa[i], faixa[j]};
            }
        }
    }
    
    return r;
}

int main() {
    Ponto p[MAX];
    int n;
    
    printf("Quantidade de pontos (2 a %d): ", MAX);
    if (scanf("%d", &n) != 1 || n < 2 || n > MAX) {
        return 1;
    }
    
    for (int i = 0; i < n; i++) {
        printf("Ponto %d (X Y): ", i + 1);
        scanf("%lf %lf", &p[i].x, &p[i].y);
    }
    
    qsort(p, n, sizeof(Ponto), cmp);
    Resultado r = menor(p, n);
    
    printf("\nMenor distancia: %.2f\n", r.dist);
    printf("Pontos: (%.1f, %.1f) e (%.1f, %.1f)\n", r.p1.x, r.p1.y, r.p2.x, r.p2.y);
    
    return 0;
}

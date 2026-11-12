#include<stdio.h>

#define N 5

const char *nomes[N] = {"A(calculo", "B(fisica)", "C(algebra)", "D(programacao)", "E(estatistica)"};

int grafo[N][N] = {
    {0,1,1,0,0},
    {1,0,1,1,0},
    {1,1,0,1,0},
    {0,1,1,0,1},
    {0,0,0,1,0}
};

int cor[N];

long chamadas = 0;

int podeColorir(int v, int c){
    int u;
    
    for(u = 0; u<N; u++){
        if(grafo[v][u] && cor[u] == c){
            return 0;
        }
        return 1;
    }
}


int colorir(int v , int k){
    int c;
    chamadas++;
    if(v == N){
        return 1;
    }
    
    for(c = 1; c<=k; c++){
        if(podeColorir(v, c)){
            cor[v] = c;
            if(colorir(v+1, k)){
                return 1;
            }
        }
        cor[v] = 0;
    }
    return 0;
}

int main(void){
    int i;
    int k;
    
    printf("==== Com coloracao de grafos =======\n\n");
    for(k = 0 ; k<=N;k++){
        for(i = 0; i<N; i++){
            cor[i] = 0;
        }
        chamadas = 0;
        if(colorir(0, k)){
            printf("K = %d: SIM (%ld chamadas)\n\n", k, chamadas);
            printf("Numero cromatico X(G) = %d horarios\n\n", k);
            for(i = 0; i<N; i++){
                printf("%-16s -> horarios %d\n", nomes[i], cor[i]);
            }
            return 0;
        }
    }
}

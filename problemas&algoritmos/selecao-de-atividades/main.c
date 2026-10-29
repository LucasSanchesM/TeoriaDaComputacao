#include<stdio.h>
#include<stdlib.h>
int *tabuleiro;
int N;
int quantidadeDeSolucoes;

void imprimirResolucao(){
    int i;
    int j;
    quantidadeDeSolucoes++;
    printf("Resolução %d\n", quantidadeDeSolucoes);
    
    for(int i = 0; i<N ; i++){
        for(int j = 0; j<N; j++){
            if(tabuleiro[i] == j){
                printf("Q ");
            }
            else{
                printf(". ");
            }
        }
        printf("\n");
    }
    printf("\n");
    
}

int ehSeguro(int linha, int coluna){
    int i;
    
    for(i = 0; i < linha; i++){
        if(tabuleiro[i] == coluna){
            return 0;
        }
        if(abs(linha - i) == abs(tabuleiro[i] - coluna)){
            return 0;
        }
    }
    return 1;
    
}
void resolver(int linha){
     if(linha == N){
         imprimirResolucao();
         return;
     }
    
    int coluna;
    
    for(coluna = 0; coluna<N; coluna++){
        if(ehSeguro(linha, coluna)){
            tabuleiro[linha] = coluna;
            resolver(linha + 1);
        }
    }
}


int main(){
    printf("Insira o valor de N: ");
    scanf("%d", &N);
    
    tabuleiro = malloc(N*sizeof(int));
    quantidadeDeSolucoes = 0;
    
    resolver(0);
    printf("\nquantidadeDeSolucoes: %d", quantidadeDeSolucoes);
    
    
    return 1;
}

#include<stdio.h>

#define MAX_ITENS 100
#define MAX_CAPACIDADE 1000

int main(){
	int n, capacidade;
	int peso[MAX_ITENS + 1];
	int valor[MAX_ITENS + 1];
	int dp[MAX_ITENS + 1][MAX_CAPACIDADE + 1];
	int i, j;
	
	printf("Quantidade de Itens(maximo %d):", MAX_ITENS);
	scanf("%d", &n);
	
	if(n < 1 || n > MAX_ITENS){
		printf("Quantidade de itens invalida.\n");
		return 1;
	}
	
	printf("Capacidade de mochila: ");
	scanf("%d", &capacidade);
	if(capacidade < 0 || capacidade > MAX_CAPACIDADE){
		printf("Capacidade invalida");
		return 1;
	}
	
	for(i = 1; 1 <= n; i++){
		printf("\nItem %d\n", i);
		printf("Peso: ");
		scanf("%d", &peso[i]);
		printf("Valor: ");
		scanf("%d", &valor[i]);
		
		if(peso[i] <= 0 || valor[i] < 0){
			printf("Peso ou valor invalido.\n");
			return 1;
		}
	}
	
	for(i = 0; i<= n; i++){
		dp[i][0] = 0;
	}
	
	for(j = 0; j<= capacidade; j++){
		dp[0][i] = 0;
	}
	
	for(i = 0; i<= n; i++){
        for(j = 0; j<= capacidade; j++){
			if(peso[i] > j){
				dp[i][j] = dp[i-1][j];
			}else{
				int melhorAnterior = dp[i -1][j];
				int pegar = valor[i] + dp[i - 1][j - peso[i]];
				if(pegar > melhorAnterior){
				dp[i][j] = pegar;
				}else{
					dp[i][j] = melhorAnterior;
				}
			}
			
			
		}
	}
	printf(" RESULTADOS \n");
	printf("Vakor  maximo: %d\n", dp[n][capacidade]);
	
	printf("\nIens selecionados:\n");
	
	j = capacidade;
	
	for(i = n; i >= 1; i--){
		if(dp[i][j] != dp[i-1][j]){
			printf("Item %d - Peso: %d - valor: %d\n", i, peso[i], valor[i]);
			j = j - peso[i];
		}
	}
	printf("\n Capacidade utilizada: %d de %d\n", capacidade -j, capacidade);

	
	return 1;
}

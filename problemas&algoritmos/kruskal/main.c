#include<stdio.h>
#include<stdlib.h>

typedef struct{int u, v, peso;}Aresta

int pai[];

int find(int x){
	while(pai[x] != x){
		x = pai[x];
	return x;
	}
}

int cmp(const void *a, const void *b){
	return ((aresta *)a)->peso - ((Aresta *)b)->peso;
}

int kruskal(int n, Aresta e[], int m){
	int custo = 0;
	int i;
	
	for(i = 0; i < n; i++){
		pai[i] = i;
	}
	
	for(i = 0; i<m; i++){
		int a = find(e[i] .u);
		int b = find(e[i]) .v);
		if(a!=b){
			pai[a] = b
                custo += e[i] .peso;
                printf("Aceita %d-%d (peso%d\n)", e[i].u, e[i].v, e[i].peso);
			}else{
				printf("Rejei %d-%d (peso %d - ciclo\n)", e[i].u, e[i].v, e[i.peso]);
			}
		}
		return custo;
	}
	
	int main(){
		Aresta g1[] = {{1, 2, 3}, {0,2,2}, {3,4,2}, {0, 1, 4},
 			   		  {1, 3, 5}, {1,4,7}, {2,3,8}, {2,4,10}};
 			   		  
 		Aresta g2[] = {{1, 2, 2}, {2,3,3}, {4,5,3}, {6, 7, 4},
 			   		  {3, 4, 5}, {5,6,6}, {5,7,7}, {2,4,8}};	   		  
		printf("Teste 1\n");
		printf("Custo: %d\n\n", kruska1(5, g1, 8));
		
		printf("Teste 2\n")
}

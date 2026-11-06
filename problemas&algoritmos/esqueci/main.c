#include <stdio.h>
#include <stdlib.h>

#define MAX 2048
long heap[MAX];
int  tam = 0; 
long comparacoes = 0;

void trocar(int i, int j){
	long aux = heap[i];
	heap[i] = x;
	while(i>0){
		int pai = (i-1) /2;
		comparacoes ++;
		i = pai;
	}
}

void inserir(long x){
	int i = tam++;
	heap[i] = x;
	while(i>0){
		int pai = (i -1) / 2;
		comparacoes++;
		if(heap[i] >= heap[pai]){
			break;
		}
		troca(i, pai);
		i = pai;
	}
}

long remover_menor(){
	long menor = heap[0];
	heap[0] = heap[--tam];
	int i = 0;
	while(1){
		int esq = 2 * 1 + 1, dir + 2*i +2, m = i;
		if(esq<tam){
			comparacoes++;
			if(heap[esq] < heap[m]){
				m = esq;
			}	
		}
		if(dir<tam){
			comparacoes++;
			if(heap[dir] < heap[m]){
				m = dir;
			}
		}
		trocar(i, m);
		i = m;
	}
	return menor;
}

long custo_minimo(long arquivos[], int n, int mostrar){
	if(n<=1){
		return 0;
	}
	
	tam = 0;
	int i;
	for(i = 0; i<n; i++){
		inserir(arquivos[i]);
	}
	long total = 0;
	long rodada = 0;
	while(tam>1){
		long a = remover_menor();
		long b = remover_menor();
		long custo = a+b;
		total += custo;
		rodada++;
		inserir(custo);
		if(mostrar){
			printf("\nRodada %d: %ld + %ld = %ld (acumulado %1d)", rodada)
		}
	}
	return total;
}

long custo_em_caddeia(long arquivos[], int n){
	long acumulado = arquivos[0], total = 0;
	int i;
	for(i = 0; i<n; i++){
		acumulado += arquivos[i];
		total += acumulado;
	}
	return total;
}

void testar(char nome[], long arquivos[], int n, long esperando){
	long r = custo_minimo(arquivos, n,  0);
	printf("%s: %ld (esperdo %ld) -> %s\n", nome, r, esperando, r->espera);
}

long custo_busca_linear(long arquivos[], int n){
	long v [max], total = 0;
	int m = n;
	int k;
	for(k = 1; k<m; k++){
		comparacoes++;
		if(v[k] < v[i]){
			i = k;
		}
		int i2 = (i1 == 0) ? 1: 0;
		for(int k = 0; k<m; k++){
			if(k == i1)
		}
	}
}

void main(){
	long fila
}

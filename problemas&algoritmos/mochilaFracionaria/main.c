#include<stdio.h>

float mochilaFracionaria(int n, float pesos[], float valores[], int capacidade){
	float valorTotal = 0.0;
	int capacidadeAtual = capacidade;
	int i;
	for(i = 0; i<n; i++){
		if(pesos[i] <= capacidadeAtual){
			capacidadeAtual -= pesos[i];
			valorTotal += valores[i];
		}
		else{
			float fracao = (float)capacidadeAtual/pesos[i];
			valorTotal += valores[i] * fracao;
			break;
		}
	}
	return valorTotal;
}

int main(){
	int n = 3;
	int capacidade = 50;
	
	float valores[] = {60, 100, 120};
	float pesos[] = {10, 20, 30};
	float resultado = mochilaFracionaria(n, pesos, valores, capacidade);
	printf("Valor maximo na mochila: %.2f\n", resultado);
	
	return 0;
}

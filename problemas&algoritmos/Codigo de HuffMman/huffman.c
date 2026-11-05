#include "huffman.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALFABETO 256
#define MAX_NOS (2 * ALFABETO - 1)

typedef struct No {
	unsigned char caractere;
	size_t frequencia;
	int menor_byte;
	struct No *esquerda, *direita;
} No;

typedef struct {
	No *dados[MAX_NOS];
	int tamanho;

} MinHeap;

static int anterior(const No *a, const No *b) {
	   if(a->frequencia != b->frequencia)
	       return a->frequencia < b->frequencia;
	   return a->menor_byte < b->menor_byte;
}

static void inserir(MinHeap *heap, No *no) {
	   int i =  heap->tamanho++;
	   while(i > 0 && anterior(no, heap->dados[(i - 1)/ 2])){
	   	heap->dados[i] = heap->dados[(i - 1)/2];
	   	i = (i - 1)/2;
	   }
	   heap->dados[i] = no;
}

static No *remover_minimo(MinHeap *heap) {
	   No *minimo = heap->dados[0];
	   No *ultimo = heap->dados[--heap->tamanho];
	   if(heap->tamanho == 0) return minimo;
	   int i = 0;
	   while(2 * i + 1 < heap->tamanho){
	   	int filho = 2 * i + 1;
	   	if(filho + 1 < heap->tamanho && anterior(heap->dados[filho + 1], heap->dados[filho]))
		   filho++;
	    if(!anterior(heap->dados[filho], ultimo)) break;
	    heap->dados[i] = heap->dados[filho];
	    i = filho;
	   }
	   heap->dados[i] = ultimo;
	   return minimo;
}

static No *novo_no(unsigned char c, size_t freq, No *esq, No *dir) {
	   No *no = malloc(sizeof *no);
	   if(!no){ 
	   			fprintf(stderr, "Memoria insuficiente.\n"); exit(EXIT_FAILURE);
	   }
	   no->caractere = c;
	   no->frequencia = freq;
	   no->esquerda = esq;
	   no->direita = dir;
	   no->menor_byte = (!esq && !dir) ? c :
	   	(esq->menor_byte < dir->menor_byte ? esq->menor_byte : dir->menor_byte);
	   	return no;
}

static void gerar_codigos(const No *no, char caminho[ALFABETO], int profundidade, char codigos[ALFABETO][ALFABETO]) {
	   if(!no->esquerda && !no->direita){
	   	if(profundidade == 0) caminho[profundidade++] = '0';
	   	caminho[profundidade] = '\0';
	   	strcpy(codigos[no->caractere], caminho);
	   	return;
	   }
	   if(no->esquerda){
	   	caminho[profundidade] = '0';
	   	gerar_codigos(no->esquerda, caminho, profundidade + 1, codigos);	
	   }
	   if(no->direita){
	   	caminho[profundidade] = '1';
	   	gerar_codigos(no->direita, caminho, profundidade + 1, codigos);
	   }
}

static void liberar_arvore(No *no) {
	   if(!no) return;
	   liberar_arvore(no->esquerda);
	   liberar_arvore(no->direita);
	   free(no);
}

static void mostrar_byte(int c) {
	   if(c == ' ')printf("espaco");
	   else if( c == '\t') printf("TAB");
	   else if(c == '\r') printf("CR");
	   else if(c >= 33 && c <= 126)printf("'%c'", c);
	   else printf("0x%02X", c);
}

void huffman_analisar(const unsigned char *mensagem, size_t tamanho) {
	 size_t freq[ALFABETO] = {0};
	 char codigos[ALFABETO][ALFABETO] = {{0}};
	 char caminho[ALFABETO];
	 MinHeap heap = {.tamanho = 0};
	 int distintos = 0;
	 size_t i = 0;
	 
	 for(i = 0; i < tamanho; i++)
	 			freq[mensagem[i]]++;
	 
	 int c;
	 for(c = 0; c < ALFABETO; c++){
	 	if(freq[c] != 0){
	 		inserir(&heap, novo_no((unsigned char)c, freq[c], NULL, NULL));
	 		distintos++;
		 }
	 }
	 while(heap.tamanho > 1){
	 	No *esq = remover_minimo(&heap);
	 	No *dir = remover_minimo(&heap);
	 	inserir(&heap, novo_no(0, esq->frequencia + dir->frequencia, esq, dir));
	 }
	 
	 No *raiz = remover_minimo(&heap);
	 gerar_codigos(raiz, caminho, 0, codigos);
	 
	 size_t bits_comprimidos = 0;
	 printf("\n%-12s %12s %12s  %s\n", "Caractere", "Frequencia", "Bits/simbolo", "Codigo Huffman");
	 puts("----------------------------------------------------------------------");
	 for( c = 0;  c < ALFABETO; c++){
	 	if(freq[c] == 0)continue;
	 	mostrar_byte(c);
	 	printf("\n%-12s %12zu %12zu  %s\n", "", freq[c], strlen(codigos[c]), codigos[c]);
	 	bits_comprimidos += freq[c] * strlen(codigos[c]);
	 }
	 size_t bits_originais = tamanho * 8;
	 printf("\nBytes de entrada: %zu | Simbolos distintos: %d\n", tamanho, distintos);
	 printf("Tamanho original (8 bits/byte): %zu bits\n", bits_originais);
	 printf("Tamanho codificado (sem cabecalho): %zu bits\n", bits_comprimidos);
	 printf("Reducao teorica: %.2f%%\n", 100.0 * (1.0 - (double)bits_comprimidos / bits_originais));
	 printf("\nMensagem codificada(bits:)\n");
	 for(i = 0; i < tamanho; i++)printf("%s", codigos[mensagem[i]]);
	 putchar('\n');
	 liberar_arvore(raiz);
}

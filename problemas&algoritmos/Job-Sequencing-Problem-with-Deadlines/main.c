#include<stdio.h>
#include<stdlib.h>

typedef struct{
	char nome;
	int prazo;
	int lucro;	
} Tarefa;

int compararLucro(const void *a, const void *b){
	const Tarefa *t1 = (const Tarefa*)a;
	const Tarefa *t2 = (const Tarefa*)b;
	if(t1->lucro <  t2->lucro){
		return 1;
	}
	if(t1->lucro > t2->lucro){
		return -1;
	}
	return 0;
}

void executarTeste(const char *titulo, Tarefa tarefas[], int quantidade){
	int maiorPrazo = 0;
	int lucroTotal = 0;
	int i;
	for(i= 0; i < quantidade; i++){
		if(tarefas[i].prazo > maiorPrazo){
			maiorPrazo = tarefas[i].prazo;
		}
	}
	
	qsort(tarefas, quantidade, sizeof(Tarefa), compararLucro);
	Tarefa **agenda = calloc((size_t)maiorPrazo + 1, sizeof(Tarefa*));
	
	if(agenda == NULL){
		printf("Erro de alocacao.\n");
		return;
	}
	printf("\n===========\n");
	printf("%s\n", titulo);
	printf("Tarefas ordenadas por lucro decrescente:\n");
	for(i = 0; i < quantidade; i++){
		printf("%c (prazo %, lucro R$ %d)\n", tarefas[i].nome, tarefas[i].prazo);
		
	}
	for(i = 0; i < quantidade; i++){
		int ultimoHorario = tarefas[i].prazo;
		if(ultimoHorario > maiorPrazo){
			ultimoHorario = maiorPrazo;
		}
		int horario;
		for(horario = ultimoHorario; horario>= 1; horario--){
			if(agenda[horario] == NULL){
				agenda[horario] = &tarefas[i];
				break;
			}
		}
	}
	printf("\nAgenda Final:\n");
	
	int horario;
	
	for(horario =1; horario <= maiorPrazo; horario++){
		if(agenda[horario] != NULL){
			printf("Horario %d: tarefa: %c (lucro R$ %d)\n", horario, agenda[horario]->nome, agenda[horario]->lucro);
			lucroTotal +=	agenda[horario]->lucro;
		}
		else{
			printf("Horario %d: livre \n", horario);
		}
	}
	printf("\nSequencia de execucao: ");
	int primeira = 1;
	for(horario = 1; horario<=maiorPrazo; horario++){
		if(agenda[horario] != NULL){
			if(!primeira){
				printf(" -> ");
			}
			printf("%c", agenda[horario]->nome);
			primeira = 0;
		}
	}
	
	if(primeira){
		printf("nenhuma\n");
	}
	
	printf("\nLucro total: R$ %d\n", lucroTotal);
	free(agenda);
}

int main(){
	Tarefa teste1[] = {
		   			   {'A', 2, 100},
 					   {'B', 1, 80},
 					   {'C', 2, 50},
 						{'D', 1, 20}
						 };
	Tarefa teste2[] = {
		   			   {'A', 1, 35},
 					   {'B', 1, 30},
 					   {'C', 2, 25},
						{'D', 1, 15},
 						{'E', 3, 10}
						 };
	int quantidade1 = (int)(sizeof(teste1)/ sizeof(teste1[0]));
	int quantidade2 = (int)(sizeof(teste2)/ sizeof(teste2[0]));	 
 	executarTeste("Teste 1 - Exemplo Principal", teste1, quantidade1);
 	executarTeste("Teste 2 - Exemplo Principal", teste2, quantidade2);
	
	return 0;
}

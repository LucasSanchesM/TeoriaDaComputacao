#include<stdio.h>
#define N 4
#define INF 999

void dijkstra(int grafo[N][N]){
    int dist[N] = {0, INF, INF, INF};
    int visitado[N] = {0};
    
    for(int i = 0; i<N; i++){
        int menor = INF;
        int atual = -1;
        
        for(int j = 0; j<N; j++){
            if(visitado[j] == dist[j]<menor){
                menor = dist[j];
                atual = j;
            }
        }
    
    if(atual == -1) break;
    
    visitado[atual] = 1;
    
    for(int j = 0; j<N; j++){
        if(grafo[atual][j] > 0 && visitado[j] && dist[atual] + grafo[atual][j] < dist[j]){
            dist[j] = dist[atual] + grafo[atual][j];
        }
    }
    }
    printf("Distancia de A até D: %d km\n", dist[3] );
}

int main(){
    int grafo1[N][N] = {
        {0,2,5,0}, {2,0,1,5}, {5, 1, 0,2}, {0,5,2,0}
    };
    
    int grafo2[N][N] = {
        {0,4,2,0}, {4,0,1,3}, {2, 1, 0, 7}, {0, 3, 7, 0}
    };
    
    printf("Teste 1: ");
    dijkstra(grafo1);
    printf("Teste 2: ");
    dijkstra(grafo2);
    
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct No{
    int destino;
    int valor;
    struct No* prox;
} tNo;

void menu(tNo *grafo[], char msg[]);
void clearScreen();

void intializeGrafo(tNo *grafo[]){
    for (int i = 0; i<50; i++){
        grafo[i] = NULL;
    }
}

void addVertices(tNo *grafo[]){
    int origem;
    int destino;
    int valor;
    int exitLoop;
    while(1){
        printf("Digite a o vertice de origem, o de destino e o valor ponderado da aresta(1 2 5) ou 99 0 0 para voltar:");
        scanf("%d %d %d", &origem, &destino, &valor);
        if (origem >= 50 || destino >=50 || origem < 0 || destino < 0){
            break;
        }
        
        tNo *createdNo = malloc(sizeof(tNo));

        createdNo->destino = destino;
        createdNo->valor = valor;
        createdNo->prox = NULL;
        //Caso não tenha nenhum nó neste índice.
        if (grafo[origem] == NULL){
            grafo[origem] = createdNo;
        }else{
            tNo *noAux = malloc(sizeof(tNo));
            noAux = grafo[origem];
            //Caso o Nó de destino já exista, apenas altera seu valor.
            if (noAux->destino == createdNo->destino){
                printf("Origem -> Destino já existem, valor sendo alterado.\n");
                noAux->valor = createdNo->valor;
                continue;
            }
            // Caso seja o segundo nó da lista encadeada.
            if (noAux->prox == NULL){ 
                noAux->prox = createdNo;
            }else{
                exitLoop = 0;
                do{
                    //Caso o Nó de destino já exista, apenas altera seu valor.
                    if (noAux->destino == createdNo->destino){
                        printf("Origem -> Destino já existem, valor sendo alterado.\n");
                        noAux->valor = createdNo->valor;
                        exitLoop = 1;
                        break;
                    }
                    noAux = noAux->prox;
                }while(noAux->prox != NULL);
                if (!exitLoop){
                    noAux->prox = createdNo;
                }
            }

        }
    }
    menu(grafo, "Seu grafo foi criado!\n");
}

void printNo(int origem, int destino, int valor){
    printf("Origem: %d | Destino: %d | Valor Ponderado: %d\n", origem, destino, valor);
}

void printGrafo(tNo *grafo[]){
    printf("Este é o grafo até o momento:\n");
    for (int i = 0; i<50; i++){
        if (grafo[i] != NULL){
            tNo *noAux = malloc(sizeof(tNo));
            noAux = grafo[i];
            printNo(i, noAux->destino, noAux->valor);
            noAux = grafo[i]->prox;
            while(noAux != NULL){
                printNo(i, noAux->destino, noAux->valor);
                noAux = noAux->prox;
            }
        }
    }
}

void showGrafo(tNo *grafo[]){
    printGrafo(grafo);
    printf("Aperte b para voltar ao menu:");
    getchar();
    getchar();
    menu(grafo, NULL);
}

void removeNo(tNo *no){
    no->prox = no->prox->prox;
}

void removeFromGrafo(tNo *grafo[]){
    char resp;
    int origem;
    int destino;
    int maybeLast = 1;
    tNo *noAux = malloc(sizeof(tNo));
    printGrafo(grafo);
    printf("Digite o vertice de origem e destino que se deseja remover(1 2):");
    scanf("%d %d", &origem, &destino);
    if (grafo[origem] != NULL){
        //Caso seja o primeiro nó.
        if (grafo[origem]->destino == destino){
            grafo[origem] = grafo[origem]->prox;
            maybeLast = 0;
        }else{
            noAux = grafo[origem]->prox;
            //Caso seja o segundo
            while(noAux->prox->prox != NULL){
                printf("atual: %d", noAux->destino);
                if (noAux->prox->destino == destino){
                    removeNo(noAux);
                    printf("depois: %d", noAux->prox->destino);
                    maybeLast = 0;
                }
                noAux = noAux->prox;
            }
            if (maybeLast){
                printf("last: %d", noAux->destino);
                if (noAux->prox->destino == destino){
                    noAux->prox = NULL;
                }
            }
        }
    }
    printf("A aresta formada pelos vertives (%d, %d) foi removida com sucesso!", origem, destino);
    printf("Deseja remover mais? (s/n):");
    getchar();
    resp = getchar();
    if (resp == 's'){
        clearScreen();
        removeFromGrafo(grafo);
    }else{
        menu(grafo, NULL);
    }
    
}

void clearScreen()
{
  const char *CLEAR_SCREEN_ANSI = "\e[1;1H\e[2J";
  write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 12);
}

void menu(tNo *grafo[], char msg[]){
    int option;
    clearScreen();
    printf("Programa de Grafos\n\n\n");
    printf("1) Adicionar elementos ao grafo.\n");
    printf("2) Mostrar Grafo.\n");
    printf("3) Remover um elemento do grafo.\n\n");
    if (msg != NULL){
        printf("%s", msg);
    }
    printf("Digite a opção desejada: ");
    scanf("%d", &option);
    switch (option){
        case 1:
            clearScreen();
            addVertices(grafo);
            break;
        case 2:
            clearScreen();
            showGrafo(grafo);
            break;
        case 3:
            clearScreen();
            removeFromGrafo(grafo);
            break;
        default:
            clearScreen();
            printf("calma");
            break;
    }
}


int main(){
    
    tNo *grafo[50];
    intializeGrafo(grafo);
    menu(grafo, NULL);

}

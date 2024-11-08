#include <stdio.h>
#include <stdlib.h>

typedef struct {
    void **dados;
    int inicio;
    int fim;
    int tamanho;
    int capacidade;
} Fila;

Fila* criarFila(int capacidadeInicial) {
    Fila *fila = (Fila *) malloc(sizeof(Fila));
    if (fila == NULL) return NULL;

    fila->dados = (void **) malloc(sizeof(void*) * capacidadeInicial);
    fila->inicio = 0;
    fila->fim = -1;
    fila->tamanho = 0;
    fila->capacidade = capacidadeInicial;

    return fila;
}

void limparFila(Fila *fila) {
    if (fila != NULL) {
        free(fila->dados);
        free(fila);
    }
}

void dobrarCapacidade(Fila *fila) {
    int novaCapacidade = fila->capacidade * 2;
    void **novosDados = (void **) malloc(sizeof(void*) * novaCapacidade);
    
    for (int i = 0; i < fila->tamanho; i++) {
        novosDados[i] = fila->dados[(fila->inicio + i) % fila->capacidade];
    }

    free(fila->dados);
    fila->dados = novosDados;
    fila->inicio = 0;
    fila->fim = fila->tamanho - 1;
    fila->capacidade = novaCapacidade;
}

void inserirNaFila(Fila *fila, void *item) {
    if (fila->tamanho == fila->capacidade) {
        dobrarCapacidade(fila);
    }
    fila->fim = (fila->fim + 1) % fila->capacidade;
    fila->dados[fila->fim] = item;
    fila->tamanho++;
}

void* removerDaFila(Fila *fila) {
    if (fila->tamanho == 0) return NULL;
    void *item = fila->dados[fila->inicio];
    fila->inicio = (fila->inicio + 1) % fila->capacidade;
    fila->tamanho--;
    return item;
}

int main() {
    Fila *fila = criarFila(2);
    
    int a = 1, b = 2, c = 3, d = 4;
    inserirNaFila(fila, &a);
    inserirNaFila(fila, &b);
    inserirNaFila(fila, &c);
    inserirNaFila(fila, &d);
    
    int *item;
    while ((item = (int *) removerDaFila(fila)) != NULL) {
        printf("Removido: %d\n", *item);
    }
    
    limparFila(fila);
    return 0;
}

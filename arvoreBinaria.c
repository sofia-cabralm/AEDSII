#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0

typedef struct no {
    int info;
    struct no *esq;
    struct no *dir;
} Node;

Node* insere(Node* raiz, int valor) {
    Node* node = (Node*) malloc(sizeof(Node));
    node->info = valor;
    node->esq = NULL;
    node->dir = NULL;
    if (raiz == NULL) {
        return node;
    } else {
        // Vamos para a esquerda
        if (valor < raiz->info) {
            raiz->esq = insere(raiz->esq, valor);
        }
        if (valor > raiz->info) {
            raiz->dir = insere(raiz->dir, valor);
        }
    }
    return raiz;
}

// TODO: Mostrar a árvore
// Notações: Pré-Ordem, Em-Ordem e Pós-Ordem
void mostraArvorePreOrdem(Node *raiz) {
    // printf("%d \t", raiz->info);
    if (raiz != NULL) { // if (raiz)
        printf("%d \t", raiz->info);
        mostraArvorePreOrdem(raiz->esq);
        mostraArvorePreOrdem(raiz->dir);
    }
}

void mostraArvoreEmOrdem(Node *raiz) {
    // printf("%d \t", raiz->info);
    if (raiz != NULL) { // if (raiz)
        mostraArvoreEmOrdem(raiz->esq);
        printf("%d \t", raiz->info);
        mostraArvoreEmOrdem(raiz->dir);
    }
}

void mostraArvorePosOrdem(Node *raiz) {
    // printf("%d \t", raiz->info);
    if (raiz != NULL) { // if (raiz)
        mostraArvorePosOrdem(raiz->esq);
        mostraArvorePosOrdem(raiz->dir);
        printf("%d \t", raiz->info);
    }
}
// TODO: Remover da árvore
// DECISÃO: Maior item subárvore esquerda OU menor item subárvore direita
// ESCOLHA: Maior item subárvore esquerda
// remove(raiz, NULL, 5)
Node* remover(Node *raiz, int valor) {
    if (raiz == NULL) {
        return raiz;
    }
    if (raiz->info == valor) {
        if (raiz->esq == NULL && raiz->dir == NULL) {
            free(raiz);
            return NULL;
        }
        if (raiz->esq == NULL) {
            Node* temp = raiz->dir;
            free(raiz);
            return temp;
        }
        if (raiz->dir == NULL) {
            Node* temp = raiz->esq;
            free(raiz);
            return temp;
        }
        Node* atual = raiz->esq;
        Node* anterior = atual;
        Node* anteriorDoAnterior = anterior;
        while (atual->dir != NULL) {
            anteriorDoAnterior = anterior;
            anterior = atual;
            atual = atual->dir;
        }
        anterior->dir = raiz->dir;
        anterior->esq = raiz->esq;
        // atual = anterior;
        anteriorDoAnterior->dir = NULL;
        atual = anterior;
        // remover(raiz, anterior->info);
        free(raiz);
        return anterior;
    } else if (raiz->info > valor) {
        raiz->esq = remover(raiz->esq, valor);
    } else {
        raiz->dir = remover(raiz->dir, valor);
    }
    return raiz;
}

// TODO: Buscar elemento na árvore O(log n)
int busca(Node *raiz, int valor) {
    if (raiz == NULL) {
        return FALSE;
    }
    if (raiz->info == valor) {
        return TRUE;
    }
    if (raiz->info > valor) {
        return busca(raiz->esq, valor);
    } else {
        return busca(raiz->dir, valor);
    }
}

int main() {
    // Podemos suprimir a função "inicia" / "iniciaArvore"
    Node *raiz = NULL;
    raiz = insere(raiz, 50);
    raiz = insere(raiz, 80);
    raiz = insere(raiz, 35);
    // raiz = insere(raiz, 80);
    // raiz = insere(raiz, 20);
    // raiz = insere(raiz, 45);
    // raiz = insere(raiz, 90);
    // raiz = insere(raiz, 75);
    raiz = remover(raiz, 50);
    // raiz = insere(raiz, 50);
    mostraArvorePreOrdem(raiz);
    // int result = busca(raiz, -50);
    // printf("Valor existe na árvore? %d", result);
    // printf("Valor eh: %d\n", raiz->info);
    return 1;
}
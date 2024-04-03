#include<stdio.h>
#include<stdlib.h>

typedef struct no {
    int info;
    int fb;
    struct no *esq;
    struct no *dir;
} Node;

Node* rotacaoEsquerda(Node* raiz) {
    Node* temp = raiz->dir;
    raiz->dir = temp->esq;
    temp->esq = raiz;
    raiz->fb = 0;
    temp->fb = 0;
    return temp;
}

Node* rotacaoDireita(Node* raiz) {
    Node* temp = raiz->esq;
    raiz->esq = temp->dir;
    temp->dir = raiz;
    raiz->fb = 0;
    temp->fb = 0;
    return temp;
}

Node* rotacaoDuplaDireita(Node* raiz) {
    raiz->esq = rotacaoEsquerda(raiz->esq);
    return rotacaoDireita(raiz);
}

Node* rotacaoDuplaEsquerda(Node* raiz) {
    raiz->dir = rotacaoDireita(raiz->dir);
    return rotacaoEsquerda(raiz);
}

int altura(Node* raiz) {
    if (raiz == NULL) return -1;
    int altura_esq = altura(raiz->esq);
    int altura_dir = altura(raiz->dir);
    return 1 + (altura_esq > altura_dir ? altura_esq : altura_dir);
}

Node* insere(Node* raiz, int valor) {
    if (raiz == NULL) {
        Node* novoNoh = (Node*) malloc(sizeof(Node));
        novoNoh->info = valor;
        novoNoh->esq = NULL;
        novoNoh->dir = NULL;
        novoNoh->fb = 0;
        return novoNoh;
    }

    if (raiz->info > valor) {
        raiz->esq = insere(raiz->esq, valor);
    } else if (raiz->info < valor) {
        raiz->dir = insere(raiz->dir, valor);
    }

    // Atualiza o fator de balanceamento
    raiz->fb = altura(raiz->esq) - altura(raiz->dir);

    // Realiza as rotacoes se necessario
    if (raiz->fb >= 2) {
        if (valor < raiz->esq->info) {
            return rotacaoDireita(raiz);
        } else {
            return rotacaoDuplaDireita(raiz);
        }
    }

    if (raiz->fb <= -2) {
        if (valor > raiz->dir->info) {
            return rotacaoEsquerda(raiz);
        } else {
            return rotacaoDuplaEsquerda(raiz);
        }
    }

    return raiz;
}

void emOrdem(Node* raiz) {
    if (raiz != NULL) {
        emOrdem(raiz->esq);
        printf("%d ", raiz->info);
        emOrdem(raiz->dir);
    }
}

int main() {
    Node *raiz = NULL;
    raiz = insere(raiz, 5);
    raiz = insere(raiz, 2);
    raiz = insere(raiz, 4);

    // Exibe a arvore em ordem
    emOrdem(raiz);

    return 0;
}

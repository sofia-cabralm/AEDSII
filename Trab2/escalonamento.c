
/*+-------------------------------------------------------------+
| UNIFAL – Universidade Federal de Alfenas. |
| BACHARELADO EM CIENCIA DA COMPUTACAO. |
| Trabalho..: Métodos de Escalonamento |
| Disciplina: Algoritmos e Estrutura de Dados II – Pratica |
| Professor.: Fellipe Rey |
| Aluno(s).: Sofia Cabral Marcelino - 2022.2.08.002 |
| Data......: 15/12/2023 |
+-------------------------------------------------------------+*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*Criando processos*/
typedef struct {
    int id;
    int temppro;
    int prioridade;
    int execucao;
    int espera;
    struct Processo* prox;
} Processo;

/*Criando uma Fila*/
typedef struct {
    Processo* frente;
    Processo* tras;
} Fila;

/*Criando uma Lista*/
typedef struct {
    Processo* inicio;
    Processo* fim;
} Lista;

/*Criando uma lista encadeada*/
typedef struct {
    Processo* frente;
    Processo* tras;
} ListaEncadeada;

/*Funções*/
Processo* criar_processo(int id, int temppro, int prioridade);
void enfileirar(Fila* fila, Processo* processo);
Processo* desenfileirar(Fila* fila);
void inserirLista(Lista* lista, Processo* processo);
Processo* removerLista(Lista* lista);
void inicializarListaEncadeada(ListaEncadeada* lista);
void inserirlistaencad(ListaEncadeada* lista, Processo* processo);
Processo* removerListaEncadeada(ListaEncadeada* lista);
void fcfs(Fila* fila);
void sjf(Lista* lista);
void roundRobin(Lista* lista, int quantum);
void menu(Fila* filaFCFS, Lista* listaSJF, Lista* listaRoundRobin);
void imprimirFila(Fila* fila);
void imprimirLista(Lista* lista);
void imprimirListaEncadeada(ListaEncadeada* lista);


int main() {
    srand(time(NULL));

    Fila filaFCFS;
    filaFCFS.frente = NULL;
    filaFCFS.tras = NULL;

    Lista listaSJF;
    listaSJF.inicio = NULL;
    listaSJF.fim = NULL;

    Lista listaRoundRobin;
    listaRoundRobin.inicio = NULL;
    listaRoundRobin.fim = NULL;

    menu(&filaFCFS, &listaSJF, &listaRoundRobin);

    return 0;
}

void menu(Fila* filaFCFS, Lista* listaSJF, Lista* listaRoundRobin) {
    int opcao;
    int processoscriados = 0;
    int n = 0;
    int i;

    do {
        printf("Entrou no loop do menu. Opção: %d\n", opcao);
        printf("\n===== MENU =====\n");
        printf("1. Criar Processos\n");
        printf("2. Escalonar FCFS\n");
        printf("3. Escalonar SJF\n");
        printf("4. Escalonar Round-Robin\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite a quantidade de processos: ");
                scanf("%d", &n);
                for (i = 0; i < n; i++) {
                    if (rand() % 100 < 30) {
                        int temppro = rand() % 20 + 1;
                        int prioridade = rand() % 5 + 1;
                        Processo* processo = criar_processo(i + 1, temppro, prioridade);

                        // Para FCFS (fila)
                        enfileirar(filaFCFS, processo);

                        // Para SJF (lista SJF)
                        inserirLista(listaSJF, processo);

                        // Para Round-Robin (lista Round-Robin)
                        inserirlistaencad(listaRoundRobin, processo);

                        processoscriados++;

                         printf("Processo criado: ID=%d, Tempo=%d, Prioridade=%d\n", processo->id, processo->temppro, processo->prioridade);
                    }
                }
            printf("Foram criados %d processos.\n", processoscriados);
            break;

            case 2:
            imprimirFila(filaFCFS);
            fcfs(filaFCFS);
            break;

            case 3:
            imprimirLista(listaSJF);
            sjf(listaSJF);
            break;

            case 4:
            imprimirListaEncadeada(listaRoundRobin);
            roundRobin(listaRoundRobin, 6);
            break;

            case 0:
                printf("Saindo do programa.\n");
                break;

            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 0);
}

Processo* criar_processo(int id, int temppro, int prioridade) {
    Processo* proc = (Processo*)malloc(sizeof(*proc));
    if (proc == NULL) {
        printf("Erro Fatal: Falha Alocacao de memoria.\nFinalizar.\n");
        exit(1);
    }
    proc->id = id;
    proc->temppro = temppro;
    proc->prioridade = prioridade;
    proc->execucao = 0;
    proc->espera = 0;
    proc->prox = NULL;
    return proc;
}

void imprimirFila(Fila* fila) {
    Processo* atual = fila->frente;

    printf("Fila FCFS: ");

    while (atual != NULL) {
        printf("%d ", atual->id);
        atual = atual->prox;
    }

    printf("\n");
}

void imprimirLista(Lista* lista) {
    Processo* atual = lista->inicio;

    printf("Lista SJF: ");

    while (atual != NULL) {
        printf("%d ", atual->id);
        atual = atual->prox;
    }

    printf("\n");
}

void imprimirListaEncadeada(ListaEncadeada* lista) {
    Processo* atual = lista->frente;

    printf("Lista Round-Robin: ");

    while (atual != NULL) {
        printf("%d ", atual->id);
        atual = atual->prox;
    }

    printf("\n");
}

void enfileirar(Fila* fila, Processo* processo) {
    if (fila->frente == NULL) {
        fila->frente = fila->tras = processo;
    } else {
        fila -> tras -> prox = processo;
        fila -> tras = processo;
    }
}

Processo* desenfileirar(Fila* fila) {
    if (fila->frente == NULL) {
        return NULL;
    }
    Processo* frente = fila->frente;
    fila->frente = fila->frente->prox;
    if (fila->frente == NULL) {
        fila->tras = NULL;
    }
    return frente;
}

void inserirLista(Lista* lista, Processo* processo) {
    if (lista->inicio == NULL) {
        lista->inicio = lista->fim = processo;
    } else {
        lista->fim->prox = processo;
        lista->fim = processo;
    }
}

Processo* removerLista(Lista* lista) {
    if (lista->inicio == NULL) {
        return NULL;
    }

    Processo* primeiroNo = lista->inicio;
    Processo* processo = primeiroNo;

    lista->inicio = primeiroNo->prox;
    if (lista->inicio == NULL) {
        lista->fim = NULL;
    }

    return processo;
}

void inicializarListaEncadeada(ListaEncadeada* lista) {
    lista->frente = NULL;
    lista->tras = NULL;
}

void inserirlistaencad(ListaEncadeada* lista, Processo* processo) {
    if (lista->frente == NULL) {
        lista->frente = lista->tras = processo;
    } else {
        lista->tras->prox = processo;
        lista->tras = processo;
    }
}

Processo* removerListaEncadeada(ListaEncadeada* lista) {
    if (lista->frente == NULL) {
        return NULL;
    }

    Processo* primeiroNo = lista->frente;
    Processo* processo = primeiroNo;

    lista->frente = primeiroNo->prox;
    if (lista->frente == NULL) {
        lista->tras = NULL;
    }

    return processo;
}

/**
 * Função com a implementação do método first Come, First Serverd em fila
*/
void fcfs(Fila* fila) {
    int tempo = 0;
    int inicio, fim;
    Processo* atual;

    while (1) {
        atual = desenfileirar(fila);

        if (atual == NULL) {
            break;
        }

        inicio = tempo;
        tempo += atual->temppro;
        fim = tempo;

        printf("Processo: %d\tUnidades de Tempo do Processo: %d\tEspera: %d\tRetorno: %d\n", atual->id, atual->temppro, inicio, fim);

        free(atual);
    }

    printf("\n");
}

/**
 * Função com a implementação do método Shortest job first em lista
*/
void sjf(Lista* lista) {
    int tempo = 0;
    int inicio, fim;
    int shortest;
    Processo* atual;

    Lista lista_temp;
    lista_temp.inicio = lista_temp.fim = NULL;

    while (1) {
        while (lista->inicio != NULL && lista->inicio->temppro <= tempo) {
            Processo* processo = removerLista(lista);
            inserirLista(&lista_temp, processo);
        }

        if (lista_temp.inicio == NULL && lista->inicio == NULL) {
            break;
        }

        atual = removerLista(&lista_temp);
        shortest = atual->temppro;

        inicio = tempo;
        tempo += atual->temppro;
        fim = tempo;

        printf("Processo: %d\tUnidades de Tempo do Processo: %d\tEspera: %d\tRetorno: %d\n", atual->id, atual->temppro, inicio, fim);

        free(atual);
    }

    printf("\n");
}

/**
 * Função com a inmplementação do método Round-Robin em Lista
*/
void roundRobin(Lista* lista, int quantum) {
    int tempo = 0;
    int inicio, fim;
    Processo* atual;

    ListaEncadeada lista_temp;
    inicializarListaEncadeada(&lista_temp);

    while (1) {
        while (lista->inicio != NULL && lista->inicio->temppro <= tempo) {
            Processo* processo = removerLista(lista);
            inserirlistaencad(&lista_temp, processo);
        }

        if (lista_temp.frente == NULL && lista->inicio == NULL) {
            break;
        }

        atual = removerListaEncadeada(&lista_temp);

        inicio = tempo;
        tempo += (atual->temppro > quantum) ? quantum : atual->temppro;
        fim = tempo;

        printf("Processo: %d\tUnidades de Tempo do Processo: %d\tEspera: %d\tRetorno: %d\n", atual->id, atual->temppro, inicio, fim);

        atual->execucao += (atual->temppro > quantum) ? quantum : atual->temppro;
        atual->espera += tempo - inicio - (atual->temppro > quantum ? quantum : atual->temppro);

        if (atual->execucao < atual->temppro) {
            inserirlistaencad(&lista_temp, atual);
        } else {
            free(atual);
        }
    }

    printf("\n");
}
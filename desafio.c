#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INV 50

typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Item;

typedef struct {
    Item itens[MAX_INV];
    int tamanho;
} Mochila;

// Lista encadeada (VERSÃO FLEXÍVEL struct No {
    Item dado;
    struct No *prox;
} No;


void inicializarMochila(Mochila *m) {
    m->tamanho = 0;
}

void inserirItem(Mochila *m, Item novo) {
    if (m->tamanho >= MAX_INV) {
        printf("Mochila cheia!\n");
        return;
    }
    m->itens[m->tamanho] = novo;
    m->tamanho++;
}

void removerItem(Mochila *m, char nome[]) {
    int i, pos = -1;

    for (i = 0; i < m->tamanho; i++) {
        if (strcmp(m->itens[i].nome, nome) == 0) {
            pos = i;
            break;
        }
    }

    if (pos == -1) {
        printf("Item não encontrado!\n");
        return;
    }

    for (i = pos; i < m->tamanho - 1; i++)
        m->itens[i] = m->itens[i + 1];

    m->tamanho--;
}

void mostrarMochila(Mochila *m) {
    printf("\n--- INVENTÁRIO ---\n");
    for (int i = 0; i < m->tamanho; i++) {
        printf("%d. %s | %s | Prioridade: %d\n",
               i + 1,
               m->itens[i].nome,
               m->itens[i].tipo,
               m->itens[i].prioridade);
    }
    printf("-------------------\n");
}

void selectionSort(Mochila *m) {
    for (int i = 0; i < m->tamanho - 1; i++) {
        int min = i;
        for (int j = i + 1; j < m->tamanho; j++) {
            if (strcmp(m->itens[j].nome, m->itens[min].nome) < 0)
                min = j;
        }
        Item temp = m->itens[i];
        m->itens[i] = m->itens[min];
        m->itens[min] = temp;
    }
}

int buscaBinaria(Mochila *m, char nome[]) {
    int inicio = 0;
    int fim = m->tamanho - 1;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;

        int comp = strcmp(nome, m->itens[meio].nome);

        if (comp == 0) return meio;
        else if (comp > 0) inicio = meio + 1;
        else fim = meio - 1;
    }

    return -1;
}

No* inserirLista(No *lista, Item x) {
    No *novo = malloc(sizeof(No));
    novo->dado = x;
    novo->prox = lista;
    return novo;
}

void mostrarLista(No *lista) {
    printf("\n--- LISTA ENCADEADA ---\n");
    while (lista != NULL) {
        printf("%s | %s | Prioridade: %d\n",
               lista->dado.nome,
               lista->dado.tipo,
               lista->dado.prioridade);
        lista = lista->prox;
    }
    printf("------------------------\n");
}

// ---------------------------------------------
// TORRE DE FUGA – exemplo simples de integração
// ---------------------------------------------
void construirTorre(Mochila *m) {
    printf("\nConstruindo torre de fuga...\n");

    int ferramentas = 0;

    for (int i = 0; i < m->tamanho; i++) {
        if (strcmp(m->itens[i].tipo, "Ferramenta") == 0)
            ferramentas++;
    }

    if (ferramentas >= 3)
        printf("Torre construída com sucesso! Você escapou!\n");
    else
        printf("Você não possui ferramentas suficientes!\n");
}

int main() {
    Mochila mochila;
    inicializarMochila(&mochila);

    No *listaEncadeada = NULL;

    int opc;
    do {
        printf("\n===== MENU FREE FIRE C =====\n");
        printf("1 - Inserir item na mochila\n");
        printf("2 - Remover item da mochila\n");
        printf("3 - Mostrar mochila\n");
        printf("4 - Ordenar mochila (Selection Sort)\n");
        printf("5 - Buscar item (Binária)\n");
        printf("6 - Inserir na lista encadeada\n");
        printf("7 - Mostrar lista encadeada\n");
        printf("8 - Construir torre de fuga\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opc);
        getchar();

        if (opc == 1) {
            Item novo;
            printf("Nome: ");
            fgets(novo.nome, 30, stdin); novo.nome[strcspn(novo.nome, "\n")] = 0;

            printf("Tipo (Arma/Ferramenta/Alimento): ");
            fgets(novo.tipo, 20, stdin); novo.tipo[strcspn(novo.tipo, "\n")] = 0;

            printf("Prioridade (1 a 10): ");
            scanf("%d", &novo.prioridade);

            inserirItem(&mochila, novo);
        }

        else if (opc == 2) {
            char nome[30];
            printf("Nome do item a remover: ");
            fgets(nome, 30, stdin); nome[strcspn(nome, "\n")] = 0;
            removerItem(&mochila, nome);
        }

        else if (opc == 3) {
            mostrarMochila(&mochila);
        }

        else if (opc == 4) {
            selectionSort(&mochila);
            printf("Inventário ordenado!\n");
        }

        else if (opc == 5) {
            char nome[30];
            printf("Nome a buscar: ");
            fgets(nome, 30, stdin); nome[strcspn(nome, "\n")] = 0;
            int pos = buscaBinaria(&mochila, nome);
            if (pos == -1) printf("Item não encontrado!\n");
            else printf("Item encontrado na posição %d.\n", pos + 1);
        }

        else if (opc == 6) {
            Item novo;
            printf("Nome: ");
            fgets(novo.nome, 30, stdin); novo.nome[strcspn(novo.nome, "\n")] = 0;

            printf("Tipo: ");
            fgets(novo.tipo, 20, stdin); novo.tipo[strcspn(novo.tipo, "\n")] = 0;

            printf("Prioridade: ");
            scanf("%d", &novo.prioridade);

            listaEncadeada = inserirLista(listaEncadeada, novo);
        }

        else if (opc == 7) {
            mostrarLista(listaEncadeada);
        }

        else if (opc == 8) {
            construirTorre(&mochila);
        }

    } while (opc != 0);

    return 0;
}

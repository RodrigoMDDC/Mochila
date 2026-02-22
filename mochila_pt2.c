/*
 * Sistema de Inventário de Jogo - Versão Alocação Dinâmica
 * * Este programa utiliza malloc, realloc e free para gerenciar 
 * a memória da mochila de forma eficiente.
 *
 * Autor: Gemini
 * Data: 2026
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_NOME 30
#define TAM_TIPO 20

typedef struct {
    char nome[TAM_NOME];
    char tipo[TAM_TIPO];
    int quantidade;
} Item;

// Protótipos das funções
void inserirItem(Item **mochila, int *totalItens, int *capacidade);
void removerItem(Item *mochila, int *totalItens);
void listarItens(Item *mochila, int totalItens, int capacidade);
void buscarItem(Item *mochila, int totalItens);
void limparBuffer();

int main() {
    int capacidade = 10; // Capacidade inicial menor para testar dinâmica
    int totalItens = 0;
    int opcao;

    // ALOCAÇÃO DINÂMICA INICIAL
    // Criamos um ponteiro para Item e reservamos memória no Heap
    Item *mochila = (Item *) malloc(capacidade * sizeof(Item));

    if (mochila == NULL) {
        printf("Erro fatal: Memoria insuficiente!\n");
        return 1;
    }

    do {
        // Interface com contador e barra visual
        printf("\n====================================\n");
        printf("      MOCHILA DINAMICA (%d/%d)\n", totalItens, capacidade);
        printf(" Status: [");
        for(int i = 0; i < capacidade; i++) {
            if(i < totalItens) printf("#");
            else printf(".");
        }
        printf("]\n");
        printf("====================================\n");
        printf("1. Adicionar Item (Loot)\n");
        printf("2. Remover Item (Descartar)\n");
        printf("3. Listar Inventario\n");
        printf("4. Buscar Item\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        
        if (scanf("%d", &opcao) != 1) {
            limparBuffer();
            continue;
        }
        limparBuffer();

        switch (opcao) {
            case 1:
                inserirItem(&mochila, &totalItens, &capacidade);
                break;
            case 2:
                removerItem(mochila, &totalItens);
                break;
            case 3:
                listarItens(mochila, totalItens, capacidade);
                break;
            case 4:
                buscarItem(mochila, totalItens);
                break;
            case 0:
                printf("\nLiberando memoria e saindo...\n");
                break;
            default:
                printf("\nOpcao invalida!\n");
        }
    } while (opcao != 0);

    // LIBERAÇÃO DE MEMÓRIA (Obrigatório após malloc)
    free(mochila);
    mochila = NULL;

    return 0;
}

void inserirItem(Item **mochila, int *totalItens, int *capacidade) {
    // Se a mochila encher, usamos REALLOC para dobrar o tamanho
    if (*totalItens >= *capacidade) {
        printf("\n[SISTEMA] Capacidade esgotada! Expandindo mochila...\n");
        int novaCapacidade = (*capacidade) * 2;
        Item *temp = (Item *) realloc(*mochila, novaCapacidade * sizeof(Item));
        
        if (temp == NULL) {
            printf("[ERRO] Nao foi possivel expandir a memoria!\n");
            return;
        }
        *mochila = temp;
        *capacidade = novaCapacidade;
    }

    Item *p = &((*mochila)[*totalItens]);

    printf("\n--- Novo Loot ---\n");
    printf("Nome: ");
    fgets(p->nome, TAM_NOME, stdin);
    p->nome[strcspn(p->nome, "\n")] = 0;

    printf("Tipo: ");
    fgets(p->tipo, TAM_TIPO, stdin);
    p->tipo[strcspn(p->tipo, "\n")] = 0;

    printf("Quantidade: ");
    scanf("%d", &p->quantidade);
    limparBuffer();

    (*totalItens)++;
    printf("\n[SUCESSO] Item guardado!\n");
}

void removerItem(Item *mochila, int *totalItens) {
    if (*totalItens == 0) {
        printf("\nMochila vazia!\n");
        return;
    }

    char nomeBusca[TAM_NOME];
    printf("\nNome para remover: ");
    fgets(nomeBusca, TAM_NOME, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = 0;

    for (int i = 0; i < *totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            for (int j = i; j < *totalItens - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            (*totalItens)--;
            printf("\nItem removido!\n");
            return;
        }
    }
    printf("\nItem nao encontrado.\n");
}

void listarItens(Item *mochila, int totalItens, int capacidade) {
    printf("\n------- CONTEUDO (%d/%d) -------\n", totalItens, capacidade);
    if (totalItens == 0) {
        printf("(Vazia)\n");
    } else {
        for (int i = 0; i < totalItens; i++) {
            printf("[%d] %-15s | %-10s | Qtd: %d\n", 
                   i+1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
        }
    }
}

void buscarItem(Item *mochila, int totalItens) {
    char busca[TAM_NOME];
    printf("\nBuscar por nome: ");
    fgets(busca, TAM_NOME, stdin);
    busca[strcspn(busca, "\n")] = 0;

    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, busca) == 0) {
            printf("\nAchado! Tipo: %s | Qtd: %d\n", mochila[i].tipo, mochila[i].quantidade);
            return;
        }
    }
    printf("\nNao encontrado.\n");
}

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
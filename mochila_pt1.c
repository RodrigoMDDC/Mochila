/*
 * Sistema de Inventário de Jogo - Desafio de Estrutura de Dados
 * * Este programa simula uma mochila de loot inicial onde o jogador pode
 * gerenciar seus recursos (armas, munição, cura, etc.) usando Structs
 * e Vetores em C.
 *
 * Autor: Gemini
 * Data: 2026
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição de constantes
#define MAX_ITENS 10
#define TAM_NOME 30
#define TAM_TIPO 20

/* * CRIAÇÃO DA STRUCT
 * Define a estrutura 'Item' que agrupa os dados de cada objeto.
 * Requisito: Campos char nome[30], char tipo[20] e int quantidade.
 */
typedef struct {
    char nome[TAM_NOME];
    char tipo[TAM_TIPO];
    int quantidade;
} Item;

// Protótipos das funções
void inserirItem(Item mochila[], int *totalItens);
void removerItem(Item mochila[], int *totalItens);
void listarItens(Item mochila[], int totalItens);
void limparBuffer(); // Função auxiliar para limpeza de entrada

int main() {
    // VETOR DE STRUCTS: Cria a mochila com capacidade para 10 itens
    Item mochila[MAX_ITENS];
    int totalItens = 0; // Contador atual de itens na mochila
    int opcao;

    do {
        // Interface do Sistema (Usabilidade)
// Interface do Sistema com contador de capacidade
        printf("\n====================================\n");
        printf("      MOCHILA TATICA (%d/%d)\n", totalItens, MAX_ITENS);
        
        // Opcional: Uma barra visual de progresso
        printf(" Status: [");
        for(int i = 0; i < MAX_ITENS; i++) {
            if(i < totalItens) printf("#"); // Slot ocupado
            else printf(".");              // Slot vazio
        }
        printf("]\n");
        
        printf("====================================\n");
        printf("1. Adicionar Item (Loot)\n");
        printf("2. Remover Item (Descartar)\n");
        printf("3. Listar Inventario\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limparBuffer(); // Consome o \n deixado pelo scanf

        switch (opcao) {
            case 1:
                inserirItem(mochila, &totalItens);
                break;
            case 2:
                removerItem(mochila, &totalItens);
                break;
            case 3:
                listarItens(mochila, totalItens);
                break;
            case 0:
                printf("\nFechando mochila... Boa sorte na missao!\n");
                break;
            default:
                printf("\nComando invalido!\n");
        }
    } while (opcao != 0);

    return 0;
}

/*
 * Função: inserirItem
 * Objetivo: Cadastra um novo item na primeira posição vazia do vetor.
 * Verifica se a mochila já está cheia (MAX_ITENS).
 */
void inserirItem(Item mochila[], int *totalItens) {
    if (*totalItens >= MAX_ITENS) {
        printf("\n[ALERTA] Mochila cheia! Descarte itens antes de coletar novos.\n");
        return;
    }

    printf("\n--- Novo Loot ---\n");
    
    // Leitura do Nome
    printf("Nome do item: ");
    fgets(mochila[*totalItens].nome, TAM_NOME, stdin);
    mochila[*totalItens].nome[strcspn(mochila[*totalItens].nome, "\n")] = 0; // Remove o \n do final

    // Leitura do Tipo
    printf("Tipo (ex: arma, municao, cura): ");
    fgets(mochila[*totalItens].tipo, TAM_TIPO, stdin);
    mochila[*totalItens].tipo[strcspn(mochila[*totalItens].tipo, "\n")] = 0;

    // Leitura da Quantidade
    printf("Quantidade: ");
    scanf("%d", &mochila[*totalItens].quantidade);
    limparBuffer();

    (*totalItens)++; // Incrementa o contador de itens
    printf("\n[SUCESSO] Item guardado na mochila!\n");
    
    // Requisito: Listar após operação
    listarItens(mochila, *totalItens);
}

/*
 * Função: removerItem
 * Objetivo: Remove um item pelo nome e reorganiza o vetor 
 * para não deixar "buracos" (shift à esquerda).
 */
void removerItem(Item mochila[], int *totalItens) {
    char nomeBusca[TAM_NOME];
    int i, j, encontrado = 0;

    if (*totalItens == 0) {
        printf("\n[ALERTA] A mochila esta vazia.\n");
        return;
    }

    printf("\nNome do item para remover: ");
    fgets(nomeBusca, TAM_NOME, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = 0;

    // Busca Sequencial para encontrar o índice
    for (i = 0; i < *totalItens; i++) {
        // strcasecmp poderia ser usado para ignorar maiúsculas/minúsculas (não padrão ANSI C puro)
        // strcmp retorna 0 se as strings forem iguais
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            encontrado = 1;
            
            // Reorganização do vetor (Shift Left)
            // Move todos os itens seguintes uma posição para trás
            for (j = i; j < *totalItens - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            
            (*totalItens)--; // Decrementa o total
            printf("\n[SUCESSO] %s foi removido da mochila.\n", nomeBusca);
            break; // Sai do loop pois já removeu
        }
    }

    if (!encontrado) {
        printf("\n[ERRO] Item '%s' nao encontrado.\n", nomeBusca);
    } else {
        // Requisito: Listar após operação
        listarItens(mochila, *totalItens);
    }
}

/*
 * Função: listarItens
 * Objetivo: Percorre o vetor e exibe todos os itens cadastrados.
 */
void listarItens(Item mochila[], int totalItens) {
    printf("\n------- CONTEUDO DA MOCHILA (%d/%d) -------\n", totalItens, MAX_ITENS);
    
    if (totalItens == 0) {
        printf("(Mochila Vazia)\n");
    } else {
        printf("%-20s | %-15s | %s\n", "NOME", "TIPO", "QTD");
        printf("--------------------------------------------------\n");
        for (int i = 0; i < totalItens; i++) {
            printf("%-20s | %-15s | %d\n", 
                   mochila[i].nome, 
                   mochila[i].tipo, 
                   mochila[i].quantidade);
        }
    }
    printf("--------------------------------------------------\n");
}

/*
 * Função auxiliar para limpar o buffer do teclado.
 * Essencial quando misturamos scanf com fgets.
 */
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
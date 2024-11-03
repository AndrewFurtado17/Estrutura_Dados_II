#aluno andrew

#include <stdio.h>
#include <stdlib.h>

// Estrutura do nó da Treap
struct No {
    int chave;
    int prioridade;
    struct No* esquerda;
    struct No* direita;
};

// Função para criar um novo nó
struct No* novoNo(int chave) {
    struct No* temp = (struct No*)malloc(sizeof(struct No));
    temp->chave = chave;
    temp->prioridade = rand() % 100;  // Atribui uma prioridade aleatória
    temp->esquerda = temp->direita = NULL;
    return temp;
}

// Função para rotacionar para a direita
struct No* rotacionarDireita(struct No* raiz) {
    struct No* novaRaiz = raiz->esquerda;
    raiz->esquerda = novaRaiz->direita;
    novaRaiz->direita = raiz;
    return novaRaiz;
}

// Função para rotacionar para a esquerda
struct No* rotacionarEsquerda(struct No* raiz) {
    struct No* novaRaiz = raiz->direita;
    raiz->direita = novaRaiz->esquerda;
    novaRaiz->esquerda = raiz;
    return novaRaiz;
}

// Função para inserir um novo nó na treap
struct No* inserirNaTreap(struct No* raiz, int chave) {
    if (!raiz) {
        return novoNo(chave);
    }

    if (chave < raiz->chave) {
        raiz->esquerda = inserirNaTreap(raiz->esquerda, chave);
        if (raiz->esquerda->prioridade > raiz->prioridade) {
            raiz = rotacionarDireita(raiz);
        }
    } else {
        raiz->direita = inserirNaTreap(raiz->direita, chave);
        if (raiz->direita->prioridade > raiz->prioridade) {
            raiz = rotacionarEsquerda(raiz);
        }
    }

    return raiz;
}

// Função para encontrar o nó com o menor valor
struct No* encontrarMinimo(struct No* raiz) {
    while (raiz->esquerda != NULL) {
        raiz = raiz->esquerda;
    }
    return raiz;
}

// Função para excluir um nó da treap
struct No* excluirDaTreap(struct No* raiz, int chave) {
    if (!raiz) {
        return raiz;
    }

    if (chave < raiz->chave) {
        raiz->esquerda = excluirDaTreap(raiz->esquerda, chave);
    } else if (chave > raiz->chave) {
        raiz->direita = excluirDaTreap(raiz->direita, chave);
    } else {
        if (!raiz->esquerda) {
            struct No* temp = raiz->direita;
            free(raiz);
            return temp;
        } else if (!raiz->direita) {
            struct No* temp = raiz->esquerda;
            free(raiz);
            return temp;
        }

        struct No* minimo = encontrarMinimo(raiz->direita);
        raiz->chave = minimo->chave;
        raiz->direita = excluirDaTreap(raiz->direita, minimo->chave);
    }

    return raiz;
}

// Função para imprimir a treap em ordem
void imprimirTreap(struct No* raiz, int nivel) {
    if (raiz) {
        imprimirTreap(raiz->direita, nivel + 1);
        for (int i = 0; i < nivel; i++) {
            printf("   ");
        }
        printf("(%d, %d)\n", raiz->chave, raiz->prioridade);
        imprimirTreap(raiz->esquerda, nivel + 1);
    }
}

// Função principal
int main() {
    struct No* raiz = NULL;

    int elementos[] = {12, 11, 13, 5, 6, 7};
    int tamanho = sizeof(elementos) / sizeof(elementos[0]);

    printf("Elementos a serem inseridos:\n");
    for (int i = 0; i < tamanho; i++) {
        printf("%d ", elementos[i]);
    }
    printf("\n");

    // Inserir elementos na treap
    for (int i = 0; i < tamanho; i++) {
        printf("\nInserindo elemento %d na treap:\n", elementos[i]);
        raiz = inserirNaTreap(raiz, elementos[i]);
        imprimirTreap(raiz, 0);
    }

    // Excluir elementos da treap um por um e mostrar a treap após cada remoção
    for (int i = 0; i < tamanho; i++) {
        printf("\nExcluindo elemento %d da treap:\n", elementos[i]);
        raiz = excluirDaTreap(raiz, elementos[i]);
        imprimirTreap(raiz, 0);
    }

    return 0;
}

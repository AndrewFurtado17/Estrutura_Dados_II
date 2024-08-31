#include <stdio.h>
#include <stdlib.h>

struct NodoArvore
{
    int valor;
    struct NodoArvore *esquerda;
    struct NodoArvore *direita;
};

struct NodoArvore *criarNodo(int valor)
{
    struct NodoArvore *novoNodo = (struct NodoArvore *)malloc(sizeof(struct NodoArvore));
    if (novoNodo == NULL)
    {
        printf("Erro: Falha ao alocar memória para o novo nodo.\n");
        exit(-1);
    }
    novoNodo->valor = valor;
    novoNodo->esquerda = NULL;
    novoNodo->direita = NULL;
    return novoNodo;
}

struct NodoArvore *inserirNodo(struct NodoArvore *raiz, int valor)
{
    if (raiz == NULL)
    {
        raiz = criarNodo(valor);
    }
    else
    {
        if (valor <= raiz->valor)
        {
            raiz->esquerda = inserirNodo(raiz->esquerda, valor);
        }
        else
        {
            raiz->direita = inserirNodo(raiz->direita, valor);
        }
    }
    return raiz;
}

struct NodoArvore *encontrarMinimoNodo(struct NodoArvore *raiz)
{
    struct NodoArvore *atual = raiz;
    while (atual->esquerda != NULL)
    {
        atual = atual->esquerda;
    }
    return atual;
}

struct NodoArvore *excluirNodo(struct NodoArvore *raiz, int valor)
{
    if (raiz == NULL)
    {
        return raiz;
    }

    if (valor < raiz->valor)
    {
        raiz->esquerda = excluirNodo(raiz->esquerda, valor);
    }
    else if (valor > raiz->valor)
    {
        raiz->direita = excluirNodo(raiz->direita, valor);
    }
    else
    {
        // Caso 1: Nodo folha ou nodo com apenas um filho
        if (raiz->esquerda == NULL)
        {
            struct NodoArvore *temp = raiz->direita;
            free(raiz);
            return temp;
        }
        else if (raiz->direita == NULL)
        {
            struct NodoArvore *temp = raiz->esquerda;
            free(raiz);
            return temp;
        }

        // Caso 2: Nodo com dois filhos, encontra o sucessor in-order (menor valor na subárvore direita)
        struct NodoArvore *temp = encontrarMinimoNodo(raiz->direita);
        raiz->valor = temp->valor;
        raiz->direita = excluirNodo(raiz->direita, temp->valor);
    }
    return raiz;
}

void percorrerEmOrdem(struct NodoArvore *raiz)
{
    if (raiz != NULL)
    {
        percorrerEmOrdem(raiz->esquerda);
        printf("%d ", raiz->valor);
        percorrerEmOrdem(raiz->direita);
    }
}

void percorrerPreOrdem(struct NodoArvore *raiz)
{
    if (raiz != NULL)
    {
        printf("%d ", raiz->valor);
        percorrerPreOrdem(raiz->esquerda);
        percorrerPreOrdem(raiz->direita);
    }
}

void percorrerPosOrdem(struct NodoArvore *raiz)
{
    if (raiz != NULL)
    {
        percorrerPosOrdem(raiz->esquerda);
        percorrerPosOrdem(raiz->direita);
        printf("%d ", raiz->valor);
    }
}

// Função auxiliar para imprimir um caractere precedido por uma quantidade específica de espaços
void imprimirNodo(int valor, int espacos)
{
    int i;
    for (i = 0; i < espacos; i++)
        printf("   ");
    printf("%i\n", valor);
}

// Função para exibir a árvore no formato esquerda-raiz-direita segundo Sedgewick
void exibirArvore(struct NodoArvore *raiz, int espacos)
{
    if (raiz == NULL)
    {
        return;
    }
    exibirArvore(raiz->direita, espacos + 1);
    imprimirNodo(raiz->valor, espacos); // Convertendo para caractere para imprimir
    exibirArvore(raiz->esquerda, espacos + 1);
}

int main()
{
    struct NodoArvore *raiz = NULL;

    // Inserindo elementos na árvore
    raiz = inserirNodo(raiz, 1);
    raiz = inserirNodo(raiz, 2);
    raiz = inserirNodo(raiz, 3);
    raiz = inserirNodo(raiz, 4);
    raiz = inserirNodo(raiz, 5);
    raiz = inserirNodo(raiz, 6);
    raiz = inserirNodo(raiz, 7);
    raiz = inserirNodo(raiz, 8);
    raiz = inserirNodo(raiz, 9);
    raiz = inserirNodo(raiz, 10);

    exibirArvore(raiz, 3);
    raiz = excluirNodo(raiz, 5);
    exibirArvore(raiz, 3);

    /* Imprimindo a árvore em ordem
    printf("\nÁrvore em pré-ordem: ");
    percorrerPreOrdem(raiz);
    printf("\n");

    printf("Árvore em ordem: ");
    percorrerEmOrdem(raiz);
    printf("\n");

    printf("Árvore em pós-ordem: ");
    percorrerPosOrdem(raiz);
    printf("\n");*/

    return 0;
}

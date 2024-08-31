#include <stdio.h>
#include <stdlib.h>

// Definindo a estrutura do nó da árvore
struct NodoArvore
{
    int valor;                    // Valor armazenado no nó
    struct NodoArvore *esquerda;  // Ponteiro para o filho à esquerda
    struct NodoArvore *direita;   // Ponteiro para o filho à direita
};

// Função para criar um novo nó
struct NodoArvore *criarNodo(int valor)
{
    struct NodoArvore *novoNodo = (struct NodoArvore *)malloc(sizeof(struct NodoArvore));
    if (novoNodo == NULL)
    {
        printf("Erro: Falha ao alocar memória para o novo nodo.\n");
        exit(-1);  // Encerra o programa se a alocação falhar
    }
    novoNodo->valor = valor;      // Define o valor do novo nó
    novoNodo->esquerda = NULL;   // Inicializa o ponteiro esquerdo como NULL
    novoNodo->direita = NULL;    // Inicializa o ponteiro direito como NULL
    return novoNodo;             // Retorna o novo nó criado
}

// Função para inserir um valor na árvore
struct NodoArvore *inserirNodo(struct NodoArvore *raiz, int valor)
{
    // Se a árvore estiver vazia, cria um novo nó e o define como raiz
    if (raiz == NULL)
    {
        raiz = criarNodo(valor);
    }
    else
    {
        // Se o valor for menor ou igual ao valor do nó atual, insere na subárvore esquerda
        if (valor <= raiz->valor)
        {
            raiz->esquerda = inserirNodo(raiz->esquerda, valor);
        }
        // Se o valor for maior, insere na subárvore direita
        else
        {
            raiz->direita = inserirNodo(raiz->direita, valor);
        }
    }
    return raiz;  // Retorna a raiz da árvore atualizada
}

// Função para encontrar o nó com o menor valor na subárvore
struct NodoArvore *encontrarMinimoNodo(struct NodoArvore *raiz)
{
    struct NodoArvore *atual = raiz;
    // Navega para o nó mais à esquerda (menor valor na subárvore)
    while (atual->esquerda != NULL)
    {
        atual = atual->esquerda;
    }
    return atual;  // Retorna o nó com o menor valor
}

// Função para excluir um valor da árvore
struct NodoArvore *excluirNodo(struct NodoArvore *raiz, int valor)
{
    // Se a árvore estiver vazia, não há nada para excluir
    if (raiz == NULL)
    {
        return raiz;
    }

    // Navega pela árvore para encontrar o nó a ser excluído
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
        // Caso 1: O nó tem no máximo um filho
        if (raiz->esquerda == NULL)
        {
            struct NodoArvore *temp = raiz->direita;
            free(raiz);  // Libera a memória do nó
            return temp; // Retorna o filho à direita (ou NULL se não houver)
        }
        else if (raiz->direita == NULL)
        {
            struct NodoArvore *temp = raiz->esquerda;
            free(raiz);  // Libera a memória do nó
            return temp; // Retorna o filho à esquerda (ou NULL se não houver)
        }

        // Caso 2: O nó tem dois filhos
        struct NodoArvore *temp = encontrarMinimoNodo(raiz->direita);
        raiz->valor = temp->valor;  // Substitui o valor do nó a ser excluído pelo valor do sucessor
        raiz->direita = excluirNodo(raiz->direita, temp->valor);  // Exclui o sucessor
    }
    return raiz;  // Retorna a raiz da árvore atualizada
}

// Função para percorrer a árvore em ordem (in-order traversal)
void percorrerEmOrdem(struct NodoArvore *raiz)
{
    if (raiz != NULL)
    {
        percorrerEmOrdem(raiz->esquerda);  // Visita a subárvore esquerda
        printf("%d ", raiz->valor);        // Imprime o valor do nó atual
        percorrerEmOrdem(raiz->direita);   // Visita a subárvore direita
    }
}

// Função para percorrer a árvore em pré-ordem (pre-order traversal)
void percorrerPreOrdem(struct NodoArvore *raiz)
{
    if (raiz != NULL)
    {
        printf("%d ", raiz->valor);        // Imprime o valor do nó atual
        percorrerPreOrdem(raiz->esquerda); // Visita a subárvore esquerda
        percorrerPreOrdem(raiz->direita);  // Visita a subárvore direita
    }
}

// Função para percorrer a árvore em pós-ordem (post-order traversal)
void percorrerPosOrdem(struct NodoArvore *raiz)
{
    if (raiz != NULL)
    {
        percorrerPosOrdem(raiz->esquerda); // Visita a subárvore esquerda
        percorrerPosOrdem(raiz->direita);  // Visita a subárvore direita
        printf("%d ", raiz->valor);        // Imprime o valor do nó atual
    }
}

// Função auxiliar para imprimir um valor precedido por uma quantidade específica de espaços
void imprimirNodo(int valor, int espacos)
{
    int i;
    for (i = 0; i < espacos; i++)
        printf("   ");  // Imprime espaços para a formatação
    printf("%i\n", valor);  // Imprime o valor do nó
}

// Função para exibir a árvore em formato visual (com formatação de espaçamento)
void exibirArvore(struct NodoArvore *raiz, int espacos)
{
    if (raiz == NULL)
    {
        return;  // Se o nó for NULL, não faz nada
    }
    exibirArvore(raiz->direita, espacos + 1);  // Exibe a subárvore direita com maior espaçamento
    imprimirNodo(raiz->valor, espacos);        // Imprime o valor do nó atual com o espaçamento adequado
    exibirArvore(raiz->esquerda, espacos + 1); // Exibe a subárvore esquerda com maior espaçamento
}

int main()
{
    struct NodoArvore *raiz = NULL;  // Inicializa a raiz da árvore como NULL

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

    // Exibe a árvore antes da exclusão
    exibirArvore(raiz, 3);
    raiz = excluirNodo(raiz, 5);  // Exclui o nó com valor 5
    // Exibe a árvore após a exclusão
    exibirArvore(raiz, 3);

    // Comentado para não exibir
    /*printf("\nÁrvore em pré-ordem: ");
    percorrerPreOrdem(raiz);
    printf("\n");

    printf("Árvore em ordem: ");
    percorrerEmOrdem(raiz);
    printf("\n");

    printf("Árvore em pós-ordem: ");
    percorrerPosOrdem(raiz);
    printf("\n");*/

    return 0;  // Encerra o programa
}

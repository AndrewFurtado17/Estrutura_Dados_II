// Aluno: Andrew Furtado
// Turma: CC6N - Estrutura de Dados 2

#include <stdio.h>
#include <stdlib.h>

// Estrutura do nó da árvore AVL
struct NodoAVL {
    int valor;
    struct NodoAVL *esquerda;
    struct NodoAVL *direita;
    int altura;
};

// Função auxiliar para encontrar o valor mínimo na árvore
struct NodoAVL *encontrarMinimo(struct NodoAVL *raiz) {
    struct NodoAVL *atual = raiz;
    while (atual->esquerda != NULL) {
        atual = atual->esquerda;
    }
    return atual;
}

// Função auxiliar para encontrar o valor máximo na árvore
struct NodoAVL *encontrarMaximo(struct NodoAVL *raiz) {
    struct NodoAVL *atual = raiz;
    while (atual->direita != NULL) {
        atual = atual->direita;
    }
    return atual;
}

// Função auxiliar para exibir a árvore em PRE-ORDER
void exibirPreOrdem(struct NodoAVL *raiz) {
    if (raiz != NULL) {
        printf("%i ", raiz->valor);
        exibirPreOrdem(raiz->esquerda);
        exibirPreOrdem(raiz->direita);
    }
}

// Função auxiliar para exibir a árvore em IN-ORDER
void exibirEmOrdem(struct NodoAVL *raiz) {
    if (raiz != NULL) {
        exibirEmOrdem(raiz->esquerda);
        printf("%i ", raiz->valor);
        exibirEmOrdem(raiz->direita);
    }
}

// Função auxiliar para exibir a árvore em POS-ORDER
void exibirPosOrdem(struct NodoAVL *raiz) {
    if (raiz != NULL) {
        exibirPosOrdem(raiz->esquerda);
        exibirPosOrdem(raiz->direita);
        printf("%i ", raiz->valor);
    }
}

// Função para validar a entrada do usuário
int validarEntrada() {
    int entradaValida, chave;
    while (1) {
        entradaValida = scanf("%i", &chave);
        if (entradaValida == 1) {
            if (chave < 0) {
                printf("\nValor inválido.\nTente novamente: ");
                while (getchar() != '\n'); // Limpa o buffer de entrada
            } else {
                break; // Entrada válida
            }
        } else {
            printf("\nEntrada inválida.\nTente novamente: ");
            while (getchar() != '\n'); // Limpa o buffer de entrada
        }
    }
    return chave; // Retorna o valor válido
}

// Função para calcular o fator de balanceamento
int obterFatorBalanceamento(struct NodoAVL *nodo) {
    if (nodo == NULL) {
        return 0;
    }
    int altEsq = nodo->esquerda ? nodo->esquerda->altura : -1;
    int altDir = nodo->direita ? nodo->direita->altura : -1;
    return altEsq - altDir;
}

// Função para atualizar o nível (altura) do nó
void atualizarAltura(struct NodoAVL *nodo) {
    int altEsq = nodo->esquerda ? nodo->esquerda->altura : -1;
    int altDir = nodo->direita ? nodo->direita->altura : -1;
    nodo->altura = (altEsq > altDir ? altEsq : altDir) + 1;
}

// Função para criar um novo nodo
struct NodoAVL *criarNodo(int chave) {
    struct NodoAVL *novoNodo = (struct NodoAVL *)malloc(sizeof(struct NodoAVL));
    if (novoNodo == NULL) {
        printf("Erro ao alocar memória para o Nodo\n");
        exit(-1);
    }
    novoNodo->valor = chave;
    novoNodo->esquerda = NULL;
    novoNodo->direita = NULL;
    novoNodo->altura = 0;
    return novoNodo;
}

// Função para realizar a rotação à direita
struct NodoAVL *rotacionarDireita(struct NodoAVL *nodo) {
    struct NodoAVL *novaRaiz = nodo->esquerda;
    struct NodoAVL *subArvDir = novaRaiz->direita;

    novaRaiz->direita = nodo;
    nodo->esquerda = subArvDir;

    atualizarAltura(nodo);
    atualizarAltura(novaRaiz);

    return novaRaiz;
}

// Função para realizar a rotação à esquerda
struct NodoAVL *rotacionarEsquerda(struct NodoAVL *nodo) {
    struct NodoAVL *novaRaiz = nodo->direita;
    struct NodoAVL *subArvEsq = novaRaiz->esquerda;

    novaRaiz->esquerda = nodo;
    nodo->direita = subArvEsq;

    atualizarAltura(nodo);
    atualizarAltura(novaRaiz);

    return novaRaiz;
}

// Função para balancear a árvore AVL
struct NodoAVL *balancear(struct NodoAVL *raiz, int chave) {
    atualizarAltura(raiz);

    int balanceamento = obterFatorBalanceamento(raiz);

    if (balanceamento > 1 && chave < raiz->esquerda->valor) {
        return rotacionarDireita(raiz);
    }

    if (balanceamento < -1 && chave > raiz->direita->valor) {
        return rotacionarEsquerda(raiz);
    }

    if (balanceamento > 1 && chave > raiz->esquerda->valor) {
        raiz->esquerda = rotacionarEsquerda(raiz->esquerda);
        return rotacionarDireita(raiz);
    }

    if (balanceamento < -1 && chave < raiz->direita->valor) {
        raiz->direita = rotacionarDireita(raiz->direita);
        return rotacionarEsquerda(raiz);
    }

    return raiz;
}

// Função para inserir um nodo na árvore AVL
struct NodoAVL *inserir(struct NodoAVL *raiz, int chave) {
    if (raiz == NULL) {
        return criarNodo(chave);
    }

    if (chave < raiz->valor) {
        raiz->esquerda = inserir(raiz->esquerda, chave);
    } else if (chave > raiz->valor) {
        raiz->direita = inserir(raiz->direita, chave);
    } else {
        return raiz;
    }

    return balancear(raiz, chave);
}

// Função para procurar um nodo na árvore AVL
void procurar(struct NodoAVL *raiz, int chave) {
    if (raiz == NULL) {
        printf("Valor %d não encontrado.\n", chave);
        return;
    }

    if (chave == raiz->valor) {
        printf("Valor %d encontrado!\n", chave);
    } else if (chave < raiz->valor) {
        procurar(raiz->esquerda, chave);
    } else {
        procurar(raiz->direita, chave);
    }
}

// Função para remover um Nodo da árvore AVL
struct NodoAVL *remover(struct NodoAVL *raiz, int chave) {
    if (raiz == NULL) {
        printf("Valor %d não encontrado.\n", chave);
        return raiz;
    }

    if (chave < raiz->valor) {
        raiz->esquerda = remover(raiz->esquerda, chave);
    } else if (chave > raiz->valor) {
        raiz->direita = remover(raiz->direita, chave);
    } else {
        if (raiz->esquerda == NULL) {
            struct NodoAVL *temp = raiz->direita;
            free(raiz);
            printf("Valor %d removido.\n", chave);
            return temp;
        } else if (raiz->direita == NULL) {
            struct NodoAVL *temp = raiz->esquerda;
            free(raiz);
            printf("Valor %d removido.\n", chave);
            return temp;
        }

        struct NodoAVL *temp = encontrarMinimo(raiz->direita);
        raiz->valor = temp->valor;
        raiz->direita = remover(raiz->direita, temp->valor);
    }

    return balancear(raiz, chave);
}

// Função para calcular a altura da árvore
int altura(struct NodoAVL *raiz) {
    if (raiz == NULL) {
        return -1;
    }
    
    int altEsq = altura(raiz->esquerda) + 1;
    int altDir = altura(raiz->direita) + 1;

    return (altEsq > altDir ? altEsq : altDir);
}

#include <stdio.h>
#include <stdlib.h>

int main() {
    struct NodoAVL *raiz = NULL;

    int opcao, valor;

    do {
        printf("\n-=-=-=-=-=- MENU -=-=-=-=-=-=-");
        printf("\n\n[1] Inserir um elemento");
        printf("\n[2] Procurar um elemento");
        printf("\n[3] Excluir um elemento");
        printf("\n[4] Calcular a altura");
        printf("\n[5] Exibir a árvore");
        printf("\n[0] Sair do programa");
        printf("\n\nDigite a sua opção: ");

        opcao = validarEntrada();

        switch (opcao) {
        case 1:
            printf("\nINSERIR NÓ");
            int n = 0;
            printf("\nDigite a quantidade de nós a serem adicionados: ");
            n = validarEntrada();

            while (n > 0) {
                int num = 0;
                printf("\nDigite um valor: ");
                num = validarEntrada();
                raiz = inserir(raiz, num);
                n--;
            }
            break;

        case 2:
            printf("\nPROCURAR NÓ");
            printf("\nDigite um valor para procurar: ");
            valor = validarEntrada();
            procurar(raiz, valor);
            break;

        case 3:
            printf("\nEXCLUIR NÓ");
            printf("\nDigite um valor para ser excluido: ");
            valor = validarEntrada();
            raiz = remover(raiz, valor);
            break;

        case 4:
            printf("\nALTURA DA ÁRVORE");
            int alturaAtual = altura(raiz);
            printf("\nA altura da árvore é: %i\n", alturaAtual);
            break; 

        case 5:
            printf("\nEXIBIR ÁRVORE \n");
            printf("\nPRE-ORDER: ");
            exibirPreOrdem(raiz);

            printf("\nIN-ORDER: ");
            exibirEmOrdem(raiz);

            printf("\nPOS-ORDER: ");
            exibirPosOrdem(raiz);
            printf("\n");
            break;

        case 0:
            printf("\nSAIR DO PROGRAMA");
            free(raiz);
            break;

        default:
            printf("\nOpção Inválida.");
            break;
        }
    } while (opcao != 0);

    return 0;
}

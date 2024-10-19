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
struct NodoAVL *obterMinimo(struct NodoAVL *raiz) {
    struct NodoAVL *atual = raiz;
    while (atual->esquerda != NULL) {
        atual = atual->esquerda;
    }
    return atual;
}

// Função auxiliar para encontrar o valor máximo na árvore
struct NodoAVL *obterMaximo(struct NodoAVL *raiz) {
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
    int entradaValida, valor;
    while (1) {
        entradaValida = scanf("%i", &valor);
        if (entradaValida == 1) {
            if (valor < 0) {
                printf("\nValor inválido.\nTente novamente: ");
                while (getchar() != '\n');
            } else {
                break;
            }
        } else {
            printf("\nEntrada inválida.\nTente novamente: ");
            while (getchar() != '\n');
        }
    }
    return valor;
}

// Função para calcular o fator de balanceamento
int obterFatorBalanceamento(struct NodoAVL *nodo) {
    if (nodo == NULL) {
        return 0;
    }
    int alturaEsquerda = nodo->esquerda ? nodo->esquerda->altura : -1;
    int alturaDireita = nodo->direita ? nodo->direita->altura : -1;
    return alturaEsquerda - alturaDireita;
}

// Função para atualizar o nível (altura) do nó
void atualizarAltura(struct NodoAVL *nodo) {
    int alturaEsquerda = nodo->esquerda ? nodo->esquerda->altura : -1;
    int alturaDireita = nodo->direita ? nodo->direita->altura : -1;
    nodo->altura = (alturaEsquerda > alturaDireita ? alturaEsquerda : alturaDireita) + 1;
}

// Função para criar um novo nodo
struct NodoAVL *criarNodo(int valor) {
    struct NodoAVL *novoNodo = (struct NodoAVL *)malloc(sizeof(struct NodoAVL));
    if (novoNodo == NULL) {
        printf("Erro ao alocar memória para o Nodo\n");
        exit(-1);
    }
    novoNodo->valor = valor;
    novoNodo->esquerda = NULL;
    novoNodo->direita = NULL;
    novoNodo->altura = 0;
    return novoNodo;
}

// Função para realizar a rotação à direita
struct NodoAVL *rotacionarDireita(struct NodoAVL *nodo) {
    struct NodoAVL *novaRaiz = nodo->esquerda;
    struct NodoAVL *subArvoreDireita = novaRaiz->direita;

    novaRaiz->direita = nodo;
    nodo->esquerda = subArvoreDireita;

    atualizarAltura(nodo);
    atualizarAltura(novaRaiz);

    return novaRaiz;
}

// Função para realizar a rotação à esquerda
struct NodoAVL *rotacionarEsquerda(struct NodoAVL *nodo) {
    struct NodoAVL *novaRaiz = nodo->direita;
    struct NodoAVL *subArvoreEsquerda = novaRaiz->esquerda;

    novaRaiz->esquerda = nodo;
    nodo->direita = subArvoreEsquerda;

    atualizarAltura(nodo);
    atualizarAltura(novaRaiz);

    return novaRaiz;
}

// Função para balancear a árvore AVL
struct NodoAVL *balancear(struct NodoAVL *raiz, int valor) {
    atualizarAltura(raiz);

    int balanceamento = obterFatorBalanceamento(raiz);

    if (balanceamento > 1 && valor < raiz->esquerda->valor) {
        return rotacionarDireita(raiz);
    }

    if (balanceamento < -1 && valor > raiz->direita->valor) {
        return rotacionarEsquerda(raiz);
    }

    if (balanceamento > 1 && valor > raiz->esquerda->valor) {
        raiz->esquerda = rotacionarEsquerda(raiz->esquerda);
        return rotacionarDireita(raiz);
    }

    if (balanceamento < -1 && valor < raiz->direita->valor) {
        raiz->direita = rotacionarDireita(raiz->direita);
        return rotacionarEsquerda(raiz);
    }

    return raiz;
}

// Função para inserir um nodo na árvore AVL
struct NodoAVL *inserir(struct NodoAVL *raiz, int valor) {
    if (raiz == NULL) {
        return criarNodo(valor);
    }

    if (valor < raiz->valor) {
        raiz->esquerda = inserir(raiz->esquerda, valor);
    } else if (valor > raiz->valor) {
        raiz->direita = inserir(raiz->direita, valor);
    } else {
        return raiz;
    }

    return balancear(raiz, valor);
}

// Função para procurar um nodo na árvore AVL
void procurar(struct NodoAVL *raiz, int valor) {
    if (raiz == NULL) {
        printf("Valor %d não encontrado.\n", valor);
        return;
    }

    if (valor == raiz->valor) {
        printf("Valor %d encontrado!\n", valor);
    } else if (valor < raiz->valor) {
        procurar(raiz->esquerda, valor);
    } else {
        procurar(raiz->direita, valor);
    }
}

// Função para remover um Nodo da árvore AVL
struct NodoAVL *remover(struct NodoAVL *raiz, int valor) {
    if (raiz == NULL) {
        printf("Valor %d não encontrado.\n", valor);
        return raiz;
    }

    if (valor < raiz->valor) {
        raiz->esquerda = remover(raiz->esquerda, valor);
    } else if (valor > raiz->valor) {
        raiz->direita = remover(raiz->direita, valor);
    } else {
        if (raiz->esquerda == NULL) {
            struct NodoAVL *temp = raiz->direita;
            free(raiz);
            printf("Valor %d removido.\n", valor);
            return temp;
        } else if (raiz->direita == NULL) {
            struct NodoAVL *temp = raiz->esquerda;
            free(raiz);
            printf("Valor %d removido.\n", valor);
            return temp;
        }

        struct NodoAVL *temp = obterMinimo(raiz->direita);
        raiz->valor = temp->valor;
        raiz->direita = remover(raiz->direita, temp->valor);
    }

    return balancear(raiz, valor);
}

// Função para calcular a altura da árvore
int altura(struct NodoAVL *raiz) {
    if (raiz == NULL) {
        return -1;
    }

    int alturaEsquerda = altura(raiz->esquerda) + 1;
    int alturaDireita = altura(raiz->direita) + 1;

    return (alturaEsquerda > alturaDireita ? alturaEsquerda : alturaDireita);
}

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
            int quantidade = 0;
            printf("\nDigite a quantidade de nós a serem adicionados: ");
            quantidade = validarEntrada();

            while (quantidade > 0) {
                int numero = 0;
                printf("\nDigite um valor: ");
                numero = validarEntrada();
                raiz = inserir(raiz, numero);
                quantidade--;
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

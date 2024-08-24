#include <stdio.h>
#include <stdlib.h>

struct Node {

  int data;
  struct Node *left;
  struct Node *rigth;  
};

struct Node *newNode(int data){
  struct Node *novoNode = (struct Node *)malloc(sizeof(struct Node));
if(novoNode == NULL)){
  printf("Erro ao alocar memória para o novo nó.\n");
}
  
};

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "projeto.h"
#include <stdbool.h>

typedef struct celula {
  struct celula *anterior;
  char nome[256];
  char rg[256];
  int senha;
  struct celula *proximo;
} celula;

typedef struct {
  celula *primeiro;
  celula *ultimo;
  int qtde;
} fila;

int criaSenha(){ 
    return rand() % 100;
}

fila *criar_fila() {
  fila *f = malloc(sizeof(fila));
  f->primeiro = NULL;
  f->ultimo = NULL;
  f->qtde = 0;
  return f;
}

celula *criar_celula(char *nome) {
  celula *c = malloc(sizeof(celula));
  c->anterior = NULL;
  c->proximo = NULL;
  c->senha = criaSenha();
  strcpy(c->nome, nome);
  
  return c;
}

void enfileirar(fila *f, char *nome) {
  celula *nova = criar_celula(nome);

  if (f->qtde == 0) {
    f->primeiro = nova;
  } else {
    f->ultimo->proximo = nova;
    nova->anterior = f->ultimo;
  }

  f->ultimo = nova;
  f->qtde++;
}

int desenfileirar(fila *f) {

  if (f->qtde == 0) {
    printf("Fila vazia\n");
  }

  char *nome = f->primeiro->nome;
  celula *endereco = f->primeiro;

  if (f->qtde == 1) {

    f->ultimo = NULL;

  } else {
    f->primeiro->proximo->anterior = NULL;
  }

  f->primeiro = f->primeiro->proximo;
  f->qtde--;
  free(endereco);
  return *nome;
}

void mostrar(fila *f) {
  
  celula *atual = f->primeiro;
  printf("\n");
  printf("início -> ");
 
  while (atual != NULL) {
    printf("\nPaciente: %s -> Senha: %d", atual->nome, atual->senha);
    atual = atual->proximo;
  }
  printf("\n");
  printf(" <- final\n");
}

void mostrar_invertido(fila *f){
  celula *atual = f->ultimo;
  printf("\nfinal -> ");
  while (atual != NULL) {
    printf("%s ", atual->nome);
    atual = atual->anterior;
  }
  printf(" <- início\n");

}

fila *retorna_fila(fila *f){
  FILE *pacientes = fopen("pacientes.txt", "r");
    if (pacientes == NULL) {
      printf("--> Erro ao abrir o arquivo.\n");
      return f;
    }
    char linha[256];
    while (fgets(linha, sizeof(linha), pacientes)) {
      char nome[100], rg[100];
      int idade, dia, mes, ano;
      sscanf(
          linha,
          "Nome: %99[^,]",
          nome);
      enfileirar(f, nome);
    }
  fclose(pacientes);
  return f;
}

bool verificaNome(fila *f, char *nome) {
  celula *atual = f->primeiro;
  celula *anterior = NULL;
  while (atual != NULL && strcmp(atual->nome, nome) != 0) {
    anterior = atual;
    atual = atual->proximo;
  }
  if (atual == NULL) {
    printf("\n--> Paciente não encontrado. Repita o processo.\n");
    return false;
  }
  printf("\n--> Paciente encontrado e enfileirado.\n");
  return true;
}


void enfileiramento (){
  fila *f = criar_fila();
  retorna_fila(f);
  FILE *pacientes = fopen("pacientes.txt", "r");
  int escolhaUsuario;
  mostraCadastros();
  printf("\n1 - Enfileirar Paciente GSS\n");
  printf("0 - Sair\n");
  printf("Escolha: ");
  scanf("%d", &escolhaUsuario);
  printf("\n");
  getchar();
  char nome[256];
  fila *fila = criar_fila();
  while(escolhaUsuario != 0){
    if(escolhaUsuario == 1){
      printf("Escolha o paciente: ");
      fgets(nome,sizeof(nome), stdin);
      nome[strcspn(nome, "\n")] = '\0';  
      if(verificaNome(f, nome)){
        enfileirar(fila,nome);
        printf("\n--- FILA ATUAL ---\n");
        mostrar(fila);
        printf("\n--------------------\n");
      }
      printf("\n1 - Continuar ?\n");
      printf("2 - Desenfileirar paciente GSS\n");
      printf("3- Mostrar fila GSS\n");
      printf("0 - Sair\n");
      printf("Escolha: ");
      scanf("%d", &escolhaUsuario);
      printf("\n");
      getchar();   
    }else if(escolhaUsuario == 2){
      desenfileirar(fila);
      printf("\n--> Primeiro paciente da fila retirado\n");
      printf("\n--- FILA ATUAL ---\n");
      mostrar(fila);
      printf("\n--------------------\n");
      printf("\n1 - Enfileirar Paciente GSS\n");
      printf("2 - Continuar desenfileiramento\n");
      printf("3- Mostrar fila GSS\n");
      printf("0 - Sair\n");
      printf("Escolha: ");
      scanf("%d", &escolhaUsuario);
      printf("\n");
      getchar();  
    } else if(escolhaUsuario == 3){
      printf("\n--- FILA ATUAL ---\n");
      mostrar(fila);
      printf("\n--------------------\n");
      printf("\n1 - Enfileirar Paciente GSS\n");
      printf("2 - Desenfileirar paciente GSS\n");
      printf("0 - Sair\n");
      printf("Escolha: ");
      scanf("%d", &escolhaUsuario);
      printf("\n");
      getchar(); 
    }
    
  }
  return;
}
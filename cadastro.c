#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Celula {
    struct Celula *proximo;
    char nome[100];
    int idade;
    char rg[100];
    int dia;
    int mes;
    int ano;
} Celula;

typedef struct Lista {
    int qtde;
    Celula *primeiro;
} Lista;


void inserirLDE(Lista *l, char *nome, int idade, char *rg, int dia, int mes, int ano) {
    Celula *novo = malloc(sizeof(Celula));
    if (novo == NULL) {
        printf("Vazio\n");
        return;
    }
    strcpy(novo->nome, nome);
    novo->idade = idade;
    strcpy(novo->rg, rg);
    novo->dia = dia;
    novo->mes = mes;
    novo->ano = ano;
    novo->proximo = NULL;

    if (l->primeiro == NULL) {
        l->primeiro = novo;
    } else {
        Celula *atual = l->primeiro;
        Celula *anterior = NULL;
        while (atual != NULL)  {
            anterior = atual;
            atual = atual->proximo;
        }
        if (anterior == NULL) {
            novo->proximo = l->primeiro;
            l->primeiro = novo;
        } else {
            if (atual == NULL) {
                anterior->proximo = novo;
            } else {
                novo->proximo = atual;
                anterior->proximo = novo;
            }
        }
    }
    l->qtde++;
}


void removerLDE(Lista *l, char *rg) {
    Celula *atual = l->primeiro;
    Celula *anterior = NULL;

    while (atual != NULL && strcmp(atual->rg, rg) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }
    if (atual == NULL) {
        printf("Paciente não encontrado.\n");
        return;
    }
    if (anterior == NULL) {
        l->primeiro = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }
    free(atual); 
    l->qtde--;
}

Lista *inicializa_LDE() {
    Lista *l = malloc(sizeof(Lista));

    l->primeiro = NULL;
    l->qtde = 0;
    return l;
}

void imprimirLDE(Lista *l) {
    Celula *atual = l->primeiro;
    while (atual != NULL) {
        printf("Nome: %s, Idade: %d, RG: %s, Data de Nascimento: %d/%d/%d\n",
               atual->nome, atual->idade, atual->rg, atual->dia, atual->mes, atual->ano);
        atual = atual->proximo;
    }
}

int cadastroDePaciente(){
  char nome[100];
  char idade_str[10];
  char dia_str[10];
  char rg[100];
  char mes_str[10];
  char ano_str[10];
  int idade, dia, mes, ano, escolhaUsuario;
  Lista *l = inicializa_LDE();

  do{

      
      printf("Insira os dados do paciente abaixo: ");
      printf("\n");
      printf("\n");
      getchar();
      printf("Nome: ");
      fgets(nome, sizeof(nome), stdin);
      nome[strcspn(nome, "\n")] = '\0'; 
      printf("\n");
      printf("Idade: ");
      fgets(idade_str, sizeof(idade_str), stdin);
      idade = atoi(idade_str); 
      printf("\n");
      printf("RG: ");
      fgets(rg, sizeof(rg), stdin);
      rg[strcspn(rg, "\n")] = '\0'; 
      printf("\n");
      printf("Dia do nascimento: ");
      fgets(dia_str, sizeof(dia_str), stdin);
      dia = atoi(dia_str); 
      printf("\n");
      printf("Mês do nascimento: ");
      fgets(mes_str, sizeof(mes_str), stdin);
      mes = atoi(mes_str); 
      printf("\n");
      printf("Ano do nascimento: ");
      fgets(ano_str, sizeof(ano_str), stdin);
      ano = atoi(ano_str); 
      printf("\n");

      inserirLDE(l, nome, idade, rg, dia, mes, ano);

      printf("Pacientes cadastrados até o momento: ");
      printf("\n");
      printf("\n");
      imprimirLDE(l);
      printf("\n");
      printf("\n");
      printf("Continuar cadastramento ? ");
      printf("\n");
      printf("1 - SIM // 2 - NÃO");  
      printf("\n");
      scanf("%d", &escolhaUsuario);
      getchar();

  } while (escolhaUsuario != 2); 
  return 0;
}

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
        printf("Memória insuficiente.\n");
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
    if (atual == NULL) {
        printf("Lista vazia.\n");
        return;
    }
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
 
    FILE *pacientes;
  
    do {
        printf("\nInsira os dados do paciente abaixo: \n");
        printf("Nome: ");
        fgets(nome, sizeof(nome), stdin);
        nome[strcspn(nome, "\n")] = '\0'; 
        printf("Idade: ");
        fgets(idade_str, sizeof(idade_str), stdin);
        idade = atoi(idade_str); 
        printf("RG: ");
        fgets(rg, sizeof(rg), stdin);
        rg[strcspn(rg, "\n")] = '\0'; 
        printf("Dia do nascimento: ");
        fgets(dia_str, sizeof(dia_str), stdin);
        dia = atoi(dia_str); 
        printf("Mês do nascimento: ");
        fgets(mes_str, sizeof(mes_str), stdin);
        mes = atoi(mes_str); 
        printf("Ano do nascimento: ");
        fgets(ano_str, sizeof(ano_str), stdin);
        ano = atoi(ano_str); 
        if (dia > 31 || mes > 12 || ano < 1910) {
          printf("\nDatas inválidas\n");
        } else if (mes == 2) {
            if (ano % 4 == 0) {
                if (dia > 29) {
                  printf("\nDatas inválidas\n");
              }
              } else {
              if (dia > 28) {
                  printf("\nDatas inválidas\n");
              }
          }
        }else{
        inserirLDE(l, nome, idade, rg, dia, mes, ano);
        printf("\n");
        printf("Pacientes cadastrados até o momento:\n\n");
        imprimirLDE(l);
        printf("\nContinuar cadastramento ?\n\n");
        printf("1 - SIM // 2 - Salvar em Arquivo // 0 - Cancelar operação)\n");
        printf("Escolha: ");
        scanf("%d", &escolhaUsuario);
        getchar(); 
        if (escolhaUsuario == 2){
          Celula *atual = l->primeiro;
          while (atual != NULL){
            pacientes = fopen("pacientes.txt", "a");
            fprintf(pacientes, "Nome: %s, Idade: %d, RG: %s, Dia: %d, Mês: %d, Ano: %d \n", atual->nome, atual->idade, atual -> rg, atual-> dia, atual->mes, atual-> ano);
            atual = atual->proximo;
            printf("\nIndivíduo cadastrado no banco de pacientes.\n\n");
          }
          fclose(pacientes);
          return 0;
        } 
      }
    } while (escolhaUsuario != 0);

    return 0;
}


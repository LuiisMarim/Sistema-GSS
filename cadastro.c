#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Celula {
  struct Celula *proximo;
  struct Celula *anterior;
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


void inserirLDE(Lista *l, char *nome, int idade, char *rg, int dia, int mes,
                int ano) {
  Celula *novo = malloc(sizeof(Celula));
  if (novo == NULL) {
    return;
  }
  strcpy(novo->nome, nome);
  novo->idade = idade;
  strcpy(novo->rg, rg);
  novo->dia = dia;
  novo->mes = mes;
  novo->ano = ano;
  novo->proximo = l->primeiro; 
  novo->anterior = NULL; 
  if (l->primeiro != NULL) {
    l->primeiro->anterior = novo; 
  }
  l->primeiro = novo; 
  l->qtde++;
}

void inserirNoFimLDE(Lista *l, char *nome, int idade, char *rg, int dia, int mes, int ano) {
    Celula *novo = malloc(sizeof(Celula));
    if (novo == NULL) {
        return;
    }
    strcpy(novo->nome, nome);
    novo->idade = idade;
    strcpy(novo->rg, rg);
    novo->dia = dia;
    novo->mes = mes;
    novo->ano = ano;
    novo->proximo = NULL;
    novo->anterior = NULL;

    if (l->primeiro == NULL) {
        l->primeiro = novo;
    } else {
        Celula *atual = l->primeiro;
        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }
        atual->proximo = novo;
        novo->anterior = atual;
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
    printf("--> Paciente não encontrado.\n");
    return;
  }
  if (atual -> anterior == NULL) {
    l->primeiro = atual->proximo;
  } else {
    anterior->proximo = atual->proximo;
  }
  printf("\n--> Paciente Removido\n");
  free(atual);
  l->qtde--;
}

void removerListaCompleta(Lista *l) {
  Celula *atual = l->primeiro;
  Celula *proximo;

  while (atual != NULL) {
    proximo = atual->proximo;
    free(atual);
    atual = proximo;
  }
  l->primeiro = NULL;
  l->qtde = 0;
}

Lista *inicializa_LDE() {
  Lista *l = malloc(sizeof(Lista));
  if (l == NULL) {
    printf("Erro ao alocar memória.\n");
    return NULL;
  }

  l->primeiro = NULL;
  l->qtde = 0;
  return l;
}

Lista *retorna_lista(Lista *lista){
      FILE *pacientes = fopen("pacientes.txt", "r");
      if (pacientes == NULL) {
        printf("--> Erro ao abrir o arquivo.\n");
        return lista;
      }
      char linha[256];
      while (fgets(linha, sizeof(linha), pacientes)) {
        char nome[100], rg[100];
        int idade, dia, mes, ano;
        sscanf(
            linha,
            "Nome: %99[^,], Idade: %d, RG: %99[^,], Dia: %d, Mês: %d, Ano: %d",
            nome, &idade, rg, &dia, &mes, &ano);
        inserirNoFimLDE(lista, nome, idade, rg, dia, mes, ano);
      }
    fclose(pacientes);
    return lista;
}

void imprimirLDE(Lista *l) {
  Celula *atual = l->primeiro;
  if (atual == NULL) {
    printf("--> Lista vazia.\n");
    return;
  }
  while (atual != NULL) {
    printf("Nome: %s, Idade: %d, RG: %s, Data de Nascimento: %d/%d/%d\n",
           atual->nome, atual->idade, atual->rg, atual->dia, atual->mes,
           atual->ano);
    atual = atual->proximo;
  }
}

void removerCadastro() {
  FILE *arquivo = fopen("pacientes.txt", "r");
  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo.\n");
    return;
  }
  fclose(arquivo);

  remove("pacientes.txt");

  FILE *temp = fopen("temp.txt", "w");

  fclose(temp);

  rename("temp.txt", "pacientes.txt"); 
}

void atualizaNome(Lista *l, char *rg, char *nome) {
  Celula *atual = l->primeiro;
  Celula *anterior = NULL;

  while (atual != NULL && strcmp(atual->rg, rg) != 0) {
    anterior = atual;
    atual = atual->proximo;
  }
  if (atual == NULL) {
    printf("--> Paciente não encontrado.\n");
    return;
  }
  strcpy(atual->nome, nome);
  printf("\n--> Paciente com nome atualizado. --> Lista total de pacientes: \n");
}

void atualizaData(Lista *l, char *rg , int dia, int mes, int ano){
  Celula *atual = l->primeiro;
  Celula *anterior = NULL;

  while (atual != NULL && strcmp(atual->rg, rg) != 0) {
    anterior = atual;
    atual = atual->proximo;
  }
  if (atual == NULL) {
    printf("--> Paciente não encontrado.\n");
    return;
  }
  atual ->dia = dia;
  atual->mes = mes;
  atual->ano = ano;
  printf("\n--> Paciente com data atualizada. --> Lista completa de pacientes: \n");
}

void mostraCadastros() {
  printf("\n--- PACIENTES GSS ---\n\n");
  Lista *lista = inicializa_LDE();
  FILE *pacientes = fopen("pacientes.txt", "r");
  if (pacientes == NULL) {
    printf("--> Erro ao abrir o arquivo.\n");
    return;
  }
  char linha[256];
  while (fgets(linha, sizeof(linha), pacientes)) {
    char nome[100], rg[100];
    int idade, dia, mes, ano;
    sscanf(linha,
           "Nome: %99[^,], Idade: %d, RG: %99[^,], Dia: %d, Mês: %d, Ano: %d",
           nome, &idade, rg, &dia, &mes, &ano);
    inserirLDE(lista, nome, idade, rg, dia, mes, ano);
  }
  imprimirLDE(lista);
  printf("\n--- FIM ---\n");
  fclose(pacientes);
}

void mostraPaciente(Lista *l, char *rg){
    Celula *atual = l->primeiro;
    Celula *anterior = NULL;

    while (atual != NULL && strcmp(atual->rg, rg) != 0) {
      anterior = atual;
      atual = atual->proximo;
    }
    if (atual == NULL) {
      printf("--> Paciente não encontrado.\n");
      return;
    }
  FILE *pacientes = fopen("pacientes.txt", "r");
  if (pacientes == NULL) {
    printf("--> Erro ao abrir o arquivo.\n");
    return;
  }
  printf("\n--> Paciente: %s, Data de nascimentos: %d/%d/%d\n", atual->nome, atual-> dia, atual->mes, atual->ano);
  
}

void cadastra(Lista *l) {

  FILE *pacientes = fopen("pacientes.txt", "a+");
  if (pacientes == NULL) {
    printf("Erro ao abrir o arquivo.\n");
    return;
  }

  Celula *atual = l->primeiro;
  while (atual != NULL) {
    fprintf(pacientes,
            "Nome: %s, Idade: %d, RG: %s, Dia: %d, Mês: %d, Ano: %d\n",
            atual->nome, atual->idade, atual->rg, atual->dia, atual->mes,
            atual->ano);
    atual = atual->proximo;
  }
  fclose(pacientes);
}

int cadastroDePaciente() {
  char nome[100];
  char idade_str[10];
  char dia_str[10];
  char rg[100];
  char mes_str[10];
  char ano_str[10];
  char escolhaUsuario_str[10];
  int idade, dia, mes, ano, escolhaUsuario;
  Lista *l = inicializa_LDE();

  printf("\n--- Menu de Cadastros ---\n");
  printf("\n1 - Iniciar cadastro.\n");
  printf("2 - Manipulação de dados\n");
  printf("0 - Retornar ao menu.\n");
  printf("Escolha: ");
  fgets(escolhaUsuario_str, sizeof(escolhaUsuario_str), stdin);
  escolhaUsuario_str[strcspn(escolhaUsuario_str, "\n")] = '\0';
  escolhaUsuario = atoi(escolhaUsuario_str);

  while (escolhaUsuario != 0) {

    if (escolhaUsuario == 1) {
      printf("\nInsira os dados do paciente abaixo: \n");
      printf("Nome: ");
      fgets(nome, sizeof(nome), stdin);
      nome[strcspn(nome, "\n")] = '\0';
      printf("Idade: ");
      fgets(idade_str, sizeof(idade_str), stdin);
      idade_str[strcspn(idade_str, "\n")] = '\0';
      idade = atoi(idade_str);
      printf("RG: ");
      fgets(rg, sizeof(rg), stdin);
      rg[strcspn(rg, "\n")] = '\0';
      printf("Dia do nascimento: ");
      fgets(dia_str, sizeof(dia_str), stdin);
      dia_str[strcspn(dia_str, "\n")] = '\0';
      dia = atoi(dia_str);
      printf("Mês do nascimento: ");
      fgets(mes_str, sizeof(mes_str), stdin);
      mes_str[strcspn(mes_str, "\n")] = '\0';
      mes = atoi(mes_str);
      printf("Ano do nascimento: ");
      fgets(ano_str, sizeof(ano_str), stdin);
      ano_str[strcspn(ano_str, "\n")] = '\0';
      ano = atoi(ano_str);
      if (dia > 31 || mes > 12 || mes <= 0 || ano < 1900) {
        printf("\nDatas inválidas. Retornado ao menu\n");
        return 0;
      } else {
        inserirLDE(l, nome, idade, rg, dia, mes, ano);
        printf("\n");
        printf("--> Pacientes na fila de cadastros até o momento:\n\n");
        imprimirLDE(l);
        printf("\n--> Continuar cadastramento ?\n\n");
        printf("1 - SIM \n");
        printf("2 - Salvar em Arquivo\n");
        printf("0 - Cancelar operação e voltar ao MENU\n\n");
        printf("Escolha: ");
        fgets(escolhaUsuario_str, sizeof(escolhaUsuario_str), stdin);
        escolhaUsuario_str[strcspn(escolhaUsuario_str, "\n")] = '\0';
        escolhaUsuario = atoi(escolhaUsuario_str);
      }
    } else if (escolhaUsuario == 2) {
      Celula *atual = l->primeiro;
      if (atual == NULL) {
        l = inicializa_LDE();
        printf("\n--- Manipulação de dados ---\n");
        printf("\n1 - Iniciar novo cadastro \n");
        printf("2 - Mostrar banco de cadastros GSS\n");
        printf("3 - Remover paciente\n");
        printf("4 - Atualização de nome\n"); 
        printf("5 - Atualização de data\n"); 
        printf("6 - Mostrar paciente específico\n");
        printf("0 - Cancelar operação e voltar ao MENU\n\n");
        printf("Escolha: ");
        fgets(escolhaUsuario_str, sizeof(escolhaUsuario_str), stdin);
        escolhaUsuario_str[strcspn(escolhaUsuario_str, "\n")] = '\0';
        escolhaUsuario = atoi(escolhaUsuario_str);
        if (escolhaUsuario == 2) {
          mostraCadastros();
        }
      } else {
        cadastra(l);
        printf("\nIndivíduo(s) cadastrado no banco de pacientes.\n");
        removerListaCompleta(l);
        l = inicializa_LDE();
        printf("\n--> Continuar cadastramento ?\n\n");
        printf("1 - SIM \n");
        printf("2 - Mostrar banco de cadastros GSS\n");
        printf("3 - Remover paciente\n");
        printf("4 - Atualização de nome\n"); 
        printf("5 - Atualização de data\n"); 
        printf("6 - Mostrar paciente específico\n");
        printf("0 - Cancelar operação e voltar ao MENU\n\n");
        printf("Escolha: ");
        fgets(escolhaUsuario_str, sizeof(escolhaUsuario_str), stdin);
        escolhaUsuario_str[strcspn(escolhaUsuario_str, "\n")] = '\0';
        escolhaUsuario = atoi(escolhaUsuario_str);
        if (escolhaUsuario == 2) {
          mostraCadastros();
          printf("\n\n--> Continuar cadastramento ?\n\n");
          printf("1 - SIM \n");
          printf("0 - Cancelar operação e voltar ao MENU\n\n");
          printf("Escolha: ");
          fgets(escolhaUsuario_str, sizeof(escolhaUsuario_str), stdin);
          escolhaUsuario_str[strcspn(escolhaUsuario_str, "\n")] = '\0';
          escolhaUsuario = atoi(escolhaUsuario_str);
        }
      }
    } else if (escolhaUsuario == 3) {
      Lista *lista = inicializa_LDE();
      char rg[100];
      Celula *atual = lista->primeiro;
      retorna_lista(lista);  
      mostraCadastros();
      printf("\n");
      printf("Digite o RG do indivíduo para remoção:");
      fgets(rg, sizeof(rg), stdin);
      rg[strcspn(rg, "\n")] = '\0'; // swap
      removerLDE(lista, rg);
      removerCadastro();
      cadastra(lista);
      printf("\n--> Continuar cadastramento ?\n\n");
      printf("1 - SIM \n");
      printf("2 - Mostrar banco de cadastros GSS\n");
      printf("3 - Remover paciente\n");
      printf("4 - Atualização de nome\n");
      printf("5 - Atualização de data\n"); 
      printf("6 - Mostrar paciente específico\n");
      printf("0 - Cancelar operação e voltar ao MENU\n\n");
      printf("Escolha: ");
      fgets(escolhaUsuario_str, sizeof(escolhaUsuario_str), stdin);
      escolhaUsuario_str[strcspn(escolhaUsuario_str, "\n")] = '\0';
      escolhaUsuario = atoi(escolhaUsuario_str);
      if (escolhaUsuario == 2) {
        mostraCadastros();
      }
    } else if (escolhaUsuario == 4) {
      Lista *lista1 =inicializa_LDE();
      char nome[256];
      char rg[256];
      mostraCadastros();
      retorna_lista(lista1);
      printf("Digite o novo nome para atualização: ");
      fgets(nome, sizeof(nome), stdin);
      nome[strcspn(nome, "\n")] = '\0';
      printf("Digite o RG para localização: ");
      fgets(rg, sizeof(rg), stdin);  
      rg[strcspn(rg, "\n")] = '\0';
      atualizaNome(lista1, rg, nome);
      removerCadastro();
      cadastra(lista1);
      mostraCadastros();
      printf("\n--> Continuar cadastramento ?\n\n");
      printf("1 - SIM \n");
      printf("0 - Cancelar operação e voltar ao MENU\n\n");
      printf("Escolha: ");
      fgets(escolhaUsuario_str, sizeof(escolhaUsuario_str), stdin);
      escolhaUsuario_str[strcspn(escolhaUsuario_str, "\n")] = '\0';
      escolhaUsuario = atoi(escolhaUsuario_str);
  } else if(escolhaUsuario == 5){
      Lista *lista2 =inicializa_LDE();
      char dia_str[10];
      char mes_str[10];
      char ano_str[10];
      char rg[256];
      mostraCadastros();
      retorna_lista(lista2);
      printf("Digite o novo dia para atualização: ");
      fgets(dia_str, sizeof(dia_str), stdin);
      dia_str[strcspn(dia_str, "\n")] = '\0';
      dia = atoi(dia_str);
      printf("Mês do nascimento: ");
      fgets(mes_str, sizeof(mes_str), stdin);
      mes_str[strcspn(mes_str, "\n")] = '\0';
      mes = atoi(mes_str);
      printf("Ano do nascimento: ");
      fgets(ano_str, sizeof(ano_str), stdin);
      ano_str[strcspn(ano_str, "\n")] = '\0';
      ano = atoi(ano_str);
      printf("Digite o RG para localização: ");
      fgets(rg, sizeof(rg), stdin);  
      rg[strcspn(rg, "\n")] = '\0';
      atualizaData(lista2, rg, dia, mes, ano);
      removerCadastro();
      cadastra(lista2);
      mostraCadastros();
      printf("\n--> Continuar cadastramento ?\n\n");
      printf("1 - SIM \n");
      printf("0 - Cancelar operação e voltar ao MENU\n\n");
      printf("Escolha: ");
      fgets(escolhaUsuario_str, sizeof(escolhaUsuario_str), stdin);
      escolhaUsuario_str[strcspn(escolhaUsuario_str, "\n")] = '\0';
      escolhaUsuario = atoi(escolhaUsuario_str);
  } else if(escolhaUsuario == 6){
      Lista *lista3 =inicializa_LDE();
      retorna_lista(lista3);
      char rg[256];
      printf("Digite o RG para localização: ");
      fgets(rg, sizeof(rg), stdin);  
      rg[strcspn(rg, "\n")] = '\0';
      mostraPaciente(lista3, rg);
      printf("\n--> Continuar cadastramento ?\n\n");
      printf("1 - SIM \n");
      printf("0 - Cancelar operação e voltar ao MENU\n\n");
      printf("Escolha: ");
      fgets(escolhaUsuario_str, sizeof(escolhaUsuario_str), stdin);
      escolhaUsuario_str[strcspn(escolhaUsuario_str, "\n")] = '\0';
      escolhaUsuario = atoi(escolhaUsuario_str);
  }
  }
  return 0;
}

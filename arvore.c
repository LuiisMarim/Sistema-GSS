#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Vertice {
    int ano, dia, mes, idade;
    char nome[100];
    char rg[100];
    struct Vertice *esq;
    struct Vertice *dir;
    struct Vertice *pai;
} Vertice;


typedef struct Arvore {
    Vertice *raiz;
    int qtde;
} Arvore;

void in_ordem_ano(Vertice *raiz) {
    if (raiz != NULL) {
        in_ordem_ano(raiz->esq);
        printf("--> Paciente: %s, Ano: %d \n",raiz->nome, raiz->ano);
        in_ordem_ano(raiz->dir);
    }
}

void in_ordem_dia(Vertice *raiz) {
    if (raiz != NULL) {
        in_ordem_dia(raiz->esq);
        printf("--> Paciente: %s, Dia: %d \n ", raiz->nome, raiz->dia);
        in_ordem_dia(raiz->dir);
    }
}

void in_ordem_mes(Vertice *raiz) {
    if (raiz != NULL) {
        in_ordem_mes(raiz->esq);
        printf("--> Paciente: %s, Mês: %d \n",raiz->nome, raiz->mes);
        in_ordem_mes(raiz->dir);
    }
}

void in_ordem_idade(Vertice *raiz) {
    if (raiz != NULL) {
        in_ordem_idade(raiz->esq);
        printf("--> Paciente: %s, Idade: %d \n",raiz->nome, raiz->idade);
        in_ordem_idade(raiz->dir);
    }
}

Vertice *cria_vertice_ano(Arvore *arvore, char *nome, int ano) {
    Vertice *novo = malloc(sizeof(Vertice));
    novo->dir = NULL;
    novo->esq = NULL;
    novo->pai = NULL;
    novo->ano = ano;
    strcpy(novo->nome, nome);

    return novo;
}

Vertice *cria_vertice_dia(Arvore *arvore, char *nome, int dia) {
    Vertice *novo = malloc(sizeof(Vertice));
    novo->dir = NULL;
    novo->esq = NULL;
    novo->pai = NULL;
    novo->dia = dia;
    strcpy(novo->nome, nome);

    return novo;
}

Vertice *cria_vertice_mes(Arvore *arvore, char *nome, int mes) {
    Vertice *novo = malloc(sizeof(Vertice));
    novo->dir = NULL;
    novo->esq = NULL;
    novo->pai = NULL;
    novo->mes = mes;
    strcpy(novo->nome, nome);

    return novo;
}

Vertice *cria_vertice_idade(Arvore *arvore, char *nome, int idade) {
    Vertice *novo = malloc(sizeof(Vertice));
    novo->dir = NULL;
    novo->esq = NULL;
    novo->pai = NULL;
    novo->idade = idade;
    strcpy(novo->nome, nome);

    return novo;
}

Arvore *cria_arvore() {
    Arvore *arvore = malloc(sizeof(Arvore));
    arvore->raiz = NULL;
    arvore->qtde = 0;

    return arvore;
}

void inserir_ano(Arvore *arvore, char *nome, int ano) {
    Vertice *novo = cria_vertice_ano(arvore, nome, ano);
    if (arvore->raiz == NULL) {
        arvore->raiz = novo;
    } else {
        Vertice *atual = arvore->raiz;
        Vertice *anterior = NULL;
        while (atual != NULL) {
            anterior = atual;
            if (atual->ano > novo->ano) {
                atual = atual->esq;
            } else {
                atual = atual->dir;
            }
        }
        if (novo->ano > anterior->ano) {
            anterior->dir = novo;

        } else {
            anterior->esq = novo;
        }
        novo->pai = anterior; 
    }

    arvore->qtde++;

}

void inserir_dia(Arvore *arvore, char *nome, int dia) {
    Vertice *novo = cria_vertice_dia(arvore, nome, dia);
    if (arvore->raiz == NULL) {
        arvore->raiz = novo;
    } else {
        Vertice *atual = arvore->raiz;
        Vertice *anterior = NULL;
        while (atual != NULL) {
            anterior = atual;
            if (atual->dia > novo->dia) {
                atual = atual->esq;
            } else {
                atual = atual->dir;
            }
        }
        if (novo->dia > anterior->dia) {
            anterior->dir = novo;

        } else {
            anterior->esq = novo;
        }
        novo->pai = anterior; 
    }

    arvore->qtde++;

}

void inserir_mes(Arvore *arvore, char *nome, int mes) {
    Vertice *novo = cria_vertice_mes(arvore, nome, mes);
    if (arvore->raiz == NULL) {
        arvore->raiz = novo;
    } else {
        Vertice *atual = arvore->raiz;
        Vertice *anterior = NULL;
        while (atual != NULL) {
            anterior = atual;
            if (atual->mes > novo->mes) {
                atual = atual->esq;
            } else {
                atual = atual->dir;
            }
        }
        if (novo->mes > anterior->mes) {
            anterior->dir = novo;

        } else {
            anterior->esq = novo;
        }
        novo->pai = anterior; 
    }

    arvore->qtde++;

}

void inserir_idade(Arvore *arvore, char *nome, int idade) {
    Vertice *novo = cria_vertice_idade(arvore, nome, idade);
    if (arvore->raiz == NULL) {
        arvore->raiz = novo;
    } else {
        Vertice *atual = arvore->raiz;
        Vertice *anterior = NULL;
        while (atual != NULL) {
            anterior = atual;
            if (atual->idade > novo->idade) {
                atual = atual->esq;
            } else {
                atual = atual->dir;
            }
        }
        if (novo->idade > anterior->idade) {
            anterior->dir = novo;

        } else {
            anterior->esq = novo;
        }
        novo->pai = anterior; 
    }

    arvore->qtde++;

}

Arvore *retorna_arvore_ano(Arvore *a) {
    FILE *pacientes = fopen("pacientes.txt", "r");
    if (pacientes == NULL) {
        printf("--> Erro ao abrir o arquivo.\n");
        return a;
    }

    if (a == NULL) {
        printf("--> Erro ao alocar memória para a árvore.\n");
        return NULL;
    }

    char linha[256];
    while (fgets(linha, sizeof(linha), pacientes)) {
        char nome[100], rg[100];
        int idade, dia, mes, ano;
        sscanf(
            linha,
            "Nome: %99[^,], Idade: %d, RG: %99[^,], Dia: %d, Mês: %d, Ano: %d",
                nome, &idade, rg, &dia, &mes, &ano);
            inserir_ano(a, nome, ano);
    }
    fclose(pacientes);
    return a;
}

Arvore *retorna_arvore_dia(Arvore *a) {
    FILE *pacientes = fopen("pacientes.txt", "r");
    if (pacientes == NULL) {
        printf("--> Erro ao abrir o arquivo.\n");
        return a;
    }

    if (a == NULL) {
        printf("--> Erro ao alocar memória para a árvore.\n");
        return NULL;
    }

    char linha[256];
    while (fgets(linha, sizeof(linha), pacientes)) {
        char nome[100], rg[100];
        int idade, dia, mes, ano;
        sscanf(
            linha,
            "Nome: %99[^,], Idade: %d, RG: %99[^,], Dia: %d, Mês: %d, Ano: %d",
                nome, &idade, rg, &dia, &mes, &ano);
            inserir_dia(a, nome, dia);
    }
    fclose(pacientes);
    return a;
}

Arvore *retorna_arvore_mes(Arvore *a) {
    FILE *pacientes = fopen("pacientes.txt", "r");
    if (pacientes == NULL) {
        printf("--> Erro ao abrir o arquivo.\n");
        return a;
    }

    if (a == NULL) {
        printf("--> Erro ao alocar memória para a árvore.\n");
        return NULL;
    }

    char linha[256];
    while (fgets(linha, sizeof(linha), pacientes)) {
        char nome[100], rg[100];
        int idade, dia, mes, ano;
        sscanf(
            linha,
            "Nome: %99[^,], Idade: %d, RG: %99[^,], Dia: %d, Mês: %d, Ano: %d",
                nome, &idade, rg, &dia, &mes, &ano);
            inserir_mes(a, nome, mes);
    }
    fclose(pacientes);
    return a;
}

Arvore *retorna_arvore_idade(Arvore *a) {
    FILE *pacientes = fopen("pacientes.txt", "r");
    if (pacientes == NULL) {
        printf("--> Erro ao abrir o arquivo.\n");
        return a;
    }

    if (a == NULL) {
        printf("--> Erro ao alocar memória para a árvore.\n");
        return NULL;
    }

    char linha[256];
    while (fgets(linha, sizeof(linha), pacientes)) {
        char nome[100], rg[100];
        int idade, dia, mes, ano;
        sscanf(
            linha,
            "Nome: %99[^,], Idade: %d, RG: %99[^,], Dia: %d, Mês: %d, Ano: %d",
                nome, &idade, rg, &dia, &mes, &ano);
            inserir_idade(a, nome, idade);
    }
    fclose(pacientes);
    return a;
}

void arvorismo(){
    int escolhaUsuario;
    char escolhaUsuario_str[10];
    printf("\n--- Menu de Pesquisa ---");
    printf("\n1 - Pacientes Ordenados por ano\n");
    printf("2 - Pacientes Ordenados por mes.\n");
    printf("3 - Pacientes Ordenados por dia.\n");
    printf("4 - Pacientes Ordenados por idade. \n");
    printf("Escolha: ");
    fgets(escolhaUsuario_str, sizeof(escolhaUsuario_str), stdin);
    escolhaUsuario_str[strcspn(escolhaUsuario_str, "\n")] = '\0';
    escolhaUsuario = atoi(escolhaUsuario_str);
   
    if(escolhaUsuario == 1){
        printf("\n --- Pacientes listados por ano --- \n\n");
        Arvore *arvore_ano = retorna_arvore_ano(cria_arvore());
        in_ordem_ano(arvore_ano->raiz);
    }
    else if (escolhaUsuario == 2){
        printf("\n --- Pacientes listados por mes --- \n\n");
        Arvore *arvore_mes = retorna_arvore_mes(cria_arvore());
        in_ordem_mes(arvore_mes->raiz);
    }
    else if (escolhaUsuario == 3){
        printf("\n --- Pacientes listados por dia --- \n\n");
        Arvore *arvore_dia = retorna_arvore_dia(cria_arvore());
        in_ordem_dia(arvore_dia->raiz);
    }
    else if (escolhaUsuario == 4){
        printf("\n --- Pacientes listados por idade --- \n\n");
        Arvore *arvore_idade = retorna_arvore_idade(cria_arvore());
        in_ordem_idade(arvore_idade->raiz);
    }
}
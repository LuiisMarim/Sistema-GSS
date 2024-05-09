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
        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }
        atual->proximo = novo;
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
        return NULL;
    }

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

void atualizaCadastro(){
    FILE *pacientes = fopen("pacientes.txt", "r");
    if (pacientes == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    int busca = 0;
    char linhas[100];
    FILE *arquivo = fopen ("temp.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao criar o arquivo temporário.\n");
        fclose(pacientes);
        return;
    }
       
    fclose(pacientes);
    fclose(arquivo);
    
    remove("pacientes.txt");
    rename("temp.txt", "pacientes.txt");
    
}

void mostraCadastros(){
    printf("\n--- PACIENTES GSS ---\n\n");
    FILE *pacientes = fopen("pacientes.txt", "r");
    if (pacientes == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    char paciente[100];
    while (fgets(paciente, sizeof(paciente), pacientes) != NULL){
        paciente[strcspn(paciente, "\n")] = '\0';
        printf("%s\n", paciente);
    }
    printf("\n---------------------\n");
    fclose(pacientes);
}

void cadastra(Lista *l) {
    FILE *pacientes = fopen("pacientes.txt", "a+");
    if (pacientes == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    Celula *atual = l->primeiro;
    while (atual != NULL){  
        fprintf(pacientes, "Nome: %s, Idade: %d, RG: %s, Dia: %d, Mês: %d, Ano: %d \n",
                atual->nome, atual->idade, atual->rg, atual->dia, atual->mes, atual->ano);
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
    int idade, dia, mes, ano, escolhaUsuario;
       Lista *l = inicializa_LDE();
   


    FILE *pacientes;
    printf("\n-------------------\n");
    printf("\n1 - Iniciar cadastro.\n");
    printf("2 - Manipulação de dados\n");
    printf("0 - Retornar ao menu.\n");
    printf("Escolha: ");
    scanf("%d", &escolhaUsuario);
    getchar();
    
 
    while (escolhaUsuario != 0) {
        
        if (escolhaUsuario == 1) {
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
            if (dia > 31 || mes > 12 || mes <= 0 || ano < 1900) {
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
            } else {
                inserirLDE(l, nome, idade, rg, dia, mes, ano);
                printf("\n");
                printf("Pacientes na fila de cadastros até o momento:\n\n");
                imprimirLDE(l);
                printf("\nContinuar cadastramento ?\n\n");
                printf("1 - SIM \n");
                printf("2 - Salvar em Arquivo\n");
                printf("3 - Remover paciente\n");
                printf("0 - Cancelar operação e voltar ao MENU\n\n");
                printf("Escolha: ");
                scanf("%d", &escolhaUsuario);
                getchar();
                
            }
        } else if (escolhaUsuario == 2) {
            Celula *atual = l->primeiro;
            if (atual == NULL) {
                printf("\n1 - Iniciar novo cadastro \n");
                printf("2 - Mostrar banco de cadastros GSS\n");
                printf("3 - Remover paciente\n");
                printf("0 - Cancelar operação e voltar ao MENU\n\n");
                printf("Escolha: ");
                scanf("%d", &escolhaUsuario);
                getchar();
                if (escolhaUsuario == 2) {
                    mostraCadastros();
                }
            } else {
                cadastra(l);
                printf("\nIndivíduo(s) cadastrado no banco de pacientes.\n");
                removerListaCompleta(l);  
                Lista *l = inicializa_LDE();
                printf("\nContinuar cadastramento ?\n\n");
                printf("1 - SIM \n");
                printf("2 - Mostrar banco de cadastros GSS\n");
                printf("3 - Remover paciente\n");  
                printf("0 - Cancelar operação e voltar ao MENU\n\n");
                printf("Escolha: ");
                scanf("%d", &escolhaUsuario);
                getchar(); 
                if (escolhaUsuario == 2) {
                    mostraCadastros();
                    printf("\n\nContinuar cadastramento ?\n\n");
                    printf("1 - SIM \n");  
                    printf("0 - Cancelar operação e voltar ao MENU\n\n");
                    printf("Escolha: ");
                    scanf("%d", &escolhaUsuario);
                    getchar(); 
                }
            }
        } else if (escolhaUsuario == 3) {
            Lista *lista = inicializa_LDE();
            Celula *atual = lista->primeiro;
            FILE *pacientes = fopen("pacientes.txt", "r");
            char linha[256];
            while (fgets(linha, sizeof(linha), pacientes)) {
                char nome[100], rg[100];
                int idade, dia, mes, ano;
                sscanf(linha, "Nome: %99[^,], Idade: %d, RG: %99[^,], Dia: %d, Mês: %d, Ano: %d",
                       nome, &idade, rg, &dia, &mes, &ano);
                inserirLDE(lista, nome, idade, rg, dia, mes, ano);
            }
            printf("\n--- Lista atual para cadastramento ---\n\n");
            imprimirLDE(lista);
            printf("\n");
            printf("Digite o RG do indivíduo para remoção:");
            fgets(rg, sizeof(rg), stdin);
            rg[strcspn(rg, "\n")] = '\0'; //swap
            removerLDE(lista, rg);
            atualizaCadastro();
            cadastra(lista);
            Lista *l = inicializa_LDE();
            printf("\nContinuar cadastramento ?\n\n");
            printf("1 - SIM \n");
            printf("2 - Salvar em Arquivo\n");
            printf("3 - Remover paciente\n");  
            printf("0 - Cancelar operação e voltar ao MENU\n\n");
            printf("Escolha: ");
            scanf("%d", &escolhaUsuario);
            getchar(); 
        }
                
        }
        
        
    return 0;
}



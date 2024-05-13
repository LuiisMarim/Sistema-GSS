#include <stdio.h>
#include <stdlib.h>
#include "projeto.h"

int menu(){
  printf("--------------------");
  printf("\nSistema GSS.\n\n");
  printf("Bem vindo ao Sistema, escolha abaixo para onde gostaria de ser direcionado: \n\n");
  printf("1 - Menu para dados de cadastros.\n");
  printf("2 - Atendimento\n");
  printf("0 - Sair do sistema.\n");
  printf("Escolha: ");

  int escolhaDoUsuario;
  scanf("%d", &escolhaDoUsuario);

  getchar(); 
  return escolhaDoUsuario;
}

void sair(){
  printf("Você escolheu sair.\n");
}




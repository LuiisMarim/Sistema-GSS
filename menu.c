#include <stdio.h>
#include <stdlib.h>
#include "projeto.h"
int menu(){

  printf("Sistema GSS.");
  printf("\n");
  printf("\n");
  printf("Bem vindo ao Sistema, escolha a baixo para onde gostaria de ser direcionado: ");
  printf("\n");
  printf("\n");
  printf("1 - Cadastro pacientes.");
  printf("\n");
  printf("0 - Sair do sistema.");
  printf("\n");
  printf("\n");
  printf("Escolha: ");
  
  int escolhaDoUsuario;
  scanf("%d", &escolhaDoUsuario);
  getchar();
  return escolhaDoUsuario;
}

void sair(){
  printf("Você escolheu sair.");
}


int menuCadastroPaciente(){

  int escolhaUsuario;
  printf("\n");
  printf("\n");
  printf("Menu de Cadastro.");
  printf("\n");
  printf("\n");
  printf("1 - Cadastrar novo paciente.");
  printf("\n");
  printf("2 - Mostrar banco de cadastros atual.");
  printf("\n");
  printf("\n");
  printf("Escolha: ");
  scanf("%d", &escolhaUsuario);
  printf("\n");

  if (escolhaUsuario == 1){
      cadastroDePaciente();
  }
return 0;

}




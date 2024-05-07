#include <stdio.h>
#include <stdlib.h>
#include "projeto.h"

int menu(){
  printf("--------------------");
  printf("\nSistema GSS.\n\n");
  printf("Bem vindo ao Sistema, escolha abaixo para onde gostaria de ser direcionado: \n\n");
  printf("1 - Cadastro pacientes.\n");
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


int menuCadastroPaciente(){

  int escolhaUsuario;
  printf("\nMenu de Cadastro.\n\n");
  printf("1 - Opções de cadastrar novo paciente.\n");
  printf("2 - Mostrar banco de cadastros atual.\n");
  printf("Escolha: ");
  scanf("%d", &escolhaUsuario);

  getchar(); 
  if (escolhaUsuario == 1){
      cadastroDePaciente();
  }

  else if (escolhaUsuario == 2){
      mostraCadastros();
  }


  return 0;

}


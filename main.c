#include "projeto.h"
#include <stdio.h>

int main(){
  int escolhaDoUsuaro;
  do  {

    escolhaDoUsuaro = menu();

    if (escolhaDoUsuaro == 0){
      sair();
    }

    else if (escolhaDoUsuaro == 1){
      cadastroDePaciente();
    }

    else if( escolhaDoUsuaro ==2){
      enfileiramento();
    }

    else if( escolhaDoUsuaro ==3){
      arvorismo();
    }

  } while (escolhaDoUsuaro!=0);


}


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
      menuCadastroPaciente();
    }


  } while (escolhaDoUsuaro!=0);


}

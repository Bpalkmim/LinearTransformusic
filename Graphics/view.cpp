#include "view.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

void createMode(void)
{

}

void openMusicalFile(void)
{


}

// Janela de fechamento da aplicaçao
void closeApplication(void)
{
	char command;
	cout << "Fechando a aplicacao. Tem certeza? [s/n]"
	<< endl;
	cin >> command;

	switch(command) {
		case 's':
		case 'S':
			exit(1);
			break;
		default:
			// Volta ao Menu principal
			break;
	}
}

void showMenu(void)
{
	char userInput;

	do {
		cout << "\n\nBem-vindo ao LinearTransformusic!\n\n"
		<< "Menu principal\n"
		<< "Comandos:\n"
		<< "c - Criar musica para salvar em um arquivo\n"
		<< "a - Abrir musica de um arquivo\n"
		<< "f - Fechar aplicacao\n"
		<< endl;
		cin >> userInput;

		switch(userInput) {
			case 'c':
			case 'C':
					createMode();
				break;
			case 'a':
			case 'A':
					openMusicalFile();
				break;
			case 'f':
			case 'F':
					closeApplication();
				break;
			default:
				cout << "Comando invalido, tente novamente!\n" << endl;
				break;
		}
	} while(true);
}
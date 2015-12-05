#include "view.h"
#include "../LinAlgebra/matrix.h"
#include "../Music/music.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

// Matriz a ser utilizada pelo modulo. Pode ser criada pelo usuario ou lida de um arquivo.
Matrix<Input> * currentM;
Input ** contentM;
int index = 0;

// Abre um arquivo com valores inteiros e cria uma matriz unidimensional considerando-os
// os intervalos musicais
Matrix<Input> * openFile(char * fileName) {
	// TODO
	return NULL;
}

// Salva a matriz corrente num arquivo
bool saveFile(char * fileName) {

	// TODO
	return true;
}

// Modo de inserçao de notas
void insertMode(void) {
	int interval;

	cout << "-> Modo de insercao\n"
	<< "Insira um valor inteiro:\n"
	<< endl;
	cin >> interval;

	if (index == 0) {
		contentM = new Input*[200]; // Tamanho provisorio
		contentM[index++] = makeInput(NULL, interval);
	}
	else {
		contentM[index] = makeInput(contentM[index-1], interval);
		index++;
	}
}

// Modo de visualizaçao de musica
void visualizeMode(void) {
	// TODO
}

// Modo de salvamento de musica em um arquivo
void saveMode(void) {
	char fileName[40];
	cout << "-> Escreva o nome do arquivo a ser salvo:\n" << endl;
	cin >> fileName;

	if (saveFile(fileName)) {
		cout << "Salvo com sucesso!\n" << endl;
	}
	else {
		cout << "Problemas ao salvar.\n" << endl;
	}
}

// Modo de criaçao de musica
void createMode(void)
{
	char command;

	do {
		cout << "-> Modo de criacao\n"
		<< "i - Inserir nova nota\n"
		<< "v - Ir para o modo de visualizacao\n"
		<< "s - Salvar musica atual em um arquivo\n"
		<< "m - Voltar ao menu principal\n"
		<< endl;
		cin >> command;

		switch(command) {
			case 'i':
			case 'I':
				insertMode();
				break;
			case 'v':
			case 'V':
				visualizeMode();
				break;
			case 's':
			case 'S':
				saveMode();
				break;
			case 'm':
			case 'M':
				// Volta ao menu principal
				break;
			default:
				cout << "Comando invalido, tente novamente!\n" << endl;
				break;
		}
	} while (command != 'm');
}

// Usuario escolheu abrir um arquivo texto com a musica dele (sequencia de inteiros
// representando os intervalos em semitons)
void openMusicalFile(void)
{
	char command;
	char fileName[40];

	do {
		cout << "-> Escreva o nome do arquivo a ser aberto.\n";
		cin >> fileName;

		currentM = openFile(fileName);

		if (currentM == NULL) {
			cout << "Arquivo invalido. Tente novamente.\n" << endl;
		}
		else {
			do {
				cout << "-> Escolha uma acao para a musica lida do arquivo " << fileName << ".\n"
				<< "v - Ir para o modo de visualizacao\n"
				<< "m - Voltar ao menu principal\n"
				<< endl;
				cin >> command;

				switch(command) {
					case 'v':
					case 'V':
						visualizeMode();
						break;
					case 'm':
					case 'M':
						// Volta ao menu principal
						break;
					default:
						cout << "Comando invalido, tente novamente!\n" << endl;
						break;
				}
			}  while (command != 'm');
		}
	}  while (command != 'm');
}

// Janela de fechamento da aplicaçao
void closeApplication(void)
{
	char command;
	cout << "Fechando a aplicacao. Tem certeza? [s/n]\n" << endl;
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
		cout << "-----------------------------------------\n"
		<< "--- Bem-vindo ao LinearTransformusic! ---\n"
		<< "-----------------------------------------\n"
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
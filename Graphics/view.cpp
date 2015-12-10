#include "view.h"
#include "../LinAlgebra/matrix.h"
#include "../Music/music.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>

using namespace std;

// Matriz a ser utilizada pelo modulo. Pode ser criada pelo usuario ou lida de um arquivo.
Matrix<Input> * currentM;
Input ** contentM;
int index = 0;

// Abre um arquivo com valores inteiros e cria uma matriz unidimensional considerando-os
// os intervalos musicais
Matrix<Input> * openFile(string fileName)
{
	ifstream iFile;
	iFile.open(fileName.c_str());
	if (!iFile.is_open()) {
		return NULL;
	}

	int numRow, numCol;
	iFile >> numRow;
	iFile >> numCol;

	contentM = new Input*[numRow];
	int aux;
	for (int i = 0; i < numRow; i++) {
		iFile >> aux;
		contentM[i] = (i == 0)? makeInput(NULL, aux) : makeInput(contentM[index-1], aux);
	}

	return new Matrix<Input>(numRow, numCol, contentM);
}

// Salva a matriz corrente num arquivo
bool saveFile(string fileName)
{
	ofstream oFile;

	if (currentM == NULL) {
		cout << "Nao existe musica a ser salva.\n" << endl;
		return false;
	}

	oFile.open(fileName.c_str());
	if (!oFile.is_open()) {
		return false;
	}

	Input ** aux = currentM->getContent();
	oFile << currentM->getNumRow() << " " << currentM->getNumCol() << endl;
	for (int i = 0; i < currentM->getNumRow(); i++) {
		for (int j = 0; j < currentM->getNumCol(); j++) {
			oFile << aux[i][j].interval << " ";
		}
		oFile << "\n";
	}

	oFile.close();
	return true;
}

// Modo de inserçao de notas
void insertMode(void)
{
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
void visualizeMode(void)
{
	Matrix<Input> * temp = oneDimToTwoDim(currentM);

	Input ** twoDim = temp->getContent();
	Input ** oneDim = currentM->getContent();

	cout << "Sua musica:" << endl;

	for (int i = 0; i < currentM->getNumRow(); i++) {
		cout << "\t";

		switch(oneDim[i][0].note) {
			case C:
			default:
				cout << "C";
				break;
			case D:
				cout << "D";
				break;
			case E:
				cout << "E";
				break;
			case F:
				cout << "F";
				break;
			case G:
				cout << "G";
				break;
			case A:
				cout << "A";
				break;
			case B:
				cout << "B";
				break;
		}

		switch(oneDim[i][0].accidental) {
			case NATURAL:
			default:
				cout << " ";
				break;
			case SHARP:
				cout << "#";
				break;
			case FLAT:
				cout << "b";
				break;
		}

		cout << "\t";

		if (i > 0) {
			cout << "Intervalo: ";
			if (oneDim[i][0].interval > 0) {
				cout << "+";
			}
			cout << oneDim[i][0].interval;
			cout << " semitons.\t";

			cout << "Passos: ";
			if (oneDim[i][0].interval > 0) {
				cout << "+";
			}
			// Os passos na escala devem ser a soma de tons e semitons,
			// conforme esperado pela transformaçao de intervalo em semi-
			// tons para semitons + tons.
			cout << twoDim[i][0].interval + twoDim[i][1].interval << endl;
		}
	}
}

// Modo de salvamento de musica em um arquivo
void saveMode(void)
{
	string fileName = "";
	cout << "-> Escreva o nome do arquivo a ser salvo:\n" << endl;
	getline(cin, fileName);

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
cout << "PASSEI";
		switch(command) {
			case 'i':
			case 'I':
				insertMode();
				break;
			case 'v':
			case 'V':
cout << "PASSEI";
				currentM = new Matrix<Input>(index + 1, 1, contentM);
cout << "PASSEI";
				visualizeMode();
				break;
			case 's':
			case 'S':
				currentM = new Matrix<Input>(index + 1, 1, contentM);
				saveMode();
				break;
			case 'm':
			case 'M':
				// Volta ao menu principal
				currentM = new Matrix<Input>(index + 1, 1, contentM);
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
	string fileName = "";

	do {
		cout << "-> Escreva o nome do arquivo a ser aberto.\n";
		getline(cin, fileName);
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
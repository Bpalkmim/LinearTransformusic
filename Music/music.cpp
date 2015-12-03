#include "music.h"
#include <iostream>

Input operator*(const int &former, const Input &latter)
{
	return Input(latter.type, former * latter.interval, latter.note, latter.accidental);
}

Input * makeInput(Input * previous, int interval)
{
	Note currentNote;
	Accidental currentAccidental;

	switch(interval) {
		case 0:
			currentNote = previous->note;
			currentAccidental = previous->accidental;
			break;
		case 1:
			break;


			// COMPLETAR.
			// AQUI FICA O CALCULO LOUCO DE SABER QUAL A NOTA

	}

	return new Input(SEMITONE, interval, currentNote, currentAccidental);
}

// Observaçao: as matrizes que representam uma musica sao divididas em colunas.
// Cada coluna tem um tipo (e.g. no caso da de duas dimensoes, a primeira coluna
// representa semitons e a segunda, tons).
Matrix<Input> * oneDimToTwoDim(Matrix<Input> * entry)
{
	Input ** result = new Input*[entry->getNumRow()];

	for (int i = 0; i < entry->getNumRow(); i++) {
		result[i] = new Input[entry->getNumCol()];
		switch(entry->getContent()[i]->interval) {
			case 0:
					result[i][0].interval = 0;
					result[i][1].interval = 0;
				break;
			case 1:
					result[i][0].interval = 1;
					result[i][1].interval = 0;
				break;
			case 2:
					result[i][0].interval = 0;
					result[i][1].interval = 1;
				break;
			case 3:
					result[i][0].interval = 1;
					result[i][1].interval = 1;
				break;
			case 4:
					result[i][0].interval = 2;
					result[i][1].interval = 1;
				break;
			case 5:
					result[i][0].interval = 1;
					result[i][1].interval = 2;
				break;
			case 6:
					// Tratando sempre como quarta aumentada
					result[i][1].interval = 0;
					result[i][1].interval = 3;
				break;
			case 7:
					result[i][0].interval = 1;
					result[i][1].interval = 3;
				break;
			case 8:
					result[i][0].interval = 2;
					result[i][1].interval = 3;
				break;
			case 9:
					result[i][0].interval = 1;
					result[i][1].interval = 4;
				break;
			case 10:
					result[i][0].interval = 2;
					result[i][1].interval = 4;
				break;
			case 11:
					result[i][0].interval = 3;
					result[i][1].interval = 4;
				break;
			case -1:
					result[i][0].interval = -1;
					result[i][1].interval = 0;
				break;
			case -2:
					result[i][0].interval = 0;
					result[i][1].interval = -1;
				break;
			case -3:
					result[i][0].interval = -1;
					result[i][1].interval = -1;
				break;
			case -4:
					result[i][0].interval = 0;
					result[i][1].interval = -2;
				break;
			case -5:
					result[i][0].interval = -1;
					result[i][1].interval = -2;
				break;
			case -6:
					// Tratando sempre como quarta aumentada
					result[i][0].interval = 0;
					result[i][1].interval = -3;
				break;
			case -7:
					result[i][0].interval = -1;
					result[i][1].interval = -3;
				break;
			case -8:
					result[i][0].interval = -2;
					result[i][1].interval = -3;
				break;
			case -9:
					result[i][0].interval = -1;
					result[i][1].interval = -4;
				break;
			case -10:
					result[i][0].interval = -2;
					result[i][1].interval = -4;
				break;
			case -11:
					result[i][0].interval = -3;
					result[i][1].interval = -4;
				break;
		}
	}

	// Apenas consertando os tipos das matrizes
	for (int i = 0; i < entry->getNumRow(); i++) {
		result[i][0].type = SEMITONE;
		result[i][1].type = TONE;
	}

	return new Matrix<Input>(entry->getNumRow(), entry->getNumCol(), result);
}

Matrix<Input> * twoDimToOneDim(Matrix<Input> * entry)
{
	Matrix<Input> * result;
	int ** transf = new int*[1];
	transf[0] = new int[2];
	transf[0][0] = 1;
	transf[0][1] = 2;
	result = multiply(new Matrix<int>(2, 1, transf), entry);	

	// Apenas consertando os tipos das matrizes
	for (int i = 0; i < result->getNumRow(); i++) {
		result->getContent()[i][0].type = SEMITONE;
	}

	return result;
}
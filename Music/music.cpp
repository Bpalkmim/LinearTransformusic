#include "music.h"
#include <iostream>

Input operator*(const int &former, const Input &latter)
{
	return Input(latter.type, former * latter.interval, latter.note, latter.accidental);
}

// Cria um novo Input, dependendo do Input anterior e um intervalo musical em semitons
// Como a musica tonal segue aritmetica modular (modulo 12), os casos x e -(12 - x) sao
// iguais (0 <= x < 12).
Input * makeInput(Input * previous, int interval)
{
	Note currentNote = C;
	Accidental currentAccidental = NATURAL;

	if (previous == NULL) {
		previous = new Input();
	}

	switch(interval) {
		case 0:
		default:
			currentNote = previous->note;
			currentAccidental = previous->accidental;
			break;
		case 1:
		case -11:
			if (previous->accidental == SHARP) {
				currentNote = (Note) ((previous->note + 1) % 7);
				currentAccidental = NATURAL;
			}
			else if (previous->accidental == NATURAL) {
				if (previous-> note == E) {
					currentNote = F;
					currentAccidental = previous->accidental;
				}
				else if (previous->note == B) {
					currentNote = C;
					currentAccidental = previous->accidental;
				}
				else {
					currentNote = previous->note;
					currentAccidental = SHARP;
				}
			}
			else { // previous->accidental == FLAT
				currentNote = previous->note;
				currentAccidental = FLAT;
			}
			break;
		case 2:
		case -10:
			if (previous->accidental == SHARP) {
				if (previous->note == D) {
					currentNote = F;
					currentAccidental = NATURAL;
				}
				else if (previous->note == A) {
					currentNote = C;
					currentAccidental = NATURAL;
				}
				else { // C#, F# ou G#
					currentNote = (Note) ((previous->note + 1) % 7);
					currentAccidental = SHARP;
				}
			}
			else if (previous->accidental == NATURAL) {
				currentNote = (Note) ((previous->note + 1) % 7);
				if (previous-> note == E || previous->note == B) {
					currentAccidental = SHARP;
				}
				else {
					currentAccidental = previous->accidental;
				}
			}
			else { // previous->accidental == FLAT
				currentNote = (Note) ((previous->note + 1) % 7);
				if (previous-> note == E || previous->note == B) {
					currentAccidental = NATURAL;
				}
				else {
					currentAccidental = previous->accidental;
				}
			}
			break;
		case 3:
		case -9:
			if (previous->accidental == SHARP) {
				currentNote = (Note) ((previous->note + 2) % 7);
				if (previous->note == D || previous->note == A) {
					currentAccidental = SHARP;
				}
				else { // C#, F# ou G#
					currentAccidental = NATURAL;
				}
			}
			else if (previous->accidental == NATURAL) {
				currentNote = (Note) ((previous->note + 2) % 7);
				if (previous-> note == C || previous->note == F || previous->note == G) {
					currentAccidental = FLAT;
				}
				else {
					currentAccidental = previous->accidental;
				}
			}
			else { // previous->accidental == FLAT
				if (previous-> note == E || previous->note == B) {
					currentNote = (Note) ((previous->note + 2) % 7);
					currentAccidental = previous->accidental;
				}
				else {
					currentNote = (Note) ((previous->note + 1) % 7);
					currentAccidental = NATURAL;
				}
			}
			break;
		case 4:
		case -8:
			if (previous->accidental == SHARP) {
				if (previous->note == F) {
					currentNote = A;
					currentAccidental = SHARP;
				}
				else {
					currentNote = (Note) ((previous->note + 3) % 7);
					currentAccidental = NATURAL;
				}
			}
			else if (previous->accidental == NATURAL) {
				currentNote = (Note) ((previous->note + 2) % 7);
				if (previous-> note == C || previous->note == G || previous->note == A) {
					currentAccidental = previous->accidental;
				}
				else {
					currentAccidental = SHARP;
				}
			}
			else { // previous->accidental == FLAT
				currentNote = (Note) ((previous->note + 2) % 7);
				if (previous-> note == G) {
					currentAccidental = previous->accidental;
				}
				else {
					currentAccidental = NATURAL;
				}
			}
			break;
		case 5:
		case -7:
			if (previous->accidental == SHARP) {
				currentNote = (Note) ((previous->note + 3) % 7);
				if (previous->note == F) {
					currentAccidental = NATURAL;
				}
				else {
					currentAccidental = previous->accidental;
				}
			}
			else if (previous->accidental == NATURAL) {
				currentNote = (Note) ((previous->note + 3) % 7);
				if (previous-> note == F) {
					currentAccidental = FLAT;
				}
				else {
					currentAccidental = previous->accidental;
				}
			}
			else { // previous->accidental == FLAT
				if (previous-> note == G) {
					currentNote = B;
					currentAccidental = NATURAL;
				}
				else {
					currentNote = (Note) ((previous->note + 3) % 7);
					currentAccidental = previous->accidental;
				}
			}
			break;
		case 6:
		case -6:
			if (previous->accidental == SHARP) {
				currentNote = (Note) ((previous->note + 4) % 7);
				currentAccidental = NATURAL;
			}
			else if (previous->accidental == NATURAL) {
				if (previous->note == F) {
					currentNote = B;
					currentAccidental = NATURAL;
				}
				else if (previous->note == B) {
					currentNote = F;
					currentAccidental = NATURAL;
				}
				else {
					currentNote = (Note) ((previous->note + 3) % 7);
					currentAccidental = SHARP;
				}
			}
			else { // previous->accidental == FLAT
				currentNote = (Note) ((previous->note + 3) % 7);
				currentAccidental = NATURAL;
			}
			break;
		case 7:
		case -5:
			if (previous->accidental == SHARP) {
				if (previous->note == A) {
					currentNote = F;
					currentAccidental = NATURAL;
				}
				else {
					currentNote = (Note) ((previous->note - 3 + 7) % 7);
					currentAccidental = previous->accidental;
				}
			}
			else if (previous->accidental == NATURAL) {
				currentNote = (Note) ((previous->note - 3 + 7) % 7);
				if (previous-> note == B) {
					currentAccidental = SHARP;
				}
				else {
					currentAccidental = previous->accidental;
				}
			}
			else { // previous->accidental == FLAT
				currentNote = (Note) ((previous->note - 3 + 7) % 7);
				if (previous-> note == B) {
					currentAccidental = NATURAL;
				}
				else {
					currentAccidental = previous->accidental;
				}
			}
			break;
		case 8:
		case -4:
			if (previous->accidental == SHARP) {
				currentNote = (Note) ((previous->note - 2 + 7) % 7);
				if (previous-> note == A) {
					currentAccidental = previous->accidental;
				}
				else {
					currentAccidental = NATURAL;
				}
			}
			else if (previous->accidental == NATURAL) {
				currentNote = (Note) ((previous->note - 2 + 7) % 7);
				if (previous-> note == E || previous->note == A || previous->note == B) {
					currentAccidental = previous->accidental;
				}
				else {
					currentAccidental = FLAT;
				}
			}
			else { // previous->accidental == FLAT
				if (previous->note == B) {
					currentNote = G;
					currentAccidental = previous->accidental;
				}
				else {
					currentNote = (Note) ((previous->note - 3 + 7) % 7);
					currentAccidental = NATURAL;
				}
			}
			break;
		case 9:
		case -3:
			if (previous->accidental == SHARP) {
				if (previous-> note == C || previous->note == F) {
					currentNote = (Note) ((previous->note - 2 + 7) % 7);
					currentAccidental = previous->accidental;
				}
				else {
					currentNote = (Note) ((previous->note - 1 + 7) % 7);
					currentAccidental = NATURAL;
				}
			}
			else if (previous->accidental == NATURAL) {
				currentNote = (Note) ((previous->note - 2 + 7) % 7);
				if (previous-> note == E || previous->note == A || previous->note == B) {
					currentAccidental = SHARP;
				}
				else {
					currentAccidental = previous->accidental;
				}
			}
			else { // previous->accidental == FLAT
				currentNote = (Note) ((previous->note - 2 + 7) % 7);
				if (previous->note == D || previous->note == G) {
					currentAccidental = FLAT;
				}
				else { // Eb, Ab ou Bb
					currentAccidental = NATURAL;
				}
			}
			break;
		case 10:
		case -2:
			if (previous->accidental == SHARP) {
				currentNote = (Note) ((previous->note - 1 + 7) % 7);
				if (previous-> note == C || previous->note == F) {
					currentAccidental = NATURAL;
				}
				else {
					currentAccidental = previous->accidental;
				}
			}
			else if (previous->accidental == NATURAL) {
				currentNote = (Note) ((previous->note - 1 + 7) % 7);
				if (previous-> note == C || previous->note == F) {
					currentAccidental = FLAT;
				}
				else {
					currentAccidental = previous->accidental;
				}
			}
			else { // previous->accidental == FLAT
				if (previous->note == D) {
					currentNote = B;
					currentAccidental = NATURAL;
				}
				else if (previous->note == G) {
					currentNote = E;
					currentAccidental = NATURAL;
				}
				else { // Eb, Ab ou Bb
					currentNote = (Note) ((previous->note - 1 + 7) % 7);
					currentAccidental = FLAT;
				}
			}
			break;
		case 11:
		case -1:
			if (previous->accidental == SHARP) {
				currentNote = previous->note;
				currentAccidental = NATURAL;
			}
			else if (previous->accidental == NATURAL) {
				if (previous-> note == F) {
					currentNote = E;
					currentAccidental = previous->accidental;
				}
				else if (previous->note == C) {
					currentNote = B;
					currentAccidental = previous->accidental;
				}
				else {
					currentNote = previous->note;
					currentAccidental = FLAT;
				}
			}
			else { // previous->accidental == FLAT
				currentNote = (Note) ((previous->note - 1 + 7) % 7);
				currentAccidental = FLAT;
			}
			break;
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
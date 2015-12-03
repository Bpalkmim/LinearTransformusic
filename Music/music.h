#ifndef MUSIC_H
#define MUSIC_H

#include "../LinAlgebra/matrix.h"

enum intervalType {
	SEMITONE = 0,
	TONE
};

enum note {
	C = 0,
	D,
	E,
	F,
	G,
	A,
	B
};

enum accidental {
	NATURAL = 0,
	SHARP,
	FLAT
};

// Definicao dos tipos das matrizes.
typedef enum intervalType IntervalType;
typedef enum note Note;
typedef enum accidental Accidental;

// A classe Input representa o intervalo com relaçao a nota anterior, o nome e o acidente
// (caso ocorra) da nota representada, alem de dizer se o intervalo e em semitons ou tons
class Input
{
	public:
		Input(IntervalType interType, int inter, Note note, Accidental acc) 
			: type(interType), interval(inter), note(note), accidental(acc) {}
		Input() { this->type = SEMITONE; this->interval = 0; this->note = C; this->accidental = NATURAL; }

		IntervalType type;
		int interval;
		Note note;
		Accidental accidental;
};

// Sobrecarga do operador de multiplicaçao para inteiros com Input, com resultado Input
Input operator*(const int &former, const Input &latter);

// Cria um Input a partir de um intervalo recebido e o Input anterior
Input * makeInput(Input * previous, int interval);

// Funcoes de transformaçao entre dimensoes
// 1D -> 2D
Matrix<Input> * oneDimToTwoDim(Matrix<Input> * entry);

// 2D -> 1D
Matrix<Input> * twoDimToOneDim(Matrix<Input> * entry);

#endif
#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>

using namespace std;

// Classe que representa uma Matriz (cada coluna pode ter um tipo diferente)
template<typename T>
class Matrix
{
	public:
		Matrix(int numR, int numC, T ** content)
			: numRow(numR), numCol(numC), content(content) {}
		~Matrix();

		int getNumRow() { return this->numRow; }
		int getNumCol() { return this->numCol; }
		T ** getContent() { return this->content; }

	private:
		int numRow;
		int numCol;
		T ** content;
};

template<typename T>
Matrix<T>::~Matrix()
{
	for (int i = 0; i < this->numRow; i++) {
		delete [] this->content[i];
	}
	delete [] this->content;
}

// Funçao que multiplica duas matrizes, realizando checagem de tipos e tamanhos
// Retorna null caso os tamanhos nao batam
template<typename T, typename U>
Matrix<U> * multiply(Matrix<T> * first, Matrix<U> * second)
{
	// Verifica se o numero de colunas da primeira sao iguais ao de linhas da segunda
	if (first->getNumCol() != second->getNumRow()) {
		return NULL;
	}

	U ** result = new U*[first->getNumRow()];
	for (int i = 0; i < first->getNumRow(); i++) {
  		result[i] = new U[second->getNumCol()];
	}

	T ** firstM = first->getContent();
	U ** secondM = second->getContent(); 
	// algoritmo naive de multiplicaçao de matrizes
	for (int i = 0; i < first->getNumRow(); i++) {
		for (int j = 0; j < second->getNumCol(); j++) {
			for (int k = 0; k < first->getNumCol(); k++) {
				// Caso a multiplicaçao nao esteja definida para os tipos T e U com resultado em U,
				// aqui ocorrera um erro
				result[i][j] = firstM[i][k] * secondM[k][j];
			}
		}
	}

	return new Matrix<U>(first->getNumRow(), second->getNumCol(), result);
}

#endif
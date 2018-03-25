#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "Matrix.h"

Matrix::Matrix(int numLines, int numCols){
    cout << "Creating a matrix " << numLines << "x" << numCols << endl;
    numberOfLines = numLines;
    numberOfColumns = numCols;
    matrix = new int*[numberOfLines];
    for (int i = 0 ; i < numberOfLines; i++){
        matrix[i] = new int[numberOfColumns];
    }
}

Matrix::Matrix(){

}

Matrix::Matrix(int** matrix){
    this->matrix = matrix;
}

void Matrix::fillMatrix(){
    for (int line = 0; line < numberOfLines; line++){
        for (int column = 0; column < numberOfColumns; column++){
            cout << "Insert a number for the position " << line << column << endl ;
            cin >> matrix[line][column];
        }
    }
}

void Matrix::fillMatrixWithRandom(){
    srand(time(NULL));
    for (int line = 0; line < numberOfLines; line++){
        for (int column = 0; column < numberOfColumns; column++){
            matrix[line][column] = (rand() + 42) % 10 ;
        }
    }
}

void Matrix::fillMatrixWithRandom(int maxNumber){
    srand(NULL);
    for (int line = 0; line < numberOfLines; line++){
        for (int column = 0; column < numberOfColumns; column++){
            matrix[line][column] = (rand() + 42) % maxNumber;
        }
    }
}

void Matrix::insertIntoPosition(int line, int col, int value){
    matrix[line][col] = value;
}

Matrix::~Matrix(){
    delete[] matrix;
}

int Matrix::getCols(){
    return numberOfColumns;
}

int Matrix::getLines(){
    return numberOfLines;
}

int** Matrix::getMatrixPrimitive(){
    return matrix;
}

Matrix& Matrix::getMatrix(){
    return *this;
}

int Matrix::getValue(int line, int col){
    return matrix[line][col];
}

void Matrix::printMatrix(){
    for(int i = 0; i < numberOfLines; i++){
        for (int j = 0; j < numberOfColumns; j++){
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

ostream& operator<<(ostream& output, Matrix& matrix){
    int numberOfLines = matrix.getLines();
    int numberOfColumns = matrix.getCols();
    for(int i = 0; i < numberOfLines; i++){
        for (int j = 0; j < numberOfColumns; j++){
            output << matrix.getValue(i,j) << " ";
        }
        output << "\n";
    }
    return output;
}

Matrix& Matrix::operator*(Matrix& m2){
    int numLinesM1 = this->getLines();
    int numColsM1 = this->getCols();
    int numColsM2 = m2.getCols();
    Matrix* matrixResult = new Matrix(numLinesM1,numColsM2);
    if (numLinesM1 != numColsM2){
        throw Exception(multiplyDiffColLine,__LINE__);
    }
    for (int line = 0; line < numLinesM1; line++){
        for (int column = 0; column < numColsM2; column++){
            int sum = 0;
            for (int index = 0 ; index < numColsM1 ;index++){
                sum +=  this->getValue(line,index) * m2.getValue(index,column);
            }
            matrixResult->insertIntoPosition(line,column,sum);
        }
    }
    return *matrixResult;
}

Matrix& Matrix::operator+(Matrix& m2){
    int numLinesM1 = this->getLines();
    int numColsM1 = this->getCols();
    int numLinesM2 = m2.getLines();
    int numColsM2 = m2.getCols();
    Matrix* matrixResult = new Matrix(numLinesM1, numColsM1);

    if (numLinesM1 != numLinesM2 || numColsM1 != numColsM2){
        throw Exception(incompatibleMatrices,__LINE__);
    }

    for (int line = 0; line < numLinesM1; line++){
        for(int column = 0; column < numColsM1; column++){
            int sum = this->getValue(line,column) + m2.getValue(line,column);
            matrixResult->insertIntoPosition(line,column,sum);
        }
    }
    return *matrixResult;
}

Matrix& Matrix::operator-(Matrix& m2){
    int numLinesM1 = this->getLines();
    int numColsM1 = this->getCols();
    int numLinesM2 = m2.getLines();
    int numColsM2 = m2.getCols();
    cout << numColsM2 << endl;
    Matrix* matrixResult = new Matrix(numLinesM1, numColsM1);

    if (numLinesM1 != numLinesM2 || numColsM1 != numColsM2){
        throw Exception(incompatibleMatrices,__LINE__);
    }

    for (int line = 0; line < numLinesM1; line++){
        for(int column = 0; column < numColsM1; column++){
            int sum = this->getValue(line,column) - m2.getValue(line,column);
            matrixResult->insertIntoPosition(line,column,sum);
        }
    }
    return *matrixResult;
}




Exception::Exception(Exceptions exception, int line){
	this->exception = exception;
	this->line = line;
}

string Exception::message(){
	stringstream stream;
	stream << "A problem has ocurred on line " << line << ": ";
	switch(exception){
		case incompatibleMatrices:
			stream << "To perform an operation on two matrices, both must have the same proportions ";
			break;
        case multiplyDiffColLine:
            stream << "To perform a multiplication on two matrices, the number of rows in the first matrix must be equal to the number of columns in the second matrix";
            break;
        default :
            stream << "Undefined problem";
            break;
	}
	return stream.str();
 }

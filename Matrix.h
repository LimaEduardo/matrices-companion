#ifndef MATRIX_H
#define MATRIX_H 1

#include <sstream>
#include <string>

using namespace std;


enum Exceptions {incompatibleMatrices, multiplyDiffColLine};

class Exception{
private:
    Exceptions exception;
    int line;

public:
    Exception(Exceptions exception, int line);
    string message();
};


class Matrix{
private:
    static const int defaultNumberLines = 4;
    static const int defaultNumberColumns = 4;
    int numberOfLines;
    int numberOfColumns;
    int **matrix;


public:
    Matrix();
    Matrix(int numLines, int numCols);
    Matrix(int** matrix);
    ~Matrix();
    void fillMatrix();
    void fillMatrixWithRandom();
    void fillMatrixWithRandom(int maxNumber);
    void printMatrix();
    void insertIntoPosition(int line, int col, int value);
    int getCols();
    int getLines();
    int** getMatrixPrimitive();
    Matrix& getMatrix();
    int getValue(int line, int col);
    Matrix& operator*(Matrix& m2);
    Matrix& operator+(Matrix& m2);
    Matrix& operator-(Matrix& m2);
    friend ostream& operator<<(ostream& output, Matrix& matrix);
};

#endif

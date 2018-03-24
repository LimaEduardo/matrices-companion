#ifndef MATRIX_H
#define MATRIX_H 1

using namespace std;

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
    ~Matrix();
    void fillMatrix();
    void printMatrix();
    void insertIntoPosition(int line, int col, int value);
    int getCols();
    int getLines();
    int** getMatrix();
    int getValue(int line, int col);
    Matrix& operator*(Matrix m2);
};

#endif

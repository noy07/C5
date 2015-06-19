#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <algorithm>
#include "matrix_project.hpp"

using std::string;
using namespace std;

static void print_matrix(int* m, int r, int c) {
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			cout << *(m + (c * i + j)) << " ";
		}
		cout << endl;
	}
}

Matrix::Matrix(string matrix_str1) :
		matrix_str(matrix_str1) {
	//update rowNum
	rowsNum = count(matrix_str1.begin(), matrix_str1.end(), ';') + 1;

	//split to rows (by ";")
	string row_str = matrix_str1.substr(1, matrix_str1.size() - 2);
	for (int i = 0; i < rowsNum; i++) {
		string row = row_str.substr(0, row_str.find(";"));
		row_str = row_str.substr(row_str.find(";") + 1, row_str.size() - 1);

		//split to cols (by ",")
		string col_str = row;
		for (int j = 0; j < colsNum; j++) {
			string col = col_str.substr(0, col_str.find(","));
			*(matrix + (colsNum * i + j)) = atoi(col.c_str());
			col_str = col_str.substr(col_str.find(",") + 1, col_str.size() - 1);
		}
	}
}

bool Matrix::is_legal(string matrix1) {
	//update rowNum
	rowsNum = count(matrix1.begin(), matrix1.end(), ';') + 1;

	//split to rows (by ";")
	string row_str = matrix1.substr(1, matrix1.size() - 2);
	for (int i = 0; i < rowsNum; i++) {
		string row = row_str.substr(0, row_str.find(";"));
		row_str = row_str.substr(row_str.find(";") + 1, row_str.size() - 1);

		//split to cols (by ",")
		if (i == 0) {
			colsNum = count(row.begin(), row.end(), ',') + 1;
		} else {
			if (colsNum != count(row.begin(), row.end(), ',') + 1) {
				return false;
			}
		}
	}
	return true;
}

int Matrix::rows_number() {
	return rowsNum;
}

int Matrix::cols_number() {
	return colsNum;
}

int* Matrix::plus_matrixes(string matrix1, string matrix2) {
	Matrix m1(matrix1);
	Matrix m2(matrix2);
		int* plusMatrix = (int*) malloc(
				sizeof(int) * (m1.rowsNum * m1.colsNum));
		for (int i = 0; i < (m1.rowsNum * m1.colsNum); i++) {
			*(plusMatrix + i) = *(m1.matrix + i) + *(m2.matrix + i);
		}
		return plusMatrix;
}

int* Matrix::minus_matrixes(string matrix1, string matrix2) {
	Matrix m1(matrix1);
	Matrix m2(matrix2);
	int* minusMatrix = (int*) malloc(sizeof(int) * (m1.rowsNum * m1.colsNum));
	for (int i = 0; i < (m1.rowsNum * m1.colsNum); i++) {
		*(minusMatrix + i) = *(m1.matrix + i) - *(m2.matrix + i);
	}
	return minusMatrix;
}

int* Matrix::mult_matrixes(string matrix1, string matrix2) {
	Matrix m1(matrix1);
	Matrix m2(matrix2);
	int index = 0;
	int* multMatrix = (int*) malloc(sizeof(int) * (m1.rowsNum * m2.colsNum));
	for (int i = 0; i < m1.rowsNum; i++) {
		for (int j = 0; j < m2.colsNum; j++) {
			int rowSum = 0;
			for (int k = 0; k < m1.colsNum; k++) {
				rowSum += (*(m1.matrix + (i * m1.colsNum) + k))
						* (*(m2.matrix + (k * m2.colsNum) + j));
			}
			*(multMatrix + index) = rowSum;
			index++;
		}
	}
	return multMatrix;
}

void Matrix::change_value(string matrix1, int i, int j, int value) {
	Matrix m(matrix1);
	print_matrix(m.matrix, m.rowsNum, m.colsNum);
	*(m.matrix + ((i - 1) * m.colsNum) + j - 1) = value;
	print_matrix(m.matrix, m.rowsNum, m.colsNum);
}


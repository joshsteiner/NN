#pragma once

#include <vector>
#include <random>


using namespace std;


struct matrix_size_mismatch : public exception
{
	const char* what() const throw();
};


class matrix
{
	vector<vector<double>> data;
public:
	matrix(size_t m, size_t n);
	matrix(initializer_list<initializer_list<double>> init);
	double& at(size_t i, size_t j);
	size_t row_count();
	size_t column_count();
	matrix elem_mult(matrix &other);
	matrix T();
	matrix map(double(*f)(double));
};

matrix map2(double(*f)(double, double), matrix &A, matrix &B);

matrix operator+(matrix &A, matrix &B);
matrix operator-(matrix &A);
matrix operator-(matrix &A, matrix &B);
matrix operator*(double x, matrix &A);
matrix operator*(matrix &A, matrix &B);

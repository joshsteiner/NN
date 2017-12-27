#pragma once

#include <vector>
#include <random>


struct matrix_size_mismatch : public std::exception
{
	const char* what() const throw();
};


class matrix
{
	std::vector<std::vector<double>> data;
public:
	matrix();
	matrix(size_t m, size_t n);
	matrix(std::initializer_list<std::initializer_list<double>> init);
	inline double &at(size_t i, size_t j);
	inline double at(size_t i, size_t j) const;
	inline size_t row_count() const;
	inline size_t column_count() const;
	matrix elem_mult(const matrix &other) const;
	matrix T() const;
	matrix map(double(*f)(double)) const;
};

matrix map2(double(*f)(double, double), const matrix &A, const matrix &B);

matrix operator+(const matrix &A, const matrix &B);
matrix operator-(const matrix &A);
matrix operator-(const matrix &A, const matrix &B);
matrix operator*(double x, const matrix &A);
matrix operator*(const matrix &A, const matrix &B);

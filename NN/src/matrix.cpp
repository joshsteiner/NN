#include "matrix.h"

#include <cstdlib>
#include <cmath>
#include <random>


const char* matrix_size_mismatch::what() const throw() 
{
	return "matrices are incompatible in size";
}


matrix::matrix() {}


matrix::matrix(size_t m, size_t n)
{
	for (int i = 0; i < m; ++i)
	{
		data.push_back(std::vector<double>{});
		for (int j = 0; j < n; ++j)
		{
			long double r = std::rand() / 10'000.0;
			r -= std::floor(r);
			data.back().push_back(r);
		}
	}
}


matrix::matrix(std::initializer_list<std::initializer_list<double>> init)
{
	for (auto row : init)
	{
		data.push_back(std::vector<double>{});
		for (auto elem : row)
			data.back().push_back(elem);
	}
}


inline double& matrix::at(size_t i, size_t j)
{
	return data[i][j];
}


inline double matrix::at(size_t i, size_t j) const
{
	return data[i][j];
}


inline size_t matrix::row_count() const
{
	return data.size();
}


inline size_t matrix::column_count() const 
{
	return data[0].size();
}


matrix matrix::T() const
{
	matrix transposed(column_count(), row_count());

	for (int i = 0; i < row_count(); ++i)
		for (int j = 0; j < column_count(); ++j)
			transposed.at(j,i) = this->at(i,j);
			
	return transposed;
}


matrix matrix::map(double(*f)(double)) const
{
	matrix result(row_count(), column_count());

	for (int i = 0; i < row_count(); ++i)
		for (int j = 0; j < column_count(); ++j)
			result.at(i,j) = f(this->at(i,j));

	return result;
}


matrix map2(double(*f)(double, double), const matrix &A, const matrix &B)
{
	if (A.row_count() != B.row_count()
		|| A.column_count() != B.column_count())
		throw matrix_size_mismatch();

	matrix result(A.row_count(), A.column_count());

	for (int i = 0; i < A.row_count(); ++i)
		for (int j = 0; j < A.column_count(); ++j)
			result.at(i,j) = f(A.at(i,j), B.at(i,j));

	return result;
}


static inline double mult(double x, double y) { return x * y; }
matrix matrix::elem_mult(const matrix &other) const
{
	return map2(mult, *this, other);
}


matrix operator*(double x, const matrix &A)
{
	matrix result(A.row_count(), A.column_count());

	for (int i = 0; i < A.row_count(); ++i)
		for (int j = 0; j < A.column_count(); ++j)
			result.at(i,j) = x * A.at(i,j);

	return result;
}


matrix operator*(const matrix &A, const matrix &B)
{
	if (A.column_count() != B.row_count())
		throw matrix_size_mismatch();

	matrix result(A.row_count(), B.column_count());

	for (int i = 0; i < A.row_count(); ++i)
		for (int j = 0; j < B.column_count(); ++j)
		{
			double dot_product = 0;
			for (int k = 0; k < A.column_count(); ++k)
				dot_product += A.at(i,k) * B.at(k,j);
			result.at(i,j) = dot_product;
		}

	return result;
}


static inline double add(double x, double y) { return x + y; };
matrix operator+(const matrix &A, const matrix &B)
{
	return map2(add, A, B);
}


matrix operator-(const matrix &A)
{
	return (-1) * A;
}


matrix operator-(const matrix &A, const matrix &B)
{
	return A + (-B);
}

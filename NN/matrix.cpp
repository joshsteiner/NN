#include "matrix.h"

using namespace std;


const char* matrix_size_mismatch::what() const throw() 
{
	return "matrices are incompatible in size";
}


matrix::matrix(size_t m, size_t n)
{
	for (size_t i = 0; i < m; ++i)
	{
		data.push_back(vector<double>{});
		for (size_t j = 0; j < n; ++j)
		{
			double r = rand() / 10'000.0;
			r -= floor(r);
			data.back().push_back(r);
		}
	}
}


matrix::matrix(initializer_list<initializer_list<double>> init)
{
	for (auto row : init)
	{
		data.push_back(vector<double>{});
		for (auto elem : row)
			data.back().push_back(elem);
	}
}


double& matrix::at(size_t i, size_t j)
{
	return data[i][j];
}


size_t matrix::row_count()
{
	return data.size();
}


size_t matrix::column_count()
{
	return data[0].size();
}


matrix matrix::T()
{
	matrix transposed(column_count(), row_count());

	for (size_t i = 0; i < row_count(); ++i)
		for (size_t j = 0; j < column_count(); ++j)
			transposed.at(j, i) = this->at(i, j);

	return transposed;
}


matrix matrix::map(double(*f)(double))
{
	matrix result(row_count(), column_count());

	for (size_t i = 0; i < row_count(); ++i)
		for (size_t j = 0; j < column_count(); ++j)
			result.at(i, j) = f(this->at(i, j));

	return result;
}


matrix map2(double(*f)(double, double), matrix &A, matrix &B)
{
	if (A.row_count() != B.row_count()
		|| A.column_count() != B.column_count())
		throw matrix_size_mismatch();

	matrix result(A.row_count(), A.column_count());

	for (size_t i = 0; i < A.row_count(); ++i)
		for (size_t j = 0; j < A.column_count(); ++j)
			result.at(i, j) = f(A.at(i, j), B.at(i, j));

	return result;
}


double mult(double x, double y) { return x * y; }
matrix matrix::elem_mult(matrix &other)
{
	return map2(mult, *this, other);
}


matrix operator*(double x, matrix &A)
{
	matrix result(A.row_count(), A.column_count());

	for (size_t i = 0; i < A.row_count(); ++i)
		for (size_t j = 0; j < A.column_count(); ++j)
			result.at(i, j) = x * A.at(i, j);

	return result;
}


matrix operator*(matrix &A, matrix &B)
{
	if (A.column_count() != B.row_count())
		throw matrix_size_mismatch();

	matrix result(A.row_count(), B.column_count());

	for (size_t i = 0; i < A.row_count(); ++i)
		for (size_t j = 0; j < B.column_count(); ++j)
		{
			double dot_product = 0;
			for (size_t k = 0; k < A.column_count(); ++k)
				dot_product += A.at(i, k) * B.at(k, j);
			result.at(i, j) = dot_product;
		}

	return result;
}


double add(double x, double y) { return x + y; };
matrix operator+(matrix &A, matrix &B)
{
	return map2(add, A, B);
}


matrix operator-(matrix &A)
{
	return (-1) * A;
}


matrix operator-(matrix &A, matrix &B)
{
	return A + (-B);
}

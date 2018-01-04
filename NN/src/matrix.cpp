#include "matrix.h"

#include <cstdlib>
#include <cmath>
#include <random>


const char* matrix_size_mismatch::what() const throw()
{
	return "matrices are incompatible in size";
}


matrix::matrix() 
{
	ncol_ = 0;
	nrow_ = 0; 
	data_ = nullptr;
}


matrix::matrix(const matrix &other)
{
	ncol_ = other.ncol();
	nrow_ = other.nrow();
	data_ = new double[nrow() * ncol()];

	for (int i = 0; i < nrow() * ncol(); ++i)
		data_[i] = other.data()[i];
}


matrix::matrix(matrix &&other)
{
	ncol_ = other.ncol();
	nrow_ = other.nrow();
	data_ = other.data();
	other.data(nullptr);
}


matrix::matrix(size_t nrow, size_t ncol, bool rand_init)
{
	nrow_ = nrow; 
	ncol_ = ncol; 
	data_ = new double[ncol*nrow];

	if (rand_init)
	{
		for (int i = 0; i < ncol * nrow; ++i)
		{
			long double r = std::rand() - RAND_MAX / 2;
			r /= 10'000;
			data_[i] = r;
		}
	}
}


matrix::matrix(std::initializer_list<std::initializer_list<double>> init)
{
	nrow_ = init.size(); 
	ncol_ = init.begin()->size(); 
	data_ = new double[ncol() * nrow()];
	
	int it = 0;
	for (auto row : init)
		for (auto elem : row)
			data_[it++] = elem;
}


matrix::~matrix()
{
	delete[] data_;
}


matrix &matrix::operator=(const matrix &other)
{
	matrix temp = matrix(other);
	*this = std::move(temp);
	return *this;
}


matrix &matrix::operator=(matrix &&other)
{
	if (this != &other)
	{
		delete[] data_;
		data_ = other.data();
		ncol_ = other.ncol();
		nrow_ = other.nrow();
		other.data(nullptr);
	}
	return *this;
}


inline double& matrix::at(size_t i, size_t j)
{
	return data()[i * ncol() + j];
}


inline double matrix::at(size_t i, size_t j) const
{
	return data()[i * ncol() + j];
}


inline const size_t matrix::ncol() const
{
	return ncol_;
}


inline const size_t matrix::nrow() const
{
	return nrow_;
}


inline double const *matrix::data() const
{
	return data_;
}


inline double *matrix::data()
{
	return data_;
}


inline void matrix::data(double *ptr)
{
	data_ = ptr;
}


matrix matrix::T() const
{
	matrix transposed(ncol(), nrow());

	for (int i = 0; i < nrow(); ++i)
		for (int j = 0; j < ncol(); ++j)
			transposed.at(j,i) = this->at(i,j);

	return transposed;
}


matrix matrix::map(std::function<double(double)> f) const
{
	matrix result(nrow(), ncol());

	for (int i = 0; i < nrow() * ncol(); ++i)
		result.data()[i] = f(data_[i]);

	return result;
}


static matrix map2(std::function<double(double, double)> f, 
	const matrix &A, const matrix &B) 
{
	if (A.nrow() != B.nrow() || A.ncol() != B.ncol())
		throw matrix_size_mismatch();

	matrix result(A.nrow(), A.ncol());

	for (int i = 0; i < A.nrow() * A.ncol(); ++i)
		result.data()[i] = f(A.data()[i], B.data()[i]);

	return result;
}


matrix matrix::elem_mult(const matrix &other) const
{
	return map2([](double x, double y) { 
		return x * y; 
	}, *this, other);
}


matrix operator*(double x, const matrix &A)
{
	return A.map([=](double y) {
		return x * y;
	});
}


matrix operator*(const matrix &A, const matrix &B)
{
	if (A.ncol() != B.nrow())
		throw matrix_size_mismatch();

	matrix result(A.nrow(), B.ncol());

	for (int i = 0; i < A.nrow(); ++i)
	{
		for (int j = 0; j < B.ncol(); ++j)
		{
			double dot_product = 0;
			for (int k = 0; k < A.ncol(); ++k)
				dot_product += A.at(i,k) * B.at(k,j);
			result.at(i,j) = dot_product;
		}
	}

	return result;
}


matrix operator+(const matrix &A, const matrix &B)
{
	return map2([](double x, double y) { 
		return x + y; 
	}, A, B);
}


matrix operator-(const matrix &A)
{
	return (-1) * A;
}


matrix operator-(const matrix &A, const matrix &B)
{
	return A + (-B);
}

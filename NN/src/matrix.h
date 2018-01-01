#pragma once

#include <vector>
#include <functional>


struct matrix_size_mismatch : public std::exception
{
	const char* what() const throw();
};


class matrix
{
	double *data_;
	size_t ncol_, nrow_;
public:
	matrix();
	matrix(const matrix &other);
	matrix(matrix &&other);
	matrix(size_t nrow, size_t ncol, bool rand_init = false);
	matrix(std::initializer_list<std::initializer_list<double>> init);
	~matrix();
	
	matrix &operator=(const matrix &other);
	matrix &operator=(matrix &&other);
	
	inline double &at(size_t i, size_t j);
	inline double at(size_t i, size_t j) const;
	inline const size_t ncol() const;
	inline const size_t nrow() const;
	inline double const *data() const;
	inline double *data();
	inline void data(double *ptr);

	matrix elem_mult(const matrix &other) const;
	matrix T() const;
	matrix map(std::function<double(double)> f) const;
};


matrix operator+(const matrix &A, const matrix &B);
matrix operator-(const matrix &A);
matrix operator-(const matrix &A, const matrix &B);
matrix operator*(double x, const matrix &A);
matrix operator*(const matrix &A, const matrix &B);

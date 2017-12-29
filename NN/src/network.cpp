#include "network.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>


inline double sigmoid(double z)
{
	return 1 / (1 + exp(-z));
}


inline double sigmoid_prime(double z)
{
	return sigmoid(z) * (1 - sigmoid(z));
}


static inline double print(double x)
{
	std::cout << x << " ";
	return x;
}


network::network(std::vector<size_t> layers, double rate)
	: rate(rate), N(layers.size()-1), input(*layers.begin(), 1)
{
	srand(time(0));

	for (auto it = layers.begin()+1; it != layers.end(); ++it)
	{
		w.push_back(matrix(*it, *(it-1)));
		b.push_back(matrix(*it, 1));
		z.push_back(matrix(*it, 1));
		a.push_back(matrix(*it, 1));
		d.push_back(matrix(*it, 1));
	}
}


network::network(const char *filename)
{
	srand(time(0));

	std::ifstream fstrm(filename);

	rate = 0.2;

	fstrm >> N;

	size_t in, out;

	// input layer
	fstrm >> in >> out;
	input = matrix(in,1);

	for (size_t L = 0; L < N; ++L)
	{
		if (L != 0)
			fstrm >> in >> out;

		w.push_back(matrix(out, in));
		b.push_back(matrix(out, 1));
		z.push_back(matrix(out, 1));
		a.push_back(matrix(out, 1));
		d.push_back(matrix(out, 1));

		// weights
		for (size_t j = 0; j < out; ++j)
		{
			for (size_t k = 0; k < in; ++k)
			{
				double n;
				fstrm >> n;
				w[L].at(j,k) = n;
			}
		}

		// biases
		for (size_t j = 0; j < out; ++j)
		{
			double n;
			fstrm >> n;
			w[L].at(j,0) = n;
		}
	}

	fstrm.close();
}


void network::save(const char *filename)
{
	std::ofstream fstrm(filename);

	fstrm << N << std::endl;

	for (size_t L = 0; L < N; ++L)
	{
		fstrm
			<< w[L].column_count() << " "         // input for layer
			<< w[L].row_count() << std::endl;    // output for layer
											   									   
		// weights
		for (size_t i = 0; i < w[L].row_count(); ++i)
			for (size_t j = 0; j < w[L].column_count(); ++j)
				fstrm << w[L].at(i,j) << " ";
		fstrm << std::endl;

		// biases
		for (size_t i = 0; i < w[L].row_count(); ++i)
			fstrm << w[L].at(i,0) << " ";
		fstrm << std::endl;
	}

	fstrm.close();
}


void network::write() const
{
	for (int i = 0; i < N; ++i)
	{
		std::cout << "Layer " << i+1 << std::endl;
		std::cout << "weights ";
		w[i].map(print);
		std::cout << std::endl;
		std::cout << "biases ";
		b[i].map(print);
		std::cout << std::endl;
	}
}


const matrix &network::output(const matrix &input)
{
	feedforward(input);
	return a[N-1];
}


void network::feedforward(const matrix &input)
{
	this->input = input;

	// weighted sums and activations for each layer 
	z[0] = w[0] * input + b[0];
	a[0] = z[0].map(sigmoid);
	for (size_t L = 1; L < N; ++L)
	{
		z[L] = w[L] * a[L-1] + b[L];
		a[L] = z[L].map(sigmoid);
	}
}


void network::backpropagate(const matrix &target)
{
	// output layer error 
	d[N-1] = (a[N-1] - target) .elem_mult (z[N-1].map(sigmoid_prime)); 

	// other layers 
	for (int L = N-2; L >= 0; --L)
		d[L] = (w[L+1].T() * d[L+1]) .elem_mult (z[L].map(sigmoid_prime));
}


void network::update_weights_biases()
{
	b[0] = b[0] - rate * d[0];
	w[0] = w[0] - rate * (d[0] * input.T());
	for (size_t L = 1; L < N; ++L)
	{
		b[L] = b[L] - rate * d[L];
		w[L] = w[L] - rate * d[L] * a[L-1].T();
	}
}


void network::learn(const matrix &input, const matrix &target)
{
	feedforward(input);
	backpropagate(target);
	update_weights_biases();
}


rsize_t network::get(const matrix &input)
{
	matrix out = output(input);
	size_t max_i = 0;
	for (size_t i = 1; i < out.row_count(); ++i)
		if (out.at(i,0) > out.at(max_i,0))
			max_i = i;
	return max_i;
}
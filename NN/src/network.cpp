#include "network.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <algorithm>


static inline double sigmoid(double z)
{
	return 1 / (1 + exp(-z));
}


static inline double sigmoid_prime(double z)
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
		w.push_back(matrix(*it, *(it-1), true));
		b.push_back(matrix(*it, 1, true));
		z.push_back(matrix(*it, 1));
		a.push_back(matrix(*it, 1));
		d.push_back(matrix(*it, 1));
		davg.push_back(matrix(*it, 1));
	}
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


void network::backpropagate(const matrix &target, int n)
{
	double dn = n;

	// output layer error
	d[N-1] = (a[N-1] - target) .elem_mult (z[N-1].map(sigmoid_prime));
	davg[N-1] = (dn-1)/dn * davg[N-1] + 1/dn * d[N-1];

	// other layers
	for (int L = N - 2; L >= 0; --L)
	{
		d[L] = (w[L+1].T() * d[L+1]) .elem_mult (z[L].map(sigmoid_prime));
		davg[L] = (dn-1)/n * davg[L] + 1/dn * d[L];
	}
}


void network::update_weights_biases()
{
	b[0] = b[0] - rate * davg[0];
	w[0] = w[0] - rate * (davg[0] * input.T());
	for (size_t L = 1; L < N; ++L)
	{
		b[L] = b[L] - rate * davg[L];
		w[L] = w[L] - rate * (davg[L] * a[L-1].T());
	}
}


void network::fit(std::vector<matrix> &input, std::vector<matrix> &target, 
	size_t batch_size, size_t epochs, bool shuffle)
{
	std::vector<std::pair<matrix, matrix>> zip(input.size());

	for (int n = 0; n < epochs; ++n)
	{
		int i = 0, j = 0;
		for (i = 0; i < input.size(); i += batch_size)
		{
			for (j = 0; j < batch_size && i+j < input.size(); ++j)
			{
				feedforward(input[i+j]);
				backpropagate(target[i+j], j+1);
			}
			update_weights_biases();
		}

		if (shuffle)
		{
			for (int i = 0; i < input.size(); ++i)
				zip[i] = { std::move(input[i]), std::move(target[i]) };

			std::random_shuffle(zip.begin(), zip.end());

			for (int i = 0; i < input.size(); ++i)
			{
				input[i] = std::move(zip[i].first);
				target[i] = std::move(zip[i].second);
			}
		}
	}
}


size_t network::get(const matrix &input)
{
	feedforward(input);

	matrix out = a[N-1];
	size_t max_i = 0;
	
	for (size_t i = 1; i < out.nrow(); ++i)
		if (out.at(i,0) > out.at(max_i,0))
			max_i = i;
	
	return max_i;
}


double network::evaluate(const std::vector<matrix> &input, std::vector<matrix> &target)
{
	int correct = 0, all = input.size();

	for (int i = 0; i < input.size(); ++i)
		if (target[i].at(this->get(input[i]), 0) == 1)
			++correct;

	return (double)correct/all;
}

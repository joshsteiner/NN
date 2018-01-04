#pragma once

#include <vector>
#include "matrix.h"


class network
{
	size_t N;                  // number of layers (excluding input)
	double rate;               // learning rate
	matrix input;
	std::vector<matrix> w;     // weights
	std::vector<matrix> b;     // biases
	std::vector<matrix> z;     // weighted sum
	std::vector<matrix> a;     // activations
	std::vector<matrix> d;     // errors
	std::vector<matrix> davg;  // error avg (per batch)

	void feedforward(const matrix &input);
	void backpropagate(const matrix &target, int n = 1);
	void update_weights_biases();

public:
	network(std::vector<size_t> layers, double rate);
	
	size_t get(const matrix &input);
	
	void network::fit(std::vector<matrix> &input, std::vector<matrix> &target, 
		size_t batch_size = 1, size_t epochs = 1, bool shuffle = false);
	double network::evaluate(const std::vector<matrix> &input, std::vector<matrix> &target);
};

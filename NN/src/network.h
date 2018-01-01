#pragma once

#include <vector>
#include "matrix.h"


class network
{
	size_t N;          // number of layers (excluding input)
	double rate;       // learning rate
	matrix input;
	std::vector<matrix> w;  // weights
	std::vector<matrix> b;  // biases
	std::vector<matrix> z;  // weighted sum
	std::vector<matrix> a;  // activations
	std::vector<matrix> d;  // errors

	void feedforward(const matrix &input);
	void backpropagate(const matrix &target);
	void update_weights_biases();

public:
	network(std::vector<size_t> layers, double rate);
	network(const char *filename);
	
	void save(const char *filename);
	
	const matrix &output(const matrix &input);
	void learn(const matrix &input, const matrix &target);
	size_t get(const matrix &input);
};

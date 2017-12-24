#include <vector>
#include <random>
#include <ctime>
#include <iostream>
#include "matrix.h"


double sigmoid(double z)
{
	return 1 / (1 + exp(-z));
}


double sigmoid_prime(double z)
{
	return sigmoid(z) * (1 - sigmoid(z));
}


double print(double x)
{
	cout << x << " ";
	return x;
}


class network
{
	size_t N;          // number of layers (excluding input)
	double rate;       // learning rate
	matrix input;
	vector<matrix> w;  // weights
	vector<matrix> b;  // biases
	vector<matrix> z;  // weighted sum
	vector<matrix> a;  // activations
	vector<matrix> d;  // errors


public:
	network(initializer_list<size_t> layers, double rate = 0.1)
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


	void write()
	{
		for (int i = 0; i < N; ++i)
		{
			cout << "Layer " << i+1 << endl;
			cout << "weights ";
			w[i].map(print);
			cout << endl;
			cout << "biases ";
			b[i].map(print);
			cout << endl;
		}
	}


	matrix output()
	{
		return a[N-1];
	}


	void feedforward(matrix input)
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


	void backpropagate(matrix target)
	{
		// output layer error
		d[N-1] = (a[N-1] - target) .elem_mult (z[N-1].map(sigmoid_prime));

		// other layers
		for (int L = N - 2; L >= 0; --L)
			d[L] = (w[L+1].T() * d[L+1]) .elem_mult (z[L].map(sigmoid_prime));
	}


	void update_weights_biases()
	{
		b[0] = b[0] - rate * d[0];
		w[0] = w[0] - rate * d[0] * input.T();
		for (size_t L = 1; L < N; ++L)
		{
			b[L] = b[L] - rate * d[L];
			w[L] = w[L] - rate * d[L] * a[L-1].T();
		}
	}
};


int main()
{
	network xor({ 2,3,2 }, 0.5);

	xor.write();

	vector<matrix> inputs = {
		{ { 0 },{ 0 } },
		{ { 1 },{ 0 } },
		{ { 0 },{ 1 } },
		{ { 1 },{ 1 } }
	};

	vector<matrix> targets = {
		{ { 1 },{ 0 } },
		{ { 0 },{ 1 } },
		{ { 0 },{ 1 } },
		{ { 1 },{ 0 } }
	};

	for (int i = 0; i < 10'000; ++i)
	{
		int r = rand();
		xor.feedforward(inputs[r%4]);
		xor.backpropagate(targets[r%4]);
		xor.update_weights_biases();
	}

	xor.write();

	getchar();
	return 0;
}

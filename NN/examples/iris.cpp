#include "examples.h"
#include "../src/network.h"
#include "../src/matrix.h"
#include <algorithm>
#include <vector>
#include <tuple>
#include <iostream>
#include <cstdlib>
#include <ctime>


matrix one_hot_true(size_t size, size_t true_one)
{
	matrix result(size, 1);
	for (unsigned i = 0; i < size; ++i)
		result.at(i,0) = i == true_one;
	return result;
}


enum Species 
{
	Setosa, Versicolor, Virginica
};


std::vector<std::pair<matrix, Species>> data = {
	{ matrix{{5.2},{3.5},{1.4},{0.2}}, Setosa },
	{ matrix{{4.9},{3.0},{1.4},{0.2}}, Setosa },
	{ matrix{{4.7},{3.2},{1.3},{0.2}}, Setosa },
	{ matrix{{4.6},{3.1},{1.5},{0.2}}, Setosa },
	{ matrix{{5.0},{3.6},{1.4},{0.3}}, Setosa },
	{ matrix{{5.4},{3.9},{1.7},{0.4}}, Setosa },
	{ matrix{{4.6},{3.4},{1.4},{0.3}}, Setosa },
	{ matrix{{5.0},{3.4},{1.5},{0.2}}, Setosa },
	{ matrix{{4.4},{2.9},{1.4},{0.2}}, Setosa },
	{ matrix{{4.9},{3.1},{1.5},{0.1}}, Setosa },
	{ matrix{{5.4},{3.7},{1.5},{0.2}}, Setosa },
	{ matrix{{4.8},{3.4},{1.6},{0.2}}, Setosa },
	{ matrix{{4.8},{3.0},{1.4},{0.1}}, Setosa },
	{ matrix{{4.3},{3.0},{1.1},{0.1}}, Setosa },
	{ matrix{{5.8},{4.0},{1.2},{0.2}}, Setosa },
	{ matrix{{5.7},{4.4},{1.5},{0.4}}, Setosa },
	{ matrix{{5.4},{3.9},{1.3},{0.4}}, Setosa },
	{ matrix{{5.1},{3.5},{1.4},{0.3}}, Setosa },
	{ matrix{{5.7},{3.8},{1.7},{0.3}}, Setosa },
	{ matrix{{5.1},{3.8},{1.5},{0.3}}, Setosa },
	{ matrix{{5.4},{3.4},{1.7},{0.2}}, Setosa },
	{ matrix{{5.1},{3.7},{1.5},{0.4}}, Setosa },
	{ matrix{{4.6},{3.6},{1.0},{0.2}}, Setosa },
	{ matrix{{5.1},{3.3},{1.7},{0.5}}, Setosa },
	{ matrix{{4.8},{3.4},{1.9},{0.2}}, Setosa },
	{ matrix{{5.0},{3.0},{1.6},{0.2}}, Setosa },
	{ matrix{{5.0},{3.4},{1.6},{0.4}}, Setosa },
	{ matrix{{5.2},{3.5},{1.5},{0.2}}, Setosa },
	{ matrix{{5.2},{3.4},{1.4},{0.2}}, Setosa },
	{ matrix{{4.7},{3.2},{1.6},{0.2}}, Setosa },
	{ matrix{{4.8},{3.1},{1.6},{0.2}}, Setosa },
	{ matrix{{5.4},{3.4},{1.5},{0.4}}, Setosa },
	{ matrix{{5.2},{4.1},{1.5},{0.1}}, Setosa },
	{ matrix{{5.5},{4.2},{1.4},{0.2}}, Setosa },
	{ matrix{{4.9},{3.1},{1.5},{0.2}}, Setosa },
	{ matrix{{5.0},{3.2},{1.2},{0.2}}, Setosa },
	{ matrix{{5.5},{3.5},{1.3},{0.2}}, Setosa },
	{ matrix{{4.9},{3.6},{1.4},{0.1}}, Setosa },
	{ matrix{{4.4},{3.0},{1.3},{0.2}}, Setosa },
	{ matrix{{5.1},{3.4},{1.5},{0.2}}, Setosa },
	{ matrix{{5.0},{3.5},{1.3},{0.3}}, Setosa },
	{ matrix{{4.5},{2.3},{1.3},{0.3}}, Setosa },
	{ matrix{{4.4},{3.2},{1.3},{0.2}}, Setosa },
	{ matrix{{5.0},{3.5},{1.6},{0.6}}, Setosa },
	{ matrix{{5.1},{3.8},{1.9},{0.4}}, Setosa },
	{ matrix{{4.8},{3.0},{1.4},{0.3}}, Setosa },
	{ matrix{{5.1},{3.8},{1.6},{0.2}}, Setosa },
	{ matrix{{4.6},{3.2},{1.4},{0.2}}, Setosa },
	{ matrix{{5.3},{3.7},{1.5},{0.2}}, Setosa },
	{ matrix{{5.0},{3.3},{1.4},{0.2}}, Setosa },
	{ matrix{{7.0},{3.2},{4.7},{1.4}}, Versicolor },
	{ matrix{{6.4},{3.2},{4.5},{1.5}}, Versicolor },
	{ matrix{{6.9},{3.1},{4.9},{1.5}}, Versicolor },
	{ matrix{{5.5},{2.3},{4.0},{1.3}}, Versicolor },
	{ matrix{{6.5},{2.8},{4.6},{1.5}}, Versicolor },
	{ matrix{{5.7},{2.8},{4.5},{1.3}}, Versicolor },
	{ matrix{{6.3},{3.3},{4.7},{1.6}}, Versicolor },
	{ matrix{{4.9},{2.4},{3.3},{1.0}}, Versicolor },
	{ matrix{{6.6},{2.9},{4.6},{1.3}}, Versicolor },
	{ matrix{{5.2},{2.7},{3.9},{1.4}}, Versicolor },
	{ matrix{{5.0},{2.0},{3.5},{1.0}}, Versicolor },
	{ matrix{{5.9},{3.0},{4.2},{1.5}}, Versicolor },
	{ matrix{{6.0},{2.2},{4.0},{1.0}}, Versicolor },
	{ matrix{{6.1},{2.9},{4.7},{1.4}}, Versicolor },
	{ matrix{{5.6},{2.9},{3.6},{1.3}}, Versicolor },
	{ matrix{{6.7},{3.1},{4.4},{1.4}}, Versicolor },
	{ matrix{{5.6},{3.0},{4.5},{1.5}}, Versicolor },
	{ matrix{{5.8},{2.7},{4.1},{1.0}}, Versicolor },
	{ matrix{{6.2},{2.2},{4.5},{1.5}}, Versicolor },
	{ matrix{{5.6},{2.5},{3.9},{1.1}}, Versicolor },
	{ matrix{{5.9},{3.2},{4.8},{1.8}}, Versicolor },
	{ matrix{{6.1},{2.8},{4.0},{1.3}}, Versicolor },
	{ matrix{{6.3},{2.5},{4.9},{1.5}}, Versicolor },
	{ matrix{{6.1},{2.8},{4.7},{1.2}}, Versicolor },
	{ matrix{{6.4},{2.9},{4.3},{1.3}}, Versicolor },
	{ matrix{{6.6},{3.0},{4.4},{1.4}}, Versicolor },
	{ matrix{{6.8},{2.8},{4.8},{1.4}}, Versicolor },
	{ matrix{{6.7},{3.0},{5.0},{1.7}}, Versicolor },
	{ matrix{{6.0},{2.9},{4.5},{1.5}}, Versicolor },
	{ matrix{{5.7},{2.6},{3.5},{1.0}}, Versicolor },
	{ matrix{{5.5},{2.4},{3.8},{1.1}}, Versicolor },
	{ matrix{{5.5},{2.4},{3.7},{1.0}}, Versicolor },
	{ matrix{{5.8},{2.7},{3.9},{1.2}}, Versicolor },
	{ matrix{{6.0},{2.7},{5.1},{1.6}}, Versicolor },
	{ matrix{{5.4},{3.0},{4.5},{1.5}}, Versicolor },
	{ matrix{{6.0},{3.4},{4.5},{1.6}}, Versicolor },
	{ matrix{{6.7},{3.1},{4.7},{1.5}}, Versicolor },
	{ matrix{{6.3},{2.3},{4.4},{1.3}}, Versicolor },
	{ matrix{{5.6},{3.0},{4.1},{1.3}}, Versicolor },
	{ matrix{{5.5},{2.5},{4.0},{1.3}}, Versicolor },
	{ matrix{{5.5},{2.6},{4.4},{1.2}}, Versicolor },
	{ matrix{{6.1},{3.0},{4.6},{1.4}}, Versicolor },
	{ matrix{{5.8},{2.6},{4.0},{1.2}}, Versicolor },
	{ matrix{{5.0},{2.3},{3.3},{1.0}}, Versicolor },
	{ matrix{{5.6},{2.7},{4.2},{1.3}}, Versicolor },
	{ matrix{{5.7},{3.0},{4.2},{1.2}}, Versicolor },
	{ matrix{{5.7},{2.9},{4.2},{1.3}}, Versicolor },
	{ matrix{{6.2},{2.9},{4.3},{1.3}}, Versicolor },
	{ matrix{{5.1},{2.5},{3.0},{1.1}}, Versicolor },
	{ matrix{{5.7},{2.8},{4.1},{1.3}}, Versicolor },
	{ matrix{{6.3},{3.3},{6.0},{2.5}}, Virginica },
	{ matrix{{5.8},{2.7},{5.1},{1.9}}, Virginica },
	{ matrix{{7.1},{3.0},{5.9},{2.1}}, Virginica },
	{ matrix{{6.3},{2.9},{5.6},{1.8}}, Virginica },
	{ matrix{{6.5},{3.0},{5.8},{2.2}}, Virginica },
	{ matrix{{7.6},{3.0},{6.6},{2.1}}, Virginica },
	{ matrix{{4.9},{2.5},{4.5},{1.7}}, Virginica },
	{ matrix{{7.3},{2.9},{6.3},{1.8}}, Virginica },
	{ matrix{{6.7},{2.5},{5.8},{1.8}}, Virginica },
	{ matrix{{7.2},{3.6},{6.1},{2.5}}, Virginica },
	{ matrix{{6.5},{3.2},{5.1},{2.0}}, Virginica },
	{ matrix{{6.4},{2.7},{5.3},{1.9}}, Virginica },
	{ matrix{{6.8},{3.0},{5.5},{2.1}}, Virginica },
	{ matrix{{5.7},{2.5},{5.0},{2.0}}, Virginica },
	{ matrix{{5.8},{2.8},{5.1},{2.4}}, Virginica },
	{ matrix{{6.4},{3.2},{5.3},{2.3}}, Virginica },
	{ matrix{{6.5},{3.0},{5.5},{1.8}}, Virginica },
	{ matrix{{7.7},{3.8},{6.7},{2.2}}, Virginica },
	{ matrix{{7.7},{2.6},{6.9},{2.3}}, Virginica },
	{ matrix{{6.0},{2.2},{5.0},{1.5}}, Virginica },
	{ matrix{{6.9},{3.2},{5.7},{2.3}}, Virginica },
	{ matrix{{5.6},{2.8},{4.9},{2.0}}, Virginica },
	{ matrix{{7.7},{2.8},{6.7},{2.0}}, Virginica },
	{ matrix{{6.3},{2.7},{4.9},{1.8}}, Virginica },
	{ matrix{{6.7},{3.3},{5.7},{2.1}}, Virginica },
	{ matrix{{7.2},{3.2},{6.0},{1.8}}, Virginica },
	{ matrix{{6.2},{2.8},{4.8},{1.8}}, Virginica },
	{ matrix{{6.1},{3.0},{4.9},{1.8}}, Virginica },
	{ matrix{{6.4},{2.8},{5.6},{2.1}}, Virginica },
	{ matrix{{7.2},{3.0},{5.8},{1.6}}, Virginica },
	{ matrix{{7.4},{2.8},{6.1},{1.9}}, Virginica },
	{ matrix{{7.9},{3.8},{6.4},{2.0}}, Virginica },
	{ matrix{{6.4},{2.8},{5.6},{2.2}}, Virginica },
	{ matrix{{6.3},{2.8},{5.1},{1.5}}, Virginica },
	{ matrix{{6.1},{2.6},{5.6},{1.4}}, Virginica },
	{ matrix{{6.3},{3.4},{5.6},{2.4}}, Virginica },
	{ matrix{{6.4},{3.1},{5.5},{1.8}}, Virginica },
	{ matrix{{6.0},{3.0},{4.8},{1.8}}, Virginica },
	{ matrix{{6.9},{3.1},{5.4},{2.1}}, Virginica },
	{ matrix{{6.7},{3.1},{5.6},{2.4}}, Virginica },
	{ matrix{{6.9},{3.1},{5.1},{2.3}}, Virginica },
	{ matrix{{5.8},{2.7},{5.1},{1.9}}, Virginica },
	{ matrix{{6.8},{3.2},{5.9},{2.3}}, Virginica },
	{ matrix{{6.7},{3.3},{5.7},{2.5}}, Virginica },
	{ matrix{{6.7},{3.0},{5.2},{2.3}}, Virginica },
	{ matrix{{6.3},{2.5},{5.0},{1.9}}, Virginica },
	{ matrix{{6.5},{3.0},{5.2},{2.0}}, Virginica },
	{ matrix{{6.2},{3.4},{5.4},{2.3}}, Virginica },
	{ matrix{{5.9},{3.0},{5.1},{1.8}}, Virginica }
};


void examples::iris::run()
{
	// shuffle data and split into training and test sets
	std::random_shuffle(data.begin(), data.end());
	std::vector<std::pair<matrix, Species>>
		test_data(data.begin(), data.begin() + 15),
		training_data(data.begin() + 15, data.end());


	network net({4, 6, 3}, 0.2);

	int epochs = 2000;

	std::cout << "learning..." << std::endl;
	for (int i = 0; i < epochs; ++i)
		for (auto example : training_data)
			net.learn(example.first, one_hot_true(3, example.second));

	std::cout << "testing..." << std::endl;
	int correct = 0;
	for (auto example : test_data)
		if (net.get(example.first) == example.second)
			++correct;
	std::cout << correct << "/15 correct" << std::endl;
}

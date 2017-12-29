#include "examples.h"

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "../src/network.h"
#include "../src/matrix.h"



	void xor_example::run()
	{
		network xor({2,3,2}, 0.2);

		std::vector<matrix> inputs = {
			matrix{{0},{0}},
			matrix{{1},{0}},
			matrix{{0},{1}},
			matrix{{1},{1}}
		};

		std::vector<matrix> targets = {
			matrix{{1},{0}},
			matrix{{0},{1}},
			matrix{{0},{1}},
			matrix{{1},{0}}
		};

		srand(time(0));

		int training_examples = 30'000;
		
		std::cout << "learning xor..." << std::endl;

		for (int i = 0; i < training_examples; ++i)
		{
			int r = rand();
			xor.learn(inputs[r%4], targets[r%4]);
		}

		std::cout
			<< "0 xor 0 = " << xor.get({ {0},{0} }) << std::endl
			<< "0 xor 1 = " << xor.get({ {0},{1} }) << std::endl
			<< "1 xor 0 = " << xor.get({ {1},{0} }) << std::endl
			<< "1 xor 1 = " << xor.get({ {1},{1} }) << std::endl;
	}


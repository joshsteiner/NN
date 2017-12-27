#include "examples.h"

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "../src/network.h"
#include "../src/matrix.h"


namespace xor_example
{
	void run()
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

		for (int i = 0; i < training_examples; ++i)
		{
			int r = rand();
			xor.learn(inputs[r%4], targets[r%4]);
		}

		getchar();
	}
}
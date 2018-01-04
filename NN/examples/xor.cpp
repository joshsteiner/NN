#include "examples.h"

#include "../src/network.h"
#include "../src/matrix.h"
#include <iostream>
#include <vector>


void examples::xor::run()
{
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

	network net({ 2,3,2 }, 1);
	
	net.fit(inputs, targets, 1, 10'000, true);
	
	std::cout
		<< "0 xor 0 = " << net.get({ {0},{0} }) << std::endl
		<< "0 xor 1 = " << net.get({ {0},{1} }) << std::endl
		<< "1 xor 0 = " << net.get({ {1},{0} }) << std::endl
		<< "1 xor 1 = " << net.get({ {1},{1} }) << std::endl;
}

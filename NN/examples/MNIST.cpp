#include "examples.h"
#include "../src/network.h"
#include "../src/matrix.h"
#include "MNISTreader.h"
#include <iostream>
#include <vector>


void examples::MNIST::run()
{
	network net({ 28*28,50,50,10 }, 1);

	std::cout << "reading..." << std::endl;
	std::vector<matrix>
		training_images = ::MNIST::read_image_file("train-images.idx3-ubyte"),
		training_labels = ::MNIST::read_label_file("train-labels.idx1-ubyte"),
		test_images     = ::MNIST::read_image_file("t10k-images.idx3-ubyte"),
		test_labels     = ::MNIST::read_label_file("t10k-labels.idx1-ubyte");

	std::cout << "training..." << std::endl;
	net.fit(
		training_images,
		training_labels,
		10,
		10,
		true
	);

	std::cout << "testing..." << std::endl;
	printf("%.1f%% correct", 
		100 * net.evaluate(test_images, test_labels));
}

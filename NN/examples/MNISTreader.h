#pragma once

#include <fstream>
#include <stdint.h>
#include "../src/matrix.h"


namespace MNIST
{
	std::vector<matrix> read_label_file(const char *filename);
	std::vector<matrix> read_image_file(const char *filename);
}

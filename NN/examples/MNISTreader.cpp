#include "MNISTreader.h"


static matrix one_hot_true(uint8_t n)
{
	matrix result = {
		{0},{0},{0},{0},{0},
		{0},{0},{0},{0},{0} 
	};

	result.at(n,0) = 1;
	return result;
}


static uint32_t to_uint32_t(char *cs)
{
	uint32_t result = 0;

	result |= (uint32_t)(uint8_t)cs[0] << 3 * 8;
	result |= (uint32_t)(uint8_t)cs[1] << 2 * 8;
	result |= (uint32_t)(uint8_t)cs[2] << 1 * 8;
	result |= (uint32_t)(uint8_t)cs[3] << 0 * 8;

	return result;
}


std::vector<matrix> MNIST::read_label_file(const char *filename)
{
	std::fstream fr(filename, std::ios::in | std::ios::binary);
	std::vector<matrix> result;

	char header_buff[2][4];

	fr.read(header_buff[0], 4);
	fr.read(header_buff[1], 4);

	if (to_uint32_t(header_buff[0]) != 2049)  // magic number
		return result;

	uint32_t count = to_uint32_t(header_buff[1]);
	
	char label_buff[1];
	for (int i = 0; i < count; ++i)
	{
		fr.read(label_buff, 1);
		result.push_back(one_hot_true(label_buff[0]));
	}

	fr.close();
	return result;
}


std::vector<matrix> MNIST::read_image_file(const char *filename)
{
	std::fstream fr(filename, std::ios::in | std::ios::binary);
	std::vector<matrix> result;

	char header_buff[2][4];

	for (int i = 0; i < 4; ++i)
		fr.read(header_buff[i], 4);

	if (to_uint32_t(header_buff[0]) != 2051)  // magic number
		return result;

	uint32_t
		count = to_uint32_t(header_buff[1]),
		row_count = to_uint32_t(header_buff[2]),
		column_count = to_uint32_t(header_buff[3]);

	for (int i = 0; i < count; ++i)
	{
		matrix image(row_count * column_count, 1);
		char pixel_buff[1];
		for (int j = 0; j < row_count * column_count; ++j)
		{
			fr.read(pixel_buff, 1);
			image.at(j,0) = (double)(uint8_t)pixel_buff[0] / 255.0;
		}
		result.push_back(std::move(image));
	}

	fr.close();
	return result;
}

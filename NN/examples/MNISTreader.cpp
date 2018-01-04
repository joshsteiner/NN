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
	label_file fr(filename);
	std::vector<matrix> result;

	while (!fr.end())
		result.push_back(fr.next());

	fr.close();
	return result;
}


std::vector<matrix> MNIST::read_image_file(const char *filename)
{
	image_file fr(filename);
	std::vector<matrix> result;

	while (!fr.end())
		result.push_back(fr.next());

	fr.close();
	return result;
}


bool MNIST::file::end() const
{
	return fstrm.bad()
		|| fstrm.eof()
		|| it == count
		|| is_end;
}


void MNIST::file::close()
{
	fstrm.close();
}


MNIST::label_file::label_file(const char *filename)
{
	this->it = 0;

	fstrm.open(filename, std::ios::in | std::ios::binary);

	char header_buff[2][4];

	fstrm.read(header_buff[0], 4);
	fstrm.read(header_buff[1], 4);

	if (to_uint32_t(header_buff[0]) != magic_number)
		is_end = true;

	count = to_uint32_t(header_buff[1]);
}


MNIST::label_file::~label_file()
{
	close();
}


matrix MNIST::label_file::next()
{
	char label_buff[1];
	fstrm.read(label_buff, 1);
	++it;
	return one_hot_true(label_buff[0]);
}


MNIST::image_file::image_file(const char *filename)
{
	this->it = 0;

	fstrm.open(filename, std::ios::in | std::ios::binary);

	char header_buff[4][4];

	for (int i = 0; i < 4; ++i)
		fstrm.read(header_buff[i], 4);

	if (to_uint32_t(header_buff[0]) != magic_number)
		is_end = true;

	count = to_uint32_t(header_buff[1]);
	row_count = to_uint32_t(header_buff[2]);
	column_count = to_uint32_t(header_buff[3]);
}


MNIST::image_file::~image_file()
{
	close();
}


matrix MNIST::image_file::next()
{
	matrix image(row_count * column_count, 1);
	char pixel_buff[1];
	for (int j = 0; !fstrm.eof() && j < row_count * column_count; ++j)
	{
		fstrm.read(pixel_buff, 1);
		image.at(j,0) = (double)(uint8_t)pixel_buff[0] / 255.0;
	}
	++it;
	return image;
}

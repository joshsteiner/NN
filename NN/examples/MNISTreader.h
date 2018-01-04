#pragma once

#include <fstream>
#include <stdint.h>
#include "../src/matrix.h"


namespace MNIST
{
std::vector<matrix> read_label_file(const char *filename);
std::vector<matrix> read_image_file(const char *filename);

class file
{
protected:
	static const uint32_t magic_number;
	uint32_t count;
	int it;
	std::ifstream fstrm;
	bool is_end = false;
public:
	void close();
	bool end() const;
	virtual matrix next() = 0;
};

class label_file : public file
{
	static const uint32_t magic_number = 2049;
public:
	label_file(const char *filename);
	~label_file();
	matrix next() override;
};

class image_file : public file
{
	static const uint32_t magic_number = 2051;
	uint32_t row_count, column_count;
public:
	image_file(const char *filename);
	~image_file();
	matrix next() override;
};

}
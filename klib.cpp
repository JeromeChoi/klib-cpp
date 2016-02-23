/* klib.cpp
	Implementation of Kitronyx API for C++
	Copyright (c) 2014-2016 Kitronyx http://www.kitronyx.com
	contact@kitronyx.com
	GPL V3.0
*/
#include "klib.h"

KLib::KLib()
{
	frame = NULL;
	row_index = NULL;
	col_index = NULL;
}

KLib::~KLib()
{
	if (frame != NULL)
	{
		for (int i = 0; i < nrow; i++) delete[] frame[i];
		delete[] frame;
	}

	if (row_index != NULL) delete[] row_index;
	
	if (col_index != NULL) delete[] col_index;
}

void KLib::init(std::string p, std::string d, std::string s)
{
	port = p;
	device = d;
	sensor = s;

	if ((device.compare("Snowboard") == 0) && (sensor.compare("1610") == 0))
	{
		baud_rate = 115200;
		nrow = 16;
		ncol = 10;
		frame = new int*[nrow];
		for (int i = 0; i < nrow; i++)
		{
			frame[i] = new int[ncol];
		}

		int _row_index[16] = { 8,9,10,11,12,13,14,15,7,6,5,4,3,2,1,0 };
		int _col_index[10] = { 0,1,2,3,4,5,6,7,8,9 };
		row_index = new int[nrow];
		for (int i = 0; i < nrow; i++) row_index[i] = _row_index[i];
		col_index = new int[ncol];
		for (int i = 0; i < ncol; i++) col_index[i] = _col_index[i];
		command = 'A';
	}
}

void KLib::start(void)
{
	serial.setup(port, baud_rate);
}

bool KLib::read(void)
{
	if (device.compare("Snowboard") == 0)
	{
		return read_snowboard();
	}
	return false;
}

bool KLib::read_snowboard(void)
{
	// request data
	serial.writeByte(0x00);

	// get data
	stringstream resp;
	std::vector<int> sensors;
	char ch = 0;
	char until = '\n';
	while (true)
	{
		if (serial.available())
		{
			ch = serial.readByte();
			resp << ch;
			if (ch == until) break;
		}
	}
	int i;
	while (resp >> i)
	{
		sensors.push_back(i);

		if (resp.peek() == ',') resp.ignore();
	}
	int k = 0;
	for (int i = 0; i < nrow; i++)
	{
		for (int j = 0; j < ncol; j++)
		{
			frame[row_index[i]][col_index[j]] = sensors.at(k++);
		}
	}
	return true;
}

void KLib::print_frame(void)
{
	for (int i = 0; i < nrow; i++)
	{
		for (int j = 0; j < ncol; j++)
		{
			printf("%04d ", frame[i][j]);
		}
		printf("\n");
	}
}

// https://sites.google.com/site/ofauckland/examples/serial-read-string-from-arduino
// http://itouchs.blogspot.kr/2015/10/openframeworks-serial-read-string-from.html
std::string KLib::trim_right(string str) {
	size_t endpos = str.find_last_not_of(" \t\r\n");
	return (string::npos != endpos) ? str.substr(0, endpos + 1) : str;
}

std::string KLib::trim_left(string str) {
	size_t startpos = str.find_first_not_of(" \t\r\n");
	return (string::npos != startpos) ? str.substr(startpos) : str;
}

std::string KLib::trim(string str) {
	return trim_left(trim_right(str));;
}

Grid::Grid(int nrow, int ncol, int size)
{
	this->nrow = nrow;
	this->ncol = ncol;
	this->size = size;
}

void Grid::draw(int ** frame, int scale)
{
	for (int i = 0; i < nrow; i++)
	{
		for (int j = 0; j < ncol; j++)
		{
			ofSetColor(0, frame[i][j]*scale, 0);
			ofFill();
			ofDrawRectangle(j*size, i*size, size, size);
		}
	}
}
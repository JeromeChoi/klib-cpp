/* klib.h
	Header of Kitronyx API for C++
	Copyright (c) 2014-2016 Kitronyx http://www.kitronyx.com
	contact@kitronyx.com
	GPL V3.0
*/

#ifndef _KLIB_H
#define _KLIB_H

#include <string>
#include "ofApp.h"

class KLib
{
public:
	int nrow;
	int ncol;
	int ** frame;

private:
	std::string port;
	int baud_rate;
	std::string device;
	std::string sensor;
	int * row_index;
	int * col_index;
	char command;

	ofSerial serial;

public:
	KLib();
	~KLib();
	void init(std::string p, std::string d, std::string s);
	void start(void);
	bool read(void);
	void print_frame(void);

private:
	bool read_snowboard(void);
	bool read_mc1509(void);
	std::string trim_right(string str);
	std::string trim_left(string str);
	std::string trim(string str);
};

class Grid
{
private:
	int nrow;
	int ncol;
	int size;

public:
	Grid(int nrow, int ncol, int size);
	void draw(int ** frame, int scale);
};

#endif // _KLIB_H
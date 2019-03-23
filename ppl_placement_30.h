#pragma once

#ifndef MYCLASS_PPL_PLACEMENT_20_INCLUDED
#define MYCLASS_PPL_PLACEMENT_20_INCLUDED

/*
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
*/
#include "std_lib_facilities.h"
#define _USE_MATH_DEFINES

using namespace std;

//-------------------------------------MATRIX CLASS---------------------------------------

class matrix {
public:
	matrix(string name, vector<double> m)
		:name(name), values(m)
	{
		element_count = sqrt(m.size());
		total_size = m.size();
	}

	matrix(string name)
		:name(name)
	{
		set_dist_values();
		element_count = sqrt(values.size());
		total_size = values.size();
	}

	void set_dist_values();
	vector<double> get_values() { return values; }
	int get_element_count() { return element_count; }
	int get_total_size() { return total_size; }
	void plot_values();

private:
	string name;
	string file_location;
	vector<double> values;
	int element_count;
	int total_size;
};

//-------------------------------------MATRIX GENERATOR CLASS---------------------------------------

class matrix_generator {
public:
	matrix_generator(int total_size)
		:total_size(total_size)
	{
		row = sqrt(total_size);
		col = row;
		generate();
	}
	matrix_generator(int total_size, int row, int col)
		:total_size(total_size), row(row), col(col)
	{
		generate();
	}

	void generate();
	vector<double> get_matrix() { return matrix; }

private:
	vector<double> matrix;
	int total_size;
	int row;
	int col;
};

//-------------------------------------SOLVER CLASS---------------------------------------

class solver
{
public:
	solver(matrix m1, matrix m2) //  // m1 = pref, m2 = dist
		:m1(m1), m2(m2)
	{
		//m1.plot_values();
		//m2.plot_values();

		calc();
	}

	vector<vector<int>> get_permutations() { return permutations; }

	void write_best_series();
	void calc();

private:
	vector<int> calc_optimized_integers(int ts);
	matrix& m2;
	matrix& m1;
	vector<vector<int>> permutations;
	vector<vector<double>> bestValue_series;
	vector<double> maxSums;
};

#endif
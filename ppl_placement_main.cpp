#include "ppl_placement_30.h"

using namespace std;

int main(void)
{
	/*
	matrix matrix1("m1");
	//cout << matrix1.get_total_size() << endl;
	matrix_generator source2(matrix1.get_total_size());
	matrix matrix2("m2", source2.get_matrix());
	*/

	
	matrix_generator source1(16);
	matrix_generator source2(16);

	matrix matrix1("m1", source1.get_matrix());
	matrix matrix2("m2", source2.get_matrix());
	

	solver mySolver(matrix1, matrix2);
	mySolver.write_best_series();
	

	keep_window_open();
}
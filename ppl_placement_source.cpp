#include "ppl_placement_30.h"
#include <windows.h>

//-------------------------------------MATRIX CLASS---------------------------------------


ifstream get_file() {
	
	string name;
	cout << "enter name for input-file ";
	cin >> name;
	ifstream ist(name);
	if (ist) {
		return ist;
	}
	return get_file();
}

void matrix::set_dist_values() {
		
	ifstream ist = get_file();
	double in;

	while (true) {
		if (ist.eof()) {
			break;
		}
		else {
			ist >> in;
			values.push_back(in);
		}
	}
}

void matrix::plot_values() {
	int w = 10;

	cout << name << ":" << endl;
	cout << setw(w) << "index";
	for (int i = 0; i < element_count; i++) {
		cout << setw(w) << i;
	}
	cout << endl;

	for (int i = 0; i < values.size(); i++) {

		if (i % element_count == 0) {
			if (i == 0) {
				cout << setw(w) << i / element_count;
			}
			else {
				cout << "\n" << setw(w) << i / element_count;
			}
		}
		cout << setw(w) << setprecision(3) << values[i];
	}
	cout << endl;
}

//-------------------------------------MATRIX GENERATOR CLASS---------------------------------------

void matrix_generator::generate() {
	vector<double> m;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (i == j) {
				m.push_back(0);
			}
			else if (i > j) {
				m.push_back(m[j * col + i]);
			}
			else {
				m.push_back(randint(100));
			}
		}
	}
	matrix = m;
}

//-------------------------------------SOLVER CLASS---------------------------------------

vector<int> solver::calc_optimized_integers(int ts) {
	// size == total value count (36)
	int total_size = ts;
	// size == (6)
	int size = (int)sqrt(total_size);
	int shift = 2;
	int i = 0;

	vector<int> optimized_integers;

	while (i < total_size) {

		// if i < (6) && i != 0
		if (i < size && i != 0) {
			// add to m_opt
			optimized_integers.push_back(i);
		}
		// if i >= (6)
		else if (i >= size) {
			// if i % 6 == 0 (i == 6, 12, 18, 24 ...)
			if (i % size == 0) {
				i += shift;
				// if i is too large after shift, break
				if (i >= total_size) {
					break;
				}
				optimized_integers.push_back(i);
				shift++;
			}
			else {
				optimized_integers.push_back(i);
			}
		}
		i++;
	}

	/*
	for (int i = 0; i < optimized_integers.size(); i++)
	{
		cout << optimized_integers[i] << endl;
	}
	*/

	return optimized_integers;
}

void solver::calc()
{
	double best_sum = 0;
	int permutation_counter = 0;

	//vector<int> optimized_integers;
	//optimized_integers = calc_optimized_integers(m1.get_total_size());

	//cout << optimized_integers.size() << endl;
	//out << m1.get_element_count() << endl;
	//cout << m1.get_values().size() << endl;

	////////////////////////////TIMER
	//cout << "Solving LP ... ";
	__int64 ctr1 = 0, ctr2 = 0, freq = 0;
	if (QueryPerformanceCounter((LARGE_INTEGER *)&ctr1) != 0) {
		////////////////////////////TIMER

		//PERMUTATION
		vector<int> v;
		vector<int> permutation;
		vector<int> best_permutation;
		int size = m1.get_element_count();

		for (int i = 0; i < size; ++i) { v.push_back(i); }

		do {
			//cout << "." << endl;
			permutation_counter++;
			for (int i = 0; i < size; i++) {
				// fill vector with permutation indexes
				permutation.push_back(v[i]);
			}
			
			//INTEGRATE MATRIXES
			double temp = 0;
			//vector<double> best_values_temp;

			for (int i = 0; i < size; i++) {

				for (int j = 0; j < size; j++)
				{
					double m1val = m1.get_values()[i * size + j];
					double m2val = m2.get_values()[permutation[i] * size + j];

					double solution = 0.0;
					if (m1val != 0.0 && m2val != 0.0)
					{
						solution = m1val / m2val;
					}

					temp += solution;
				}
			}

			if (temp > best_sum) {
				best_sum = temp;
				best_permutation = permutation;
				//bestValue_series.push_back(best_values_temp);
				//maxSums.push_back(best_sum);

				//permutations.push_back(permutation);
			}

			temp = 0;
			//best_values_temp.clear();
			permutation.clear();
			//INTEGRATE MATRIXES END

		} while (next_permutation(v.begin(), v.end()));
		//PERMUTATION END

		////////////////////////////TIMER
		QueryPerformanceCounter((LARGE_INTEGER *)&ctr2);
		QueryPerformanceFrequency((LARGE_INTEGER *)&freq);
		// Print the time spent in microseconds to the console
		cout << "done in ";
		cout << ((ctr2 - ctr1) * 1.0 / freq);
		cout << " seconds." << endl;
		////////////////////////////TIMER

		for (int i = 0; i < size; i++)
		{
			cout << best_permutation[i] << " ";

		}


		//COUNT BEST POSSIBILITIES
		/*
		int count = 0;
		for (int i = 0; i < maxSums.size(); i++) {
			if (maxSums[i] == best_sum) {
				count++;
			}
		}

		cout << permutation_counter << " total combinations." << endl;
		cout << "Best Sum: " << best_sum << endl;
		if (count == 1) {
			cout << count << " best combination detected:" << endl;			
		}
		else {
			cout << count << " best combinations detected:" << endl;
		}
		
		for (int i = 0; i < maxSums.size(); i++) {
			if (maxSums[i] == best_sum) {
				for (int j = 0; j < size; j++) {
					cout << permutations[i][j] << " ";
				}
				cout << endl;
			}
		}
		*/
	}

}

void solver::write_best_series() {

	int size = m1.get_element_count();
	ofstream ost("best.txt");
	for (int i = 0; i < permutations.size(); i++) {
		for (int j = 0; j < size; j++) {
			ost << permutations[i][j] << endl;
		}
		for (int j = 0; j < size; j++) {
			ost << bestValue_series[i][j] << endl;
		}
	}
}
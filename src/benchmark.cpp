//============================================================================
// Name        : benchmark.cpp
// Author      : Stephen Bahr (sbahr@bu.edu)
// Version     : 1.0
// Description : A simple C++ program that performs a disk benchmark.
//============================================================================

#include <iostream>
#include <fstream>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>

using namespace std;

/**
 * Writes to a file named filename.
 *
 * @param filename - name of the file
 * @param size - size of the file to write in bytes
 *
 * @return The amount of time, in seconds, the time it took to execute the
 *     write. This is based off of CPU clock calculations.
 */
float write_file(string filename, int size){

	float time = 0;

	// construct new file
	ofstream file(filename);

	if (file.is_open()){

		string text;
		for (int i = 0; i < size; i++){
			if (i % 1024 == 0){
				text += "\n";
			}
			else{
				text += "a";
			}
		}

		clock_t start = clock();
		file << text;
		clock_t end = clock();

		file.close();

		time = (float)(end - start) / CLOCKS_PER_SEC;
	}
	else cout << "Unable to open " << filename << " for writing purposes." << endl;

	return time;
}

/**
 * Reads from a file named filename.
 *
 * @param filename - name of the file
 *
 * @return The amount of time, in seconds, the time it took to execute the
 *     read. This is based off of CPU clock calculations.
 */
float read_file(string filename){

	float time = 0;

	ifstream file(filename);
	string text;

	if (file.is_open()){

		clock_t start = clock();
		while (getline(file, text)){
			//cout << text << endl;
		}
		clock_t end = clock();

		file.close();

		time = (float)(end - start) / CLOCKS_PER_SEC;
	}
	else cout << "Unable to read " << filename << endl;

	return time;
}

int main() {

	cout << "Welcome to a simple Benchmark program written in C++." << endl;

	int file_size;
	cout << "Enter the size of the file to read/write: " << endl;
	cin >> file_size;

	cout << endl << "Running Benchmark program" << endl;
	cout << "100 total files of " << file_size << " bytes..." << endl << endl;

	// we want 100 files
	int file [100] = {};
	for (int i = 0; i < 100; i++){
		file[i] = i;
	}

	// make directory for output
	mkdir("./output/", 0777);

	// shuffle for random reads
	random_shuffle(&file[0], &file[100]);

	// write 100 files
	float total_write_time = 0;
	for (int w = 0; w < 100; w++){
		string name = "./output/test-" + to_string(w) + ".txt";
		total_write_time += write_file(name, file_size);
	}

	// read 100 files randomly
	float total_read_time = 0;
	for (int r = 0; r < 100; r++){
		string name = "./output/test-" + to_string(file[r]) + ".txt";
		total_read_time += read_file(name);
	}

	cout << "Total write time: " << total_write_time << " secs." << endl;
	cout << "Total read time: " << total_read_time << " secs." << endl << endl;

	cout << "Average write time for a " << file_size << "-byte file is ";
	cout << total_write_time / 100 << " secs." << endl;

	cout << "Average read time for a " << file_size << "-byte file is ";
	cout << total_read_time / 100 << " secs." << endl << endl;

	return 0;
}

//============================================================================
// Name        : benchmark.cpp
// Author      : Stephen Bahr (sbahr@bu.edu)
// Version     : 1.0
// Description : A simple C++ program that performs a disk benchmark.
// Sources: 
//     Library references: http://www.cplusplus.com/reference/
//     Benchmarking CPU: http://stackoverflow.com/questions/275004/c-timer-function-to-provide-time-in-nano-seconds
//     Writing directly to disk: http://stackoverflow.com/questions/16605233/how-to-disable-buffering-on-a-stream
//============================================================================

#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <algorithm>

#include <sys/resource.h>
#include <sys/types.h>

using namespace std;

/**
 * Compute the CPU time between two timespecs.
 *
 * @param start - the starting timespec
 * @param end - the ending timespec
 *
 * @return The amount of time, in nanoseconds, between the two timespecs.
 */
double compute_cpu_time(struct timespec start, struct timespec end){
	double nano = static_cast<double>(end.tv_nsec - start.tv_nsec);
	double sec = static_cast<double>((end.tv_sec - start.tv_sec) * 1E9);

	return sec + nano;
}

/**
 * Writes to a file named filename.
 *
 * @param filename - name of the file
 * @param size - size of the file to write in bytes
 *
 * @return The amount of time, in seconds, it took to execute the
 *     write. This is based off of CPU clock calculations.
 */
double write_file(string filename, int size){

	double time = 0;

	// mark file to be written to disk directly
	ofstream file;
	file.rdbuf()->pubsetbuf(0, 0);
	file.open(filename.c_str());

	if (file.is_open()){

		struct timespec start, end;
		clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
		string text;
		for (int i = 0; i < size; i++){

			if (i % 1024 == 0){
				text += "\n";

				// write text to disk
				file << text;
				text = "";
			}
			else{
				text += "a";
			}
		}

		clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);

		// calculate time spent writing
		time = compute_cpu_time(start, end);

		file.close();
	}
	else cout << "Unable to open " << filename << " for writing purposes." << endl;

	return time;
}

/**
 * Reads from a file named filename.
 *
 * @param filename - name of the file
 *
 * @return The amount of time, in seconds, it took to execute the
 *     read. This is based off of CPU clock calculations.
 */
double read_file(string filename){

	double time = 0;

	// mark file to be read from disk directly
	ifstream file;
	file.rdbuf()->pubsetbuf(0, 0);
	file.open(filename.c_str());
	string text;

	if (file.is_open()){

		// time only the reading of the file
		struct timespec start, end;
		clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);

		while (getline(file, text)){
			// do nothing, as we don't actually want to store it anywhere
		}

		clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);

		time = compute_cpu_time(start, end);

		file.close();
	}
	else cout << "Unable to read " << filename << endl;

	return time;
}

int main() {

	cout << "Welcome to a simple benchmark program written in C++." << endl;

	int file_size;
	cout << "Enter the size of the file to read/write: " << endl;
	cin >> file_size;

	cout << endl << "Running Benchmark program" << endl;
	cout << "1000 total files of " << file_size << " bytes..." << endl << endl;

	int num_files = 1000;

	// we want 100 files, cannot instantiate variable amount
	int file [1000] = {};
	for (int i = 0; i < num_files; i++){
		file[i] = i;
	}

	// make directory for output
	mkdir("./output/", 0777);

	// shuffle for random reads
	random_shuffle(&file[0], &file[num_files]);

	// write num_files files
	double total_write_time = 0;
	for (int w = 0; w < num_files; w++){
		string name = "./output/test-" + to_string(static_cast<long long>(w)) + ".txt";
		total_write_time += write_file(name, file_size);
	}

	// read num_files randomly
	double total_read_time = 0;
	for (int r = 0; r < num_files; r++){
		string name = "./output/test-" + to_string(static_cast<long long>(file[r])) + ".txt";
		total_read_time += read_file(name);
	}

	double write_avg = total_write_time / num_files / 1E9;
	double read_avg = total_read_time / num_files / 1E9;

	double write_rate = (file_size / write_avg / 1000000);
	double read_rate = (file_size / read_avg / 1000000);

	cout << "Total write time: " << total_write_time / 1E9 << " secs." << endl;
	cout << "Total read time: " << total_read_time / 1E9 << " secs." << endl << endl;

	cout << "Average write time for a " << file_size << "-byte file is ";
	cout << write_avg << " secs." << endl;

	cout << "Average read time for a " << file_size << "-byte file is ";
	cout << read_avg << " secs." << endl << endl;

	cout << "Writing rate is " << write_rate << " mbps." << endl;
	cout << "Reading rate is " << read_rate << " mbps." << endl << endl;

	cout << "Note: This is CPU clock time, not Wall time." << endl;

	return 0;
}

## Introduction to Benchmark
Benchmark is a simple C++ program that performs a disk benchmark.

## Background
We don't know what hard drives to buy! - We have a series of hard drives that we are considering
for installation into our file servers. Write a simple pogram in C++ that performs a simple
disk benchmark.

## Requirements
This program was written and tested on MacOS 10.9.5, and further tested on various Scientific
Linux 6 workstations.
- g++/gcc 4.4.7 or newer

## Instructions
Use g++ to build the file:
```
g++ -std=c++0x -lrt benchmark.cpp -o benchmark
```

Run the application:
```
./benchmark
```

## Snapshots
Below is a screenshot of csa2.bu.edu, Boston University's Computer Science's main Linux computer, running 100 files of 1MB in size.
- ![alt text] (https://github.com/Unknowncmbk/Benchmark/blob/master/csa2.bu.edu-linux.png "csa2.bu.edu 100x1MB")

Below is a screenshot of csa3.bu.edu, Boston University's Computer Science's secondary Linux computer, running 100 files of 1MB in size, and then 1000 files of 1MB.
- ![alt text] (https://github.com/Unknowncmbk/Benchmark/blob/master/csa3.bu.edu-linux.png "csa3.bu.edu 100x1MB")
- ![alt text] (https://github.com/Unknowncmbk/Benchmark/blob/master/csa3.bu.edu-linux-1000.png "csa3.bu.edu 1000x1MB")

Other screenshots below include running on Dell Precision T1600 workstations:
- ![alt text] (https://github.com/Unknowncmbk/Benchmark/blob/master/duey-linux.png "duey-linux 100x1MB")
- ![alt text] (https://github.com/Unknowncmbk/Benchmark/blob/master/huey-linux.png "huey-linux 100x1MB")

## Improvements
The following improvements can be made on this program:
- Allow variable amount of files to input.
- Allow for timing of Wall time (the time the program takes to execute, as viewable from an outside source).

## License
A copy of the Benchmark's license can be found [here](https://github.com/Unknowncmbk/Benchmark/blob/master/LICENSE).

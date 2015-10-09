/* ADNA
 * FASTQ File Splitter
 */

#include <cstdio>
#include <iostream>
#include <fstream>
#include <thread>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;
string fastq_orig;
int numthreads;
int alive;

void splicer(int threadnum) {
	cerr << "Starting thread " << threadnum <<endl;
	ifstream fin;
	ofstream curof;
	string line;
	int lineno;
	fin.open(fastq_orig, ios::in);
	if (!fin.is_open()) {
		cerr << "Error: Cannot open file" << endl;
		exit(1);
	}
	int roundnum = 0;
	// where should i start? 
	//int start = (threadnum*4)+(numthreads*4*roundnum);
	for(int i=0; i<(threadnum*4); ++i) {
		fin.ignore(numeric_limits<streamsize>::max(),'\n');
	}
	lineno = (threadnum*4);
	
	while(!fin.eof()) {
		getline(fin, line);
		if (line.length() < 4) break;
		string head = "./raw/"+line.substr(5)+"--t"+to_string(threadnum);
		replace(head.begin(), head.end(), ':', '_');
		replace(head.begin(), head.end(), ' ', '_');
		curof.open(head, ios::out);
		curof<<line<<endl;
		for (int i=0; i<3; i++) {
			getline(fin, line);
			curof<<line<<endl;
		}
		curof.close();
		roundnum++;
		for(int i=0; i<(numthreads*4)-4; ++i) {
			fin.ignore(numeric_limits<streamsize>::max(),'\n');
		}
	}
	
	alive--;
	fin.close();
	exit(0);
}

int main(int argc, char **argv) {
	cout << "ADNA Split" << endl;
	if (argc < 2) {
		cout << "Error: Not enough arguments" << endl;
		cout << "Usage: " << argv[0] << " <input_fastq_file> -t <threads> -o <output> <OPTIONS>" << endl;
		return -1;
	}
	fastq_orig = argv[1];

	istringstream ss(argv[3]);
	if (!(ss >> numthreads)) { 
		cerr << "Error: Invalid number of threads" << argv[3] << '\n';
	}
	
	cerr << "Starting pool with " << numthreads << " threads"<<endl;
	thread threadpool[numthreads];
	alive = numthreads;
	
	for (int t=0; t < numthreads; t++) {
		threadpool[t] = thread(splicer, t);
	}
	for (int t=0; t < numthreads; t++) {
		threadpool[t].join();
	}
	while (alive>0);
	cout << "The thread pool has terminated." << endl;
	return 0;
}



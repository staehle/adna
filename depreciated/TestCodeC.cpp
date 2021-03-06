//============================================================================
// Name        : TestCodeC.cpp
// Author      : Steinar Bakke
// Version     :
// Copyright   : Your copyright notice
// Description : C++ Using FastQFile (LibStatGen) Library
//============================================================================

#include <iostream>
#include <fstream>
#include <string>
//#include <libStatGen.a/FastQFile.h>
#include "FastQFile.h"
#include "FastQFile.cpp"
#include <cstdio>
#include <string>
using namespace std;

//Working with an existing FastQ Processor. Not working right now


FastQFile fastQFile;

int main(){
	FastQFile fastQFile;
	   String filename = 'test1.fastq';
	   // Open the fastqfile with the default UNKNOWN space type which will determine the
	   // base type from the first character in the sequence.
	   if(fastQFile.openFile(filename) != FASTQ_SUCCESS)
	   {
	      // Failed to open the specified file.
	      // Report the error and exit (handled by error).
	      error("Failed to open file: %s", filename.c_str());
	      return (<your return info to indicate failure>);
	   }
	   // Keep reading the file until there are no more fastq sequences to process.
	   while (fastQFile.keepReadingFile())
	   {
	      // Read one sequence. This call will read all the lines for
	      // one sequence.
	      /////////////////////////////////////////////////////////////////
	      // NOTE: It is up to you if you want to process only for success:
	      //    if(readFastQSequence() == FASTQ_SUCCESS)
	      // or for FASTQ_SUCCESS and FASTQ_INVALID:
	      //    if(readFastQSequence() != FASTQ_FAILURE)
	      // Do NOT try to process on a FASTQ_FAILURE
	      /////////////////////////////////////////////////////////////////
	      if(fastQFile.readFastQSequence() == FastQFile::FASTQ_SUCCESS)
	      {
	         // The sequence is valid.
	         <Your Processing Here>
	         // For example if you want to print the lines of the sequence:
	         printf("The Sequence ID Line is: %s", fastQFile.mySequenceIdLine.c_str());
	         printf("The Sequence ID is: %s", fastQFile.mySequenceIdentifier.c_str());
	         printf("The Sequence Line is: %s", fastQFile.myRawSequence.c_str());
	         printf("The Plus Line is: %s", fastQFile.myPlusLine.c_str());
	         printf("The Quality String Line is: %s", fastQFile.myQualityString.c_str());
	      }
	   }
	   // Finished processing all of the sequences in the file.
	   // Close the input file.
	   fastQFile.closeFile();
	   return 0; //(<your return info>); // It is up to you to determine your return.
}
/*
int main() {

char mychar = '7';

string fastq_read1;
string fastq_read2;

ifstream fin;
ofstream curof;
string line;
//fin.open(fastq_read1, ios::in);

/*string line;
 ifstream myfile ("test1.text");
 if (myfile.is_open())
 {
   while (! myfile.eof() )
   {
     getline (myfile,line);
     cout << line << endl;
   }
   myfile.close();
 }

 else cout << "Unable to open file";



// to use the Quality checks from 0 as the lowest to 96 as the highest, if scanning token by token

// will already be implemented if I can get my libStatGen library to work

	cout << (int(mychar)-33) << endl; // prints !!!Hello World!!!  //33 if first ASCII number should be 0 and not 1 for quality check
	return 0;
}
*/

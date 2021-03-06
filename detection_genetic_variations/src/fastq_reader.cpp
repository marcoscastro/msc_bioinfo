#include <iostream>
#include <stdlib.h>
#include "fastq_reader.h"

/*! \file fastq_reader.cpp
 *	\brief Source-code of the class FASTQReader.
 *	\author Marcos Castro
 *	\copyright GNU Public License.
 *	\date 28/03/2016
 *
 */

FASTQReader::FASTQReader()
{
	total_reads = 0;
}

void FASTQReader::addFASTQ(const char * file_path)
{
	std::ifstream infile;

	// opens the file file_path
	infile.open(file_path);

	// tests if the file exists
	if (!infile.good())
	{
		infile.close(); //closes the file
		std::cerr << "The file \"" << file_path << "\" does not exist!\n";
		exit(0); // terminates the execution
	}

	std::string line; // line will be read
	std::string read_data; // data of the read

	// marker that indicates the amount of read lines
	int count = 0;

	// counter of reads
	int number_reads = 0;

	// flag that indicates if should create a read
	bool create_read = false;

	// to get you all the lines
	while(!infile.eof())
	{
		// saves the line in string data
		getline(infile, line);

		// tests if should be created to read
		if(create_read)
		{
			// creates a new read
			Read read(read_data, number_reads);

			// adds the read in the vector of reads
			reads.push_back(read);

			// increases number of reads
			number_reads += 1;

			// reset the variables
			count = 0;
			create_read = false;
			read_data = "";
		}

		read_data += line + "\n"; // adds the data
		count++; // increments the count

		// checks if was obtained all data of the read
		if(count % 4 == 0)
		{
			create_read = true;
		}
	}

	// increases the total of reads
	total_reads += number_reads;

	// closes the file
	infile.close();
}

std::vector<Read>& FASTQReader::getReads()
{
	return reads;
}

int FASTQReader::getTotalReads()
{
	return total_reads;
}

void FASTQReader::showRead(long long int index)
{
	if(index >= total_reads)
	{
		std::cerr << "The index " << index << " not exists!\n";
		exit(0); // terminates the execution
	}
	
	// shows information of the reads
	std::cout << reads[index].getHeader() << "\n";
	std::cout << reads[index].getSequence() << "\n";
	std::cout << reads[index].getQualityScore() << "\n";
}

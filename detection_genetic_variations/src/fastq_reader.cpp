#include <iostream>
#include <stdlib.h>
#include "fastq_reader.h"

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
		std::cerr << "The file \"" << file_path << "\" does not exist!\n";
		exit(0); // terminates the execution
	}

	std::string line; // line will be read
	std::string read_data; // data of the read

	// marker that indicates the amount of read lines
	int count = 0;

	// counter of reads
	long long int number_reads = 0;

	// flag that indicates if should create a read
	bool create_read = false;

	// to get you all the lines
	while(!infile.eof())
	{
		// saves the line in string data
		getline(infile, line);

		// tests should be created to read
		if(create_read)
		{
			// creates a new read
			Read read(read_data);

			// adds the read in the vector of reads
			reads.push_back(read);

			// increases number of reads
			number_reads += 1;

			// reset the variables
			count = 0;
			create_read = false;
			read_data = "";
		}

		read_data += line; // adds the data
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

std::vector<Read> & FASTQReader::getReads()
{
	return reads;
}

long long int FASTQReader::getTotalReads()
{
	return total_reads;
}

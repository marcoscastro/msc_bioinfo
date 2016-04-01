#include <vector>
#include <iostream>
#include "read.h"

Read::Read(const std::string & read_data)
{
	std::cout << read_data;
	
	// split string with the delimiter of newline

	std::string::size_type i = 0;
	std::string::size_type j = read_data.find('\n');
	std::vector<std::string> v;

	while(j != std::string::npos)
	{
		v.push_back(read_data.substr(i, j - i));
		i = ++j;
		j = read_data.find('\n', j);

		if(j == std::string::npos)
		{
			v.push_back(read_data.substr(i, read_data.length()));
		}
	}
	
	std::cout << v.size() << "\n";

	// make assignments
	header = v[0];
	sequence = v[1];
	quality_score = v[3];
}

std::string& Read::getHeader()
{
	return header;
}

std::string& Read::getSequence()
{
	return sequence;
}

std::string& Read::getQualityScore()
{
	return quality_score;
}

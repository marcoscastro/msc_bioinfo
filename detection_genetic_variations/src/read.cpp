#include <vector>
#include <iostream>
#include "read.h"

/*! \file read.cpp
 *	\brief Source-code of the class Read.
 *	\author Marcos Castro
 *	\copyright GNU Public License.
 *	\date 01/04/2016
 *
 */

Read::Read(const std::string& read_data, int ID)
{
	this->ID = ID;
	
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

int Read::getID()
{
	return ID;
}


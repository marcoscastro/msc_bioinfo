#include "kmer.h"
#include <numeric>

/*! \file kmer.cpp
 *	\brief Source-code of the class Edge.
 *	\author Marcos Castro
 *	\copyright GNU Public License.
 *	\date 08/04/2016
 *
 */

KMer::KMer(std::string& sequence)
{
	this->sequence = sequence;

	// initilizes the vectors
	for(int i = 0; i < 4; i++)
	{
		successors.push_back(false);
		antecessors.push_back(false);
	}
}

std::string& KMer::getSequence()
{
	return sequence;
}

void KMer::setSuccessor(char base)
{
	/*
		successors[0] -> A
		successors[1] -> T
		successors[2] -> C
		successors[3] -> G
	*/
	
	if(base == 'A')
		successors[0] = true;
	else if(base == 'T')
		successors[1] = true;
	else if(base == 'C')
		successors[2] = true;
	else // base G
		successors[3] = true;
}

void KMer::setAntecessor(char base)
{
	/*
		Example:
		if the base is 'A' then the antecessor
		is 'T' because of the reverse complement.
	*/
	if(base == 'A')
		antecessors[1] = true; // 'T'
	else if(base == 'T')
		antecessors[0] = true; // 'A'
	else if(base == 'C')
		antecessors[3] = true; // 'G'
	else // base G
		antecessors[2] = true; // 'C'
}

void KMer::addRead(int id)
{
	reads_id.insert(id);
}

int KMer::getTotalReads()
{
	return reads_id.size();
}

int KMer::getTotalSuccessors()
{
	return std::accumulate(successors.begin(), successors.end(), 0);
}

std::set<int> const & KMer::getReads()
{
	return reads_id;
}
/*! \file kmer.cpp
 *	\brief Source-code of the class KMer.
 *	\author Marcos Castro
 *	\copyright GNU Public License.
 *	\date 13/04/2016
 *
 */

#include "kmer.h"

KMer::KMer(std::string& sequence)
{
	this->sequence = sequence;
}

std::string& KMer::getSequence()
{
	return sequence;
}

std::set<int> KMer::getReads()
{
	return reads;
}

void KMer::addRead(int ID_read)
{
	reads.insert(ID_read);
}

int KMer::getTotalReads()
{
	return reads.size();
}

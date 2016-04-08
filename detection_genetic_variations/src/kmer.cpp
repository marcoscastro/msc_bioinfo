#include "kmer.h"

/*! \file kmer.cpp
 *	\brief Source-code of the class KMer.
 *	\author Marcos Castro
 *	\copyright GNU Public License.
 *	\date 06/04/2016
 *
 */

KMer::KMer(std::string& sequence, int K)
{
	this->sequence = sequence;
	prefix = sequence.substr(0, K - 1);
	suffix = sequence.substr(1, K - 1);
}

std::string& KMer::getSequence()
{
	return sequence;
}

std::string& KMer::getPrefix()
{
	return prefix;
}

std::string& KMer::getSuffix()
{
	return suffix;
}

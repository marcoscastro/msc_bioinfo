#include "kmer.h"

/*! \file kmer.cpp
 *	\brief Source-code of the class KMer.
 *	\author Marcos Castro
 *	\copyright GNU Public License.
 *	\date 06/04/2016
 *
 */

KMer::KMer(std::string& sequence, std::string& prefix, std::string& suffix)
{
	this->sequence = sequence;
	this->prefix = prefix;
	this->suffix = suffix;
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

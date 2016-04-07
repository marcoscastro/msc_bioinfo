#include "kmer.h"

/*! \file graph.cpp
 *	\brief Source-code of the class KMer.
 *	\author Marcos Castro
 *	\copyright GNU Public License.
 *	\date 06/04/2016
 *
 */

KMer::KMer(std::string& name)
{
	this->name = name;
}

std::string& KMer::getName()
{
	return name;
}
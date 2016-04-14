#include "edge.h"

/*! \file edge.cpp
 *	\brief Source-code of the class Edge.
 *	\author Marcos Castro
 *	\copyright GNU Public License.
 *	\date 08/04/2016
 *
 */

Edge::Edge(std::string& sequence)
{
	this->sequence = sequence;
}

std::string& Edge::getSequence()
{
	return sequence;
}

int Edge::getTotalReads()
{
	return total_reads;
}

void Edge::addRead(int ID_read)
{
	reads.insert(ID_read);
}
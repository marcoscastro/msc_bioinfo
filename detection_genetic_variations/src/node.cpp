/*! \file node.cpp
 *	\brief Source-code of the class Node.
 *	\author Marcos Castro
 *	\copyright GNU Public License.
 *	\date 13/04/2016
 *
 */

#include "node.h"

Node::Node(std::string& sequence)
{
	this->sequence = sequence;
}

std::string& Node::getSequence()
{
	return sequence;
}
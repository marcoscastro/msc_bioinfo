#ifndef KMER_H
#define KMER_H

#include <string>
#include <set>

/*! \file node.h
 *	\brief Node representation.
 *	\author Marcos Castro
 *	\copyright GNU Public License.
 *	\date 13/04/2016
 *
 *	Node represents the vertex of the De Bruijn Graph.
 *
 */

/*! \class Node
 * Class that represents the vertex of the graph.
 */
class Node
{
private:
	std::string sequence; //**< String that represents the node. */

public:

	/*!
	 * Constructor
	 *
	 * @param[in] sequence node sequence.
	 */
	Node(std::string& sequence);
	
	/*
		This is necessary because the class map creates
		a valor same when a key not exists. If the key
		not exists then the value returned is 0.
	*/
	Node(){}

	/*!
	 * Return the sequence of the node.
	 *
	 * \return the sequence of the node.
	 */
	std::string& getSequence();
	
	bool operator<(const Node& src) const
	{
		return (this->sequence < src.sequence);
	}
};

#endif

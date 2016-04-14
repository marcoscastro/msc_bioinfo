#ifndef EDGE_H
#define EDGE_H

#include <string>
#include <set>

/*! \file edge.h
 *	\brief Edge representation.
 *	\author Marcos Castro
 *	\copyright GNU Public License.
 *	\date 08/04/2016
 *
 *	Edge represents the edge of the De Bruijn Graph.
 *
 */

/*! \class Edge
 * Class that representes the edge.
 */
class Edge
{
private:
	std::string sequence; //**< Sequence of the read. */
	int total_reads; //**< Total of reads of the edge. */
	std::set<int> reads; //**< Set of the ID's of the reads. */

public:

	/*!
	 * Constructor
	 *
	 * @param[in] sequence sequence of the read.
	 */
	Edge(std::string& sequence);
	
	Edge(){}

	/*!
	 * Return the sequence of the read.
	 *
	 * \return the sequence of the read.
	 */
	std::string& getSequence();
	
	/*!
	 * Return the total of reads that passing in the edge.
	 *
	 * \return the total of reads of the edge.
	 */
	int getTotalReads();
	
	
	/*!
	 * Adds a ID of a read to the set of reads of the edge.
	 *
	 * @param[in] ID_read ID of the read.
	 */
	void addRead(int ID_read);
	
	bool operator<(const Edge& src) const
	{
		return (this->sequence < src.sequence);
	}
};

#endif

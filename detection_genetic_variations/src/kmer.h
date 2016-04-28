#ifndef EDGE_H
#define EDGE_H

#include <set>
#include <vector>
#include <string>

/*! \file kmer.h
 *	\brief KMer representation.
 *	\author Marcos Castro
 *	\copyright GNU Public License.
 *	\date 08/04/2016
 *
 *	KMer represents the edge of the De Bruijn Graph.
 *
 */

/*! \class KMer
 * Class that representes the edge.
 */
class KMer
{
private:
	std::string sequence; //**< Sequence kmer. */
	std::set<int> reads_id; //**< IDs of the reads. */
	std::vector<bool> successors; //**< K-Mer's successors. */

public:

	/*!
	 * Constructor
	 *
	 * @param[in] sequence sequence kmer.
	 */
	KMer(std::string& sequence);
	
	/*
		This is necessary because the class map creates
		a valor same when a key not exists. If the key
		not exists then the value returned is 0.
	*/
	KMer(){}

	/*!
	 * Return the sequence of the kmer.
	 *
	 * \return the sequence of the kmer.
	 */
	std::string& getSequence();
	
	/*!
	 * Set base_index for the successor.
	 *
	 * @param[in] base_index index of the base.
	 */
	void setSuccessor(int base_index);
	
	/*!
	 * Adds ID of the read.
	 *
	 * @param[in] read_id ID of the read.
	 */
	void addRead(int read_id);
	
	/*!
	 * Return the total of reads.
	 *
	 * \return the total of reads.
	 */
	int getTotalReads();
	
	/*!
	 * Return the total of successors.
	 *
	 * \return the total of successors.
	 */
	int getTotalSuccessors();
	
	bool operator<(const KMer& src) const
	{
		return (this->sequence < src.sequence);
	}
};

#endif

#ifndef EDGE_H
#define EDGE_H

#include <vector>
#include <string>

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
	std::string kmer_src; //**< k-mer of source*/
	std::string kmer_dest; //**< k-mer of destination */
	int total_reads; //**< total of reads of the edge */
	std::vector<int> reads; //**< vector of ID of reads of the edge */

public:

	/*!
	 * Constructor
	 *
	 * @param[in] kmer_src vertex of source.
	 * @param[in] kmer_dest vertex of destination.
	 */
	Edge(std::string& kmer_src, std::string& kmer_dest);

	/*!
	 * Return the k-mer of source.
	 *
	 * \return the k-mer of source.
	 */
	std::string& getKMerSrc();

	/*!
	 * Return the k-mer of destination.
	 *
	 * \return the k-mer of destination.
	 */
	std::string& getKMerDest();
	
	/*!
	 * Return the total of reads that passing in the edge
	 *
	 * \return the total of reads of the edge.
	 */
	int getTotalReads();
	
	/*!
	 * Set the set of reads
	 *
	 */
	void setReads(std::vector<int>& reads);
};

#endif

#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <map>
#include <set>
#include "read.h"
#include "kmer.h"

/*! \file graph.h
 *	\brief De Bruijn Graph representation.
 *	\author Marcos Castro
 *	\copyright GNU Public License.
 *	\date 04/04/2016
 *
 *	This file represents the De Bruijn Graph.
 *
 *	References:
 *	\n https://www.youtube.com/watch?v=f-ecmECK7lw
 *	\n http://www.cs.jhu.edu/~langmea/resources/lecture_notes/assembly_dbg.pdf
 */

/*! \class DeBruijnGraph
 * Class that represents the De Bruijn Graph.
 */
class DeBruijnGraph
{
private:
	int K; //**< Length of the K-mer */
	unsigned long long total_kmers; //**< Total of K-mers */
	std::map<KMer, std::set<Read> > kmers; //**< Map of K-mers */

public:

	/*!
	 * Constructor
	 *
	 * @param[in] K length of the k-mers.
	 * @param[in] reads vector of reads.
	 * @param[in] total_reads the total of reads.
	 */
	DeBruijnGraph(int K, std::vector<Read>& reads, int total_reads);

	/*!
	 * Show all the k-mers.
	 *
	 */
	void showKMers();

	/*!
	 * Return the total of k-mers.
	 *
	 * \return the total of k-mers.
	 */
	unsigned long long getTotalKMers();
};

#endif

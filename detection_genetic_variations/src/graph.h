#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <map>
#include "read.h"
#include "kmer.h"
#include "node.h"

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
	int K; //**< Length of the k-mer. */
	int total_kmers; //**< Total of k-mers. */
	bool verbose; //**< Shows the information about the execution. */
	
	std::map<std::string, KMer > kmers; //**< Map of k-mers */

public:

	/*!
	 * Constructor
	 *
	 * @param[in] K length of the k-mers.
	 * @param[in] reads vector of reads.
	 * @param[in] total_reads the total of reads.
	 * @param[in] verbose flag to show the information about the execution.
	 */
	DeBruijnGraph(int K, std::vector<Read>& reads, int total_reads, bool verbose = false);

	/*!
	 * Show all the k-mers.
	 */
	void showKMers();
};

#endif

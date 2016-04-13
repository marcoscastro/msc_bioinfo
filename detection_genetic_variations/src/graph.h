#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <map>
#include "read.h"
#include "kmer.h"
#include "edge.h"

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
	int total_edges; //**< Total of edges. */
	bool verbose; //**< Shows the information about the execution. */
	
	/*
		The key is the k-mer sequence.
		The value is the k-mer object.
	*/
	std::map<std::string, KMer> kmers; //**< Map of K-mers. */
	
	/*
		Stores all the edges of the graph.
		The key is a k-mer.
		The value is a vector of edges.
	*/
	std::map<std::string, std::vector<Edge> > edges; //**< Map of edges. */

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

	/*!
	 * Return the total of k-mers.
	 *
	 * \return the total of k-mers unique.
	 */
	int getTotalKMers();
	
	/*!
	 * Builds the De Bruijn Graph.
	 */
	void build();
	
	/*!
	 * Shows the edges of the De Bruijn Graph.
	 */
	void showEdges();
};

#endif

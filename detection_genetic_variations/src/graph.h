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
	int K; //**< Length of the K-mer */
	int total_kmers; //**< Total of K-mers */
	bool verbose; //**< shows the information about the execution */
	
	/*
		the key is a KMer object.
		
		the value is a map: the key is the ID read and value is
		a counter of the amount of times that the read appears.
	*/
	std::map<KMer, std::map<int, int> > kmers; //**< Map of K-mers */
	
	// stores all the edges of the graph
	std::vector<Edge> edges; //**< vector of edges */

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
	void showKMers(bool show_details = true);

	/*!
	 * Return the total of k-mers.
	 *
	 * \return the total of k-mers unique.
	 */
	int getTotalKMers();
	
	/*!
	 * Builds the De Bruijn Graph
	 */
	void build();
	
	/*!
	 * Shows the edges of the De Bruijn Graph
	 */
	void showEdges();
};

#endif

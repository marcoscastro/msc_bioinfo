#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <map>
#include "read.h"

/*! \brief Class to build De Bruijn Graph.
 *	\author Marcos Castro
 *	\copyright GNU Public License.
 *	\date 04/04/2016
 *
 *	Last modified: 04/04/2016
 *
 *	This file represents the De Bruijn Graph.
 *
 *	References:
 *	\n https://www.youtube.com/watch?v=f-ecmECK7lw
 *	\n http://www.cs.jhu.edu/~langmea/resources/lecture_notes/assembly_dbg.pdf
 */
class DeBruijnGraph
{
private:
	int K; //**< Length of the k-mer */
	long long int total_kmers; //**< Total of k-mers */
	std::map<std::string, int> kmers; //**< Vector of K-mers */

public:

	/*!
	 * Constructor
	 *
	 * @param[in] K length of the k-mers.
	 */
	DeBruijnGraph(int K, std::vector<Read>& reads, int total_reads);
	
	/*!
	 * Show all the k-mers.
	 *
	 */
	void showKMears();
	
	/*!
	 * Return the total of k-mers.
	 *
	 * \return the total of k-mers.
	 */
	long long int getTotalKMears();
};

#endif

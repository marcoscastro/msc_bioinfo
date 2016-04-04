#ifndef GRAPH_H
#define GRAPH_H

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
	const short int K; //**< Length of the k-mer */

public:

	/*!
	 * Constructor
	 *
	 * @param[in] K length of the k-mers.
	 */
	DeBruijnGraph(const short int K);
};

#endif

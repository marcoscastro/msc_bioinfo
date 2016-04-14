#ifndef KMER_H
#define KMER_H

#include <string>
#include <set>

/*! \file kmer.h
 *	\brief KMer representation.
 *	\author Marcos Castro
 *	\copyright GNU Public License.
 *	\date 13/04/2016
 *
 *	KMer represents the vertex of the De Bruijn Graph.
 *
 */

/*! \class KMer
 * Class that represents the k-mer (vertex of the graph).
 */
class KMer
{
private:
	std::string sequence; //**< String that represents the k-mer. */

public:

	/*!
	 * Constructor
	 *
	 * @param[in] sequence k-mer sequence.
	 */
	KMer(std::string& sequence);
	
	/*
		This is necessary because the class map creates
		a valor same when a key not exists. If the key
		not exists then the value returned is 0.
	*/
	KMer(){}

	/*!
	 * Return the sequence of the k-mer.
	 *
	 * \return the sequence of the k-mer.
	 */
	std::string& getSequence();
	
	
	bool operator<(const KMer& src) const
	{
		return (this->sequence < src.sequence);
	}
};

#endif

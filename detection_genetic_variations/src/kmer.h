#ifndef KMEAR_H
#define KMEAR_H

#include <string>

/*! \file kmer.h
 *	\brief K-Mer representation.
 *	\author Marcos Castro
 *	\copyright GNU Public License.
 *	\date 06/04/2016
 *
 *	K-Mer is a string of length K. It's a substring of the read.
 *
 * The KMer class represents the vertex of the De Bruijn Graph.
 *
 */

/*! \class KMer
 * Class that representes the K-Mer.
 */
class KMer
{
private:
	std::string sequence; //**< sequence kmer */
	std::string prefix; //**< prefix kmer */
	std::string suffix; //**< suffix kmer */

public:

	/*!
	 * Construtor of the KMer class.
	 *
	 * @param[in] sequence k-mer.
	 * @param[in] length of the k-mer.
	 */
	KMer(std::string& sequence, int K);
	
	//KMer(){}

	/*!
	 * Gets the name of the K-mer.
	 *
	 * \return the name of the K-mer.
	 */
	std::string& getSequence();
	
	/*!
	 * Gets the prefix of the K-mer.
	 *
	 * \return the prefix of the K-mer.
	 */
	std::string& getPrefix();
	
	/*!
	 * Gets the suffix of the K-mer.
	 *
	 * \return the suffix of the K-mer.
	 */
	std::string& getSuffix();
	
	bool operator<(const KMer& src) const
	{
	    return (this->sequence < src.sequence);
	}
};

#endif	
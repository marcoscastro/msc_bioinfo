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

public:

	/*!
	 * Construtor of the KMer class.
	 */
	KMer(std::string& sequence);

	/*!
	 * Gets the name of the K-mer.
	 *
	 * \return the name of the K-mer.
	 */
	std::string& getSequence();
	
	bool operator<(const KMer& src) const
    {
        return (this->sequence < src.sequence);
    }
};

#endif

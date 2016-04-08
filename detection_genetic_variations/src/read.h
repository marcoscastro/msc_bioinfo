#ifndef READ_H
#define READ_H

#include <string>

/*! \file read.h
 *	\brief Read representation.
 *	\author Marcos Castro
 *	\copyright GNU Public License.
 *	\date 01/04/2016
 *
 *	Each entry in a FASTQ file consists of four lines:
 *	\n 1) Sequence identifier
 *	\n 2) Sequence
 *	\n 3) Quality score identifier line (consisting of a +)
 *	\n 4) Quality score
 *
 *	Reference: http://goo.gl/ZMShLe (Illumina website)
 */

/*! \class Read
 * Class that represents a read.
 */
class Read
{
private:
	int ID; //**< ID of the read */
	std::string header; //**< Header of the read */
	std::string sequence; //**< sequence */
	std::string quality_score; //**< quality score */

public:

	/*!
	 * Constructor
	 *
	 * @param[in] read_data The data of read.
	 */
	Read(const std::string& read_data, int ID);

	/*!
	 * Gets the header.
	 *
	 * \return The header of read.
	 */
	std::string& getHeader();

	/*!
	 * Gets the sequence.
	 *
	 * \return The sequence.
	 */
	std::string& getSequence();

	/*!
	 * Gets the quality score.
	 *
	 * \return The quality score.
	 */
	std::string& getQualityScore();
	
	/*!
	 * ID of the read.
	 *
	 * \return The ID of the read.
	 */
	int getID();
	
	/*!
	 * Compares reads
	 *
	 */
	bool operator<(const Read& src) const
	{
	    return (this->ID < src.ID);
	}
};

#endif

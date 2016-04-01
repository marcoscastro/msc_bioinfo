#ifndef FASTQ_READER_H
#define FASTQ_READER_H

#include <vector>
#include "read.h"

/*! \brief Class to read a FASTQ file.
 *	\author Marcos Castro
 *	\copyright GNU Public License.
 *	\date 28/03/2016
 *
 *	Last modified: 01/04/2016
 *
 *	FASTQ format stores sequences and qualities in a single file. It is concise and compact.
 *
 *	References:
 *	\n http://goo.gl/ZMShLe (Illumina website)
 *	\n http://maq.sourceforge.net/fastq.shtml
 *	\n https://en.wikipedia.org/wiki/FASTQ_format
 */
class FASTQReader
{
private:
	   std::vector<Read> reads; //**< set of reads of the FASTQ file */

public:
	
	/*!
	 * Constructor
	 *
	 * @param[in] file_path The path of the FASTQ file.
	 */
	FASTQReader(std::string & file_path);
	
	/*!
	 * Returns the vector of reads.
	 *
	 * \return The vector of reads.
	 */
	std::vector<Read> & getReads()
	{
		return reads;
	}
};

#endif
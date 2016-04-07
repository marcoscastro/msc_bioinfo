#ifndef FASTQ_READER_H
#define FASTQ_READER_H

#include <vector>
#include <fstream>
#include "read.h"

/*! \brief File that manipulates the FASTQ files.
 *	\author Marcos Castro
 *	\copyright GNU Public License.
 *	\date 28/03/2016
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
	int total_reads; //**< total of reads */

public:

	/*!
	 * Construtor of the FASTQReader class.
	 */
	FASTQReader();

	/*!
	 * Adds the data of a FASTQ file.
	 *
	 * @param[in] file_path The path of the FASTQ file.
	 */
	void addFASTQ(const char * file_path);

	/*!
	 * Gets the vector of reads.
	 *
	 * \return The vector of reads.
	 */
	std::vector<Read>& getReads();

	/*!
	 * Gets the total number of reads.
	 *
	 * \return the total of reads.
	 */
	int getTotalReads();
	
	/*!
	 * Shows a read by index.
	 *
	 */
	void showRead(long long int index);
};

#endif

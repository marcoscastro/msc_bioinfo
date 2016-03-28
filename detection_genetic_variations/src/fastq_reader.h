#ifndef FASTQ_READER_H
#define FASTQ_READER_H

/*! \brief Class to read a FASTQ file.
 *	\author Marcos Castro
 *	\copyright GNU Public License.
 *	\date 28/03/2016
 *
 *	FASTQ format stores sequences and qualities in a single file. It is concise and compact.
 *
 *	References:
 *	\n http://maq.sourceforge.net/fastq.shtml
 *	\n https://en.wikipedia.org/wiki/FASTQ_format
 */
class FASTQReader
{
private:
	   std::string filename;
	   
public:
	
	/*!
	 * Constructor
	 *
	 * @param[in] filename The name of the FASTQ file.
	 */
	FASTQReader(std::string & filename)
	{
		this->filename = filename;
	}
};

#endif
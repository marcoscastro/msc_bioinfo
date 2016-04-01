#ifndef READ_H
#define READ_H

/*! \brief Class that represents a read.
 *	\author Marcos Castro
 *	\copyright GNU Public License.
 *	\date 01/04/2016
 *
 *	Last modified: 01/04/2016
 *
 *	Each entry in a FASTQ file consists of four lines:
 *	1) Sequence identifier
 *	2) Sequence
 *	3) Quality score identifier line (consisting of a +)
 *	4) Quality score
 *
 *	Reference: http://goo.gl/ZMShLe (Illumina website)
 */
class Read
{
private:
	   std::string header; //**< Header of the FASTQ file */
	   std::string sequence; //**< sequence */
	   std::string quality_score; //**< quality score */
	   
public:
	
	/*!
	 * Constructor
	 *
	 * @param[in] file_path The path of the FASTQ file.
	 */
	FASTQReader(std::string & file_path)
	{
		this->file_path = file_path;
	}
};

#endif
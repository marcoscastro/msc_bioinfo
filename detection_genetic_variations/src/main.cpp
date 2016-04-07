#include <iostream>
#include "fastq_reader.h"
#include "graph.h"

/*! \mainpage Main Page of the project
 *
 * \section intro_sec Introduction
 *
 * Project: De Bruijn Graphs for detection of genetic variations by GBS (Genotyping By Sequencing).
 *
 * The project's code is hosted in: https://github.com/marcoscastro/msc_bioinfo (private, will be public in soon...)
 *
 * The application is being made in C++ language.
 *
 * News coming soon...
 *
 * \section install_sec Installation
 *
 * In soon... Keep calm!
 *
 * \section Workflow
 *
 * <center><img src="workflow.png" /></center>
 *
 * \section Graph Graph structure idea
 *
 * <center><img src="graph_structure.jpg" height="720" width="1282" /></center>
 *
 */

/*! \brief Main function of the application.
 *	\author Marcos Castro
 *	\copyright GNU Public License.
 *	\date 28/03/2016
 *
 *	The main function, we need this!! :)
 *
 */
int main(int argc, char *argv[])
{
	if(argc < 2)
	{
		std::cerr << "Insufficient arguments!\n";
	}
	else
	{
		// test FASTQReader class
		FASTQReader fastq_reader;

		fastq_reader.addFASTQ(argv[1]);

		std::cout << "Total de reads: " << fastq_reader.getTotalReads() << "\n\n";

		/*
		int index = 25;

		std::cout << "\nShowing the read " << index << ":\n\n";
		fastq_reader.showRead(index - 1);
		*/

		// test DeBruijnGraph class
		int K = 2;

		DeBruijnGraph graph(K, fastq_reader.getReads(),
							fastq_reader.getTotalReads());

		graph.showKMears();
	}

	return 0;
}

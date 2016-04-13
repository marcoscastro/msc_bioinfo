#include <iostream>
#include "fastq_reader.h"
#include "graph.h"

/*! \file main.cpp
 * \brief The file that contains the main function of the application.
 * \mainpage Main Page of the project
 *
 * \section intro_sec Introduction
 *
 * Project: De Bruijn Graphs for detection of genetic variations by GBS (Genotyping By Sequencing).
 *
 * The project's code is hosted in: https://github.com/marcoscastro/msc_bioinfo (private, will be public in soon...)
 *
 * The application is being made in C++ language.
 *
 * Last update: 13/04/2016
 *
 * Very useful: http://www.cs.northwestern.edu/~riesbeck/programming/c++/stl-summary.html
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

		// adds the FASTQ file
		fastq_reader.addFASTQ(argv[1]);

		// length of the k-mer
		int K = 20;

		// creates the graph
		DeBruijnGraph graph(K, fastq_reader.getReads(),
							fastq_reader.getTotalReads(), true);

		// shows the information of the k-mers
		//graph.showKMers();
		
		// shows the edges of the graph
		//graph.showEdges();
	}

	return 0;
}

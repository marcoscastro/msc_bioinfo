#include <iostream>
#include <stdlib.h>
#include "graph.h"

/*! \file graph.cpp
 *	\brief Source-code of the class DeBruijnGraph.
 *	\author Marcos Castro
 *	\copyright GNU Public License.
 *	\date 04/04/2016
 *
 *	Comple
 */

DeBruijnGraph::DeBruijnGraph(int K, std::vector<Read>& reads, int total_reads)
{
	this->K = K;

	// gets the size of the read
	int size_read = reads[0].getSequence().size();

	// checks the K value
	if(K < 0 || K >= size_read)
	{
		std::cerr << "Invalid value for the parameter K.\n";
		exit(0); // terminates the execution
	}

	total_kmers = 0;

	/*
		Generates all kmers based in the parameter K.
		Breaks the reads in substrings of length K.
	*/

	std::string kmer_name, sequence;
	int i, j, counter, k;

	// iterates in all the reads
	for(i = 0; i < total_reads; i++)
	{
		// get the sequence of the read
		sequence = reads[i].getSequence();

		// iterates in the characters of each read
		for(j = 0; j < size_read; j++)
		{
			// test the length of the k-mer
			if((size_read - j) < K)
				break;

			// forms the kmer
			kmer_name = "";
			for(counter = 0, k = j; counter < K; counter++, k++)
			{
				kmer_name += sequence[k];
			}
			
			// TODO - insert kmer in the map
		}
	}
}

void DeBruijnGraph::showKMers()
{
	/*
	std::map<KMer, int>::iterator it;
	int i;

	// shows information of each kmer
	for(i = 0; i < total_kmers; i++)
	{
		std::cout << "K-Mer: " << kmers[i].getSequence() << "\n";
	}*/
}

int DeBruijnGraph::getTotalKMers()
{
	return total_kmers;
}

void DeBruijnGraph::build()
{
	// TODO
}


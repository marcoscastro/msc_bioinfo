#include <iostream>
#include <stdlib.h>
#include "graph.h"

/*! \file graph.cpp
 *	\brief Source-code of the class DeBruijnGraph.
 *	\author Marcos Castro
 *	\copyright GNU Public License.
 *	\date 04/04/2016
 *
 */

DeBruijnGraph::DeBruijnGraph(int K, std::vector<Read>& reads, int total_reads)
{
	this->K = K;
	total_kmers = 1;

	// gets the size of the read
	int size_read = reads[0].getSequence().size();

	// checks the K value
	if(K < 0 || K >= size_read)
	{
		std::cerr << "Invalid value for the parameter K.\n";
		exit(0); // terminates the execution
	}

	/*
		Generates all kmers based in the parameter K.
		Breaks the reads in substrings of length K.
	*/

	std::string kmer_name, sequence;

	// iterates in all the reads
	for(int i = 0; i < total_reads; i++)
	{
		// get the sequence of the read
		sequence = reads[i].getSequence();

		// iterates in the characters of each read
		for(int j = 0; j < size_read; j++)
		{
			// test the length of the k-mer
			if((size_read - j) < K)
				break;

			// forms the kmer
			kmer_name = "";
			for(int counter = 0, k = j; counter < K; counter++, k++)
			{
				kmer_name += sequence[k];
			}

			// creates the kmer
			KMer kmer(kmer_name);

			// insert the kmer in the map
			kmers[kmer].insert(reads[i]);
		}
	}

	total_kmers = kmers.size();
}

void DeBruijnGraph::showKMers()
{
	std::map<KMer, std::set<Read> >::iterator it;

	// shows information of each kmer
	for(it = kmers.begin(); it != kmers.end(); it++)
	{
		/** @bug NOT is bug, but improve it PLEASE!! */
		
		/*
			it->first is a constant, gets compilation
			error if to try (it->first).getSequence()
		*/
		
		KMer kmer = it->first;
		
		std::cout << "K-Mer: " << kmer.getSequence() << ", ";
		std::cout << "Total reads: " << (it->second).size() << "\n";
	}
}

unsigned long long DeBruijnGraph::getTotalKMers()
{
	return total_kmers;
}

void DeBruijnGraph::build()
{
	// TODO
}


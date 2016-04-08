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

	std::string read_sequence, kmer_sequence, kmer_prefix, kmer_suffix;
	int i, j, counter, k;

	// iterates in all the reads
	for(i = 0; i < total_reads; i++)
	{
		// get the sequence of the read
		read_sequence = reads[i].getSequence();

		// iterates in the characters of each read
		for(j = 0; j < size_read; j++)
		{
			// test the length of the k-mer
			if((size_read - j) < K)
				break;

			// forms the kmer
			kmer_sequence = "";
			for(counter = 0, k = j; counter < K; counter++, k++)
			{
				kmer_sequence += read_sequence[k];
			}

			// creates the prefix and suffix k-mer
			kmer_prefix = kmer_sequence.substr(0, K - 1);
			kmer_suffix = kmer_sequence.substr(1, K - 1);

			// creates the k-mer
			KMer kmer(kmer_sequence, kmer_prefix, kmer_suffix);

			// insert the k-mer in the map and adds the read
			kmers[kmer][reads[i].getID()]++;
		}
	}

	total_kmers = kmers.size();
}

void DeBruijnGraph::showKMers(bool show_sequence)
{
	std::map<KMer, std::map<int, int> >::iterator it;

	// shows the information of each kmer

	if(show_sequence)
	{
		for(it = kmers.begin(); it != kmers.end(); it++)
		{
			KMer kmer = it->first;
			std::cout << "K-Mer: " << kmer.getSequence() << ", ";
			std::cout << "amount of reads: " << (it->second).size() << "\n";
		}
	}

	std::cout << "\nTotal k-mers: " << total_kmers << "\n";
}

int DeBruijnGraph::getTotalKMers()
{
	return total_kmers;
}

void DeBruijnGraph::build()
{
	// TODO
}


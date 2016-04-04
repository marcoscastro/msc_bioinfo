#include <iostream>
#include <stdlib.h>
#include "graph.h"

DeBruijnGraph::DeBruijnGraph(int K, std::vector<Read>& reads, int total_reads)
{
	this->K = K;

	// gets the size of the read
	int size_read = reads[0].getSequence().size();

	/*
		Recommendation: the length of the K should be
		not less than the half of the read's size.
	*/

	// checks the K value
	if(K < 0 || K < size_read / 2 || K >= size_read)
	{
		std::cerr << "Invalid value for the parameter K.\n";
		exit(0); // terminates the execution
	}

	/*
		Generates all kmers based in the parameter K.
		Breaks the reads in substrings of length K.
	*/
	std::string kmer, sequence;

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

			kmer = "";

			// forms the kmer
			for(int k = j; k <= K; k++)
			{
				kmer += sequence[k];
			}

			// insert the k-mer in the map of k-mers
			kmers[kmer]++;
		}
	}
}

void DeBruijnGraph::showKMears()
{
	std::map<std::string, int>::iterator it = kmers.begin();
	
	
}

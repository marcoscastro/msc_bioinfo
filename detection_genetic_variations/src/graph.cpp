#include <iostream>
#include <stdlib.h>
#include <set>
#include <algorithm>
#include "graph.h"

/*! \file graph.cpp
 *	\brief Source-code of the class DeBruijnGraph.
 *	\author Marcos Castro
 *	\copyright GNU Public License.
 *	\date 04/04/2016
 *
 */

DeBruijnGraph::DeBruijnGraph(int K, std::vector<Read>& reads, int total_reads, bool verbose)
{
	// length of the k-mer
	this->K = K;

	// shows the information
	this->verbose = verbose;

	// gets the size of the read
	// assumes that the reads have equal size
	int size_read = reads[0].getSequence().size();

	// validates the K value
	if(K < 1 || K > size_read)
	{
		std::cerr << "Invalid value for the parameter K.\n";
		exit(0); // terminates the execution
	}

	std::string read_sequence, kmer_sequence;
	int i, j, counter, k;

	if(verbose)
		std::cout << "Building the graph...\n";

	// builds the graph

	// iterates in all the reads
	for(i = 0; i < total_reads; i++)
	{
		// gets the sequence of the read
		read_sequence = reads[i].getSequence();

		// iterates in the characters of each read
		for(j = 0; j < (size_read - j); j++)
		{
			// forms the k-mer sequence
			kmer_sequence = "";
			for(counter = 0, k = j; counter < K; counter++, k++)
				kmer_sequence += read_sequence[k];

			// checks if the key exists
			if(kmers.find(kmer_sequence) == kmers.end())
			{
				// creates the k-mer
				KMer kmer(kmer_sequence);

				// insert in the map
				kmers[kmer_sequence] = kmer;
			}

			// add read ID in the set of the k-mer
			kmers[kmer_sequence].addRead(reads[i].getID());

			if(j != 0)
			{
				// set the successor
				if(kmer_sequence[K - 1] == 'A')
					kmers[read_sequence.substr(j - 1, K)].setSuccessor(0);
				else if(kmer_sequence[K - 1] == 'T')
					kmers[read_sequence.substr(j - 1, K)].setSuccessor(1);
				else if(kmer_sequence[K - 1] == 'C')
					kmers[read_sequence.substr(j - 1, K)].setSuccessor(2);
				else if(kmer_sequence[K - 1] == 'G')
					kmers[read_sequence.substr(j - 1, K)].setSuccessor(3);
			}
		}
	}

	// the total of k-mers is 4^K
	total_kmers = kmers.size();

	if(verbose)
	{
		std::cout << "Total of reads: " << total_reads << "\n\n";
		std::cout << "Total K-mers: " << total_kmers << "\n";
	}
}

void DeBruijnGraph::showKMers()
{
	std::map<std::string, KMer>::iterator it;

	std::cout << "\nShowing the k-mers...\n\n";

	for(it = kmers.begin(); it != kmers.end(); it++)
	{
		std::cout << "K-Mer: " << it->first << ", ";
		std::cout << "Amount of reads: " << (it->second).getTotalReads() << ", ";
		std::cout << "Total of successors: " << (it->second).getTotalSuccessors() << "\n";
	}
}

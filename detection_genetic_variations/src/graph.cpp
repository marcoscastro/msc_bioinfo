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

	this->K = K; // length of the k-mer
	this->reads = reads; // assigns the reads
	this->total_reads = total_reads; // assigns the total of reads
	this->verbose = verbose; // shows the information

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
		std::cout << "Building the graph...\n\n";

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

			// checks if the key not exists
			if(kmers.find(kmer_sequence) == kmers.end())
			{
				// creates the k-mer
				KMer kmer(kmer_sequence);

				// insert in the map
				kmers[kmer_sequence] = kmer;
			}

			// add read ID in the set of the k-mer
			kmers[kmer_sequence].addRead(reads[i].getID());

			// set the successor: +A, +T, +C or +G?
			if(j != 0)
				kmers[read_sequence.substr(j - 1, K)].setSuccessor(kmer_sequence[K - 1]);
		}
	}

	// the maximum number of k-mers is 4^K
	total_kmers = kmers.size();

	if(verbose)
		showInfoGraph();
}

void DeBruijnGraph::showInfoGraph()
{
	std::map<std::string, KMer>::iterator it;

	std::cout << "Total of reads: " << total_reads << "\n\n";
	std::cout << "Total K-mers: " << total_kmers << "\n";
	std::cout << "\nShowing the k-mers...\n\n";

	for(it = kmers.begin(); it != kmers.end(); it++)
	{
		std::cout << "K-Mer: " << it->first << ", ";
		std::cout << "Amount of reads: " << (it->second).getTotalReads() << ", ";
		std::cout << "Total of successors: " << (it->second).getTotalSuccessors() << "\n";
	}
}

void DeBruijnGraph::showReadsPassingByPathRead(int read_ID)
{
	// validate the read's ID
	if(read_ID < 0 || read_ID >= total_reads)
	{
		std::cerr << "Invalid ID of the read.\n";
		exit(0); // terminates the execution
	}

	std::string kmer_sequence, read_sequence;
	std::set<int> reads_id;
	std::set<int>::iterator it_reads_id;
	std::map<int, int> reads_count;
	std::map<int, int>::iterator it_reads_count;
	int i, size_read;

	read_sequence = reads[read_ID].getSequence();
	size_read = read_sequence.size();

	// k-mers of the read
	for(i = 0; i < (size_read - i); i++)
	{
		kmer_sequence = read_sequence.substr(i, K);
		reads_id = kmers[kmer_sequence].getReads();

		// reads that passing by the k-mer
		for(it_reads_id = reads_id.begin(); it_reads_id != reads_id.end(); it_reads_id++)
			reads_count[*it_reads_id]++; // count the read
	}

	// shows the reads that passing by the read
	for(it_reads_count = reads_count.begin(); it_reads_count !=
			reads_count.end(); it_reads_count++)
	{
		std::cout << "The read " << it_reads_count->first << " shares " <<
				  it_reads_count->second << " " << K << "-mers with the read "
				  << it_reads_count->first << ".\n";

		if(it_reads_count->first >= 10) break;
	}
}

#include <iostream>
#include <stdlib.h>
#include <set>
#include <algorithm>
#include "graph.h"
#include "common.h"

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

	std::string read_sequence, kmer_sequence, kmer_reverse, previous_kmer;
	int i, j;

	if(verbose)
		std::cout << "Building the graph...\n\n";

	// builds the graph
	// iterates in all the reads
	for(i = 0; i < total_reads; i++)
	{
		/*
			gets the sequence of the read

			Attention: the first k-mer not contains
			successor neither antecessor.
		*/
		read_sequence = reads[i].getSequence();

		// gets the first k-mer
		kmer_sequence = read_sequence.substr(0, K);

		// checks if the key kmer_sequence not exists
		if(kmers.find(kmer_sequence) == kmers.end())
		{
			// generates the reverse complement
			kmer_reverse = getReverseComplement(kmer_sequence);

			KMer kmer(kmer_sequence); // creates the k-mer

			// insert in the map, to point to the same object
			kmers[kmer_sequence] = kmer;
			kmers[kmer_reverse] = kmer;
		}

		// add read ID in the set of the k-mer
		kmers[kmer_sequence].addRead(reads[i].getID());

		// iterates in the characters of each read
		// forms the k-mers remaining
		for(j = 1; (j + K) <= size_read; j++)
		{
			// forms the k-mer sequence
			kmer_sequence = read_sequence.substr(j, K);

			// checks if the key not exists
			if(kmers.find(kmer_sequence) == kmers.end())
			{
				// generates the reverse complement
				kmer_reverse = getReverseComplement(kmer_sequence);

				KMer kmer(kmer_sequence); // creates the k-mer

				// insert in the map, to point to the same object
				kmers[kmer_sequence] = kmer;
				kmers[kmer_reverse] = kmer;
			}

			// add read ID in the set of the k-mer
			kmers[kmer_sequence].addRead(reads[i].getID());
			
			// get the previous k-mer
			previous_kmer = read_sequence.substr(j - 1, K);

			// set the successor: +A, +T, +C or +G?
			kmers[previous_kmer].setSuccessor(kmer_sequence[K - 1]);
			
			// set the antecessor: +A, +T, +C or +G?
			//kmers[previous_kmer].setAntecessor(kmer_sequence[K - 1]);
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

	std::cout << "K: " << K << "\n";
	std::cout << "Total of reads: " << total_reads << "\n";
	std::cout << "Total k-mers: " << total_kmers << "\n";
	std::cout << "\nShowing the k-mers...\n\n";

	for(it = kmers.begin(); it != kmers.end(); it++)
	{
		std::cout << "K-Mer: " << it->first << ", ";
		std::cout << "Amount of reads: " << (it->second).getTotalReads() << ", ";
		std::cout << "Total of successors: " << (it->second).getTotalSuccessors() << "\n";
	}
}

void DeBruijnGraph::showReadsSharesKMersByRead(int read_ID)
{
	// validate the read's ID
	if(read_ID < 0 || read_ID >= total_reads)
	{
		std::cerr << "Invalid ID of the read.\n";
		exit(0); // terminates the execution
	}

	std::string kmer_sequence, read_sequence;
	int size_read;
	std::set<int> reads_id;
	std::map<int, int> reads_count;
	std::set<int>::iterator it_reads_id;
	std::map<int, int>::iterator it_reads_count;
	std::map<std::string, KMer>::iterator it_kmers;

	read_sequence = reads[read_ID].getSequence();
	size_read = read_sequence.size();

	// k-mers of the read
	for(it_kmers = kmers.begin(); it_kmers != kmers.end(); it_kmers++)
	{
		// get set of reads that shares the k-mer
		reads_id = kmers[it_kmers->first].getReads();

		// count the reads
		for(it_reads_id = reads_id.begin(); it_reads_id != reads_id.end(); it_reads_id++)
			reads_count[*it_reads_id]++;
	}

	std::cout << "\nReads that shares k-mers with the read " << read_ID + 1 << ":\n\n";

	// shows the reads that passing by the read
	for(it_reads_count = reads_count.begin(); it_reads_count !=
			reads_count.end(); it_reads_count++)
	{
		std::cout << "The read " << it_reads_count->first + 1 << " shares " <<
				  it_reads_count->second << " k-mers with the read " << read_ID + 1 << ".\n";
	}
}

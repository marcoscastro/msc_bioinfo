#include <iostream>
#include <stdlib.h>
#include <set>
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
	int size_read = reads[0].getSequence().size();

	// total of edges of the graph
	total_edges = 0;

	// validates the K value
	if(K < 0 || K >= size_read)
	{
		std::cerr << "Invalid value for the parameter K.\n";
		exit(0); // terminates the execution
	}

	// counter k-mers
	total_kmers = 0;

	/*
		Generates all kmers based in the parameter K.
		Breaks the reads in substrings of length K.
	*/

	std::string read_sequence, kmer_sequence;
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

			// forms the kmer sequence
			kmer_sequence = "";
			for(counter = 0, k = j; counter < K; counter++, k++)
			{
				kmer_sequence += read_sequence[k];
			}

			// checks if the k-mer yet exists
			if(kmers.find(kmer_sequence) == kmers.end())
			{
				// forms the k-mer object
				KMer kmer(kmer_sequence);

				// insert the k-mer object in the map of k-mers
				kmers[kmer_sequence] = kmer;
			}

			// adds the ID of the read to the k-mer
			kmers[kmer_sequence].addRead(reads[i].getID());

		}
	}

	// gets the total of k-mers
	total_kmers = kmers.size();

	if(verbose)
	{
		std::cout << "Total of reads: " << total_reads << "\n\n";
		std::cout << "Generating k-mers...\n";
		std::cout << "Total K-mers: " << total_kmers << "\n\n";
		std::cout << "Building the graph...\n";
	}

	// builds the graph
	build();

	if(verbose)
	{
		std::cout << "The graph was built!\n";
		std::cout << "Total of edges: " << total_edges << "\n";
	}
}

void DeBruijnGraph::showKMers()
{
	for(std::map<std::string, KMer>::iterator it = kmers.begin();
			it != kmers.end(); it++)
	{
		std::cout << "K-Mer: " << it->first << ", ";
		std::cout << "amount of reads: " << kmers[it->first].getTotalReads() << "\n";
	}
}

int DeBruijnGraph::getTotalKMers()
{
	return total_kmers;
}

void DeBruijnGraph::build()
{
	// all the possibles nucleotides
	std::string nucleotides("ACTG");

	// sets of reads of the k-mers
	std::set<int> reads_kmer_src, reads_kmer_dest;

	// iterates in the map of k-mers
	for(std::map<std::string, KMer>::iterator it_kmers = kmers.begin();
			it_kmers != kmers.end(); it_kmers++)
	{
		// get the sequence of the k-mer of source
		std::string kmer_src(it_kmers->first);

		// tries to find the possibles k-mers of destination in the map
		for(int i = 0; i < 4; i++)
		{
			// forms the k-mer destination
			std::string kmer_dest(kmer_src.substr(1, K - 1) + nucleotides[i]);

			// tries to find the k-mer of destination in the map of k-mers
			if(kmers.find(kmer_dest) != kmers.end())
			{
				// vector of reads that passing by the edge
				std::vector<int> vec_reads;

				// set of reads of the k-mers
				reads_kmer_src = kmers[kmer_src].getReads();
				reads_kmer_dest = kmers[kmer_dest].getReads();

				// iterates in the set of reads of the k-mer of source
				for(std::set<int>::iterator it_read = reads_kmer_src.begin();
						it_read != reads_kmer_src.end(); it_read++)
				{
					/*
						tries to find the ID of the read of the
						kmer_src in the set of reads of the kmer_dest
					*/
					if(reads_kmer_dest.find(*it_read) !=
							reads_kmer_dest.end())
					{
						// inserts in the vector of reads
						vec_reads.push_back(*it_read);
					}
				}

				// builds the edge
				Edge edge(kmer_src, kmer_dest, vec_reads);

				// adds the edge in the map of edges
				edges[kmer_src].push_back(edge);

				// increments the total of edges
				total_edges++;
			}
		}
	}
}

void DeBruijnGraph::showEdges()
{
	std::map<std::string, std::vector<Edge> >::iterator it;
	int total_edges, i;

	for(it = edges.begin(); it != edges.end(); it++)
	{
		total_edges = (it->second).size();

		for(i = 0; i < total_edges; i++)
		{
			std::cout << (it->second)[i].getKMerSrc() << " -> " << (it->second)[i].getKMerDest() << ", ";
			std::cout << "amount of reads: " << (it->second)[i].getTotalReads() << "\n";
		}
	}
}

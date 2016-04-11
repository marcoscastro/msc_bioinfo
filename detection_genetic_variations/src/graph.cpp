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

	// gets the total k-mers number
	total_kmers = kmers.size();

	if(verbose)
	{
		std::cout << "\nK-mers generated.\n";
		std::cout << "Total K-mers: " << total_kmers << "\n\n";
		std::cout << "Building the graph...";
	}
	
	// builds the graph
	build();
	
	if(verbose)
		std::cout << " Graph was built!\n";
	
}

void DeBruijnGraph::showKMers(bool show_details)
{
	std::map<KMer, std::map<int, int> >::iterator it;

	// shows the information of each kmer

	if(show_details)
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
	// iterators for the map of k-mers
	std::map<KMer, std::map<int, int> >::iterator it1_kmers;
	std::map<KMer, std::map<int, int> >::iterator it2_kmers;
	
	// VERY SLOW!!!

	// iterates in the map of k-mers
	for(it1_kmers = kmers.begin(); it1_kmers != kmers.end(); it1_kmers++)
	{
		// gets the k-mer source
		KMer kmer_src = it1_kmers->first;

		// iterates again in the map of k-mers
		for(it2_kmers = kmers.begin(); it2_kmers != kmers.end(); it2_kmers++)
		{
			// gets the k-mer destination
			KMer kmer_dest = it2_kmers->first;

			/*
				checks if suffix of the k-mer source match
				with prefix of the k-mer destionation
			*/
			if(kmer_src.getSuffix() == kmer_dest.getPrefix())
			{
				// builds the edge
				Edge edge(kmer_src.getSequence(), kmer_dest.getSequence());

				// vector of reads of the edge, stores the ID's
				std::vector<int> vec_reads;

				/*
					iterates of the values (maps) of the map of k-mers
					the values of the map of k-mers too is a map, but is
					a map of ID's of reads where the key is the ID of the
					read and the value is a counter of the read
				*/

				std::map<int, int>::iterator it1_reads;
				std::map<int, int>::iterator it2_reads;

				it1_reads = (it1_kmers->second).begin();

				while(it1_reads != (it1_kmers->second).end())
				{
					// gets ID of the read
					int ID_read = it1_reads->first;

					/*
						tries to find the ID of the read of the kmer_src
						in the map of reads of the kmer_dest
					*/
					if((it2_kmers->second).find(ID_read) !=
							(it2_kmers->second).end())
					{
						// inserts in the vector of reads
						vec_reads.push_back(ID_read);
					}
					
					it1_reads++;
				}

				// adds the set of reads in edge
				edge.setReads(vec_reads);
				
				// adds the edge in the vector of edges
				edges.push_back(edge);
			}
		}
	}
}

void DeBruijnGraph::showEdges()
{
	std::vector<Edge>::iterator it;
	
	for(it = edges.begin(); it != edges.end(); it++)
	{
		std::cout << it->getKMerSrc() << " -> " << it->getKMerDest() << ", ";
		std::cout << "amount of reads: " << it->getTotalReads() << "\n";
	}
}
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

	std::string read_sequence, kmer;
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
			kmer = "";
			for(counter = 0, k = j; counter < K; counter++, k++)
			{
				kmer += read_sequence[k];
			}

			// insert the k-mer in the map and adds the ID of the read
			kmers[kmer][reads[i].getID()]++;
		}
	}

	// gets the total of k-mers
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
	{
		std::cout << " Graph was built!\n";
		std::cout << "\nTotal of edges: " << total_edges << "\n";
	}
}

void DeBruijnGraph::showKMers(bool show_details)
{
	std::map<std::string, std::map<int, int> >::iterator it;

	// shows the information of each kmer

	if(show_details)
	{
		for(it = kmers.begin(); it != kmers.end(); it++)
		{
			std::cout << "K-Mer: " << it->first << ", ";
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
	std::map<std::string, std::map<int, int> >::iterator it_kmers;
	std::map<std::string, std::map<int, int> >::iterator it_kmer_dest;

	// possibles nucleotides
	std::string nucleotides("ACTG");

	// iterator for the value of the map of k-mers
	std::map<int, int>::iterator it_reads;

	// iterates in the map of k-mers
	for(it_kmers = kmers.begin(); it_kmers != kmers.end(); it_kmers++)
	{
		// get the k-mer sequence
		std::string kmer_src(it_kmers->first);

		// tries to find the possibles k-mers in the map
		for(int i = 0; i < 4; i++)
		{
			// forms the k-mer destination
			std::string kmer_dest(kmer_src.substr(1, K - 1) + nucleotides[i]);

			/*
				tries to find the k-mer of destination in the map of k-mers
				to find a key in the map is O(logn)

				SLOW??
			*/
			it_kmer_dest = kmers.find(kmer_dest);

			// checks if was found
			if(it_kmer_dest != kmers.end())
			{
				// vector of reads that passing by the edge
				std::vector<int> vec_reads;

				/*
					iterates of the values of the map of k-mers
					the values of the map of k-mers too is a map, but is
					a map of ID's of reads where the key is the ID of the
					read and the value is a counter of the read

					iterates in the reads of the k-mer source
				*/
				it_reads = (it_kmers->second).begin();

				while(it_reads != (it_kmers->second).end())
				{
					// gets the ID of the read
					int ID_read = it_reads->first;

					/*
						tries to find the ID of the read of the kmer_src
						in the map of reads of the kmer_dest
					*/
					if((it_kmer_dest->second).find(ID_read) !=
							(it_kmer_dest->second).end())
					{
						// inserts in the vector of reads
						vec_reads.push_back(ID_read);
					}

					it_reads++;
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

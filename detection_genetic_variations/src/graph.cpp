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
	int size_read = reads[0].getSequence().size();

	// validates the K value
	if(K < 0 || K >= size_read)
	{
		std::cerr << "Invalid value for the parameter K.\n";
		exit(0); // terminates the execution
	}

	// total k-mers and total edges
	total_kmers = total_edges = 0;

	// builds the graph

	std::string read_sequence, edge_sequence, kmer_sequence;
	int i, j, counter, k;

	// iterates in all the reads
	for(i = 0; i < total_reads; i++)
	{
		// gets the sequence of the read
		read_sequence = reads[i].getSequence();

		// iterates in the characters of each read
		for(j = 0; j < size_read; j++)
		{
			/*
				test the length of the edge sequence
				attention: the length of the sequence is (K + 1)
			*/
			if((size_read - j) < (K + 1))
				break;

			// forms the edge sequence
			edge_sequence = "";
			for(counter = 0, k = j; counter < (K + 1); counter++, k++)
			{
				edge_sequence += read_sequence[k];
			}

			// gets the k-mer sequence
			kmer_sequence = edge_sequence.substr(0, K);

			// forms the K-Mer of source
			KMer kmer_source(kmer_sequence);

			// forms the edge
			Edge edge(edge_sequence);
			
			/*
				Associates the edge to the k-mer and
				associates the ID of the read to the edge
			*/
		}
	}

	// gets the total of k-mers
	total_kmers = graph.size();

	if(verbose)
	{
		std::cout << "Total of reads: " << total_reads << "\n\n";
		std::cout << "Generating k-mers...\n";
		std::cout << "Total K-mers: " << total_kmers << "\n\n";
		std::cout << "Building the graph...\n";
	}

	if(verbose)
	{
		std::cout << "The graph was built!\n";
		std::cout << "Total of edges: " << total_edges << "\n";
	}
}

void DeBruijnGraph::showKMers()
{
	/*
	std::cout << "\nShowing the k-mers...\n\n";

	for(std::map<std::string, KMer>::iterator it = kmers.begin();
			it != kmers.end(); it++)
	{
		std::cout << "K-Mer: " << it->first << ", ";
		std::cout << "amount of reads: " << kmers[it->first].getTotalReads() << "\n";
	}
	*/
}

int DeBruijnGraph::getTotalKMers()
{
	return total_kmers;
}

void DeBruijnGraph::showEdges()
{
	/*
	std::cout << "\nShowing the edges...\n\n";

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
	*/
}

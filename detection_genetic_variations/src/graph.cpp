#include <iostream>
#include <stdlib.h>
#include "graph.h"

DeBruijnGraph::DeBruijnGraph(short int K, std::vector<Read>& reads)
{
	// gets the size of the read
	int size_read = reads[0].getSequence().size();

	/*
		Recommendation: the length of the K should be
		not less than the middle of the read's size.
	*/
	
	// checks the K value
	if(K < 0 || K < size_read / 2 || K >= size_read)
	{
		std::cerr << "Invalid value for the parameter K.\n";
		exit(0); // terminates the execution
	}
}

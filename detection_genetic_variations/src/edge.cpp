#include "edge.h"

Edge::Edge(std::string& kmer_src, std::string& kmer_dest)
{
	this->kmer_src = kmer_src;
	this->kmer_dest = kmer_dest;
	total_reads = 0;
}

std::string& Edge::getKMerSrc()
{
	return kmer_src;
}

std::string& Edge::getKMerDest()
{
	return kmer_dest;
}

int Edge::getTotalReads()
{
	return total_reads;
}

void Edge::setReads(std::vector<int>& reads)
{
	this->reads = reads;
	
	// updates the number of reads
	total_reads = reads.size();
}

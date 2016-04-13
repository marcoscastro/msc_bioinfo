#include "edge.h"

Edge::Edge(std::string& kmer_src, std::string& kmer_dest, std::vector<int>& reads)
{
	this->kmer_src = kmer_src;
	this->kmer_dest = kmer_dest;
	this->reads = reads;
	total_reads = reads.size();
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
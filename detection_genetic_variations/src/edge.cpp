#include "edge.h"

Edge::Edge(std::string& kmer_src, std::string& kmer_dest, int total_reads)
{
	this->kmer_src = kmer_src;
	this->kmer_dest = kmer_dest;
	this->total_reads = total_reads;
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

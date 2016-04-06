#include "kmer.h"

KMer::KMer(std::string& name)
{
	this->name = name;
}

std::string& KMer::getName()
{
	return name;
}
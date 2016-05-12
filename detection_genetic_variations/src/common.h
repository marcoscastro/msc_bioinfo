#ifndef COMMON_H
#define COMMON_H

/*! \file common.h
 *	\brief Common functions.
 *	\author Marcos Castro
 *	\copyright GNU Public License.
 *	\date 11/05/2016
 *
 *	Common functions that are useful.
 *
 */

std::string getReverseComplement(std::string& s)
{
	std::string new_s = "";

	for(std::string::iterator it = s.begin(); it != s.end(); ++it)
	{
		if(*it == 'A')
			new_s += "T";
		else if(*it == 'T')
			new_s += "A";
		else if(*it == 'C')
			new_s += "G";
		else if(*it == 'G')
			new_s += "C";

	}
	
	// reverse string
	std::reverse(new_s.begin(), new_s.end());
	
	return new_s;
}

#endif

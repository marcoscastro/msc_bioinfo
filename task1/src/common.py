# encoding: utf-8

# This file implements common functions

'''
	This function returns the reverse-complement of a DNA sequence
	
	Parameters:
		dna_sequence: a DNA sequence

	Return: reverse complement of DNA
'''
def reverse_complement(dna_sequence):
	dict_bases = {'A':'T', 'T':'A', 'G':'C', 'C':'G'}
	reverse_dna = dna_sequence.upper()[::-1]
	return ''.join([dict_bases[base] for base in reverse_dna])


# tests
if __name__ == "__main__":

	answer = 'ATAGCGCTCTAGATAGCTAGTCAGT'
	if reverse_complement('ACTGACTAGCTATCTAGAGCGCTAT') == answer:
		print('Success in the reverse_complement')
	else:
		print('Fail in the reverse_complement')
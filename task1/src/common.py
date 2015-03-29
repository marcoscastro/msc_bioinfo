# encoding: utf-8

# This file implements common functions

import subprocess

'''
	This function returns the reverse-complement of a DNA sequence
	
	Parameters:
		dna_sequence: a DNA sequence

	Returns: reverse complement of DNA
'''
def reverse_complement(dna_sequence):
	dict_bases = {'A':'T', 'T':'A', 'G':'C', 'C':'G'}
	reverse_dna = dna_sequence.upper()[::-1]
	return ''.join([dict_bases[base] for base in reverse_dna])


'''
	This function executes a shell command and stores the output in a variable

	Parameters:
		command: command shell

	Returns: output of command
'''
def execute_shell_command(command):
	
	# executes a shell command and stores in a output variable
	p = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
	(output, err) = p.communicate()
	return output.strip() # returns the output


# tests
if __name__ == "__main__":

	answer = 'ATAGCGCTCTAGATAGCTAGTCAGT'
	if reverse_complement('ACTGACTAGCTATCTAGAGCGCTAT') == answer:
		print('Success in the reverse_complement')
	else:
		print('Fail in the reverse_complement')

	print(execute_shell_command('date'))
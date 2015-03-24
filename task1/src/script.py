# encoding:utf-8

# Works in Python 2.x and 3.x

import sys


help_msg = '''
Execute: python <script_name.py> <file_cazy_table>
'''


'''
	This function gets only sequences that start with ATG
	and terminate with stop codon: TAG, TGA, TAA

	Parameters:
		file_cazy: path of file with the sequences cazy of table

	Return: list of sequences
'''
def get_sequences(path_file_cazy):
	
	file_cazy = open(path_file_cazy, 'r') # opens file to reading
	text = file_cazy.read() # get text of the file
	list_lines = text.splitlines() # splits lines of the file
	stop_codons = ['TAG', 'TGA', 'TAA'] # list with stop codons
	list_sequences = [] # list of sequences filtered

	# get the sequences that start with ATG and terminate with stop codon
	for line in list_lines:
		sequence = line.split('\t')[-1] # get the sequence of the line

		# test if the sequence start with ATG and terminate with stop codon
		# if sequence not terminate with stop codon, then her is incomplete
		if sequence[0:3] == 'ATG' and sequence[-3:] in stop_codons:

			sub_seq = sequence[3:len(sequence)-3] # gets a subsequence

			# test if not contains stop codon in the middle
			# if contains, then probably the sequence is wrong
			if not any(stop_codon in sub_seq for stop_codon in stop_codons):
				list_sequences.append(sequence) # adds in the list
						
	file_cazy.close() # closes the file

	return list_sequences


if __name__ == "__main__":

	len_args = len(sys.argv) # gets the amount of arguments

	if len_args < 2:
		print('\nError: insufficient arguments.')
		print(help_msg)
	else:
		path_file_cazy = sys.argv[1]
		sequences = get_sequences(path_file_cazy)
		print(len(sequences))
# encoding:utf-8

# Works in Python 2.x and 3.x
# SO: Linux

import sys, os
from common import execute_shell_command


help_msg = '''
Execute: python <script_name.py> <file_cazy_table> <file_assembly>
'''


'''
	This function gets only sequences that start with ATG
	and terminate with stop codon: TAG, TGA, TAA
	and generates FILE FASTA:

	>name_sequence
	sequence
	>name_sequence2
	sequence
	(...)

	Parameters:
		path_file_cazy: path of file with the sequences cazy of table
		fasta_file_name: name of the file fasta
'''
def generates_fasta(path_file_cazy, fasta_file_name):
	
	try:
		file_cazy = open(path_file_cazy, 'r') # try to open file to reading
	except:
		sys.exit('\nError: file %s not exists!\n' % path_file_cazy)

	text = file_cazy.read() # gets text of the file
	list_lines = text.splitlines() # splits lines of the file
	stop_codons = ['TAG', 'TGA', 'TAA'] # list with stop codons

	fasta_file = open(fasta_file_name ,'w')

	for line in list_lines:
		name_sequence = line.split('\t')[0] # gets the name of sequence
		sequence = line.split('\t')[-1] # gets the sequence of the line

		# test if the sequence start with ATG and terminate with stop codon
		# if sequence not terminate with stop codon, then her is incomplete
		if sequence[0:3] == 'ATG' and sequence[-3:] in stop_codons:

			sub_seq = sequence[3:len(sequence)-3] # gets a subsequence
			len_sub_seq = len(sub_seq) # gets length subsequence

			# test if not contains stop codon in the middle
			# if contains, then probably the sequence is wrong
			contains_stop_codon_middle = False # flag to checks if exists stop codon in the middle
			for i in range(0,len_sub_seq,3): # each codon (step 3)
				if sub_seq[i:3] in stop_codons: # checks if codon is stop codon
					contains_stop_codon_middle = True # updates the flag
					break # left the loop

			if not contains_stop_codon_middle: # checks is contains stop codon in the middle
				# stores the sequence in the file
				fasta_file.write('>' + name_sequence + '\n')
				fasta_file.write(sequence + '\n')
					
	# closes the file	
	file_cazy.close()
	fasta_file.close()


'''
	This functions gets assembly of genome of a file in FASTA format
	Example of the file's part:
		>NODE_105-0.1930
		CGCGAGCGTTGCTGG
		GAGAGGTGCGATGCA
		>NODE_438-0.460
		GAGAGGTGCGATGCA
		CGCGAGCGTTGCTGG
		(...)

	Parameters:
		path_file_assembly: path of file with the assembly of genome in FASTA format

	Returns: assembly of genome

	Do you like of shell script? In shell script (shows number of characters):

	grep -iv "^>NODE" <path_file_assembly> | tr -d '\n' | wc -c
'''
def get_assembly(path_file_assembly):
	
	try:
		file_assembly = open(path_file_assembly, 'r') # try to open file to reading
	except:
		sys.exit('\nError: file %s not exists!\n' % path_file_assembly)

	text = file_assembly.read() # get text of the file
	lines = text.splitlines() # splits lines of the file

	# gets all lines that do not begin with '>' and joins them
	assembly = ''.join([line for line in lines if not line.startswith('>')])

	file_assembly.close() # closes the file

	return assembly # returns assembly


'''
	This function executes blat command:
		blat database query [-ooc=11.ooc] output.psl

	Parameters:
		database and query are each either a .fa , .nib or .2bit file
		output is where to put the output (file output.psl)

	Returns: output of the command
'''
def execute_blat_command(database, query, output='output_blat'):

	command_blat = 'blat %s %s %s' % (database, query, output + '.psl')
	return execute_shell_command(command_blat)



if __name__ == "__main__":

	len_args = len(sys.argv) # gets the amount of arguments

	if len_args < 3: # checks the amount of args
		sys.exit(help_msg)
	
	path_file_cazy, path_file_assembly = sys.argv[1], sys.argv[2]

	fasta_file_name = 'sequences_cazy.fa'
	generates_fasta(path_file_cazy, fasta_file_name) # generates fasta file

	output_command = execute_blat_command(database=path_file_assembly, query=fasta_file_name)
	print(output_command)
	
	#assembly = get_assembly(path_file_assembly) # gets the assembly
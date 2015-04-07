# encoding:utf-8

# Works in Python 2.x and 3.x
# SO: Linux

import sys, os
from common import execute_shell_command


help_msg = '''
Execute: python <script_name.py> <file_cazy_table> <file_assembly>
'''

# map of the sequences - key: name of the sequence, value: sequence object
map_sequences = {}

# class that represents a sequence
class Sequence:

	def __init__(self, name, sequence):
		self.name, self.sequence = name, sequence
		self.t_start, self.t_end = None, None

	def getName(self):
		return self.name

	def getSequence(self):
		return self.sequence

	def setTStart(self, t_start):
		self.t_start = t_start

	def getTStart(self):
		return self.t_start

	def setTEnd(self, t_end):
		self.t_end = t_end

	def getTEnd(self):
		return self.t_end


'''
	This function gets only sequences that start with ATG
	and terminate with stop codon: TAG, TGA, TAA
	and generates a fasta file:

	>name_sequence
	sequence
	>name_sequence2
	sequence
	(...)

	Parameters:
		path_file_cazy: path of file with the sequences cazy of table
		fasta_file_name: name of the file fasta
'''
def generates_fasta(path_file_cazy, output_filename):
	
	try:
		file_cazy = open(path_file_cazy, 'r') # try to open file to reading
	except:
		sys.exit('Error: file %s not exists!' % path_file_cazy)

	text = file_cazy.read() # gets text of the file
	list_lines = text.splitlines() # splits lines of the file
	stop_codons = ['TAG', 'TGA', 'TAA'] # list with stop codons

	fasta_file = open(output_filename ,'w')

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

				# inserts in the map of the sequences
				map_sequences[name_sequence] = Sequence(name=name_sequence, sequence=sequence)

				# stores the name of the sequence in the file
				fasta_file.write('>' + name_sequence + '\n')
				
				len_sequence = len(sequence) # gets size of the sequence
				# stores each part of the sequence - 60 characters per line
				for i in range(0,len_sequence,60):
					fasta_file.write(sequence[i:i+60] + '\n')

	print('Generated the file \"%s\" successfully.' % output_filename)
					
	# closes the files	
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
		sys.exit('Error: file %s not exists!' % path_file_assembly)

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
'''
def execute_blat_command(database, query, output_filename):

	# generates blat command
	command_blat = 'blat %s %s %s' % (database, query, output_filename)
	output, error = execute_shell_command(command_blat) # executes blat command

	if not error:
		print('Generated the file \"%s\" successfully.' % output_filename)
	else:
		sys.exit('Error in the execution of the blat command.')


'''
	This function executes pslPretty command:
		pslPretty in.psl target.lst query.lst pretty.out

	Parameters:
		in of the file psl, target, query and output filename
'''
def execute_pslpretty_command(in_psl, target, query, output_filename):

	# generates pslPretty command
	command_pslpretty = 'pslPretty %s %s %s %s' % \
					(in_psl, target, query, output_filename)
	output, error = execute_shell_command(command_pslpretty) # executes pslPretty command

	if not error:
		print('Generated the file \"%s\" successfully.' % output_filename)
	else:
		sys.exit('Error in the execution of the pslPretty command.')


'''
	This function process a file blat
		path_file_blat: path of the file

	Parameters:
		in of the file psl, target, query and output filename

	A .psl file describes a series of alignments in a dense easily parsed text format.
	It begins with a five line header which describes each field.
	Following this is one line for each alignment with a tab between each field.
	The fields are describe below in  a format suitable for many relational databases.

	matches int unsigned ,           # Number of bases that match that aren't repeats
	misMatches int unsigned ,        # Number of bases that don't match
	repMatches int unsigned ,        # Number of bases that match but are part of repeats
	nCount int unsigned ,            # Number of 'N' bases
	qNumInsert int unsigned ,        # Number of inserts in query
	qBaseInsert int unsigned ,       # Number of bases inserted in query
	tNumInsert int unsigned ,        # Number of inserts in target
	tBaseInsert int unsigned ,       # Number of bases inserted in target
	strand char(2) ,                 # + or - for query strand, optionally followed by + or – for target strand
	qName varchar(255) ,             # Query sequence name
	qSize int unsigned ,             # Query sequence size
	qStart int unsigned ,            # Alignment start position in query
	qEnd int unsigned ,              # Alignment end position in query
	tName varchar(255) ,             # Target sequence name
	tSize int unsigned ,             # Target sequence size
	tStart int unsigned ,            # Alignment start position in target
	tEnd int unsigned ,              # Alignment end position in target
	blockCount int unsigned ,        # Number of blocks in alignment. A block contains no gaps.
	blockSizes longblob ,            # Size of each block in a comma separated list
	qStarts longblob ,               # Start of each block in query in a comma separated list

'''
def processFileBlat(path_file_blat):

	try:
		file_blat = open(path_file_blat, 'r') # try to open file to reading
	except:
		sys.exit('Error: file %s not exists!' % path_file_blat)

	
	lines = file_blat.readlines() # read all the lines
	size_lines = len(lines) # gets amount of lines

	for i in range(5, size_lines):
		name_sequence = lines[i].split('\t')[9] # gets the name of the sequence
		t_start = lines[i].split('\t')[15] # gets the t_start
		t_end = lines[i].split('\t')[16] # gets the t_end
		map_sequences[name_sequence].setTStart(t_start) # set the t_start
		map_sequences[name_sequence].setTEnd(t_end) # set the t_end

	file_blat.close()


if __name__ == "__main__":

	len_args = len(sys.argv) # gets the amount of arguments

	if len_args < 3: # checks the amount of args
		sys.exit(help_msg)
	
	path_file_cazy, path_file_assembly = sys.argv[1], sys.argv[2]

	print('')

	fasta_filename = 'sequences_cazy.fa'
	generates_fasta(path_file_cazy=path_file_cazy, output_filename=fasta_filename) # generates fasta file

	output_filename_blat = 'output_blat.psl'
	execute_blat_command(database=path_file_assembly, 
							query=fasta_filename, output_filename=output_filename_blat)

	output_filename_pslpretty = 'output_pretty.out'
	execute_pslpretty_command(in_psl=output_filename_blat, target=path_file_assembly, 
				query=fasta_filename, output_filename=output_filename_pslpretty)


	# process the file "blat"
	processFileBlat(path_file_blat=output_filename_blat)
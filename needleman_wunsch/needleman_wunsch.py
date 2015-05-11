'''
	Implementation of the Needleman-Wunsch Algorithm
	Works in Python 2.x and 3.x
	Author: Marcos Castro

	Needleman-Wunsch performs global alignment

	Scoring System:
		Match: two letters are the same
		Mismatch: two letters are differential
		Indel (insertion or deletion): one letter aligns to a gap in the other string
'''

import sys


'''
	Shows the pretty matrix

	Parameters:
		matrix, rows
'''
def show_pretty_matrix(matrix, rows):
	for i in range(rows):
		print('\t'.join(str(i) for i in matrix[i]))


'''
	Returns the score

	Parameters:
		s1 (sequence 1), s2 (sequence 2), match, mismatch, gap (penalty)

	Returns:
		the score
'''
def get_score(s1, s2, match, mismatch, gap):
	len_s, score = len(s1), 0
	for i in range(len_s):
		if s1[i] != '-' and s2[i] != '-':
			if s1[i] == s2[i]:
				score += match
			else:
				score += mismatch
		else:
			score += gap
	return score


'''
	Needleman-Wunsch Algorithm

	Parameters:
		s1: sequence 1
		s2: sequence 2
		match, mismatch, gap, verbose

	Returns:
		a tuple (s1, s2)
'''
def needleman_wunsch(s1, s2, match, mismatch, gap, verbose=True):

	if verbose:
		print('\nSequence 1: %s' % s1)
		print('Sequence 2: %s' % s2)

	cols, rows = len(s1) + 1, len(s2) + 1
	
	# creates the matrix
	matrix = [[0 for x in range(cols)] for x in range(rows)]

	# directions for to reconstruct the path
	directions = {}

	# fills first column and first line
	matrix[0][0] = 0
	for i in range(1, cols):
		matrix[0][i] = matrix[0][i - 1] + gap
		directions[(0, i)] = (0, i - 1)
	for i in range(1, rows):
		matrix[i][0] = matrix[i - 1][0] + gap
		directions[(i, 0)] = (i - 1, 0)


	# function that returns the maximum value
	def max_value(i, j):

		value1 = matrix[i - 1][j - 1] + (match if s2[i - 1] == s1[j - 1] else mismatch) # left diagonal
		value2 = matrix[i - 1][j] + gap # top
		value3 = matrix[i][j - 1] + gap # left

		# calculates max value
		max_value = max([value1, value2, value3])

		# checks max value
		if max_value == value1:
			directions[(i,j)] = (i - 1, j - 1)
		elif max_value == value2:
			directions[(i,j)] = (i - 1, j)
		else:
			directions[(i,j)] = (i, j - 1)

		return max_value


	# fills remaining of the matrix
	for i in range(1, rows):
		for j in range(1, cols):
			matrix[i][j] = max_value(i, j)

	s1_result, s2_result = '', '' # alignment results
	i, j = rows - 1, cols - 1 # starting with the last value

	while True:

		i_next, j_next = directions[(i, j)]

		if (i - 1) == i_next and (j - 1) == j_next: # diagonal
			s1_result += s1[j_next]
			s2_result += s2[i_next]
		elif (i - 1) == i_next and j == j_next: # top
			s1_result += '-'
			s2_result += s2[i_next]
		elif i == i_next and (j - 1) == j_next: # left
			s1_result += s1[j_next]
			s2_result += '-'

		i, j = i_next, j_next
		if not i and not j:
			break

	s1_result, s2_result = s1_result[::-1], s2_result[::-1]

	if verbose:
		print('\nMatrix:\n')
		show_pretty_matrix(matrix, rows)
		print('\nSequence 1: %s' % s1_result)
		print('Sequence 2: %s\n' % s2_result)

	return (s1_result, s2_result)


def tests():

	print('\nRunning tests...\n')

	# test1
	s1_s2 = ('ACTGATTCA', 'ACGCATCA')
	alignment = needleman_wunsch(s1_s2[0], s1_s2[1], 2, -3, -2, False)
	if alignment == ('ACTG-ATTCA', 'AC-GCA-TCA'):
		print('test1 successfully!')
	else:
		print('fail in test1...')

	# test2
	s1_s2 = ('GCATGCU', 'GATTACA')
	alignments = [('GCATG-CU', 'G-ATTACA'), ('GCAT-GCU', 'G-ATTACA'), ('GCA-TGCU', 'G-ATTACA')]
	alignment = needleman_wunsch(s1_s2[0], s1_s2[1], 1, -1, -1, False)
	if alignment in alignments:
		print('test2 successfully!')
	else:
		print('fail in test2...')

	# test3
	s1_s2 = ('AACGTTAC', 'CGATAAC')
	alignment = needleman_wunsch(s1_s2[0], s1_s2[1], 1, -1, -1, False)
	if alignment == ('AACG-TTAC', '--CGATAAC'):
		print('test3 successfully!')
	else:
		print('fail in test3...')

	# test4
	s1_s2 = ('GACTAC', 'ACGC')
	alignment = needleman_wunsch(s1_s2[0], s1_s2[1], 1, 0, -1, False)
	if alignment == ('GACTAC', '-AC-GC'):
		print('test4 successfully!')
	else:
		print('fail in test4...')

	print('\nFinished.\n')


if __name__ == "__main__":
	
	len_sys_arv = len(sys.argv)
	if len_sys_arv == 2 or len_sys_arv == 6:
		if len_sys_arv == 6:
			s1, s2 = sys.argv[1], sys.argv[2]
			match, mismatch, gap = sys.argv[3], sys.argv[4], sys.argv[5]
			needleman_wunsch(s1, s2, int(match), int(mismatch), int(gap))
		elif len_sys_arv == 2 and sys.argv[1] == 'tests':
			tests()
		else:
			print('\nExecute:\n\tpython needleman_wunsch.py <sequence1> <sequence2> <match> <mismatch> <gap>')
			print('\nExample:\n\tpython needleman_wunsch.py GCATGCU GATTACA 1 -1 -1\n')
	else:
		print('\nExecute:\n\tpython needleman_wunsch.py <sequence1> <sequence2> <match> <mismatch> <gap>')
		print('\nExample:\n\tpython needleman_wunsch.py GCATGCU GATTACA 1 -1 -1\n')
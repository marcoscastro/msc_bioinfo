'''
	Implementation of the Needleman-Wunsch Algorithm
	Works in Python 2.x and 3.x
	Author: Marcos Castro

	Needleman-Wunsch performs global alignment

	Scoring System:
		Match: two letters are the same
		Mismatch: two letters are differential
		Indel (insertion or deletion): one letter aligns to a gap in the other string

	References:
		http://en.wikipedia.org/wiki/Needleman%E2%80%93Wunsch_algorithm
		http://www.cs.utoronto.ca/~brudno/bcb410/lec2notes.pdf
'''

import sys, operator


def show_pretty_matrix(matrix, rows):
	for i in range(rows):
		print('\t'.join(str(i) for i in matrix[i]))


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


def needleman_wunsch(s1, s2, match, mismatch, gap, verbose=True):

	if verbose:
		print('\nSequence 1: %s' % s1)
		print('Sequence 2: %s' % s2)

	len_s1, len_s2 = len(s1) + 1, len(s2) + 1
	
	# creates the matrix
	matrix = [[0 for x in range(len_s1)] for x in range(len_s2)]

	# fills first column and first line
	matrix[0][0] = 0
	for i in range(1, len_s1):
		matrix[0][i] = matrix[0][i-1] + gap
	for i in range(1, len_s2):
		matrix[i][0] = matrix[i-1][0] + gap

	# fills remaining of the matrix
	for i in range(1, len_s2):
		for j in range(1 ,len_s1):
			# calculates score
			cell_top = matrix[i - 1][j] + gap
			cell_diag = matrix[i - 1][j - 1] + (match if s1[j - 1] == s2[i - 1] else mismatch)
			cell_left = matrix[i][j - 1] + gap
			max_score = max(cell_top, cell_diag, cell_left)
			matrix[i][j] = max_score

	alignments = {}

	def get_alignments(i, j, s1_aux, s2_aux):

		top = matrix[i - 1][j] if (i - 1) >= 0 and j >= 0 else None
		diag = matrix[i - 1][j - 1] if (i - 1) >= 0 and (j - 1) >= 0 else None
		left = matrix[i][j - 1] if i >= 0 and (j - 1) >= 0 else None

		values = []
		if top != None:
			values.append(top)
		if diag != None:
			values.append(diag)
		if left != None:
			values.append(left)

		if values:
			max_value = max(values)
			if top != None and max_value == top:
				get_alignments(i - 1, j, s1_aux + '-', s2_aux + s2[i - 1])
			if diag != None and max_value == diag:
				get_alignments(i - 1, j - 1, s1_aux + s1[j - 1], s2_aux + s2[i - 1])
			if left != None and max_value == left:
				get_alignments(i, j - 1, s1_aux + s1[j - 1], s2_aux + '-')
		else:
			s1_aux, s2_aux = s1_aux[::-1], s2_aux[::-1]
			alignments[(s1_aux, s2_aux)] = get_score(s1_aux, s2_aux, match, mismatch, gap)

	get_alignments(len_s2 - 1, len_s1 - 1, '', '')

	max_value = max(alignments.iteritems(), key=operator.itemgetter(1))[1]

	if verbose:
		print('\nMatrix:\n')
		show_pretty_matrix(matrix, len_s2)
		print('\nBest alignments:\n')
		for alignment in alignments:
			if max_value == alignments[alignment]:
				print('\n'.join(alignment))
				print('Score: %d\n' % alignments[alignment])
	return alignments



def tests():

	print('\nRunning tests...')

	# test1
	s1_s2 = ('ACTGATTCA', 'ACGCATCA')
	s1_s2_expected = ('ACTG-ATTCA', 'AC-GCAT-CA')
	alignments = needleman_wunsch(s1_s2[0], s1_s2[1], 2, -3, -2)
	if s1_s2_expected in alignments:
		print('test1 successfully!')
	else:
		print('fail in test1...')

	# test2
	s1_s2 = ('GCATGCU', 'GATTACA')
	s1_s2_expected1 = ('GCATG-CU', 'G-ATTACA')
	s1_s2_expected2 = ('GCAT-GCU', 'G-ATTACA')
	s1_s2_expected3 = ('GCA-TGCU', 'G-ATTACA')
	alignments = needleman_wunsch(s1_s2[0], s1_s2[1], 1, -1, -1)
	if s1_s2_expected1 in alignments or s1_s2_expected2 in alignments or s1_s2_expected3 in alignments:
		print('test2 successfully!\n')
	else:
		print('fail in test2...\n')


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
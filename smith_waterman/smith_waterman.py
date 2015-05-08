# encoding:utf-8

'''
	Implementation of The Smith-Waterman Algorithm
	Works in Python 2.x and 3.x
	Author: Marcos Castro

	Smith-Waterman algorithm perfoms local sequence alignment; that is,
	for determining similar regions between two strings or nucleotide or
	protein sequences.
'''

import sys


'''
	Shows the pretty matrix

	Parameters:
		matrix, rows
'''
def print_pretty_matrix(matrix, rows):

	for i in range(rows):
		print('\t'.join(str(i) for i in matrix[i]))


'''
	Smith-Waterman Algorithm

	Parameters:
		s1: sequence 1
		s2: sequence 2
		gap_penalty: gap penalty

	Returns:
		a tuple (s1, s2)
'''
def smith_waterman(s1, s2, match=2, mismatch=-1, gap_penalty=-1, verbose=True):

	# gets the lengths of the sequences
	len_s1, len_s2 = len(s1), len(s2)

	# matrix with order (len_s2 + 1) x (len_s1 + 1)
	rows, cols = (len_s2 + 1), (len_s1 + 1)

	# creates and initializes the matrix with 0
	matrix = [[0] * cols for i in range(rows)]

	# directions for to reconstruct the path
	directions = {}

	# info_max_value is a list with 3 elements: max_value, line position, col position
	info_max_value = 3 * [-1]

	# function that returns the maximum value
	def max_value(i, j):

		value1 = matrix[i-1][j-1] + (match if s2[i - 1] == s1[j - 1] else mismatch) # left diagonal
		value2 = matrix[i-1][j] + gap_penalty # top
		value3 = matrix[i][j-1] + gap_penalty # left

		# calculates max value
		max_value = max([0, value1, value2, value3])

		# checks max value
		if max_value == value1:
			directions[(i,j)] = (i-1, j-1)
		elif max_value == value2:
			directions[(i,j)] = (i-1, j)
		else:
			directions[(i,j)] = (i, j-1)

		# checks the highest scoring cell
		if info_max_value[0] <= max_value:
			info_max_value[0], info_max_value[1], info_max_value[2] = max_value, i, j

		return max_value


	# fills the matrix
	for i in range(1, rows):
		for j in range(1, cols):
			matrix[i][j] = max_value(i, j)

	# traceback path
	traceback = []

	# starts at the highest scoring cell in the matrix and
	# travels up/left while the score is still positive
	position = (info_max_value[1], info_max_value[2]) # 2-tuple
	while True:
		traceback.append(position)
		if not matrix[position[0]][position[1]]:
			break
		position = directions[tuple(position)]

	traceback = traceback[::-1]
	s1_result, s2_result = '', ''
	len_traceback = len(traceback)
	for k in range(len_traceback - 1):

		i, j = traceback[k]
		i_next, j_next = traceback[k+1]

		# diagonal jump implies there is an alignment
		if (i + 1) == i_next and (j + 1) == j_next:
			s1_result += s1[j_next-1]
			s2_result += s2[i_next-1]
		# top-down jump implies there is a deletion
		elif (i + 1) == i_next and j == j_next:
			s1_result += '-'
			s2_result += s2[i_next-1]
		# left-right jump implies there is a insertion
		elif i == i_next and (j + 1) == j_next:
			s1_result += s1[j_next-1]
			s2_result += '-'

	if verbose:
		print('\nMatrix:\n')
		print_pretty_matrix(matrix, rows)
		print('\nSequence 1: %s' % s1_result)
		print('Sequence 2: %s\n' % s2_result)

	return (s1_result, s2_result)


# run tests
def run_tests():

	print('\nRunning tests...\n')

	# test 1
	r1 = smith_waterman('ACACACTA', 'AGCACACA', match=2, mismatch=-1, gap_penalty=-1, verbose=False)
	if r1 == ('A-CACACTA', 'AGCACAC-A'):
		print('test1 successfully executed')
	else:
		print('fail in test1')
	# test 2
	r2 = smith_waterman('GGCTCAATCA', 'ACCTAAGG', match=2, mismatch=-1, gap_penalty=-2, verbose=False)
	if r2 == ('CTCAA', 'CT-AA'):
		print('test2 successfully executed')
	else:
		print('fail in test2')
	# test 3
	r3 = smith_waterman('ACCGT', 'AGT', match=1, mismatch=-2, gap_penalty=-8, verbose=False)
	if r3 == ('GT', 'GT'):
		print('test3 successfully executed')
	else:
		print('fail in test3')
	# test 4
	r4 = smith_waterman('AACGTTAC', 'CGATAAC', match=1, mismatch=-1, gap_penalty=-1, verbose=False)
	if r4 == ('CG-TTAC', 'CGATAAC'):
		print('test4 successfully executed')
	else:
		print('fail in test4')

	print('\nFinished.\n')


if __name__ == "__main__":

	len_sys_argv = len(sys.argv)
	
	# checks the parameters
	if len_sys_argv < 3 or len_sys_argv > 6:

		if len_sys_argv == 2 and sys.argv[1] == 'tests':
			run_tests()
		else:
			print('\nExecute:\n\tpython <script_name.py> <sequence1> <sequence2> [match] [mismatch] [gap_penalty]')
			print('\n[match], [mismatch] and [gap_penalty] are optional parameters.')
			print('\nExamples:')
			print('\tpython smith_waterman.py ACACACTA AGCACACA')
			print('\tpython smith_waterman.py ACACACTA AGCACACA 2 -1 -1')
			print('\tpython smith_waterman.py GGCTCAATCA ACCTAAGG 2 -1 -2\n')
			print('For run tests: python <script_name.py> run_tests\n')
	else:
		# gets the sequences
		s1, s2 = sys.argv[1], sys.argv[2]

		match, mismatch, gap_penalty = 2, -1, -1

		if len_sys_argv > 3:
			match = int(sys.argv[3])
			if len_sys_argv > 4:
				mismatch = int(sys.argv[4])
				if len_sys_argv > 5:
					gap_penalty = int(sys.argv[5])

		# runs the algorithm
		smith_waterman(s1, s2, match=match, mismatch=mismatch, gap_penalty=gap_penalty)
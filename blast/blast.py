# encoding:utf-8

'''
	An simple implementation of Blast algorithm
	All the references are in the folder "references".
	Author: Marcos Castro
'''

from collections import defaultdict
import score_matrix, operator, random


class Blast:

	# default BLAST: threshold 12 for words of size 3
	def __init__(self, query, database, alphabet, matrix, threshold=12, word_size=3, limit_gaps_extension=5, match=1, gap_open=-5, gap_extend=-1):
		self.query = query
		self.database = database
		self.alphabet = alphabet
		self.matrix = matrix
		self.threshold = threshold
		self.word_size = word_size
		self.limit_gaps_extension = limit_gaps_extension
		self.match = match
		self.gap_open = gap_open
		self.gap_extend = gap_extend
		self.len_query = len(query)
		self.len_database = len(database)

		# generates original words (seeds) with size "word_size"
		self.original_words = [query[i:i+word_size] for i in range(self.len_query) if len(query[i:i+word_size]) == word_size]

		# generates the neighbors for each original word
		# each key is an original word and each value is a list with the neighbors
		# each neighbor is formed by replacing of, in maximum, one letter of the alphabet
		self.neighbors = defaultdict(list)
		for original_word in self.original_words:
			self.neighbors[original_word] = []
			for i in range(self.word_size):
				list_original_word = list(original_word[:])
				for letter in alphabet:
					if list_original_word[i] != letter:
						list_original_word[i] = letter
					neighbor = ''.join(list_original_word)
					if neighbor != original_word:
						self.neighbors[original_word].append(neighbor)

		# list of words to search in the database
		# all the original words are considered for search in database
		self.words = self.original_words[:]

		# not all the neighbors are considered for search in database
		# compares the neighbors with the original word using the scoring matrix
		for original_word in self.original_words:
			for neighbor in self.neighbors[original_word]:
				score = score_matrix.score_pairwise(sequence1=original_word, sequence2=neighbor, matrix=matrix)
				if score >= self.threshold:
					self.words.append(neighbor)


		# the extension is made from the selected words
		self.alignments = {}

		for word in self.words:

			if word in self.query and word in self.database:

				hits_query = [i for i in range(self.len_query) if self.query.startswith(word, i)]
				hits_database = [i for i in range(self.len_database) if self.database.startswith(word, i)]

				for hit_query in hits_query:

					for hit_database in hits_database:

						alignment, num_gaps_left, num_gaps_right = word[:], 0, 0
						left_query, right_query = hit_query - 1, hit_query + self.word_size
						left_database, right_database = hit_database - 1, hit_database + self.word_size

						while True:

							if (left_query < 0 and right_query >= self.len_query) and (left_database < 0 and right_database >= self.len_database):
								break

							if left_query >= 0 and left_database >= 0:
								if self.query[left_query] == self.database[left_database]:
									alignment = self.query[left_query] + alignment[:]
									num_gaps_left = 0
								else:
									num_gaps_left += 1
									if num_gaps_left <= self.limit_gaps_extension:
										# adds gap
										alignment = '-' + alignment[:]
									else:
										# removes extra gaps
										alignment = alignment[self.limit_gaps_extension:]
										break

							if right_query < self.len_query and right_database < self.len_database:
								if self.query[right_query] == self.database[right_database]:
									alignment += self.query[right_query]
									num_gaps_right = 0
								else:
									num_gaps_right += 1
									if num_gaps_right <= self.limit_gaps_extension:
										# adds gap
										alignment = alignment[:] + '-'
									else:
										# removes extra gaps
										alignment = alignment[:-self.limit_gaps_extension]
										break

							left_query -= 1
							left_database -= 1
							right_query += 1
							right_database += 1

						# add alignment
						self.alignments[alignment] = 0

		# calculates the score of the alignments
		for alignment in self.alignments:
			self.alignments[alignment] = self.getScoreAlignment(alignment)


	# returns all the original words
	def getOriginalWords(self):
		return self.original_words

	# returns all the neighbors
	def getNeighbors(self):
		return self.neighbors

	# returns all the words
	def getWords(self):
		return self.words

	# returns all the alignments
	def getAlignments(self):
		return self.alignments

	# calculates the score of the alignment
	def getScoreAlignment(self, alignment):
		gap, score = False, 0
		for c in alignment:
			if not gap:
				if c == '-':
					gap = True
					score += self.gap_open
				else:
					score += self.match
			else:
				if c != '-':
					gap = False
					score += self.match
				else:
					score += self.gap_extend
		return score

	# returns the best alignments
	def getBestAlignments(self):
		best_alignments = []
		if self.alignments:
			try: # python 2.x
				max_score_alignment = max(self.alignments.iteritems(), key=operator.itemgetter(1))[1]
			except: # python 3.x
				max_score_alignment = max(self.alignments.items(), key=operator.itemgetter(1))[1]
			for alignment in self.alignments:
				if self.alignments[alignment] == max_score_alignment:
					best_alignments.append(alignment)
		return best_alignments


# returns a random DNA sequence
def randomDNA(size):

	def random_base():
		return ('ACTG')[random.randint(0,3)] 

	seq = ''
	for i in range(size):
		seq += random_base()
	return seq


# random test
def randomTest(query, database, alphabet, matrix, threshold, word_size, limit_gaps_extension, match, gap_open, gap_extend):

	print('Random test...')
	blast = Blast(query=query, database=database, alphabet=alphabet, matrix=score_matrix.blosum62, threshold=threshold, word_size=word_size, limit_gaps_extension=limit_gaps_extension, match=match, gap_open=gap_open, gap_extend=gap_extend)
	print('\nBest alignments:\n')
	print('\n'.join(blast.getBestAlignments()) + '\n')


'''
Word size:
	for proteins, the word size is normally 3
	for nucleotides, the word size is typically 7, 11 or 15
	w = 15 for example gives fewer matches and is faster than w = 11 or w = 7
'''

# test
if __name__ == "__main__":

	query = 'GCGTACCTGA'
	database = 'ACTGACACACTGGGCGTACCTGAAAAGGCGTACTGGGACACTGGGCGTACCCAAAGGCTCCCATCCACTGGGCGCTGAC'
	alphabet = 'ACTG'
	blast = Blast(query=query, database=database, alphabet=alphabet, matrix=score_matrix.nucleotide_matrix_ungapped, threshold=5, word_size=3, limit_gaps_extension=10, match=1, gap_open=-5, gap_extend=-1)
	print('\nTotal original words: %d' % len(blast.getOriginalWords()))
	print('Total words: %d' % len(blast.getWords()))
	print('\nBest alignments:\n')
	print('\n'.join(blast.getBestAlignments()) + '\n')

	randomTest(randomDNA(size=100), randomDNA(size=10000), alphabet=alphabet, matrix=score_matrix.nucleotide_matrix_ungapped, threshold=5, word_size=7, limit_gaps_extension=5, match=1, gap_open=-5, gap_extend=-1)
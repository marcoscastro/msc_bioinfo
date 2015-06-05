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
	def __init__(self, query, database, alphabet, matrix, threshold=12, word_size=3, limit_mismatch_extension=5):
		self.query = query
		self.database = database
		self.alphabet = alphabet
		self.matrix = matrix
		self.threshold = threshold
		self.word_size = word_size
		self.limit_mismatch_extension = limit_mismatch_extension
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


		# each key is a 2-tuple (alignment_query, alignment_database) and the value is score alignment
		self.alignments = {}

		# the extension (ungapped alignment) is made from the selected words
		for word in self.words:

			if word in self.query and word in self.database:

				hits_query = [i for i in range(self.len_query) if self.query.startswith(word, i)]
				hits_database = [i for i in range(self.len_database) if self.database.startswith(word, i)]

				for hit_query in hits_query:

					for hit_database in hits_database:

						alignment_query, alignment_database, num_gaps_left, num_gaps_right = word[:], word[:], 0, 0
						left_query, right_query = hit_query - 1, hit_query + self.word_size
						left_database, right_database = hit_database - 1, hit_database + self.word_size

						while True:

							# checks the extremes (if can not more extend)
							if (left_query < 0 or left_database < 0) and (right_query >= self.len_query or right_database >= self.len_database):
								break

							# checks the extremes of the left
							if left_query >= 0 and left_database >= 0:
								if self.query[left_query] == self.database[left_database]:
									# add characters
									alignment_query = self.query[left_query] + alignment_query[:]
									alignment_database = self.database[left_database] + alignment_database[:]
									num_gaps_left = 0 # updates gaps number
								else:
									num_gaps_left += 1
									if num_gaps_left <= self.limit_mismatch_extension:
										# add characters
										alignment_query = self.query[left_query] + alignment_query[:]
										alignment_database = self.database[left_database] + alignment_database[:]
									else:
										# removes extra characters (gaps)
										alignment_query = alignment_query[self.limit_mismatch_extension:]
										alignment_database = alignment_database[self.limit_mismatch_extension:]
										break

								# decrements the extremes of the lest
								left_query -= 1
								left_database -= 1

							# checks the extremes of the right
							if right_query < self.len_query and right_database < self.len_database:
								if self.query[right_query] == self.database[right_database]:
									alignment_query += self.query[right_query]
									alignment_database += self.database[right_database]
									num_gaps_right = 0 # updates gaps number
								else:
									num_gaps_right += 1 # updates gaps number
									if num_gaps_right <= self.limit_mismatch_extension:
										alignment_query += self.query[right_query]
										alignment_database += self.database[right_database]
									else:
										# removes extra characters (gaps)
										alignment_query = alignment_query[:-self.limit_mismatch_extension]
										alignment_database = alignment_database[:-self.limit_mismatch_extension]
										break

								# increments the extremes of the right
								right_query += 1
								right_database += 1

						# add the alignment in the dictionary
						self.alignments[(alignment_query, alignment_database)] = 0

		# calculates the score of the alignments
		for alignment in self.alignments:
			alignment_query, alignment_database = alignment
			self.alignments[alignment] = self.getScoreAlignment(alignment_query, alignment_database)


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
	def getScoreAlignment(self, alignment_query, alignment_database):
		return score_matrix.score_pairwise(sequence1=alignment_query, sequence2=alignment_database, matrix=self.matrix)

	# returns the best alignments
	def getBestAlignments(self):
		best_alignments = [] # 3-tuple (alignment_query, alignment_database, score)
		if self.alignments:
			try: # python 2.x
				max_score_alignment = max(self.alignments.iteritems(), key=operator.itemgetter(1))[1]
			except: # python 3.x
				max_score_alignment = max(self.alignments.items(), key=operator.itemgetter(1))[1]
			for alignment in self.alignments:
				if self.alignments[alignment] == max_score_alignment:
					best_alignments.append((alignment[0], alignment[1], max_score_alignment))
		return best_alignments

	# shows pretty the best alignments
	def showPrettyBestAlignments(self):
		print('\nBest alignments:\n')
		best_alignments = blast.getBestAlignments()
		for alignment in best_alignments:
			print(alignment[0])
			slashes, size_alignment = '', len(alignment[0])
			for i in range(size_alignment):
				if alignment[0][i] == alignment[1][i]:
					slashes += '|'
				else:
					slashes += ' '
			print(slashes)
			print(alignment[1])
			print('Score: %d\n' % alignment[2])


# returns a random DNA sequence
def randomDNA(size):

	def random_base():
		return ('ACTG')[random.randint(0,3)] 

	seq = ''
	for i in range(size):
		seq += random_base()
	return seq
	

'''
Word size:
	for proteins, the word size is normally 3
	for nucleotides, the word size is typically 7, 11 or 15
	w = 15 for example gives fewer matches and is faster than w = 11 or w = 7

The original BLAST only generates ungapped alignments.
'''

# test
if __name__ == "__main__":

	query = 'GCGTAAACCTGA'
	database = 'ACTGACACACTGGGCGTACCTGAAAAGGAC'
	alphabet = 'ACTG'
	blast = Blast(query=query, database=database, alphabet=alphabet, matrix=score_matrix.nucleotide_matrix_ungapped, threshold=5, word_size=3, limit_mismatch_extension=5)
	blast.showPrettyBestAlignments()

	print('Random test...')
	blast = Blast(randomDNA(size=1000), randomDNA(size=10000), alphabet=alphabet, matrix=score_matrix.nucleotide_matrix_ungapped, threshold=5, word_size=7, limit_mismatch_extension=5)
	blast.showPrettyBestAlignments()
CPP    = g++
RM     = rm -f
OBJS   = main.o \
         fastq_reader.o \
         read.o \
         graph.o \
         kmer.o \
         edge.o

LIBS   =
CFLAGS =

.PHONY: dgv.exe clean clean-after

all: dgv.exe

clean:
	$(RM) $(OBJS) dgv.exe

clean-after:
	$(RM) $(OBJS)

dgv.exe: $(OBJS)
	$(CPP) -Wall -s -o $@ $(OBJS) $(LIBS)

main.o: main.cpp fastq_reader.h graph.h
	$(CPP) -Wall -s -c $< -o $@ $(CFLAGS)

fastq_reader.o: fastq_reader.cpp fastq_reader.h
	$(CPP) -Wall -s -c $< -o $@ $(CFLAGS)

read.o: read.cpp read.h
	$(CPP) -Wall -s -c $< -o $@ $(CFLAGS)

graph.o: graph.cpp graph.h
	$(CPP) -Wall -s -c $< -o $@ $(CFLAGS)

kmer.o: kmer.cpp kmer.h
	$(CPP) -Wall -s -c $< -o $@ $(CFLAGS)

edge.o: edge.cpp edge.h
	$(CPP) -Wall -s -c $< -o $@ $(CFLAGS)


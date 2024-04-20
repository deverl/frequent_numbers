
all : freqc freqcpp

.PHONY : clean

freqc : freq_nums.c makefile
	gcc -Wall -pedantic -O3 -o freqc freq_nums.c
	strip freqc


freqcpp : frequentNumbers.cpp makefile
	g++ -Wall -pedantic -O3 -std=c++11 -o freqcpp frequentNumbers.cpp
	strip freqcpp


clean:
	rm -f freqc freqcpp *.class *.tmp.html a.out
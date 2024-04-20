
all : freqc freqcpp FrequentNumbers.class

.PHONY : clean runlua runpython runjs runphp


freqc : freq_nums.c makefile
	gcc -Wall -pedantic -O3 -o freqc freq_nums.c
	strip freqc


freqcpp : frequentNumbers.cpp makefile
	g++ -Wall -pedantic -O3 -std=c++11 -o freqcpp frequentNumbers.cpp
	strip freqcpp


FrequentNumbers.class: FrequentNumbers.java makefile
	javac FrequentNumbers.java


runc: freqc makefile
	./freqc


runcpp: freqcpp makefile
	./freqcpp


runjava: FrequentNumbers.class
	java -cp . FrequentNumbers


runlua:
	lua frequentNumbers.lua


runpython:
	python frequentNumbers.py


runjs:
	node frequentNumbers.js


runphp:
	php frequentNumbers.php


clean:
	rm -f freqc freqcpp *.class *.tmp.html a.out
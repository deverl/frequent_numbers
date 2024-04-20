
all : freqc freqcpp freqgo FrequentNumbers.jar

.PHONY : clean runlua runpython runpy runjavascript runjs runphp rungo


freqc : freq_nums.c makefile
	gcc -Wall -pedantic -O3 -o freqc freq_nums.c
	strip freqc


freqcpp : frequentNumbers.cpp makefile
	g++ -Wall -pedantic -O3 -std=c++11 -o freqcpp frequentNumbers.cpp
	strip freqcpp


freqgo: go/frequentNumbers.go makefile
	cd go ; go build -o freqgo ; mv freqgo ..


FrequentNumbers.jar: FrequentNumbers.java makefile
	javac FrequentNumbers.java
	echo "Main-Class: FrequentNumbers" > MainClass.txt
	jar cmfv MainClass.txt FrequentNumbers.jar *.class
	rm -f MainClass.txt *.class


runall: runc runcpp rungo runjava runjs runlua runphp runpy



runc: freqc makefile
	./freqc


runcpp: freqcpp makefile
	./freqcpp


rungo: freqgo makefile
	./freqgo


runjava: FrequentNumbers.jar
	java -jar FrequentNumbers.jar


runlua:
	lua frequentNumbers.lua


runpython:
	python frequentNumbers.py

runpy: runpython


runjavascript:
	node frequentNumbers.js

runjs: runjavascript


runphp:
	php frequentNumbers.php


clean:
	rm -f freqc freqcpp freqgo *.jar MainClass.txt *.class *.tmp.html a.out
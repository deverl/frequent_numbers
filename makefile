
# Fortran is optional: only build and run it if the flang compiler is available.
FLANG := $(shell command -v flang 2>/dev/null)

all : freqc freqcpp freqgo FrequentNumbers.jar

.PHONY : clean runlua runpython runpy runjavascript runjs runphp rungo runfortran


freqc : freq_nums.c makefile
	gcc -Wall -pedantic -O3 -o freqc freq_nums.c
	strip freqc


freqcpp : frequentNumbers.cpp makefile
	g++ -Wall -pedantic -O3 -std=c++20 -o freqcpp frequentNumbers.cpp
	strip freqcpp


freqgo: go/frequentNumbers.go makefile
	cd go ; go build -o freqgo ; mv freqgo ..


freqjava : FrequentNumbers.jar
	@echo '#/usr/bin/env bash' > freqjava
	@echo 'java -jar FrequentNumbers.jar "$$@"' >> freqjava
	@chmod a+x freqjava


freqrust : rust/src/main.rs
	cd rust ; cargo build --release ; cp target/release/freq_nums ../freqrust


freqfortran : FrequentNumbers.f90 makefile
	flang -O2 -o freqfortran FrequentNumbers.f90

FrequentNumbers.jar: FrequentNumbers.java makefile
	javac FrequentNumbers.java
	echo "Main-Class: FrequentNumbers" > MainClass.txt
	jar cmfv MainClass.txt FrequentNumbers.jar *.class
	rm -f MainClass.txt *.class

freqkt.jar: frequentNumbers.kt makefile
	kotlinc frequentNumbers.kt -include-runtime  -d freqkt.jar

freqkt: freqkt.jar
	@echo '#/usr/bin/env bash' > freqkt
	@echo 'java -jar freqkt.jar "$$@"' >> freqkt
	@chmod a+x freqkt

runall: runc runcpp rungo runjava runjs runlua runphp runpy runkt runjava runrust runfortran



runc: freqc makefile
	./freqc


runcpp: freqcpp makefile
	./freqcpp

runrust: freqrust makefile
	./freqrust

ifneq ($(FLANG),)
runfortran: freqfortran makefile
	./freqfortran
else
runfortran:
	@echo "flang not found; skipping the Fortran version."
endif

rungo: freqgo makefile
	./freqgo


runjava: freqjava
	./freqjava

runkt: freqkt
	./freqkt

runktbig: freqkt
	./freqkt 10_000_000 1_000 20

runlua:
	lua frequentNumbers.lua

runpython:
	python3 frequentNumbers.py

runpy: runpython


runjavascript:
	node frequentNumbers.js

runjs: runjavascript


runphp:
	php frequentNumbers.php


clean:
	rm -rf freq_nums freqc freqcpp freqrust freqgo freqfortran *.jar MainClass.txt *.class *.tmp.html a.out *.dSYM freqjava freqkt freqkt.jar rust/target freq_mod.mod 



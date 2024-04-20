
freq_nums : freq_nums.c makefile
	gcc -Wall -pedantic -O3 -o freq_nums freq_nums.c
	strip freq_nums

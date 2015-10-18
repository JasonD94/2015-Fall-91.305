# Makefile to build MASM, modified prom.dat file, and test objects.
# Also should test the programs against my input / output files
DIR := masm
FILES := a4_div_test a4_mult_test a4_rshift_test
TESTS := div mult rshift

# Run the whole Makefile
all: assembler prom build test

# I found a verson of this in mic1 repository's Makefile.
# URL is here:
# https://github.com/jeapostrophe/mic1/blob/master/Makefile
assembler:
	cd $(DIR) && $(MAKE)

# Make the updated prom.dat file
prom: prom.mc
	./mcc < prom.mc > prom.dat

# Build the test objects
build:
	./masm/masm < a4_div_test.asm > div.obj
	./masm/masm < a4_mult_test.asm > mult.obj
	./masm/masm < a4_rshift_test.asm > rshift.obj

# Test the input files (.ins) against the output files (.outs).
test:
	./mic1 prom.dat div.obj 0 1024 < div.in > actual.out || true
	diff -c actual.out div.out | cat -vet

	./mic1 prom.dat mult.obj 0 1024 < mult.in > actual.out || true
	diff -c actual.out mult.out | cat -vet

	./mic1 prom.dat rshift.obj 0 1024 < rshift.in > actual.out || true
	diff -c actual.out rshift.out | cat -vet

# Clean up all the files.
clean:
	rm prom.dat *.obj
	cd $(DIR) && make clean
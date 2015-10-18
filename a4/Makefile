# Makefile to build MASM, modified prom.dat file, and test objects.
# Also should test the programs against my input / output files
DIR := masm

# Run the whole Makefile
all: assembler prom

# I found a verson of this in mic1 repository's Makefile. URL is here:
# https://github.com/jeapostrophe/mic1/blob/master/Makefile
assembler:
	cd $(DIR) && $(MAKE)

# Make the updated prom.dat file
prom: prom.mc
	./mcc < prom.mc > prom.dat

# Clean up all the files.
clean:
	rm prom.dat
	cd $(DIR) && make clean
CC = gcc
CFLAGS	 = -o -Werror -Wextra -Wall

# Run ./a1 < test.in to run the test file.
# Run ./a1 < test.in > standard_output.out to run the test file while redirecting to a file named standard_output.out

# This site was helpful:
# http://www.cs.toronto.edu/~penny/teaching/csc444-05f/maketutorial.html

all:
	# Compile the program.
	$(CC) $(CFLAGS) a1.c -o a1

	# Run the program using the test.in file, and redirect to a file named standard_output.out
	./a1 < test.in > standard_output.out

	# Compare standard_output.out against test.out
	diff standard_output.out test.out

clean:
	# Remove the executable / standard output file.
	rm a1 standard_output.out

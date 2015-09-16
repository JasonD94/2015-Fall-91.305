CC = gcc
CFLAGS	 = -o -Werror -Wextra -Wall

all:
	# Compile the program.
	$(CC) $(CFLAGS) a2.c -o a2

	# Run the program using the test.in file, and redirect to a file named standard_output.out
	./a2 < test.in > output

	# Compare standard_output.out against test.out
	diff  -c output test.out

clean:
	# Remove the executable / standard output file.
	rm a2 output

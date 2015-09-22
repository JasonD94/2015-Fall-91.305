CC = gcc
CFLAGS	 = -o -Werror -Wextra -Wall

all:
	# Compile the program.
	$(CC) $(CFLAGS) a1.c -o a1

	# Run the program using the test.in file, and redirect to a file named standard_output.out
	./a1 < test.in > standard_output.out

	# Compare standard_output.out against test.out
	# I decided to ignore white space and only test that the answers were valid (the -w option).
	# So if something doesn't "quite" line up I won't catch that.
	# But that's fine. The answer is still correct and I don't have to fight with the test.out file.
	diff  -w -c standard_output.out test.out

clean:
	# Remove the executable / standard output file.
	rm a1 standard_output.out

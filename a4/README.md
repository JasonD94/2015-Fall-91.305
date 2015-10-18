3.5 MIC-1 Microcode Extension
==============================
For this assignment, we will be writing new MIC-1 opcodes. The following codes
will be written (HALT will be changed):

- MULT   - 1111111 1 00 mmmmmm
- RSHIFT - 1111111 1 01 ??ssss
- DIV    - 1111111 1 10 ??????
- HALT   - 1111111 1 11 ??????

We should use the three example programs as tests for the new instructions.

- [a4 divide test](https://jeapostrophe.github.io/courses/2015/fall/305/notes/dist/a4_div_test.asm)
- [a4 multiply test](https://jeapostrophe.github.io/courses/2015/fall/305/notes/dist/a4_mult_test.asm)
- [a4 rshift test](https://jeapostrophe.github.io/courses/2015/fall/305/notes/dist/a4_rshift_test.asm)

We should turn in the following files:

- README
- rmd.mc
- rmd.prom
- masm source directory
- test files: div.in, mult.in, rshift.in
- test output files: div.out, mult.out, rshift.out
- Makefile that: builds microcode, builds assembler, builds test object files using
the .in files and compares the output to the .out files.

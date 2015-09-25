start:  call main:   ;push return address on stack
        halt         ;enter debugger
main:   lodd count:  ;load AC with value at count
        jzer done:   ;if count is less than 0 we are done.
        halt         ;enter debugger after each Fibonacci number.
        call fibn:   ;fibonacci loop
fibn:   lodd n:      ;load Fibonacci # to calculate.
        jzer add1:   ;when n is less than 0 we can jump back to the main loop.
        lodd fib:    ;load the current fib #
        addd fn1:    ;Add fn1 to AC
        addd fn2:    ;Add fn2 to AC
        stod fib:    ;Store fib #
        lodd fn1:    ;Load fn1
        stod fn2:    ;Store fn1 at fn2
        lodd fib:    ;Load fib #
        stod fn1:    ;Store Fib # at fib
        lodd n:      ;Load value of n
        subd one1:   ;Subtract 1 from AC (n)
        stod n:      ;Store AC (n) in var n.
        jump fibn:   ;Jump to top of fibonacci loop
add1:   lodd n:      ;load N
        addd one1:   ;add 1 to N
        stod n:      ;store N
        jump disp:   ;load Fib # into AC
disp:   lodd fib:    ;^
        halt         ;Call debugger.
        jump main:   ;back to main.
done:   pop          ;come here when all data added, sum in AC
        retn         ;return to caller
        halt         ;should never get here (safety halt)
count:  25           ;location for running count
n:      0            ;location for running data pointer
fib:    0            ;Fibonacci number. Formula: Fn = Fn-1 + Fn-2
fn1:    0            ;Fn-1
fn2:    1            ;Fn-2
zero:   0            ;location of a constant value of 0
one1:   1            ;location of a constant value of 1

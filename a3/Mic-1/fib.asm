main:   lodd count:   ;load AC with value at count (counting down to 0 from 25)
        jzer done:    ;if count is less than 0 we are done.
        lodd zero:    ;load 0 into AC
        stod fn:      ;make fn (current fib number)  start at 0.
        stod fn1:     ;make fn-1 start at 0. (seed value 0)
        lodd one:     ;load one into AC
        stod fn2:     ;make fn-2 start at 1. (seed value 1)
        lodd x:       ;load the Fibonacci # we want to calculate.
        stod fibnum:  ;store fibonacci # in tempn counter.
        ; This is the fibonacci function.
        ; fibnum: is the fibonacci number you want to calculate.
fibn:   lodd fibnum:  ;load Fibonacci # to calculate.
        jzer add1:    ;when tempn is less than 0 we can jump to add1
        lodd zero:    ;LOAD ZERO NOT FIB #.
        addd fn1:     ;Add fn1 to AC
        addd fn2:     ;Add fn2 to AC
        stod fn:      ;Store fib number
        lodd fn1:     ;Load fn-1
        stod fn2:     ;Store fn-1 at fn-2
        lodd fn:      ;Load fib number
        stod fn1:     ;Store Fib number at fn-1
        lodd fibnum:  ;Load value of tempn
        subd one:     ;Subtract 1 from AC (tempn)
        stod fibnum:  ;Store AC (tempn) in var tempn.
        jump fibn:    ;Jump to top of fibonacci loop
add1:   lodd x:       ;load while loop var (x)
        addd one:     ;add 1 to x
        stod x:       ;incremented so save x
        lodd count:   ;load count
        subd one:     ;subtract 1 from count.
        stod count:   ;store count
        lodd fn:      ;load Fib # into AC
        push          ;push onto stack. should end up starting at location 1023
        jump main:    ;jump back to main.
done:   retn          ;return to caller
        halt          ;should never get here (safety halt)
count:  25            ;location for running count, counts down to -1.
x:       0            ;
fibnum:  0            ;The Fibonacci number we want to calculate.
fn:      0            ;Fibonacci number. Formula: Fn = Fn-1 + Fn-2
fn1:     0            ;Fn-1
fn2:     1            ;Fn-2
zero:    0            ;location of a constant value of 0
one:     1            ;location of a constant value of 1

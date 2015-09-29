main:   lodd count:   ;load AC with value at count (counting down to 0 from 25)
        stod fibnum:  ;store fibonacci # we want to calculate.
        jneg done:    ;if count is less than 0 then we are done.
        lodd zero:    ;load 0 into AC
        stod fn:      ;make fn (current fib number)  start at 0.
        stod fn1:     ;make fn-1 start at 0. (seed value 0)
        lodd one:     ;load one into AC
        stod fn2:     ;make fn-2 start at 1. (seed value 1)
        ; This is the fibonacci function. fibnum: is the fib number to calculate.
fibn:   lodd fibnum:  ;load Fibonacci # to calculate.
        jzer incr:    ;when fibnum equals 0 we can jump to incr
        lodd zero:    ;LOAD ZERO NOT FIB #. (clear the AC)
        addd fn1:     ;Add fn1 to AC
        addd fn2:     ;Add fn2 to AC
        stod fn:      ;Store fib number   (fn = fn-1 + fn-2)
        lodd fn1:     ;Load fn-1
        stod fn2:     ;Store fn-1 at fn-2 (fn-2 = fn-1)
        lodd fn:      ;Load fib number
        stod fn1:     ;Store Fib number at fn-1 (fn-1 = fn)
        lodd fibnum:  ;Load the fibnum counter
        subd one:     ;Subtract 1 from AC (which is fibnum)
        stod fibnum:  ;Store AC (fibnum) into var fibnum.
        jump fibn:    ;Jump to top of fibonacci loop (keep jumping til fibnum == 0)
incr:   lodd count:   ;load count
        subd one:     ;subtract 1 from count.
        stod count:   ;store count
        lodd fn:      ;load Fib # into AC
        push          ;push onto stack. should end up starting at location 1024
        jump main:    ;jump back to main, to get the next fibonacci number.
done:   halt          ;we are done, so halt and don't catch fire.
count:  25            ;location for running count, counts down to 0.
fibnum:  0            ;The Fibonacci number we want to calculate. (decrements down to 0)
fn:      0            ;This is Fn in the formula: Fn = Fn-1 + Fn-2
fn1:     0            ;this is basically Fn-1 in  ^^^
fn2:     1            ;this is basically Fn-2 in  ^^^
zero:    0            ;location of a constant value of 0
one:     1            ;location of a constant value of 1

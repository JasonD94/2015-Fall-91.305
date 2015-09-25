start:  call main:   ;go to main
        halt         ;enter debugger
main:   lodd count:  ;load AC with value at count
        jneg done:   ;if count is less than 0 we are done.
        lodd zero:   ;load 0 into AC
        stod fn:     ;make fn start at 0.
        stod fn1:    ;make fn1 start at 0.
        lodd one1:   ;load one into AC
        stod fn2:    ;make fn2 start at 1.
        lodd n:      ;load Fibonacci # to calculate.
        stod tempn:  ;store fibonacci # in tempn counter.
        call fibn:   ;fibonacci loop
fibn:   lodd tempn:  ;load Fibonacci # to calculate.
        jneg add1:   ;when tempn is less than 0 we can jump to add1
        lodd zero:   ;BUG HERE, LOAD ZERO NOT FIB #. (i'm such a moron.)
        addd fn1:    ;Add fn1 to AC
        addd fn2:    ;Add fn2 to AC
        stod fn:     ;Store fib #
        lodd fn1:    ;Load fn1
        stod fn2:    ;Store fn1 at fn2
        lodd fn:     ;Load fib #
        stod fn1:    ;Store Fib # at fib
        lodd tempn:  ;Load value of tempn
        subd one1:   ;Subtract 1 from AC (tempn)
        stod tempn:  ;Store AC (n) in var n.
        jump fibn:   ;Jump to top of fibonacci loop
add1:   lodd n:      ;load N
        addd one1:   ;add 1 to N
        stod n:      ;store N
        lodd count:  ;load count
        subd one1:   ;subtract 1 from count.
        stod count:  ;store count
        jump disp:   ;go to display Fib # function
disp:   lodd fn:     ;load Fib # into AC
        halt         ;Call debugger.
        jump main:   ;jump back to main.
done:   pop          ;come here when all data added, sum in AC
        retn         ;return to caller
        halt         ;should never get here (safety halt)
count:  25           ;location for running count
n:      -1           ;location for running data pointer
tempn:  0            ;temp counter for fibn loop.
fn:     -1           ;Fibonacci number. Formula: Fn = Fn-1 + Fn-2
fn1:    0            ;Fn-1
fn2:    1            ;Fn-2
zero:   0            ;location of a constant value of 0
one1:   1            ;location of a constant value of 1

# ttyout code: assume value to print in reg2
# FOR NOW: assume return address is in reg1
# assume tty registers are:
# 1020: status
# 1021: control/command
# 1022: data-out

# Assume this code is at 1000
# read busy bit in status register until it is 0
mov *1020 reg0
jnz reg0 1000
# busy bit is cleared:  set write bit in control reg.
mov 2 1021
# put character to print in data-out
mov reg2 1022
# set command-ready and write bit 
mov 3 1021
# return to caller
jmp reg1

# ttyin code: read from kbd registers and leave
# value in reg2.
# FOR NOW: assume return address is in reg1
# assume tty registers are:
# 997: status
# 998: control/command
# 999: data-in

# This code starts at 1006.
# read busy bit in status register until it is 0
mov *997 reg0
jnz reg0 1006
# busy bit is cleared: set command-ready and read bits in control reg
mov 5 998
# loop while command-ready bit is set.
mov *998 reg0
jnz reg0 1009
# move value to reg2 and return
mov *999 reg2
jmp reg1



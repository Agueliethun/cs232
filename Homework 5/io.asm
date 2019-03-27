# Assumes this code is loaded at address 20.
# return address
mov 22 reg1
# get input from kybd
jmp 1006

# use memory location 2 to store inputted character.
mov reg2 2
mov *2 reg2
mov 26 reg1
# output value
jmp 1000
mov *2 reg2
mov 29 reg1
jmp 1000
mov *2 reg2
mov 32 reg1
jmp 1000
end
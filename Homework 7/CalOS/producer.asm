# Program must be loaded at address 200.
# Locations of values the program uses:
# next_val: 199
# BUFFER_SIZE 250
# counter: 251
# in: 252
# out: 253 (used by consumer.asm)
# producer_n: 254 number of times producer should run -- for debugging
# buffer: 260 - (260+BUFFER_SIZE-1)

# Produce increasing integers into a circular buffer,
# using a counter keeping track of how many are in the buffer.

# Algorithm:

# assume user sets these to 0 before starting program
# next_val = 0;
# in = 0
# out = 0

# 1 do {
# 2	next_produced = next_val
# 3	next_val = next_val + 1
# 4	while (counter == BUFFER_SIZE)
# 5		; /* do nothing */ 
# 6	buffer[in] = next_produced; 
# 7	in = in + 1
# 8	if in == BUFFER_SIZE:
# 9		in = 0
# 10	counter++; 
# 11 } while (--n != 0)

__main:	
# line 2  location 200  move next_val reg0
mov *199 reg0
# line 3
mov reg0 reg1
add 1 reg1
mov reg1 199

# while:    lines 4 and 5. location 204  move counter to reg1
mov *251 reg1
# subtract BUFFER_SIZE 
sub *250 reg1
# jump back to while: line if == 0
jez reg1 204		

# line 6: add in to buffer, in reg1   260 is location of buffer[]
mov 260 reg1
# move value in "in" to reg2
mov *252 reg2
add reg2 reg1
# move next_produced to address in reg1
mov reg0 *reg1

# line 7: in is still in reg2
add 1 reg2	
mov reg2 252
# line 8  subtract BUFFER_SIZE from in.
sub *250 reg2
# jump nz to inc_counter:
jnz reg2 216
# line 9: move 0 to "in" variable
mov 0 252		

# inc_counter		line 10  location 216
mov *251 reg1
add 1 reg1
mov reg1 251

# line 11 jump to main
mov *254 reg1
sub 1 reg1
mov reg1 254
jnz reg1 200
end





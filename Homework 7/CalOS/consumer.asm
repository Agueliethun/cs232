# Program must be loaded at address 225.
# Locations of values the program uses:
# consumed_val: 224
# BUFFER_SIZE: 250: usually 10: 10 slots in circular buffer
# counter: 251
# in: 252  (used by producer.asm)
# out: 253
# producer_n: 254: number of times producer should run -- for debugging
# consumer_n: 255: number of times consumer should run -- for debugging
# buffer: 260 - (260 + BUFFER_SIZE - 1)

# Consumes integers from a circular buffer,
# using a counter keeping track of how many are in the buffer.

# Algorithm:

# 1 do {
# 2	while (counter == 0) 
# 3		; /* do nothing */ 
# 4	consumed_val = buffer[out];
# 5	out = out + 1
# 6    if out == BUFFER_SIZE:
# 7		out = 0
# 8     counter--;
# 9 } while (--n != 0);

# Starts at memory location 225
__main:
# lines 2 and 3.
mov *251 reg0
jez reg0 225

# line 4
mov 260 reg0
mov *253 reg1
add reg1 reg0
mov *reg0 reg2
mov reg2 224

# line 5: increment out and store
mov *253 reg0
add 1 reg0
mov reg0 253

# line 6: subtract BUFFERSIZE from out.
sub *250 reg0
jnz 238
# line 7: move 0 to out
mov 0 253

# line 8 decrement counter.
mov *251 reg0
sub 1 reg0
mov reg0 251

# line 9
mov *255 reg0
sub 1 reg0
mov reg0 255
jnz reg0 225
end





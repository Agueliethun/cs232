# Add two numbers, found in locations 3 and 4, leaving the result in location 5.
# Code can be loaded anywhere.
__main:
# zero out the result
mov *3 reg0
add *4 reg0
mov reg0 5
end

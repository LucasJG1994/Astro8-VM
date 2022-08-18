;setup variable
ldib 0d0
ldia 0d13
sta  0d0

;loop
ain 0d0
sta 0d65278, b
inb
ldia 0d256
sub
jclr 0d3
hlt

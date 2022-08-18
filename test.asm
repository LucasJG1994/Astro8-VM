color = 0d0
screen = 0d65278

	;setup variable
	ldib 0d0
	ldia 0d13
	sta  color
	
	;loop
	
	call draw
	hlt
	
	
draw
	ain color
	sta screen, b
	inb
	ldia 0d256
	sub
	jclr draw
	ret



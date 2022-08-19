;Drawing function
draw_color = 0d2
draw_screen = 0d65278
	
draw
	pla
	sta.l draw_color
	
draw_while0
	ain.l draw_color
	sta draw_screen, b
	inb
	ldia 0d256
	sub
	jclr draw_while0
	ret
	
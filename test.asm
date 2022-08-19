;main function
	.include "draw.asm"

main
	ldia 0d13
	pha
	call draw
	hlt
	
                .global getColor

                .text
@ getColor(iters) -> rgb
getColor:

	push	{ip, lr}
	
	@numerator = iters - 1 
	ldr	r1, =palette_size	@load location of palettesize to r1
	ldr	r1, [r1]		@load palettesize into r1
	sub	r0, r0, #1		@decrement r0 (itters)
	@denominator = colorpalettesize
	bl	remainder		@r0 returns remainder	
	ldr	r2, =palette		@load palette location to r2
	@color in palette at palettesize+remainder * 4(# of bytes per color)
	ldr	r0, [r2, r0, lsl #2]	@load r0 with color ^
	
	@return in r0, the color from the palette0
	
	pop	{ip, pc}

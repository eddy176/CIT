                .global writeRGB

                .text
@ writeRGB(buffer, rgb) -> number of bytes written
writeRGB:
                @ r0: buffer passed in
                @ r1: scratch/ rgb value passed in
                @ r2: scratch/ count return value?
                @ r3: scratch/ input register
                @ r4: buffer pointer backup
                @ r5: location in buffer backup
		@ r6: counter to add to location in buffer
	
	push	{r4, r5, r6, lr}@allocating registers
	
	mov	r4, r0			@back up the buffer
	mov	r5, r1			@back up rgb
	mov	r6, #0			@start count at 0

	@blue
	
	mov	r1, #0xff		@set up barell shifter
	and	r1, r1, r5, lsr #16	@shift the bits 16 right
	add	r0, r4, r6		@pass in offset buffer
	bl	itoa
	add	r6, r6, r0		@increment buffer count

	mov	r2, #' '		@put space into r2 to
	strb	r2, [r4, r6]		@put space between channel values
	add	r6, r6, #1		@increment buffer count

	@green
	mov	r1, #0xff		@set up barell shifter
	and	r1, r1, r5, lsr #8	@shift the bits 8 right
	add	r0, r4, r6		@pass in offset buffer
	bl	itoa
	add	r6, r6, r0		@save new buffer location value
	
	mov	r2, #' '		@put space in r2 to
	strb	r2, [r4, r6]		@put space between channel values
	add	r6, r6, #1		@increment buffer count
	
	@red
	mov	r1, #0xff		@set up barell shifter
	and	r1, r1, r5		@and rgb with barell shifter
	add	r0, r4, r6		@pass in offset buffer
	bl	itoa
	add	r6, r6, r0		@save new buffer location value

	mov	r0, r6			@move count into r0

	pop	{r4, r5, r6, pc} 	

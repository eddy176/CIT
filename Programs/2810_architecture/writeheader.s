			
			.global writeHeader
			
			.equ color_magic, 255
			
			.text
writeHeader:
		@r0: return value
		@r1: scratch
		@r2: scratch
		@r3: scratch	input register
		@r4: (used)	buffer backup
		@r5: (used)	new_n back-up
		@r6: (used)	len of buffer(stackpointer)
	push	{r4, r5, r6, r7, ip, lr}	@allocating registers
	mov 	r4, r0			@back-up the buffer
	mov	r5, r2			@back-up Y
	mov	r6, #0
	ldr	r7, =color_magic	@save maxcolor
	
	mov	r3, #'P'		@put p into r3
	strb	r3, [r4, r6]		@store it into the buffer
	add 	r6, r6, #1		@increment buffer size
	
	mov	r3, #'3'		@put 3 into r3
	strb	r3, [r4, r6]		@store it into the buffer
	add	r6, r6, #1		@increment buffer size
	
	mov	r3, #'\n'		@put new line into r3
	strb	r3, [r4, r6]		@store it into the buffer
	add	r6, r6, #1		@increment buffer size

	add	r0, r4, r6		@set buffer to correct location
	
	bl	itoa			@call itoa
	add 	r6, r6, r0		@adds itoa's change to buffer size

	mov	r3, #' '		@put space into buffer
	strb	r3, [r4, r6]		@store it into the buffer
	add	r6, r6, #1		@increment buffer size
	
	add	r0, r4, r6		@set buffer to the correct location
	mov	r1, r5			@put new_n into r1


	bl	itoa			@r0 is bytes written, r1-3 scratched


	add	r6, r6, r0		@add itoa's change to buffer size

	mov	r3, #'\n'		@put newline into r3 to be stored 
	strb	r3, [r4, r6]		@store it into the buffer
	add	r6, r6, #1		@increment buffer size

	add	r0, r4, r6		@buffer and length stored at r0	
	mov	r1, r7			@move maxcolor to r1
	bl 	itoa			@call itoa
	
	add	r6, r6, r0		@add itoa's count to buffer length
	
	mov	r3, #'\n'		@put \n into r3 to be stored
	strb	r3, [r4, r6]		@store it into the buffer
	add	r6, r6, #1		@increment count

	mov	r0, r6			@move count into r0
	
	pop	{r4, r5, r6, r7, ip, pc}	@reset registers to original

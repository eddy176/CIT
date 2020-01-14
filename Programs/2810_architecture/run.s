                .global run

                .equ    flags, 577
                .equ    mode, 0644

                .equ    sys_write, 4
                .equ    sys_open, 5
                .equ    sys_close, 6

                .equ    fail_open, 1
                .equ    fail_writeheader, 2
                .equ    fail_writerow, 3
                .equ    fail_close, 4

                .text

@ run() -> exit code
run:

@ your code goes here
			@pass these into calcPixel			
			@calc r0 =	maxiters
			@calc r1 =	column
			@calc r2 =	row
			@calc r3 =	xsize
			@calc push	ysize
			@calc d0 =	xcenter
			@calc d1 =	ycenter
			@calc d2 =	magnification

			@r11 =	filetype (fd)
			@r5 =	column #
			@r6 = 	buffer length
			@r7 = 	command for sys
			@r8 =	
			@r9 =	row #
			@r10=	xsize
			@r4=	ysize
			@lr =	filler
	push	{r4-r11,ip,lr}

	@open
	ldr	r0, =filename	@put filename into r0
	ldr	r1, =flags	@put flags into r1
	ldr	r2, =mode	@put the mode into r2
	mov	r7, #sys_open	@open file command
	svc 	#0		@super call(call OS to write to file)	
				@os should return something >= 0
	cmp	r0, #0		@compare value in r0 with 0
	bge	1f		@call if >= 0 to 1f
	
	mov	r0, #fail_open	@puts fail_open command into r0, passing
				
	b	9f
	@in case of failure, branch to 9f to complete program


	@writeheader into buffer
1:				@1f is run if r0 >= 0
	mov	r11, r0		@put filetype to r11
	ldr	r0, =buffer	@load buffer into r0
	ldr	r1, =xsize	@load address of xsize into r1
	ldr	r1, [r1]	@load xsize to r10 from location r1
	ldr	r2, =ysize	@load address of ysize into r2
	ldr	r2, [r2]	@load r2 with ysize
	bl	writeHeader	@branch with link to writeheader
	@writeheader returns # of bytes in r0
	
	mov	r6, r0
	@write the buffer to the file
	mov 	r0, r11		@move filetype into r0
	ldr	r1, =buffer	@load buffer into r1
	mov	r2, r6		@pass in bytes from writeheader to r2
	mov	r7, #sys_write	@move the write command into r7
	svc	#0		@call os to write to file

	mov	r9, #0		@row counter
	cmp	r0, #0		@compare r0 with 0
	bge	2f		@branch if >= 0 to 2f

	mov	r0, #fail_writeheader	@write fail if writeheader failed
	b	9f


2:	
	
	ldr	r4, =ysize
	ldr	r4, [r4]
	mov	r5, #0		@column counter = 0
	mov	r6, #0		@buffer counter = 0
	@length = 0
	cmp	r9, r4
	bge	7f
	

	@for column in range(xsize):
3:
	ldr	r10, =xsize	@load xsize location into r10
	ldr	r10, [r10]	@load xsize from locaion into r10
	@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@	
	cmp	r5, r10
	bge	4f
	
	ldr	r0, =xcenter	@putting xcenter into d0 register
	fldd	d0, [r0]			@	to pass in

	ldr	r0, =ycenter	@putting ycenter into d1 register
	fldd	d1, [r0]			@	to pass in
	
	ldr	r0, =mag	@putting magnification into d2 register
	fldd	d2, [r0]			@	to pass in
	
	ldr	r0, =iters	@put iters into r0
	ldr	r0, [r0]	@load iters from location saved in r0
				@r0 contains maxiters	to pass in
	mov	r1, r5		@move column into r1	to pass in
	mov	r2, r9		@move row into r2 	to pass in
	mov	r3, r10		@move xsize into r3 	to pass in
	sub	sp, sp, #8	@decrement the stack pointer before
	push	{r4, lr}	@push ysize onto stack	to pass in

	@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	bl	calcPixel	@branch to calcPixel(return rgb in r0)
	@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@	

	pop	{r4, lr}
	add	sp, sp, #8	@re-increment after pop
	mov	r1, r0		@move color into r1
	@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	@@@@@@@@@@@@@@@@color = column << 8
	@@@@@mov	r1, r9, lsl #16
	@@@@@add	r1, r1, r5, lsl #8	@add column and row together
	
	@length += writeRGB(buffer+length, color)
	ldr	r0, =buffer	@put buffer address into r0 
	add	r0, r0, r6	@length to buffer to pass to writeRGB
	
	bl	writeRGB	@branch to writergb, byte # in r0
	
	add	r6, r6, r0	@increment buffer size with wrgb's return

	@buffer[length] = ' '
	ldr	r1, =buffer	@load buffer address into r1
	mov	r2, #' '	@move a ' ' into r2
	strb	r2, [r1, r6]	@store ' ' into the buffer
	
	@length += 1
	add	r6, r6, #1	@increment the buffer size
	add	r5, r5, #1	@increment column count	

	cmp	r5, r10		@comparing column and xsize 	
	blt	3b		@if less than, loop back to 3

4:
	ldr	r1, =buffer
	sub	r6, r6, #1	@decrement buffer length
	mov	r2, #'\n'	@put new line into r2
	strb	r2, [r1, r6]	@push r2 into buffer
	add	r6, r6, #1	@increment buffer length	
	
	mov 	r0, r11		@move filetype into r0

	ldr	r1, =buffer
	mov	r2, r6		@pass in bytes from writeheader to r2
	mov	r7, #sys_write	@move the write command into r7
	svc	#0		@call os to write to file
	
	add	r9, r9, #1	@increment row counter
	cmp	r9, r4
	ble	2b		@if less than, loop back to 2

	cmp	r0, #0		@compare r0 with 0
	
	bge	7f		@branch if >= 0 to 7f
	mov	r0, #fail_writerow
	
	b	9f

	

7:	
	mov	r0, r11			@put fd into r0
	mov	r7, #sys_close		@put close file command into r7
	svc	#0			@call os to close file
	cmp	r0, #0			@compare what os returned with 0
	bge	8f			@branch if >= 0 to success

	mov	r0, #fail_close		@report failure in r0
	b	9f			@branch to end of program

8:
	mov	r0, #0			@move success into r0
9:
	
	
	pop	{r4-r11,ip,pc}		@end program

                .bss
buffer:         .space 64*1024

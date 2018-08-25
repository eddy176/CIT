                .global calcPixel

                .text
@ calcPixel(maxiters, col, row) -> rgb
calcPixel:
		@r0= itters
		@r1= column
		@r2= row
		@r3= xsize
		@r4= ysize	
		@r5= minsize
		@d0= xcenter
		@d1= ycenter
		@d2= magnification	,magnification * (minsize - 1)
		@d3= math register
		@d4= 2.0
		@d5= minsize - 1
		@d6=
		@d7=
		@d8=
		@d9= -1
		@d10= x
		@d11= y
		@d12= ysize , ysize/2.0 
		@d13= xsize , xsize/2.0
	
	
	push	{r4-r6, lr}

	ldr	r4, [sp, #16]

	@x = xcenter + (column - xsize/2.0) / ((magnification * minsize - 1))
	cmp	r3, r4			@compare xsize and ysize
	mov	r5, r4			@r5 = ysize (r5 = minsize)
	
	bgt	1f			@branch if xsize < ysize
	mov	r5, r3			@r5 = xsize(minsize)
1:
	@r5 saves lesser size
	sub	r5, r5, #1		@(minsize - 1)
	
	vmov	s9, r5			@vmov r5 into s10
	fsitod	d5, s9			@d5 = double of minsize

	fmuld	d5, d5, d2		@mag(minsize - 1)
	
	vmov	s19, r1			@vmov r1 into s20
	fsitod	d10, s19		@convert int(column) to double d10
	
	vmov	s25, r3			@vmov r3 into s26
	fsitod	d13, s25		@convert int(xsize) to double d13
	fldd	d4, two			@put 2.0 into d4
	fdivd	d13, d13, d4		@divide xsize/2.0 saving it in d13
	fsubd	d10, d10, d13		@subtract column - xsize/2.0 save>d10
	
	
	fdivd	d10, d10, d5		@d10 = x = all dat math
	faddd	d0, d0, d10		@add d0 and d10, save in d0
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	@y = ycenter- (row-ysize/2.0) / (magnification*(minsize-1)
	vmov	s21, r2			@vmov r2 into s3
	fsitod	d11, s21		@convert int(row) to double d11
	
	vmov	s24, r4			@s24 = ysize
	fsitod	d12, s24		@d12 = ysize converted to double
	
	fdivd	d12, d12, d4		@d12 = ysize/2.0
	fsubd	d12, d11, d12		@d12 = row - ysize/2
	fdivd	d12, d12, d5		@d1 = y = all dat math
	fsubd	d1, d1, d12		@d1 = ycenter-(row-ysize/2)
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
2:
@breaking between mandel, getcolor, and remainder@@@@@@@@@@@@@@@@@@@
					@y already in d1 	to pass in
	bl	mandel
	bl	getColor

	pop	{r4-r6, pc}

twofivefive:	.double	255.0
four:		.double	4.0
onetwoeight:	.double 128.0
two:		.double 2.0

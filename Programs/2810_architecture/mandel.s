                .global mandel

                .text

@ mandel(maxiters, x, y) -> iters

		@d0: x
		@d1: y
		@d2: a
		@d3: b
		@d4: a^2
		@d5: b^2
		@d6: a^2 + b^2
		@d7: 4.0
mandel:
		push	{ip, lr}

	@load 4.0 into d7
	fldd d7, four		@load 4.0 into d7
	
@copy maxIterations to r1
	mov	r1, r0		@push maxiters into r1

@set r0 (number of iterations) to 1
	mov	r0, #1		@mov 1 into r0
	
@copy x into a, and y into b
	fcpyd	d2, d0		@copy d0 to d2^
	fcpyd	d3, d1		@copy d3 to d1^
	
@forever:
1:
	@compute a², b², and a² + b²
	fmuld d4, d2, d2	@d2^2 (a^2)
	fmuld d5, d3, d3	@d3^2 (b^2)
	faddd d6, d4, d5	@add d4, d5, save result in d6(a^2 + b^2)

	@if a² + b² ≥ 4.0, return iterations
	fcmpd	d6, d7		@compare d6, d7(a^2 + b^2 and 4.0)
	fmstat			@stores the flag into int register
	bge	3f		@if >= branch to 2f

	@increment iteration count
	add	r0, r0, #1	@increment count

	@if iterations > maxIterations, return 0
	cmp	r0, r1		@compare r0, r1 (count and iters)
	bgt	2f		@branch to 2f if count > iters

	@compute b = 2ab + y (this can be computed in-place,
	@@overwriting the old value of b)
	fmuld	d3, d3, d2	@a * b
	faddd	d3, d3, d3	@ab + ab
	faddd	d3, d3, d1	@2b * a + y

	@compute a = a² - b² + x (this can be computed in-place,
	fsubd	d2, d4, d5	@a^2 - b^2
	faddd	d2, d2, d0	@a + x (a^2 - b^2 + x)
	
	b	1b

	@overwriting the old value of a; note that a² and b² are
        @already computed)
	
2:
	mov	r0, #0		@return 0 if pass

3:
		pop	{ip, pc}

four:	.double 4.0


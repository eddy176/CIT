                .global remainder

                .text
@ remainder(numerator, denominator) -> remainder
remainder:

	push	{ip, lr}
		
	@def remainder(n, d):
	@r0 = numerator
	@r1 = denom
	@if n < d:
	cmp	r0, r1
	@return n
	blt	4f
	
	@shift = (leading 0s of d) - (leading 0s of n)
	clz	r2, r1		@d's leading 0s count
	clz	r3, r0		@n's leading 0s count

	sub	r3, r2, r3	@r3 = shift r2 - r3(#d - #n)
1:
	mov 	r2, r1, lsl r3	@r2 = d shifted left r3*
	@while shift >= 0:
	cmp	r0, r2		@compare shift to numerator >= denom << r3
	bge	2f		@branch if greater than or equal to
	b	3f		@if not, branch to 3f

2:	
	@n = n - d<<shift
	sub	r0, r0, r2	@n -= d left shifted 
3:
	sub	r3, r3, #1	@decriment r3(shift)

	@while >= 0:
	cmp	r3, #0		@comparing r3(shift) with 0
	bge	1b		@back to loop

4:
	@return n
	pop	{ip, pc}

	




@final writing assignment

    @birthday(n) -> p
    @ int n = # of people
    @ int p = probability
    @birthdays(23 people) = (p > 50% chance)
    @birthdays(41 people) = (p > 90% chance)

birthday:

        @ r0 = n
        @ r1 = i              #birthdays
        @ r2 = days in year
        @ r3 = days in year - #birthdays
        @ d0 = one
        @ d1 = hundred
        @ d2 = double days in year
        @ d3 = p * float(unusedDays) / 365.0
    push {ip, lr}
@   def birthday(n):
    
@       p = 1.0
    mov r1, #0
    mov r2, #365
    flddd   d0, =one
    flddd   d1, =hundred
    flddd   d2, =year
1:
@       for i in range(n):
@           unusedDays = 365 - i
    sub     r3, r2, r1
    vmov    s6, r3
    fsitod  d3, r3      @d3 = 365 - i
    fdivd   d3, d3, d2  @d3 = (365 - i)/365.0
@           p = p * (float(unusedDays) / 365.0)
    fmuld   d3, d3, d1  @d3 = 100*((365 - 1)/365.0)
    
    ftosid  s8, d3
    vmov    ip, s8

    add r1, r1, #1
    @ p <= n
    cmp     ip, r0
    bge     1b
@       chanceOfCollision = (1.0 - p) * 100.0
@       return int(round(chanceOfCollision))

    mov r0, ip
    pop {ip, pc}

one:        .double 1.0
hundred:    .double 100.0
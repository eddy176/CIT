print ("""Welcome to the rainwater tank calculator.
We\'ll ask you for a few parameters about your
rainfall and rain catchment area. Then, we\'ll
tell you how big to make your tank. We assume
that your catchment area is rectangular.""")
print("")

print ("How many inches of rain fall in a large storm?")
RainFall = input("Rain in inches:   ")
print ("How wide is your catchment area, in feet?")
CatchWidth = input("Width in feet:  ")
print ("How long is your catchment area, in feet?")
CatchLength = input("Length in feet:  ")
print("")
total = (float(RainFall)/12) * float(CatchWidth) * float(CatchLength) * 7.48
print ("You need a tank with "+ str(total) + """ gallons capacity
to capture that much rain at one time.""")

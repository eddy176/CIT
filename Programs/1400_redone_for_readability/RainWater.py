# Rain Water
# Kacy Stocks
# Updated 5/15/2019 for readability, left as a script for a purpose
print ("""
Welcome to the rainwater tank calculator.
We'll ask you for a few parameters about your
rainfall and rain catchment area. Then, we\'ll
tell you how big to make your tank. We assume
that your catchment area is rectangular.
""")
RainFall = float(input("Rainfal in inches: "))
CatchWidth = float(input("How wide is your catchment area, in feet?:  "))
CatchLength = float(input("How long is your catchment area, in feet?: "))
total = RainFall / 12 * CatchWidth * CatchLength * 7.48
print ("You need a tank with", total, "gallons capacity to capture that much rain at one time.")
print("Thank you for using Rain Water Calculator")
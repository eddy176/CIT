print ("""Welcome to the highway travel advisor.
This application has been configured to work
with travel on I-15 within the state of Utah.
We'll ask for a few pieces of info, then
give you advice on your travel.""")
print ("")

print ("What mile marker are you starting at?")
start = float(input())
print ("What mile marker are you exiting at?")
end = float(input())
print ("In how many hours do you want to arrive at your appointment?")
arrivetime = float(input())
print ("What is your expected average travel speed in mph?")
avgspeed = float(input())
print ("")
traveltime = abs((end - start) / avgspeed)
xtratime = abs(arrivetime - traveltime)

if avgspeed > 80:
    print ("You are going too fast, slow down!")
elif avgspeed < 60:
    print ("You are going too slow granny, speed up or you will cause an accident!")
elif traveltime > arrivetime:
    print ("You will need to leave earlier, you will be " + str(xtratime) + " hours late!")
else:
    print ("You will travel " + str(traveltime) + " miles. You have " + str(xtratime) + " hours before you have to leave.")

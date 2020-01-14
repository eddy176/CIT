print("Hey Dipper, I'll calculate the temperature for you.")
print("Using your stopwatch, count how many times")
print("the cricket chirps in 13 seconds.")
print("")

print("How many chirps did you count?")
chirps = int(input())

answer = int(chirps + 40)

if answer>54:
    print("By my calculations it is about " + str(answer) + " degrees.")
    

else:
    print("It's too cold for crickets")



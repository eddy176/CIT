class CaloricBalance:

    def __init__(self, gender, age, height, weight):
        self.mgetWeight = weight
        self.mgetBalance = -1 * self.getBMR(gender, age, height, weight)
        return
    
    def getBMR(self, gender, age, height, weight):
        if gender == 'm':
            BMR = 66 + 12.7 * float(height) + 6.23 * float(weight) - 6.8 * float(age)
        elif gender == 'f':
            BMR = 655 + 4.7 * float(height) + 4.35 * float(weight) - 4.7 * float(age)
        else:
            BMR = 0.0
        return BMR

    def getBalance(self):
        balance = self.mgetBalance
        return balance

    def recordActivity(self, caloric_burn_per_pound_per_minute, minutes):
        minutes = float(minutes)
        kcals = caloric_burn_per_pound_per_minute * self.mgetWeight
        tcals = kcals * minutes
        self.mgetBalance = self.mgetBalance - tcals
        return self.mgetBalance

    def eatFood(self, calories):
        self.mgetBalance += calories
        return

#Thomas Gilman
#ETEC 2110
#51
#Assignment 2.2
import time
startT = time.time()

RangeOfNums=100000000 #MY VARIABLES
Average=0
Sum=0

for i in range(RangeOfNums): #adds up the sum of all RangeOfNums
    Sum+=i

Average = Sum/RangeOfNums #get Average

print("The Range of Numbers is: "+str(RangeOfNums))
print("The Sum is: "+str(Sum))
print("The Average is: "+str(Average))
print("The time it took to run this program is: "+str(time.time()-startT)) #get the time it took
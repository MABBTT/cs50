from cs50 import get_int

#Get credit card number
n = get_int("Number: ")

#Convert credit card number to list of integers
ccardints = [int(i) for i in str(n)]
#Count total digits
totaldigits = len(ccardints)
#print(f"{totaldigits}")
#Get first digit
d1 = ccardints[0]
#Get first two digits
d2 = int(str(n)[:2])
#Luhn's Algo
md = ccardints[-2::-2]
#print(f"'{md}")
md2 = [i * 2 for i in md]
#print(f"'{md2}")
md3 = "".join([str(i) for i in md2])
md4 = [int(i) for i in str(md3)]
#print(f"{md4}")
summd = sum(md4)
#print(f"{summd}")
nmd = ccardints[-1::-2]
#print(f"'{nmd}")
sumnmd = sum(nmd)
#print(f"{sumnmd}")
luhntotal = sumnmd + summd
#print(f"{luhntotal}")
ltp = luhntotal % 10
#print(f"{ltp}")
#Luhn's validation and print card type
if luhntotal % 10 == 0:
    if d1 == 4 and (totaldigits == 13 or totaldigits == 16):
        print("VISA")
    elif (d2 == 34 or d2 ==37) and totaldigits == 15:
        print("AMEX")
    elif (d2 >= 51 and d2 <=55) and totaldigits ==16:
        print("MASTERCARD")
    else:
        print("INVALID")
else:
    print("INVALID")

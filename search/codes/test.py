import random

a = set()

for i in range(0,100):
    a.add(random.randint(0,10000))

print('{')
for i in a:
    print(i,", ",sep="",end="")
print('}')
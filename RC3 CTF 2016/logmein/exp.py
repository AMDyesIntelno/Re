a=":\"AL_RT^L*.?+6/46"
b="harambe"
for i in range(len(a)):
    print(chr(ord(b[i%7])^ord(a[i])),end="")
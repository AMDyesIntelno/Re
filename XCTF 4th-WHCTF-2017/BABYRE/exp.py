fmcd=[102, 109, 99, 100, 127, 107, 55, 100, 59, 86, 96, 59, 110, 112]
for i in range(len(fmcd)):
    print(chr(fmcd[i]^i),end="")
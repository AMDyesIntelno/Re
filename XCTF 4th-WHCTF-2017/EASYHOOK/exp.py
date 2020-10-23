byte_40A030=[97, 106, 121, 103, 107, 70, 109, 46, 127, 95, 126, 45, 83, 86, 123, 56, 109, 76, 110, 0]
flag=[0 for i in range(19)]
flag[18]=byte_40A030[18]^0x13
for i in range(18):
    v3=byte_40A030[i]^i
    if i%2:
        flag[i]=v3+i
    else:
        flag[i+2]=v3
for i in flag:
    print(chr(i),end="")
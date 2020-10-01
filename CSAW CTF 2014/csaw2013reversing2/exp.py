v2=0xBBAACCDD
a2=[0xBBCCA0BC,0xDCD1BEB8,0xCDCFBEAE,0xD2C4AB82,0xD2D993B3,0xD4DE93A9,0xD3CBB882,0xD3CBBEB9,0x9AD7CCDD]
flag=""
for i in range(9):
    flag+=format((a2[i]^v2),"x")
print(flag)
print(bytearray.fromhex(flag).decode())
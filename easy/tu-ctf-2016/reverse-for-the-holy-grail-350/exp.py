firstchar=[65, 105, 110, 69, 111, 97, 0, 0]
thirdchar=[751, 708, 732, 711, 734, 764, 0, 0]
v7=[666, 667, 669, 673, 676, 677, 679, 683, 686, 687, 689, 693, 696, 697, 699, 703, 706, 707, 709, 713, 716, 717, 719, 723]
masterarray=[471, 12, 580, 606, 147, 108]
password=[0 for i in range(24)]

for i in range(6):
    password[i*3]=firstchar[i]
    password[i*3+2]=thirdchar[i]^v7[i*3+2]
    for j in range(1,128):
        if ((password[i*3]^v7[i*3])*(j^v7[i*3+1]))%(password[i*3+2]^v7[i*3+2])==masterarray[i]:
            password[i*3+1]=j
            break
print(password)
print("tuctf{",end="")
for i in password:
    print(chr(i),end="")
print("}")
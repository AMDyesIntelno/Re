data=[81, 124, 106, 123, 103, 82, 253, 22, 164, 137, 189, 146, 128, 19, 65, 84, 160, 141, 69, 24, 129, 222, 252, 149, 240, 22, 121, 26, 21, 91, 117, 31]
for i in range(5,32):
        if i%2==0:
            for j in range(256):
                v5=(j>>6)|(j<<2)
                v5=v5&0xff
                if v5==data[i]:
                    data[i]=j
                    break
        else:
            for j in range(256):
                v5=(j>>2)|(j<<6)
                v5=v5&0xff
                if v5==data[i]:
                    data[i]=j
                    break
print(data)
for i in range(32):
    print(chr(data[i]^(32-i)),end="")
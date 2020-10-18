import hashlib
a=[2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113]
b="CreateByTenshine"
flag=""
for i in b:
    ch=i
    for j in range(1,15):
        ch=chr(ord(ch)^a[j])
    flag+=ch
flag=hashlib.md5(flag.encode("utf-8"))
print("flag{"+flag.hexdigest().upper()+"}")#提交的flag要大写....
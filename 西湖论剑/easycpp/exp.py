def fib(a):
    if a==0 or a==1:
        return 1
    return fib(a-1)+fib(a-2)
flag=[]
for i in range(16):
    flag.append(fib(i))
flag=flag[::-1]
for i in range(1,16):
    flag[i]-=flag[0]
for i in range(16):
    print(flag[i],end=" ")
print()
print()
print("flag{",end="")
for i in range(16):
    if flag[i]%2:
        print(flag[i],end="")
print("}")
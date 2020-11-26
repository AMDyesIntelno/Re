from pwn import *
import time
payload="TWCTF{1234567890-=!@#$%^&*()_+qwertyuiop[]\\asdfghjkl;'zxcvbnm,./QWERTYUIOP{}|ASDFGHJKL:\"ZXCVBNM<>?}"
target="95eeaf95ef"
a=[]
while a[0:10]!=target:
    p = process(argv=["/home/misaka/Downloads/reverse_box", payload])
    a=bytes.decode(p.recvline(keepends=False))
    p.recvall()
    time.sleep(1)
print(a)
print(a[0:10])
#95eeaf95ef94729676ad23b02fb2a7b16d9248bc93838aed425081107a441640f8f52703284c1de48cf9ff5a3af68630f0b7cae557796f094e8d1f2a89c484a064eedbb5957e498e31e6944aa53658aeef15e763069c35260bdfaf04999a565e07c04a
#95eeaf95ef
题目提示

>$ ./reverse_box ${FLAG}
>95eeaf95ef94234999582f722f492f72b19a7aaf72e6e776b57aee722fe77ab5ad9aaeb156729676ae7a236d99b1df4a

main函数

```cpp
int __cdecl main(int a1, char **a2)
{
  size_t i; // [esp+18h] [ebp-10Ch]
  int v4; // [esp+1Ch] [ebp-108h]
  unsigned int v5; // [esp+11Ch] [ebp-8h]

  v5 = __readgsdword(0x14u);
  if ( a1 <= 1 )
  {
    printf("usage: %s flag\n", *a2);
    exit(1);
  }
  sub_804858D(&v4);
  for ( i = 0; i < strlen(a2[1]); ++i )
    printf("%02x", *(&v4 + a2[1][i]));
  putchar('\n');
  return 0;
}
```

sub_804858D函数

```cpp
int __cdecl sub_804858D(_BYTE *a1)
{
  unsigned int v1; // eax
  int v2; // edx
  char v3; // al
  char v4; // ST1B_1
  char v5; // al
  int result; // eax
  unsigned __int8 v7; // [esp+1Ah] [ebp-Eh]
  char v8; // [esp+1Bh] [ebp-Dh]
  char v9; // [esp+1Bh] [ebp-Dh]
  int v10; // [esp+1Ch] [ebp-Ch]

  v1 = time(0);
  srand(v1);
  do
    v10 = rand();                               // &0xff
  while ( !v10 );
  *a1 = v10;
  v7 = 1;
  v8 = 1;
  do
  {
    v2 = v7 ^ 2 * v7;                           // v7^(v7<<1)
    if ( (v7 & 0x80u) == 0 )
      v3 = 0;
    else
      v3 = 0x1B;
    v7 = v2 ^ v3;
    v4 = 4 * (2 * v8 ^ v8) ^ 2 * v8 ^ v8;
    v9 = 16 * v4 ^ v4;
    if ( v9 >= 0 )
      v5 = 0;
    else
      v5 = 9;
    v8 = v9 ^ v5;
    result = __ROR1__(v8, 4) ^ __ROR1__(v8, 5) ^ __ROR1__(v8, 6) ^ __ROR1__(v8, 7) ^ (v8 ^ *a1);
    a1[v7] = result;
  }
  while ( v7 != 1 );
  return result;
}
```

sub_804858D函数根据一个在`0`到`0xff`之间的随机数,生成了一个长度为256的随机数组,根据题目提示输入flag得到的结果进行反推,进而得到flag,flag的头部为`TWCTF`,由此进行爆破

# pwntools解法

```python
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
```

得到字符串中每个字符对应的hex为`95eeaf95ef94729676ad23b02fb2a7b16d9248bc93838aed425081107a441640f8f52703284c1de48cf9ff5a3af68630f0b7cae557796f094e8d1f2a89c484a064eedbb5957e498e31e6944aa53658aeef15e763069c35260bdfaf04999a565e07c04a`

根据hex构建字典进行推导

```python
a="95eeaf95ef94729676ad23b02fb2a7b16d9248bc93838aed425081107a441640f8f52703284c1de48cf9ff5a3af68630f0b7cae557796f094e8d1f2a89c484a064eedbb5957e498e31e6944aa53658aeef15e763069c35260bdfaf04999a565e07c04a"
b="TWCTF{1234567890-=!@#$%^&*()_+qwertyuiop[]\\asdfghjkl;'zxcvbnm,./QWERTYUIOP{}|ASDFGHJKL:\"ZXCVBNM<>?}"
flag_hex="95eeaf95ef94234999582f722f492f72b19a7aaf72e6e776b57aee722fe77ab5ad9aaeb156729676ae7a236d99b1df4a"
list_a=[]
list_flag=[]
for i in range(0,len(a),2):
    list_a.append("0x"+a[i]+a[i+1])
for i in range(0,len(flag_hex),2):
    list_flag.append("0x"+flag_hex[i]+flag_hex[i+1])
print(list_flag)
for i in range(len(b)):
    print("\"",list_a[i],"\"",":","\"",b[i],"\"",sep="",end=",")
#"0x95":"T","0xee":"W","0xaf":"C","0x95":"T","0xef":"F","0x94":"{","0x72":"1","0x96":"2","0x76":"3","0xad":"4","0x23":"5","0xb0":"6","0x2f":"7","0xb2":"8","0xa7":"9","0xb1":"0","0x6d":"-","0x92":"=","0x48":"!","0xbc":"@","0x93":"#","0x83":"$","0x8a":"%","0xed":"^","0x42":"&","0x50":"*","0x81":"(","0x10":")","0x7a":"_","0x44":"+","0x16":"q","0x40":"w","0xf8":"e","0xf5":"r","0x27":"t","0x03":"y","0x28":"u","0x4c":"i","0x1d":"o","0xe4":"p","0x8c":"[","0xf9":"]","0xff":"\","0x5a":"a","0x3a":"s","0xf6":"d","0x86":"f","0x30":"g","0xf0":"h","0xb7":"j","0xca":"k","0xe5":"l","0x57":";","0x79":"'","0x6f":"z","0x09":"x","0x4e":"c","0x8d":"v","0x1f":"b","0x2a":"n","0x89":"m","0xc4":",","0x84":".","0xa0":"/","0x64":"Q","0xee":"W","0xdb":"E","0xb5":"R","0x95":"T","0x7e":"Y","0x49":"U","0x8e":"I","0x31":"O","0xe6":"P","0x94":"{","0x4a":"}","0xa5":"|","0x36":"A","0x58":"S","0xae":"D","0xef":"F","0x15":"G","0xe7":"H","0x63":"J","0x06":"K","0x9c":"L","0x35":":","0x26":""","0x0b":"Z","0xdf":"X","0xaf":"C","0x04":"V","0x99":"B","0x9a":"N","0x56":"M","0x5e":"<","0x07":">","0xc0":"?","0x4a":"}"
print()
dic={"0x95":"T","0xee":"W","0xaf":"C","0x95":"T","0xef":"F","0x94":"{","0x72":"1","0x96":"2","0x76":"3","0xad":"4","0x23":"5","0xb0":"6","0x2f":"7","0xb2":"8","0xa7":"9","0xb1":"0","0x6d":"-","0x92":"=","0x48":"!","0xbc":"@","0x93":"#","0x83":"$","0x8a":"%","0xed":"^","0x42":"&","0x50":"*","0x81":"(","0x10":")","0x7a":"_","0x44":"+","0x16":"q","0x40":"w","0xf8":"e","0xf5":"r","0x27":"t","0x03":"y","0x28":"u","0x4c":"i","0x1d":"o","0xe4":"p","0x8c":"[","0xf9":"]","0xff":"\\","0x5a":"a","0x3a":"s","0xf6":"d","0x86":"f","0x30":"g","0xf0":"h","0xb7":"j","0xca":"k","0xe5":"l","0x57":";","0x79":"'","0x6f":"z","0x09":"x","0x4e":"c","0x8d":"v","0x1f":"b","0x2a":"n","0x89":"m","0xc4":",","0x84":".","0xa0":"/","0x64":"Q","0xee":"W","0xdb":"E","0xb5":"R","0x95":"T","0x7e":"Y","0x49":"U","0x8e":"I","0x31":"O","0xe6":"P","0x94":"{","0x4a":"}","0xa5":"|","0x36":"A","0x58":"S","0xae":"D","0xef":"F","0x15":"G","0xe7":"H","0x63":"J","0x06":"K","0x9c":"L","0x35":":","0x26":"\"","0x0b":"Z","0xdf":"X","0xaf":"C","0x04":"V","0x99":"B","0x9a":"N","0x56":"M","0x5e":"<","0x07":">","0xc0":"?","0x4a":"}"}
print(len(list_flag))
for i in list_flag:
    print(dic[i],end="")
```

得到flag`TWCTF{5UBS717U710N_C1PH3R_W17H_R4ND0M123D_5-B0X}`


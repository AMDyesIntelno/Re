main函数

```cpp
__int64 __fastcall maybe_main(__int64 a1, __int64 a2)
{
  __int64 v2; // rdx
  __int64 v3; // rcx
  __int64 v4; // r8
  __int64 v5; // r9
  int rand; // eax
  char password[136]; // [rsp+10h] [rbp-B0h]
  int v9; // [rsp+98h] [rbp-28h]
  char v10; // [rsp+9Fh] [rbp-21h]
  int v11; // [rsp+A0h] [rbp-20h]
  unsigned __int8 v12; // [rsp+A6h] [rbp-1Ah]
  char v13; // [rsp+A7h] [rbp-19h]
  int v14; // [rsp+A8h] [rbp-18h]
  int v15; // [rsp+ACh] [rbp-14h]
  unsigned int v16; // [rsp+B0h] [rbp-10h]
  int v17; // [rsp+B4h] [rbp-Ch]
  _BOOL4 v18; // [rsp+B8h] [rbp-8h]
  int i; // [rsp+BCh] [rbp-4h]

  maybe_print("Give me the password: ", a2);
  sub_4075A0("%s", password);
  for ( i = 0; password[i]; ++i )
    ;
  v18 = i == 22;                                // 长度22
  v17 = 10;
  do
  {
    rand = sub_406D90("%s", password, v2, v3, v4, v5);
    v3 = (rand % 22);
    v14 = rand % 22;
    v16 = 0;
    v13 = byte_6B4270[rand % 22];
    v12 = password[rand % 22];
    v11 = rand % 22 + 1;
    v15 = 0;
    while ( v15 < v11 )
    {
      ++v15;
      v16 = 0x6D01788D * v16 + 0x3039;
    }
    v2 = v16;
    v10 = v16 ^ v12;
    if ( v13 != (v16 ^ v12) )
      v18 = 0;
    --v17;
  }
  while ( v17 );
  if ( v18 )
    v9 = maybe_print("Congras\n");
  else
    v9 = maybe_print("Oh no!\n");
  return 0LL;
}
```

根据

```cpp
for ( i = 0; password[i]; ++i )
    ;
  v18 = i == 22;                                // 长度22
```

推测`password`的长度为22

在`do...while`循环中,`sub_406D90`是一个较为复杂的函数,猜测是用来生成随机数

循环中的关键代码为

```cpp
v13 = byte_6B4270[rand % 22];
v12 = password[rand % 22];
v11 = rand % 22 + 1;
v15 = 0;
while ( v15 < v11 )
{
  ++v15;
  v16 = 0x6D01788D * v16 + 0x3039;
}
```

`rand%22`说明处理范围在`[0,21]`之间,而

```cpp
v13 = byte_6B4270[rand % 22];
v12 = password[rand % 22];
```

说明两者存在一一对应的关系,由此可以得到exp

```cpp
#include<iostream>
#include<cstdint>
using namespace std;
int main(){
    int byte_6B4270[]={95, 242, 94, 139, 78, 14, 163, 170, 199, 147, 129, 61, 95, 116, 163, 9, 145, 43, 73, 40, 147, 103, 0, 0};
    for(int i=0;i<22;++i){
        int v13=byte_6B4270[i];
        int v16=0;
        int v15=0;
        for(int j=0;j<=i;++j){
            v16 = 0x6D01788D * v16 + 0x3039;
        }
        cout<<char(v16^v13);
    }
    return 0;
}
```

`flag{d826e6926098ef46}`
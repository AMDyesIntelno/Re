# 一道迷宫题

汇编代码

```cpp
__int64 __fastcall main(__int64 a1, char **a2, char **a3)
{
  signed __int64 v3; // rbx
  signed int v4; // eax
  bool v5; // bp
  bool v6; // al
  const char *v7; // rdi
  __int64 v9; // [rsp+0h] [rbp-28h]

  v9 = 0LL;
  puts("Input flag:");
  scanf("%s", &input, 0LL);
  if ( strlen(&input) != 24 || strncmp(&input, "nctf{", 5uLL) || *(&byte_6010BF + 24) != '}' )// 输入长度为24,格式为nctf{xxx}
  {
LABEL_22:
    puts("Wrong flag!");
    exit(-1);
  }
  v3 = 5LL;
  if ( strlen(&input) - 1 > 5 )
  {
    while ( 1 )
    {
      v4 = *(&input + v3);                      // 先取第五位
      v5 = 0;
      if ( v4 > 'N' )
      {
        v4 = (unsigned __int8)v4;
        if ( (unsigned __int8)v4 == 'O' )
        {
          v6 = Left((_DWORD *)&v9 + 1);         // v7=((&v9+1)的ascii>0),即越界判断,同时(&v9+1)的ascii-1
                                                // 向左
          goto LABEL_14;
        }
        if ( v4 == 'o' )
        {
          v6 = Right((int *)&v9 + 1);           // v7=(((&v9+1)的ascii+1)<8),同时(&v9+1)的ascii+1
                                                // 向右
          goto LABEL_14;
        }
      }
      else
      {
        v4 = (unsigned __int8)v4;
        if ( (unsigned __int8)v4 == '.' )
        {
          v6 = Up(&v9);                         // v6=(v9>0)(减一之前),v9的值-1
                                                // 向上
          goto LABEL_14;
        }
        if ( v4 == '0' )
        {
          v6 = Down((int *)&v9);                // v6=(v9+1)<8,v9的值+1
                                                // 向下
LABEL_14:
          v5 = v6;
          goto LABEL_15;
        }
      }
LABEL_15:
      if ( !(unsigned __int8)Check((__int64)maze, SHIDWORD(v9), v9) )// asc='  *******   *  **** * ****  * ***  *#  *** *** ***     *********'
        goto LABEL_22;
      if ( ++v3 >= strlen(&input) - 1 )
      {
        if ( v5 )
          break;
LABEL_20:
        v7 = "Wrong flag!";
        goto LABEL_21;
      }
    }
  }
  if ( maze[8 * (signed int)v9 + SHIDWORD(v9)] != '#' )// 说明v9的低位是行移动即上下移动,v9的高位是列移动即左右移动
    goto LABEL_20;
  v7 = "Congratulations!";
LABEL_21:
  puts(v7);
  return 0LL;
}
```

1. 将迷宫提取

```py
import numpy as np
asc='  *******   *  **** * ****  * ***  *#  *** *** ***     *********'
asc=list(asc)
asc=np.array(asc).reshape(8,8)
print(asc)
'''
[[' ' ' ' '*' '*' '*' '*' '*' '*']
 ['*' ' ' ' ' ' ' '*' ' ' ' ' '*']
 ['*' '*' '*' ' ' '*' ' ' '*' '*']
 ['*' '*' ' ' ' ' '*' ' ' '*' '*']
 ['*' ' ' ' ' '*' '#' ' ' ' ' '*']
 ['*' '*' ' ' '*' '*' '*' ' ' '*']
 ['*' '*' ' ' ' ' ' ' ' ' ' ' '*']
 ['*' '*' '*' '*' '*' '*' '*' '*']]

00111111
10001001
11101011
11001011
1001#001
11011101
11000001
11111111
'''
```

2. 确定移动方向所代表的函数以及所使用的代表字符

```cpp
if ( maze[8 * (signed int)v9 + SHIDWORD(v9)] != '#' )// 说明v9的低位是行移动即上下移动,v9的高位是列移动即左右移动
```

而根据移动函数的边界判断可以确认该函数的移动方向,由此可以确认函数和函数所使用的字符

3. 走迷宫

```py
dic={"上":".","下":"0","左":"O","右":"o"}
answer="右下右右下下左下下下右右右右上上左左"
for i in answer:
  print(dic[i],end="")
```

`flag:nctf{o0oo00O000oooo..OO}`
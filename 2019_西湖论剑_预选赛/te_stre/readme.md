main函数

```cpp
__int64 __fastcall main(__int64 a1, char **a2, char **a3)
{
  void *ptr; // ST10_8
  __int64 v5; // [rsp+18h] [rbp-28h]
  char input; // [rsp+20h] [rbp-20h]
  int v7; // [rsp+3Ch] [rbp-4h]

  v7 = 0;
  v5 = 256LL;
  sub_400D00(&input, 17uLL);
  ptr = malloc(256uLL);
  sub_400700(ptr, &v5, &input, 16uLL);
  free(ptr);
  return 0LL;
}
```

sub_400D00函数(读入函数)

```cpp
__int64 __fastcall sub_400D00(__int64 a1, unsigned __int64 a2)
{
  char buf; // [rsp+17h] [rbp-19h]
  unsigned __int64 i; // [rsp+18h] [rbp-18h]
  unsigned __int64 v5; // [rsp+20h] [rbp-10h]
  __int64 v6; // [rsp+28h] [rbp-8h]

  v6 = a1;
  v5 = a2;
  for ( i = 0LL; i < v5; ++i )                  // 长度为17
  {
    read(0, &buf, 1uLL);
    *(v6 + i) = buf;
  }
  *(v6 + v5 - 1) = 0;
  fflush(stdout);
  return i;
}
```

输入长度为17,最后一位被去除,实际有效长度为16位

sub_400700函数(处理函数)

```cpp
// a2=256,a4=16
__int64 __fastcall sub_400700(void *a1, _QWORD *a2, __int64 a3, size_t a4)
{
  unsigned __int8 *v4; // rcx
  __int64 v6; // [rsp+0h] [rbp-C0h]
  int c; // [rsp+8h] [rbp-B8h]
  char v8; // [rsp+Fh] [rbp-B1h]
  int v9; // [rsp+10h] [rbp-B0h]
  bool v10; // [rsp+17h] [rbp-A9h]
  unsigned __int8 *v11; // [rsp+18h] [rbp-A8h]
  char v12; // [rsp+27h] [rbp-99h]
  int v13; // [rsp+28h] [rbp-98h]
  int v14; // [rsp+2Ch] [rbp-94h]
  unsigned __int64 i; // [rsp+30h] [rbp-90h]
  size_t n_num_23; // [rsp+38h] [rbp-88h]
  size_t v17; // [rsp+40h] [rbp-80h]
  size_t v18; // [rsp+48h] [rbp-78h]
  size_t j; // [rsp+50h] [rbp-70h]
  size_t v20; // [rsp+58h] [rbp-68h]
  int per_ch; // [rsp+64h] [rbp-5Ch]
  unsigned __int64 temp; // [rsp+68h] [rbp-58h]
  int v23_num_20; // [rsp+74h] [rbp-4Ch]
  __int64 *v24; // [rsp+78h] [rbp-48h]
  __int64 input; // [rsp+80h] [rbp-40h]
  void *v26; // [rsp+88h] [rbp-38h]
  int v27; // [rsp+94h] [rbp-2Ch]
  unsigned __int64 len_16; // [rsp+98h] [rbp-28h]
  __int64 v29; // [rsp+A0h] [rbp-20h]
  _QWORD *v30; // [rsp+A8h] [rbp-18h]
  void *result; // [rsp+B0h] [rbp-10h]
  char v32; // [rsp+BFh] [rbp-1h]

  result = a1;
  v30 = a2;
  v29 = a3;
  len_16 = a4;
  v27 = 0xDEADBEEF;
  v26 = malloc(0x100uLL);
  input = v29;
  v24 = &v6;
  temp = 0LL;
  v17 = 0LL;
  for ( i = 0LL; i < len_16; ++i )              // junk code
  {
    v13 = *(input + i);
    *(v26 + i) = byte_400E90[i % 29] ^ v13;
    *(v26 + i) += *(input + i);
  }
  while ( 1 )                                   // check0
  {
    v12 = 0;
    if ( v17 < len_16 )
      v12 = ~(*(input + v17) != 0);
    if ( !(v12 & 1) )                           // v12是偶数
      break;
    ++v17;
  }
  n_num_23 = ((0x28F5C28F5C28F5C3LL * (138 * (len_16 - v17) >> 2) >> 64) >> 2) + 1;// 23
  v23_num_20 = ((0xAAAAAAAAAAAAAAABLL * ((v17 + len_16) << 6) >> 64) >> 5) - 1;// 20
  v11 = &v6 - ((((0x28F5C28F5C28F5C3LL * (138 * (len_16 - v17) >> 2) >> 64) >> 2) + 16) & 0xFFFFFFFFFFFFFFF0LL);
  memset(v11, 0, n_num_23);
  v20 = v17;
  v18 = n_num_23 - 1;
  while ( v20 < len_16 )
  {
    per_ch = *(input + v20);
    for ( j = n_num_23 - 1; ; --j )
    {
      v10 = 1;
      if ( j <= v18 )
        v10 = per_ch != 0;
      if ( !v10 )
        break;
      temp = v11[j] << 6;
      per_ch += v11[j] << 8;                    // per_ch=per_ch+v11[j]*256
      v9 = 64;
      v11[j] = per_ch % 58;                     // base58???
      *(v26 + j) = temp & 0x3F;
      temp >>= 6;
      per_ch /= 58;
      v27 /= v9;
      if ( !j )
        break;
    }
    ++v20;
    v18 = j;
  }
  for ( j = 0LL; ; ++j )                        // check0
  {
    v8 = 0;
    if ( j < n_num_23 )
      v8 = ~(v11[j] != 0);
    if ( !(v8 & 1) )
      break;
  }
  if ( *v30 > n_num_23 + v17 - j )
  {
    if ( v17 )
    {
      c = 61;
      memset(result, 49, v17);
      memset(v26, c, v17);
    }
    v20 = v17;
    while ( j < n_num_23 )
    {
      v4 = v11;
      *(result + v20) = byte_400EB0[v11[j]];
      *(v26 + v20++) = byte_400EF0[v4[j++]];
    }
    *(result + v20) = 0;
    *v30 = v20 + 1;
    if ( !strncmp(result, "D9", 2uLL)
      && !strncmp(result + 20, "Mp", 2uLL)
      && !strncmp(result + 18, "MR", 2uLL)
      && !strncmp(result + 2, "cS9N", 4uLL)
      && !strncmp(result + 6, "9iHjM", 5uLL)
      && !strncmp(result + 11, "LTdA8YS", 7uLL) )// D9cS9N9iHjMLTdA8YSMRMp
                                                // 可以对v11进行推导
    {
      HIDWORD(v6) = puts("correct!");
    }
    v32 = 1;
    v14 = 1;
  }
  else
  {
    *v30 = n_num_23 + v17 - j + 1;
    v32 = 0;
    v14 = 1;
  }
  return v32 & 1;
}
```

从结果往前推导,便于提出混淆函数与变量

目标结果为`D9cS9N9iHjMLTdA8YSMRMp`,而`result`与`v11`有关

```cpp
while ( v20 < len_16 )
  {
    per_ch = *(input + v20);
    for ( j = n_num_23 - 1; ; --j )
    {
      v10 = 1;
      if ( j <= v18 )
        v10 = per_ch != 0;
      if ( !v10 )
        break;
      temp = v11[j] << 6;
      per_ch += v11[j] << 8;                    // per_ch=per_ch+v11[j]*256
      v9 = 64;
      v11[j] = per_ch % 58;                     // base58???
      *(v26 + j) = temp & 0x3F;
      temp >>= 6;
      per_ch /= 58;
      v27 /= v9;
      if ( !j )
        break;
    }
    ++v20;
    v18 = j;
  }
```

```cpp
per_ch += v11[j] << 8;                    // per_ch=per_ch+v11[j]*256
v11[j] = per_ch % 58;                     // base58???
per_ch /= 58;
```

可以推断为`base58`

根据密文`D9cS9N9iHjMLTdA8YSMRMp`进行解密,得到flag`base58_is_boring`

```py
import base58
print(base58.b58decode(b"D9cS9N9iHjMLTdA8YSMRMp"))
```
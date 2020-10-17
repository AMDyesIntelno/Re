main函数

```cpp
int __cdecl main(int argc, const char **argv, const char **envp)
{
  unsigned int v3; // edx
  unsigned int v4; // ecx
  __m128i v5; // xmm1
  unsigned int v6; // esi
  const __m128i *v7; // eax
  __m128i v8; // xmm0
  int v9; // eax
  char input; // [esp+0h] [ebp-CCh]
  char v12; // [esp+1h] [ebp-CBh]
  char v13; // [esp+64h] [ebp-68h]
  char v14; // [esp+65h] [ebp-67h]
  unsigned int v15; // [esp+C8h] [ebp-4h]

  printf("please input your flah:");
  input = 0;
  memset(&v12, 0, 0x63u);
  scanf("%s", &input);
  v13 = 0;
  memset(&v14, 0, 0x63u);
  sub_491000(&v15, &v13, &input, strlen(&input));
  v3 = v15;
  v4 = 0;
  if ( v15 )
  {
    if ( v15 >= 16 )
    {
      v5 = _mm_load_si128(&xmmword_4A4F20);
      v6 = v15 - (v15 & 0xF);
      v7 = &v13;
      do
      {
        v8 = _mm_loadu_si128(v7);
        v4 += 16;
        ++v7;
        _mm_storeu_si128(&v7[-1], _mm_xor_si128(v8, v5));
      }
      while ( v4 < v6 );
    }
    for ( ; v4 < v3; ++v4 )
      *(&v13 + v4) ^= 37u;
  }
  v9 = strcmp(&v13, "you_know_how_to_remove_junk_code");
  if ( v9 )
    v9 = -(v9 < 0) | 1;
  if ( v9 )
    printf("wrong\n");
  else
    printf("correct\n");
  system("pause");
  return 0;
}
```

提示`you_know_how_to_remove_junk_code`,说明存在垃圾代码

sub_491000函数

```cpp
// a2=0
signed int __usercall sub_491000@<eax>(unsigned int *a1@<edx>, _BYTE *a2@<ecx>, unsigned __int8 *input, unsigned int input_len)
{
  int v4; // ebx
  unsigned int _input_len; // eax
  int v6; // ecx
  unsigned __int8 *v7; // edi
  int v8; // edx
  bool v9; // zf
  unsigned __int8 v10; // cl
  unsigned __int8 v11; // cl
  _BYTE *v12; // esi
  unsigned int v13; // ecx
  int v14; // ebx
  unsigned __int8 v15; // cl
  char v16; // dl
  _BYTE *v18; // [esp+Ch] [ebp-Ch]
  unsigned int *_input; // [esp+10h] [ebp-8h]
  int v20; // [esp+14h] [ebp-4h]
  unsigned int v21; // [esp+14h] [ebp-4h]
  int input_lena; // [esp+24h] [ebp+Ch]

  v4 = 0;
  v18 = a2;
  _input_len = 0;
  v6 = 0;
  _input = a1;
  v20 = 0;
  if ( !input_len )
    return 0;
  v7 = input;
  do
  {
    v8 = 0;
    v9 = _input_len == input_len;
    if ( _input_len < input_len )
    {
      do
      {
        if ( input[_input_len] != 32 )          // 首位空格检查,直到第一个非空格字符??
          break;
        ++_input_len;
        ++v8;
      }
      while ( _input_len < input_len );
      v9 = _input_len == input_len;
    }
    if ( v9 )
      break;
    if ( input_len - _input_len >= 2 && input[_input_len] == 13 && input[_input_len + 1] == 10
      || (v10 = input[_input_len], v10 == 10) )
    {
      v6 = v20;
    }
    else
    {
      if ( v8 )
        return -44;
      if ( v10 == 61 && ++v4 > 2 )
        return -44;
      if ( v10 > 0x7Fu )
        return -44;
      v11 = byte_4A4E40[v10];
      if ( v11 == 127 || v11 < '@' && v4 )
        return -44;
      v6 = v20++ + 1;
    }
    ++_input_len;
  }
  while ( _input_len < input_len );
  if ( !v6 )
    return 0;
  v12 = v18;
  v13 = ((6 * v6 + 7) >> 3) - v4;
  if ( v18 && *_input >= v13 )
  {
    v21 = 3;
    v14 = 0;
    for ( input_lena = 0; _input_len; --_input_len )
    {
      v15 = *v7;
      if ( *v7 != '\r' && v15 != '\n' && v15 != ' ' )
      {
        v16 = byte_4A4E40[v15];
        v21 -= v16 == 0x40;
        v14 = v16 & 0x3F | (v14 << 6);          // 4*6->3*8
        if ( ++input_lena == 4 )
        {
          input_lena = 0;
          if ( v21 )
            *v12++ = BYTE2(v14);
          if ( v21 > 1 )
            *v12++ = BYTE1(v14);
          if ( v21 > 2 )
            *v12++ = v14;
        }
      }
      ++v7;
    }
    *_input = v12 - v18;
    return 0;
  }
  *_input = v13;
  return -42;
}
```
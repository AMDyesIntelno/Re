main函数

```cpp
__int64 __fastcall main(__int64 a1, char **a2, char **a3)
{
  void *v3; // ST00_8
  const char *flag; // ST08_8

  v3 = malloc(188uLL);
  flag = malloc(0x50uLL);
  sub_400BBF();  //初始化
  get_input(flag);
  check_and_split(flag);
  sub_400AAA("that_girl", v3);                  // 记录字符频数
  sub_400E54(flag, v3);
  return 0LL;
}
```

check_and_split函数

```cpp
void __fastcall check_and_split(__int64 a1)
{
  int v1; // [rsp+14h] [rbp-Ch]
  void *dest; // [rsp+18h] [rbp-8h]

  dest = malloc(0x50uLL);
  if ( memcmp(a1, "QCTF{", 5uLL) )
    exit(-1);
  memcpy(dest, (a1 + 5), 0x4BuLL);
  v1 = strlen(dest);
  if ( *(dest + v1 - 1) == '}' )
    *(dest + v1 - 1) = 0;
  memcpy(a1, dest, 0x50uLL);
  free(dest);
}
```

sub_400AAA函数

```cpp
int __fastcall sub_400AAA(const char *a1, __int64 a2)
{
  int posi; // eax
  __int64 v4; // [rsp+0h] [rbp-20h]
  char buf; // [rsp+13h] [rbp-Dh]
  int fd; // [rsp+14h] [rbp-Ch]
  unsigned __int64 v7; // [rsp+18h] [rbp-8h]

  v7 = __readfsqword(0x28u);
  fd = open(a1, 0, a2, a1);
  while ( read(fd, &buf, 1uLL) == 1 )
  {
    posi = get_character_frequency(buf);
    ++*(4LL * posi + v4);
  }
  return close(fd);
}
```

get_character_frequency函数

```cpp
__int64 __fastcall get_character_frequency(char a1)
{
  __int64 result; // rax

  result = (a1 - 10);
  switch ( a1 )
  {
    case 10:
      result = (a1 + 35);
      break;
    case 32:
    case 33:
    case 34:
      result = (a1 + 10);
      break;
    case 39:
      result = (a1 + 2);
      break;
    case 44:
      result = (a1 - 4);
      break;
    case 46:
      result = (a1 - 7);
      break;
    case 58:
    case 59:
      result = (a1 - 21);
      break;
    case 63:
      result = (a1 - 27);
      break;
    case 95:
      result = (a1 - 49);
      break;
    default:
      if ( a1 <= 47 || a1 > 48 )
      {
        if ( a1 <= 64 || a1 > 90 )
        {
          if ( a1 > 96 && a1 <= 122 )
            result = (a1 - 87);
        }
        else
        {
          result = (a1 - 55);
        }
      }
      else
      {
        result = (a1 - 48);
      }
      break;
  }
  return result;
}
```
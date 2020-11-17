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
  int v2; // eax
  __int64 v4; // [rsp+0h] [rbp-20h]
  char buf; // [rsp+13h] [rbp-Dh]
  int fd; // [rsp+14h] [rbp-Ch]
  unsigned __int64 v7; // [rsp+18h] [rbp-8h]

  v7 = __readfsqword(0x28u);
  fd = open(a1, 0, a2, a1);
  while ( read(fd, &buf, 1uLL) == 1 )
  {
    v2 = get_character_new_index(buf);
    ++*(4LL * v2 + v4);
  }
  return close(fd);
}
```

get_character_frequency函数

```cpp
__int64 __fastcall get_character_new_index(char a1)
{
  __int64 result; // rax

  result = (a1 - '\n');
  switch ( a1 )
  {
    case '\n':
      result = (a1 + 35);
      break;
    case ' ':
    case '!':
    case '"':
      result = (a1 + 10);
      break;
    case '\'':
      result = (a1 + 2);
      break;
    case ',':
      result = (a1 - 4);
      break;
    case '.':
      result = (a1 - 7);
      break;
    case ':':
    case ';':
      result = (a1 - 21);
      break;
    case '?':
      result = (a1 - 27);
      break;
    case '_':
      result = (a1 - 49);
      break;
    default:
      if ( a1 <= '/' || a1 > '0' )
      {
        if ( a1 <= '@' || a1 > 'Z' )
        {
          if ( a1 > '`' && a1 <= 'z' )
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

sub_400E54函数

```cpp
unsigned __int64 __fastcall sub_400E54(const char *flag, __int64 a2)
{
  int i; // [rsp+18h] [rbp-48h]
  int flag_len; // [rsp+1Ch] [rbp-44h]
  char v5[56]; // [rsp+20h] [rbp-40h]
  unsigned __int64 v6; // [rsp+58h] [rbp-8h]

  v6 = __readfsqword(0x28u);
  flag_len = strlen(flag);
  for ( i = 0; i < flag_len; ++i )
    v5[i] = *(4LL * get_character_new_index(flag[i]) + a2);
  convert(v5);
  encrypt(v5, flag_len);
  sub_400CC0(v5, "out", flag_len);
  return __readfsqword(0x28u) ^ v6;
}
```

convert函数

```cpp
__int64 __fastcall convert(unsigned __int8 *a1)
{
  __int64 result; // rax
  _BYTE v2[5]; // [rsp+13h] [rbp-5h]

  v2[4] = 0;
  *v2 = *a1;
  while ( dword_6020A0[*&v2[1]] )
  {
    a1[*&v2[1]] = a1[dword_6020A0[*&v2[1]]];
    *&v2[1] = dword_6020A0[*&v2[1]];
  }
  result = v2[0];
  a1[*&v2[1]] = v2[0];
  return result;
}
```

encrypt函数

```cpp
_BYTE *__fastcall encrypt(_BYTE *a1, int a2)
{
  _BYTE *result; // rax
  char v3; // [rsp+17h] [rbp-5h]
  int i; // [rsp+18h] [rbp-4h]

  v3 = *a1 >> 5;
  for ( i = 0; a2 - 1 > i; ++i )
    a1[i] = 8 * a1[i] | (a1[i + 1] >> 5);       // a_new[0]=a[0]<<3 | a[1]>>5
  result = &a1[i];
  *result = 8 * *result | v3;
  return result;
}
```

encrypt函数得到的结果被保存在`out`文件中

可以根据encrypt函数进行反推

```
EC29E341E1F7AA1D29ED299939F3B7A9E7AC2BB7AB409FA931352C29EFA83D4BB0E9E1687B41
```

解密

```python
a=[0xEC,0x29,0xE3,0x41,0xE1,0xF7,0xAA,0x1D,0x29,0xED,0x29,0x99,0x39,0xF3,0xB7,0xA9,0xE7,0xAC,0x2B,0xB7,0xAB,0x40,0x9F,0xA9,0x31,0x35,0x2C,0x29,0xEF,0xA8,0x3D,0x4B,0xB0,0xE9,0xE1,0x68,0x7B,0x41]
print(a)
tail5=[]
head3=[0]
for i in range(len(a)):
    tail5.append(a[i]>>3)
for i in range(len(a)-1):
    head3.append((a[i]<<5)&0xff)
head3[0]=(a[len(a)-1]<<5)&0xff
after_convert=[]
for i in range(len(tail5)):
    after_convert.append(tail5[i]+head3[i])
print(after_convert)
#[61, 133, 60, 104, 60, 62, 245, 67, 165, 61, 165, 51, 39, 62, 118, 245, 60, 245, 133, 118, 245, 104, 19, 245, 38, 38, 165, 133, 61, 245, 7, 169, 118, 29, 60, 45, 15, 104]
```

验证

```cpp
#include<iostream>
using namespace std;
int main(){
    unsigned char a1[]={61, 133, 60, 104, 60, 62, 245, 67, 165, 61, 165, 51, 39, 62, 118, 245, 60, 245, 133, 118, 245, 104, 19, 245, 38, 38, 165, 133, 61, 245, 7, 169, 118, 29, 60, 45, 15, 104};
    unsigned char v3; // [rsp+17h] [rbp-5h]
    int i; // [rsp+18h] [rbp-4h]
    unsigned char *result=nullptr;
    v3 = *a1 >> 5;
    for ( i = 0; 38 - 1 > i; ++i )
         a1[i] = 8 * a1[i] | (a1[i + 1] >> 5);       // a_new[0]=a[0]<<3 | a[1]>>5
    result = &a1[i];
    *result = 8 * *result | v3;
    for(i=0;i<38;++i){
        cout<<int(a1[i])<<' ';
    }
    return 0;
}
/*[236, 41, 227, 65, 225, 247, 170, 29, 41, 237, 41, 153, 57, 243, 183, 169, 231, 172, 43, 183, 171, 64, 159, 169, 49, 53, 44, 41, 239, 168, 61, 75, 176, 233, 225, 104, 123, 65]*/
```

对convert函数进行逆向

```python
dword_6020A0=[22, 0, 6, 2, 30, 24, 9, 1, 21, 7, 18, 10, 8, 12, 17, 23, 13, 4, 3, 14, 19, 11, 20, 16, 15, 5, 25, 36, 27, 28, 29, 37, 31, 32, 33, 26, 34, 35]
#print(sorted(dword_6020A0))
#[0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37]
posi=0
after_convert=[61, 133, 60, 104, 60, 62, 245, 67, 165, 61, 165, 51, 39, 62, 118, 245, 60, 245, 133, 118, 245, 104, 19, 245, 38, 38, 165, 133, 61, 245, 7, 169, 118, 29, 60, 45, 15, 104]
convert=[0]
while dword_6020A0[posi]:
    convert.append(dword_6020A0[posi])
    posi=dword_6020A0[posi]
#print(convert)
#[0, 22, 20, 19, 14, 17, 4, 30, 29, 28, 27, 36, 34, 33, 32, 31, 37, 35, 26, 25, 5, 24, 15, 23, 16, 13, 12, 8, 21, 11, 10, 18, 3, 2, 6, 9, 7, 1]
posi=0
before_convert=[0 for i in range(38)]
for i in range(37):
    before_convert[convert[i+1]]=after_convert[convert[i]]
before_convert[0]=after_convert[1]
print(before_convert)
#[133, 67, 104, 133, 245, 38, 60, 61, 39, 245, 51, 104, 62, 60, 118, 38, 245, 118, 165, 245, 19, 165, 61, 245, 62, 165, 45, 61, 245, 7, 60, 118, 29, 60, 15, 104, 133, 169]
```

根据反汇编对sub_400AAA进行模拟,从而得到字符频数数组

```cpp
#include<iostream>
#include<cstring>
using namespace std;
int get_character_new_index(char a1)
{
  int result; // rax

  result = (a1 - '\n');
  switch ( a1 )
  {
    case '\n':
      result = (a1 + 35);
      break;
    case ' ':
    case '!':
    case '"':
      result = (a1 + 10);
      break;
    case '\'':
      result = (a1 + 2);
      break;
    case ',':
      result = (a1 - 4);
      break;
    case '.':
      result = (a1 - 7);
      break;
    case ':':
    case ';':
      result = (a1 - 21);
      break;
    case '?':
      result = (a1 - 27);
      break;
    case '_':
      result = (a1 - 49);
      break;
    default:
      if ( a1 <= '/' || a1 > '0' )
      {
        if ( a1 <= '@' || a1 > 'Z' )
        {
          if ( a1 > '`' && a1 <= 'z' )
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
int main(){
    int get_ch[80]={0};
    const char * text="There's_a_girl_but_I_let_her_get_away\nIt's_all_my_fault_cause_pride_got_in_the_way\nAnd_I'd_be_lying_if_I_said_I_was_OK\nAbout_that_girl_the_one_I_let_get_away\nI_keep_saying_no\nThis_can't_be_the_way_we're_supposed_to_be\nI_keep_saying_no\nThere's_gotta_be_a_way_to_get_you_close_to_me\nNow_I_know_you_gotta\nSpeak_up_if_you_want_somebody\nCan't_let_him_get_away_oh_no\nYou_don't_wanna_end_up_sorry\nThe_way_that_I'm_feeling_everyday\nNo_no_no_no\nThere's_no_hope_for_the_broken_heart\nNo_no_no_no\nThere's_no_hope_for_the_broken\nThere's_a_girl_but_I_let_her_get_away\nIt's_my_fault_cause_I_said_I_needed_space\nI've_been_torturing_myself_night_and_day\nAbout_that_girl_the_one_I_let_get_away\nI_keep_saying_no\nThis can't be the way we're supposed to be\nI keep saying no\nThere's gotta be a way to get you\nThere's gotta be a way\nTo_get_you_close_to_me\nYou_gotta\nSpeak_up_if_you_want_somebody\nCan't_let_him_get_away_oh_no\nYou_don't_wanna_end_up_sorry\nThe_way_that_I'm_feeling_everyday\nNo_no_no_no\nThere's_no_hope_for_the_broken_heart\nNo no no no\nThere's no hope for the broken\nNo home for me\nNo home cause I'm broken\nNo room to breathe\nAnd I got no one to blame\nNo home for me\nNo_home_cause_I'm_broken\nAbout_that_girl\nThe_one_I_let_get_away\nSo_you_better\nSpeak_up_if_you_want_somebody\nYou_can't_let_him_bet_away_no_no\nYou_don't_wanna_end_up_sorry\nThe_way_that_I'm_feeling_everyday\nDon't_you_know\nNo_no_no_no\nThere's_no_hope_for_the_broken_hearty\nDon't you know\nNo no no no\nThere's no hope for the broken\nOh\nYou don't wanna lose at love\nIt's only gonna hurt too much\nI'm telling you\nYou_don't_wanna_lose_at_love\nIt's_only_gonna_hurt_too_much\nI'm_telling_you\nYou_don't_wanna_lose_at_love\nCause_there's_no_hope_for_the_broken_heart\nThat_girl\nThe_one_I_let_get_away\n";
    for(int i=0;i<strlen(text);++i){//模拟反汇编代码进行字频读取
        get_ch[get_character_new_index(text[i])]++;
    }
    for(int i=33;i<126;++i){//生成字符与下标的对应关系
        cout<<get_character_new_index(i)<<":"<<"\""<<char(i)<<"\""<<',';
    }
    cout<<endl;
    for(int i=0;i<80;++i){
        cout<<get_ch[i]<<',';
    }
    return 0;
}

/*
43:"!",44:""",25:"#",26:"$",27:"%",28:"&",41:"'",30:"(",31:")",32:"*",33:"+",40:",",35:"-",39:".",37:"/",0:"0",39:"1",40:"2",41:"3",42:"4",43:"5",44:"6",45:"7",46:"8",47:"9",37:":",38:";",50:"<",51:"=",52:">",36:"?",54:"@",10:"A",11:"B",12:"C",13:"D",14:"E",15:"F",16:"G",17:"H",18:"I",19:"J",20:"K",21:"L",22:"M",23:"N",24:"O",25:"P",26:"Q",27:"R",28:"S",29:"T",30:"U",31:"V",32:"W",33:"X",34:"Y",35:"Z",81:"[",82:"\",83:"]",84:"^",46:"_",86:"`",10:"a",11:"b",12:"c",13:"d",14:"e",15:"f",16:"g",17:"h",18:"i",19:"j",20:"k",21:"l",22:"m",23:"n",24:"o",25:"p",26:"q",27:"r",28:"s",29:"t",30:"u",31:"v",32:"w",33:"x",34:"y",35:"z",113:"{",114:"|",115:"}",
0,0,0,0,0,0,0,0,0,0,104,30,15,29,169,19,38,67,60,0,20,39,28,118,165,26,0,61,51,133,45,7,34,0,62,0,0,0,0,0,0,40,71,0,0,66,245,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
*/
```

exp

```py
a=[0xEC,0x29,0xE3,0x41,0xE1,0xF7,0xAA,0x1D,0x29,0xED,0x29,0x99,0x39,0xF3,0xB7,0xA9,0xE7,0xAC,0x2B,0xB7,0xAB,0x40,0x9F,0xA9,0x31,0x35,0x2C,0x29,0xEF,0xA8,0x3D,0x4B,0xB0,0xE9,0xE1,0x68,0x7B,0x41]
#print(a)
tail5=[]
head3=[0]
for i in range(len(a)):
    tail5.append(a[i]>>3)
for i in range(len(a)-1):
    head3.append((a[i]<<5)&0xff)
head3[0]=(a[len(a)-1]<<5)&0xff
after_convert=[]
for i in range(len(tail5)):
    after_convert.append(tail5[i]+head3[i])
#print(after_convert)
#[61, 133, 60, 104, 60, 62, 245, 67, 165, 61, 165, 51, 39, 62, 118, 245, 60, 245, 133, 118, 245, 104, 19, 245, 38, 38, 165, 133, 61, 245, 7, 169, 118, 29, 60, 45, 15, 104]
dword_6020A0=[22, 0, 6, 2, 30, 24, 9, 1, 21, 7, 18, 10, 8, 12, 17, 23, 13, 4, 3, 14, 19, 11, 20, 16, 15, 5, 25, 36, 27, 28, 29, 37, 31, 32, 33, 26, 34, 35]
#print(sorted(dword_6020A0))
#[0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37]
posi=0
convert=[0]
while dword_6020A0[posi]:
    convert.append(dword_6020A0[posi])
    posi=dword_6020A0[posi]
#print(convert)
#[0, 22, 20, 19, 14, 17, 4, 30, 29, 28, 27, 36, 34, 33, 32, 31, 37, 35, 26, 25, 5, 24, 15, 23, 16, 13, 12, 8, 21, 11, 10, 18, 3, 2, 6, 9, 7, 1]
posi=0
before_convert=[0 for i in range(38)]
for i in range(37):
    before_convert[convert[i+1]]=after_convert[convert[i]]
before_convert[0]=after_convert[1]
#print(before_convert)
#[133, 67, 104, 133, 245, 38, 60, 61, 39, 245, 51, 104, 62, 60, 118, 38, 245, 118, 165, 245, 19, 165, 61, 245, 62, 165, 45, 61, 245, 7, 60, 118, 29, 60, 15, 104, 133, 169]

dic={43:"!",44:"\"",25:"#",26:"$",27:"%",28:"&",41:"'",30:"(",31:")",32:"*",33:"+",40:",",35:"-",39:".",37:"/",0:"0",39:"1",40:"2",41:"3",42:"4",43:"5",44:"6",45:"7",46:"8",47:"9",37:":",38:";",50:"<",51:"=",52:">",36:"?",54:"@",10:"A",11:"B",12:"C",13:"D",14:"E",15:"F",16:"G",17:"H",18:"I",19:"J",20:"K",21:"L",22:"M",23:"N",24:"O",25:"P",26:"Q",27:"R",28:"S",29:"T",30:"U",31:"V",32:"W",33:"X",34:"Y",35:"Z",81:"[",82:"\\",83:"]",84:"^",46:"_",86:"`",10:"a",11:"b",12:"c",13:"d",14:"e",15:"f",16:"g",17:"h",18:"i",19:"j",20:"k",21:"l",22:"m",23:"n",24:"o",25:"p",26:"q",27:"r",28:"s",29:"t",30:"u",31:"v",32:"w",33:"x",34:"y",35:"z",113:"{",114:"|",115:"}"}

get_frequency=[0,0,0,0,0,0,0,0,0,0,104,30,15,29,169,19,38,67,60,0,20,39,28,118,165,26,0,61,51,133,45,7,34,0,62,0,0,0,0,0,0,40,71,0,0,66,245,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]

for i in before_convert:
    print(dic[get_frequency.index(i)],end="")
```

flag:`QCTF{that_girl_saying_no_for_your_vindicate}`
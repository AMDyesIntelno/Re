**使用动态调试**

main函数

```cpp
int __cdecl main(int argc, const char **argv, const char **envp)
{
  int result; // eax
  HANDLE v4; // eax
  DWORD NumberOfBytesWritten; // [esp+4h] [ebp-24h]
  char Buffer; // [esp+8h] [ebp-20h]

  maybe_print(aPleaseInputFla);
  scanf(a31s, &Buffer);
  if ( strlen(&Buffer) == 19 )
  {
    sub_401220();
    v4 = CreateFileA(FileName, 0x40000000u, 0, 0, 2u, 0x80u, 0);
    WriteFile(v4, &Buffer, 0x13u, &NumberOfBytesWritten, 0);// 对输入进行了修改
                                                // int __stdcall kernel32_WriteFile(HANDLE hFile, LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite, LPDWORD lpNumberOfBytesWritten, LPOVERLAPPED lpOverlapped)
                                                // {
                                                //   return sub_401080(hFile, lpBuffer, nNumberOfBytesToWrite, lpNumberOfBytesWritten, lpOverlapped);
                                                // }
    compare(&Buffer, &NumberOfBytesWritten);
    if ( NumberOfBytesWritten == 1 )
      maybe_print(aRightFlagIsYou);
    else
      maybe_print(aWrong);
    system(aPause);
    result = 0;
  }
  else
  {
    maybe_print(aWrong);
    system(aPause);
    result = 0;
  }
  return result;
}
```

将断点下在`sub_401220();`,进入函数,步过直到`return sub_4010D0();`

```cpp
int sub_401220()
{
  HMODULE v0; // eax
  DWORD v2; // eax

  v2 = GetCurrentProcessId();                   // 返回当前进程ID
  hProcess = OpenProcess(0x1F0FFFu, 0, v2);     // 打开一个已存在的进程对象,并返回进程的句柄
  v0 = LoadLibraryA(LibFileName);               // 链接DLL
  dword_40C9C4 = GetProcAddress(v0, ProcName);  // 获取WriteFile在DLL中的地址
                                                // .data:0040C9C4 dword_40C9C4 dd 763E35B0h
                                                // kernel32.dll:763E35B0 jmp     off_7644105C
                                                // kernel32.dll:7644105C off_7644105C dd offset kernelbase_WriteFile
  writefile_address = dword_40C9C4;
  if ( !dword_40C9C4 )
    return maybe_print(&unk_40A044);
  unk_40C9B4 = *writefile_address;              // 取出跳转到WriteFile的指令
  *(&unk_40C9B4 + 4) = *(writefile_address + 4);
  byte_40C9BC = 0xE9u;                          // 0xE9 的汇编为 jmp
  dword_40C9BD = hook_sub - writefile_address - 5;// 计算地址偏移量
  return sub_4010D0();                          // 对writefile函数进行hook,使其执行sub_4010D0
}
```

`sub_401220();`对`WriteFile`进行hook,进入`sub_4010D0()`

```cpp
BOOL sub_4010D0()
{
  DWORD v1; // [esp+4h] [ebp-8h]
  DWORD flOldProtect; // [esp+8h] [ebp-4h]

  v1 = 0;
  VirtualProtectEx(hProcess, writefile_address, 5u, 4u, &flOldProtect);// 改变在特定进程中内存区域的保护属性,使得writefile_address可以被更改
                                                // BOOL VirtualProtectEx(
                                                // HANDLE hProcess, // 要修改内存的进程句柄
                                                // LPVOID lpAddress, // 要修改内存的起始地址
                                                // DWORD dwSize, // 页区域大小
                                                // DWORD flNewProtect, // 新访问方式
                                                // PDWORD lpflOldProtect // 原访问方式 用于保存改变前的保护属性 易语言要传址
                                                // );
  WriteProcessMemory(hProcess, writefile_address, &byte_40C9BC, 5u, 0);// 将数据写入内存区域
                                                // BOOL WriteProcessMemory(
                                                //   HANDLE  hProcess,
                                                //   LPVOID  lpBaseAddress, 指向要写入数据的指定进程中的基地址的指针,系统要先确认其是否可写,在VirtualProtectEx使其可写
                                                //   LPCVOID lpBuffer, 指向缓冲区的指针，该缓冲区包含要在指定进程的地址空间中写入的数据,byte_40C9BC的值为0xE9,即jmp
                                                //   SIZE_T  nSize,
                                                //   SIZE_T  *lpNumberOfBytesWritten
                                                // );
                                                // 
                                                // 执行完成后,得到
                                                // .data:0040C9B0 writefile_address dd 763E35B0h
                                                // kernel32.dll:763E35B0 kernel32_WriteFile proc near
                                                // kernel32.dll:763E35B0 jmp     sub_401080
                                                // 可以推断writefile被hook成sub_401080
  return VirtualProtectEx(hProcess, writefile_address, 5u, flOldProtect, &v1);// 恢复保护属性
}
```

当`WriteProcessMemory(hProcess, writefile_address, &byte_40C9BC, 5u, 0);`执行完成时,`writefile_address`已经变成`763E35B0h`,被修改为`jmp     sub_401080`,说明已经hook完成

此时,回到main函数中,步过到`WriteFile(v4, &Buffer, 0x13u, &NumberOfBytesWritten, 0);`,进入`WriteFile`

```
kernel32.dll:763E35B0
kernel32.dll:763E35B0 kernel32_WriteFile:
kernel32.dll:763E35B0 jmp     hook_sub
```

```cpp
int __stdcall kernel32_WriteFile(HANDLE hFile, LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite, LPDWORD lpNumberOfBytesWritten, LPOVERLAPPED lpOverlapped)
{
   return sub_401080(hFile, lpBuffer, nNumberOfBytesToWrite, lpNumberOfBytesWritten, lpOverlapped);
}
```

进入`sub_401080`

```cpp
int __stdcall hook_sub(HANDLE hFile, LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite, LPDWORD lpNumberOfBytesWritten, LPOVERLAPPED lpOverlapped)
{
  signed int v5; // ebx

  v5 = encode(lpBuffer, nNumberOfBytesToWrite);
  recover();
  WriteFile(hFile, lpBuffer, nNumberOfBytesToWrite, lpNumberOfBytesWritten, lpOverlapped);
  if ( v5 )
    *lpNumberOfBytesWritten = 1;
  return 0;
}
```

`encode`函数即为对输入进行处理的函数

```cpp
signed int __cdecl encode(int input, signed int len)
{
  char posi; // al
  char v3; // bl
  char v4; // cl
  int v5; // eax

  posi = 0;
  if ( len > 0 )
  {
    do
    {
      if ( posi == 18 )
      {
        *(input + 18) ^= 0x13u;
      }
      else
      {
        if ( posi % 2 )
          v3 = *(posi + input) - posi;
        else
          v3 = *(posi + input + 2);
        *(posi + input) = posi ^ v3;
      }
      ++posi;
    }
    while ( posi < len );
  }
  v4 = 0;
  if ( len <= 0 )
    return 1;
  v5 = 0;
  while ( byte_40A030[v5] == *(v5 + input) )
  {
    v5 = ++v4;
    if ( v4 >= len )
      return 1;
  }
  return 0;
}
```

根据逻辑进行恢复

```py
byte_40A030=[97, 106, 121, 103, 107, 70, 109, 46, 127, 95, 126, 45, 83, 86, 123, 56, 109, 76, 110, 0]
flag=[0 for i in range(19)]
flag[18]=byte_40A030[18]^0x13
for i in range(18):
    v3=byte_40A030[i]^i
    if i%2:
        flag[i]=v3+i
    else:
        flag[i+2]=v3
for i in flag:
    print(chr(i),end="")
```

得到`lag{Ho0k_w1th_Fun}`,补个`f`得到`flag{Ho0k_w1th_Fun}`
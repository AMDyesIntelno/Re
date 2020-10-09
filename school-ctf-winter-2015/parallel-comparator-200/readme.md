```cpp
for (i = 0; i < FLAG_LEN; i++) {
        if (generated_string[i] != just_a_string[i])//gen==just a string
            return 0;
    }
```

说明`generated_string[i] == just_a_string[i]`

由`generated_string[i] = *(char *)result + just_a_string[i];`知,`result`等于0

```cpp
*result = (argument[0]+argument[1]) ^ argument[2];//(first_letter+difference)^user_string=0
return result;//null
```

返回的`result`为`NULL`,`(first_letter+difference)^user_string=0`,`first_letter+difference=user_string`

```py
difference=[0, 9, -9, -1, 13, -13, -4, -11, -9, -1, -7, 6, -13, 13, 3, 9, -13, -11, 6, -7]
for first_letter in range(97,123):
    user_string=""
    for i in range(20):
        user_string+=chr(first_letter+difference[i])
    print(user_string)
#lucky_hacker_you_are
```

flag:`lucky_hacker_you_are`

P.S.

在Linux环境下

```cpp
while ((initialization_number = random()) >= 64);
    
    int first_letter;
    first_letter = (initialization_number % 26) + 97;
```

`initialization_number`恒为`37`,`first_letter`恒为`108`,因为只有`random`而没有`srand`

```cpp
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

int main(){
	int a;
	while ((a=random())>=64);
	int f=(a%26)+97;
	printf("a=%d,f=%d",a,f);
	return 0;
}
```

`a=37,f=108`

然而在Windows环境下

`first_letter`恒为`112`
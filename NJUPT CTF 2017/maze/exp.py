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
dic={"上":".","下":"0","左":"O","右":"o"}
answer="右下右右下下左下下下右右右右上上左左"
for i in answer:
  print(dic[i],end="")
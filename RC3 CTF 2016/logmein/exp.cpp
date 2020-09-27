#include<iostream>
#include<cstdlib>
#include<cstring>
using namespace std;
int main(){
    const char *v8=":\"AL_RT^L*.?+6/46";
    __int64 v7 = 28537194573619560LL;
    int v6=7;
    for(int i=0;i<strlen(v8);++i){
        cout<<(char)(*((unsigned char *)&v7 + i % v6) ^ v8[i]);
    }
    return 0;
}
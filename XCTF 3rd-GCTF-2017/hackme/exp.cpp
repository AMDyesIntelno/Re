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
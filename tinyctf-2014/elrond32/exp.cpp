#include<iostream>
using namespace std;
void fun(int a){
    if(a==0){
        cout<<"i";
        fun(7*(a+1)%11);
    }
    else if(a==1){
        cout<<"e";
        fun(7*(a+1)%11);
    }
    else if(a==3){
        cout<<"n";
        fun(7*(a+1)%11);
    }
    else if(a==4){
        cout<<"d";
        fun(7*(a+1)%11);
    }
    else if(a==5){
        cout<<"a";
        fun(7*(a+1)%11);
    }
    else if(a==6){
        cout<<"g";
        fun(7*(a+1)%11);
    }
    else if(a==7){
        cout<<"s";
        fun(7*(a+1)%11);
    }
    else if(a==9){
        cout<<"r";
        fun(7*(a+1)%11);
    }
}
int main(){
    fun(0);
    return 0;
}
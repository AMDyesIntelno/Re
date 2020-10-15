//tea
#include <stdint.h>
#include <iostream>
using namespace std;

void encrypt (uint32_t* v, uint32_t* k) {
    uint32_t v0=v[0], v1=v[1], sum=0, i;           /* set up */
    uint32_t delta=0x9e3779b9;                     /* a key schedule constant */
    uint32_t k0=k[0], k1=k[1], k2=k[2], k3=k[3];   /* cache key */
    for (i=0; i < 32; i++) {                       /* basic cycle start */
        sum += delta;
        v0 += ((v1<<4) + k0) ^ (v1 + sum) ^ ((v1>>5) + k1);
        v1 += ((v0<<4) + k2) ^ (v0 + sum) ^ ((v0>>5) + k3);
    }                                              /* end cycle */
    v[0]=v0; v[1]=v1;
}

void decrypt (uint32_t* v, uint32_t* k) {
    uint32_t v0=v[0], v1=v[1], sum=0xC6EF3720, i;  /* set up */
    uint32_t delta=0x9e3779b9;                     /* a key schedule constant */
    uint32_t k0=k[0], k1=k[1], k2=k[2], k3=k[3];   /* cache key */
    for (i=0; i<32; i++) {                         /* basic cycle start */
        v1 -= ((v0<<4) + k2) ^ (v0 + sum) ^ ((v0>>5) + k3);
        v0 -= ((v1<<4) + k0) ^ (v1 + sum) ^ ((v1>>5) + k1);
        sum -= delta;                                
    }                                              /* end cycle */
    v[0]=v0; v[1]=v1;
}
int main(){
    char plaintext[]="asdfghjkqwertyui";
    uint32_t ciphertext[4]={0};
    uint32_t key[4]={0x30343842,0x31353943,0x32364044,0x33374145};
    for(int i=0;i<=15;i+=4){
        ciphertext[i%4]+=plaintext[i];
        ciphertext[i%4]<<=8;
        ciphertext[i%4]+=plaintext[i+1];
        ciphertext[i%4]<<=8;
        ciphertext[i%4]+=plaintext[i+2];
        ciphertext[i%4]<<=8;
        ciphertext[i%4]+=plaintext[i+3];
        printf("%X\n",ciphertext[i%4]);
    }
    encrypt(ciphertext,key);
    encrypt(ciphertext+2,key);
    printf("%X %X %X %X",ciphertext[0],ciphertext[1],ciphertext[2],ciphertext[3]);
    return 0;

    /*
    uint32_t value[2]={0x01234567,0x89ABCDEF};
    uint32_t key[4]={0x30343842,0x31353943,0x32364044,0x33374145};
    encrypt(value,key);
    cout<<"---------------"<<endl;
    decrypt(value,key);
    return 0;
    */
}
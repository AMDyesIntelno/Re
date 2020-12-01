#include<stdio.h>

void test(unsigned char arg1,unsigned char arg2,unsigned char arg3,unsigned char arg4,unsigned char arg5,unsigned char arg6){
    unsigned char *v10;
    unsigned char v17[113]={0xFE,0xA0,0xAD,0x80,0x20,0x59,0xAB,0x12,0xD7,0xC3,0x9C,0x88,0xFA,0x2C,0x1D,0xFC,0x81,0x46,0x0D,0xDC,0xE9,0xCE,0xCC,0x57,0x78,0xF5,0x41,0x5F,0x52,0x02,0x36,0xD5,0x33,0x18,0x66,0x3A,0x40,0x26,0xE8,0x6E,0xB6,0xCD,0x72,0xB7,0x3C,0x01,0x66,0xB1,0x4F,0x99,0x23,0x63,0x95,0x77,0x34,0x61,0x69,0xF6,0xA9,0x53,0x40,0x37,0x41,0x43,0x4F,0x98,0x95,0x2C,0x7A,0x27,0x3C,0x98,0x68,0x1A,0x88,0xA8,0xB7,0x85,0xBB,0x15,0x4F,0x1A,0x01,0x4D,0xC9,0xC8,0x9B,0x75,0x78,0x57,0x7F,0x98,0x0D,0xD8,0x51,0xA8,0x22,0xB9,0x5E,0x59,0x4D,0x71,0x4F,0x1A,0x81,0xA9,0xBF,0x07,0x29,0xED,0xFD,0x83};
    unsigned char v18[16]={0x21,0x00,0x86,0xb7,0xff,0x86,0x5d,0x06,0x2d,0x30};
    v18[10]=arg1;
    v18[11]=arg2;
    v18[12]=arg3;
    v18[13]=arg4;
    v18[14]=arg5;
    v18[15]=arg6;
    unsigned int v12 = (v18[2] << 16) | (v18[3] << 24) | *v18 | (v18[1] << 8);
    unsigned int v13 = (v18[6] << 16) | (v18[7] << 24) | v18[4] | (v18[5] << 8);
    unsigned int v14 = (v18[10] << 16) | (v18[11] << 24) | v18[8] | (v18[9] << 8);
    unsigned int v6 = (v18[15] << 24) | v18[12] | (v18[13] << 8) | (v18[14] << 16);
    int v5=112;
    if(v5>0){
        unsigned char *v15=v17+1;
        unsigned char *v16 = v17 + ((v5 - 1) & 0xFFFFFFF8) + 9;
        do{
            unsigned int v7 = (*v15 << 8) | (v15[2] << 24) | *(v15 - 1) | (v15[1] << 16);
            unsigned int v8 = 0xD5B7DDE0;
            unsigned int v9 = (v15[4] << 8) | v15[3] | (v15[6] << 24) | (v15[5] << 16);
            do{
                v9 -= (v7 + v8) ^ (16 * v7 + v14) ^ (v6 + (v7 >> 5));
                v7 -= (v9 + v8) ^ (16 * v9 + v12) ^ (v13 + (v9 >> 5));
                v8 += 0x21524111;
            }while(v8);
            unsigned char v7_0,v7_1,v7_2,v7_3,v9_0,v9_1,v9_2,v9_3;
            v7_0=v7&0xff;
            v7_1=(v7>>8)&0xff;
            v7_2=(v7>>16)&0xff;
            v7_3=(v7>>24)&0xff;
            v9_0=v9&0xff;
            v9_1=(v9>>8)&0xff;
            v9_2=(v9>>16)&0xff;
            v9_3=(v9>>24)&0xff;
            *(v15 - 1) = v7_0;
            unsigned char *v10 = (v15 + 8);
            *(v10 - 8) = v7_1;
            *(v10 - 7) = v7_2;
            *(v10 - 6) = v7_3;
            *(v10 - 5) = v9_0;
            *(v10 - 4) = v9_1;
            *(v10 - 3) = v9_2;
            *(v10 - 2) = v9_3;
            v15 += 8;
        }while(v10 != v16 && v15-v17<=112);
    }
    /*for(int i=0;i<112;++i){
        printf("%c",v17[i]);
    }
    printf("\n");*/
    if(v17[0]==67&&v17[1]==111&&v17[2]==110){//Con
        printf("%c%c%c%c%c%c  ",arg1,arg2,arg3,arg4,arg5,arg6);
        for(int i=0;i<112;++i){
            printf("%c",v17[i]);
        }
        printf("\n\n");
    }
}
int main(){
    unsigned char button[12]=" 1234567890";
    for(int i=0;i<12;++i){
        for(int j=0;j<12;++j){
            for(int k=0;k<12;++k){
                for(int l=0;l<12;++l){
                    for(int m=0;m<12;++m){
                        for(int n=0;n<12;++n){
                            test(button[i],button[j],button[k],button[l],button[m],button[n]);
                        }
                    }
                }
            }
        }
    }
    return 0;
}
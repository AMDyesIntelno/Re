#include "stdio.h"
#include "stdlib.h"
#include "string.h"

const char *base64_table = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

char *base64_encode(const char *in) {
    char temp[3];
    int count = 0, posi = 0;
    char *out = (char *)malloc(((strlen(in) + 2) / 3 + 1) * sizeof(char));
    for (int i = 0; i < strlen(in); ++i) {
        temp[count++] = in[i];
        if (in[i] == 'y') {

        }
        if (count == 3) {
            out[posi++] = base64_table[temp[0] >> 2];//取第一个字符的前六位
            out[posi++] = base64_table[((temp[0] & 0x3) << 4) | (temp[1] >> 4)];//取第一个字符的后两位,取第二个字符的前四位
            out[posi++] = base64_table[((temp[1] & 0xF) << 2) | (temp[2] >> 6)];//取第二个字符的后四位,取第三个字符的前两位
            out[posi++] = base64_table[temp[2] & 0x3F];//取第三个字符的后六位
            count = 0;
        }
    }
    if (count) {
        out[posi++] = base64_table[temp[0] >> 2];//取第一个字符的前六位
        if (count == 1) {
            out[posi++] = base64_table[(temp[0] & 0x3) << 4];//取第一个字符的后两位
            out[posi++] = '=';
        } else {
            out[posi++] = base64_table[((temp[0] & 0x3) << 4) | (temp[1] >> 4)];//取第一个字符的后两位,取第二个字符的前四位
            out[posi++] = base64_table[(temp[1] & 0xF) << 2];//取第二个字符的后四位,取第三个字符的前两位
        }
        out[posi++] = '=';
    }
    out[posi] = '\0';
    return out;
}

char *base64_decode(const char *in) {
    int out_len = strlen(in) / 4 * 3;
    if (in[strlen(in) - 1] == '=') {
        out_len--;
    }
    if (in[strlen(in) - 2] == '=') {
        out_len--;
    }
    char temp[4];
    int count = 0, posi = 0;
    char *out = (char *)malloc((out_len + 1) * sizeof(char));
    for (int i = 0; i < strlen(in); i++) {
        if (in[i] >= 'A' && in[i] <= 'Z') {
            temp[count++] = in[i] - 'A';
        } else if (in[i] >= 'a' && in[i] <= 'z') {
            temp[count++] = in[i] - 'a' + 26;
        } else if (in[i] >= '0' && in[i] <= '9') {
            temp[count++] = in[i] - '0' + 52;
        } else if (in[i] == '+') {
            temp[count++] = 62;
        } else if (in[i] == '/') {
            temp[count++] = 63;
        } else {
            temp[count++] = 0;
        }
        if (count == 4) {
            out[posi++] = (temp[0] << 2) | (temp[1] >> 4);
            out[posi++] = (temp[1] << 4) | (temp[2] & 0x3C) >> 2;
            out[posi++] = (temp[2] << 6) | temp[3];
            count = 0;
        }
    }
    out[posi] = '\0';
    return out;
}

int main() {
    const char *a = "Man is distinguished, not only by his reason, but by this singular passion from";
    //const char *a = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    //const char *a=" by";
    printf("%s\n", base64_encode(a));
    const char *b = "TWFuIGlzIGRpc3Rpbmd1aXNoZWQsIG5vdCBvbmx5";
    printf("%s", base64_decode(b));
    return 0;
}
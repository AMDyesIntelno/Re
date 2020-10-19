#include "stdio.h"
#include "stdlib.h"
#include "string.h"

const char *base64_table = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

char *base64_encode(const char *in) {
    char temp[3];
    int count = 0, posi = 0;
    char *out = malloc((strlen(in) / 3 + 1) * sizeof(char));//3*8->4*6
    for (int i = 0; in[i]; ++i) {
        temp[count++] = in[i];
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
    return out;
}

int main() {
    const char *a = "A";
    printf("%s", base64_encode(a));
    return 0;
}
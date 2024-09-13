// 전치 암호

#include <bits/stdc++.h>
using namespace std;

int en[] = { 2, 6, 1, 7, 0, 5, 3, 4 };
int de[] = { 4, 2, 0, 6, 7, 5, 1, 3 };
int mask = 0x80;
char p[100], e[100], d[100];

int main() {
    fgets(p, 100, stdin);
    
    // encryption
    size_t len = strlen(p);
    for(int i = 0; i < len; i++)
        for(int j = 0; j < 8; j++)
            if(p[i] & (mask >> en[j]))
                e[i] |= (mask >> j);
    printf("%s\n", e);
    
    // decryption
    len = strlen(e);
    for(int i = 0; i < len; i++)
        for(int j = 0; j < 8; j++)
            if(e[i] & (mask >> de[j]))
                d[i] |= (mask >> j);
    printf("%s\n", d);
}

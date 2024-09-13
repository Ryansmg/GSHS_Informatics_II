#include <bits/stdc++.h>

int n;
char str[10001];
int main() {
    FILE *in = fopen("rleencoded.txt", "r");
    FILE *out = fopen("rledecoded.txt", "w");

    while(!feof(in)) fscanf(in, "%c", &str[n++]);
    n--;

    for(int i=0; i<n; i++) {
        int cnt = str[i] - '0';
        while((i+1<n) && ((str[i+1]>='0') && (str[i+1] <= '9'))) {
            cnt *= 10;
            cnt += str[i+1] - '0';
            i++;
        }
        for(int j=0; j<cnt; j++) fprintf(out, "%c", str[i+1]);
        i++; //skip character
    }

    fclose(in); fclose(out);
}

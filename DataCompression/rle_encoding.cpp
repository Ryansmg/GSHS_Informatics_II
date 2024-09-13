#include <bits/stdc++.h>

int n;
char str[10001];
int main() {
    FILE *in = fopen("rletext.txt", "r");
    FILE *out = fopen("rleencoded.txt", "w");

    while(!feof(in)) fscanf(in, "%c", &str[n++]);
    n--;
    for(int i=0; i<n; i++) {
        int cnt = 1;
        while((i+1<n) && (str[i] == str[i+1])) cnt++, i++;
        fprintf(out, "%d%c", cnt, str[i]);
    }
    fclose(in); fclose(out);
}

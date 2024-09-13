#include <bits/stdc++.h>

int n = 10000;
char str[10001];
int main() {
    FILE *out = fopen("rletext.txt", "w");
    for(int i=1; i<=n; i++) str[i] = 'W';
    srand((int)time(nullptr));
    for(int i=1; i<=n/10; i++) {
        int c = rand() % n;
        str[c] = (str[c]=='W'?'B':'W');
    }
    for(int i=1; i<=n; i++) fprintf(out, "%c", str[i]);
    fclose(out);
}
// 전치 암호 2

#include <bits/stdc++.h>
int n;
char rail[10][100];
char d[100], e[100];

int main() {
    scanf("%d ", &n);
    fgets(e, 100, stdin);
    int elen = strlen(e)-1;
    
    bool di;
    int row = 0, col = 0;
    for(int i=0; i<elen; i++) {
        if(row == 0) di = true;
        if(row == n-1) di = false;
        rail[row][col++] = '0';
        di?row++:row--;
    }
    
    int cnt = 0;
    for(int i=0; i<n; i++)
        for(int j=0; j<elen; j++)
            if(rail[i][j] == '0' && cnt < elen)
                rail[i][j] = e[cnt++];
    row = col = 0;
    
    for(int i=0; i<elen; i++) {
        if(row == 0) di = true;
        if(row == n-1) di = false;
        if(rail[row][col] != '0')
            d[i] = rail[row][col++];
        di?row++:row--;
    }
    
    printf("%s\n", d);
}
// 전치 암호 2

#include <bits/stdc++.h>
int n;
char rail[10][100];
char p[100], e[100];

int main() {
    scanf("%d ", &n);
    fgets(p, 100, stdin);
    int plen = strlen(p)-1;
    
    bool di = false;
    int row = 0, col = 0;
    for(int i=0; i<plen; i++) {
        if(row==0 || row==n-1) di = !di;
        rail[row][col++] = p[i];
        di ? row++ : row--;
    }
    
    int cnt = 0;
    for(int i=0; i<n; i++)
        for(int j=0; j<plen; j++)
            if(rail[i][j] != '\0')
                e[cnt++] = rail[i][j];
    
    printf("%s\n", e);
}

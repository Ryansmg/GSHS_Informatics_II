// 치환 암호

#include <bits/stdc++.h>
using string = std::string;
using std::cin; using std::cout;

string enc = "ksrdngfbjcpwyuhtvaoqlziexm";
string dec = "abcdefghijklmnopqrstuvwxyz";

int main() {
    string raw;
    getline(cin, raw);
    
    string encStr = raw;
    for(char &c : encStr)
        if('a' <= c && c <= 'z')
            c = enc[c-'a'];
    
    cout << encStr << '\n';
    
    string decStr = encStr;
    for(int i = 0; i < 26; i++)
        dec[enc[i]-'a'] = 'a' + i;
    for(char &c : decStr)
        if('a' <= c && c <= 'z')
            c = dec[c-'a'];
    
    cout << decStr << '\n';
}
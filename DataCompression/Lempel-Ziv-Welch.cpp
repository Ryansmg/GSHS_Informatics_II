#include <bits/stdc++.h>
using namespace std;

map<string, int> endic;
int dcnt, enc[10000], ecnt;

int main() {
    ifstream in("lzwtext.txt");
    ofstream out("lzwencoded.txt");

    dcnt = 1;
    char c;
    string s;
    while(in.get(c)) {
        s = c;
        if(endic.find(s) != endic.end()) continue;
        endic.insert({s, dcnt});
        dcnt++;
    }
    in.close();

    in.open("lzwtext.txt");
    s = "";
    ecnt = 1;
    while(in.get(c)) {
        if(endic.find(s+c) != endic.end()) s += c;
        else {
            enc[ecnt++] = endic[s];
            endic.insert({s+c, dcnt++});
            s = c;
        }
    }
    enc[ecnt] = endic[s];
    ecnt++;

    dcnt--;
    cout << dcnt << endl;
    for(const auto &it : endic) cout << it.first << " " << it.second << endl;
    ecnt--;
    for(int i = 1; i <= ecnt; i++) {
        cout << enc[i] << " ";
        out << enc[i] << " ";
    }
    cout << endl; out << endl;
}

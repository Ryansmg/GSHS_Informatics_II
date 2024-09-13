#include <bits/stdc++.h>
using namespace std;

map<int, string> dedic;
int dcnt, enc[10000], ecnt;

int main() {
    ifstream in("lzwencoded.txt");
    ofstream out("lzwdecoded.txt");

    dedic[1] = 'A', dedic[2] = 'B', dedic[3] = 'C';
    dcnt = 4; ecnt = 1;
    while(in >> enc[ecnt]) ecnt++;

    string prestr = dedic[enc[1]];
    out << prestr;
    for(int i=2; i<ecnt; i++) {
        string addstr;
        if(dedic.find(enc[i]) != dedic.end()) {
            addstr = prestr + dedic[enc[i]][0];
            prestr = dedic[enc[i]];
        } else {
            addstr = prestr + prestr[0];
            prestr = addstr;
        }
        out << prestr;
        dedic[dcnt++] = addstr;
    }

    for(const auto &it : dedic) cout << it.first << " " << it.second << endl;
}

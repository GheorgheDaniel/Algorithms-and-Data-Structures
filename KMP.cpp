//https://codeforces.com/contest/126/problem/B
#include <bits/stdc++.h>
using namespace std;

const int MAX = 1e6;
string s, s1;
int kmp[MAX + 3];
bool fr[MAX + 3];

int main() {
    //freopen("file.in", "r", stdin);
    //freopen("file.out", "w", stdout);

    cin.tie(0); cout.tie(0);
    ios_base::sync_with_stdio(false);
    s.push_back('a');
    cin >> s1;
    s += s1;
    int k = 0;
    for(int i = 2; i < s.size(); i++) {
        while(k != 0 && s[k + 1] != s[i]) {
            k = kmp[k];
        }

        if(s[k + 1] == s[i])    
            k++;

        kmp[i] = k;

    }
    
    int best = 0;
    k = kmp[s.size() - 1];

    while(k != 0) {
        fr[k] = 1;
        k = kmp[k];
        
    }
    
    for(int i = 2; i < s.size() - 1; i++) {
        int poz = 0;

        if(fr[kmp[i]]) {
            best = max(best, kmp[i]);
        }
    }

    if(best == 0) {
        cout << "Just a legend";
        return 0;
    }


    

    for(int i = 1; i <= best; i++) {
        cout << s[i];
    }

}

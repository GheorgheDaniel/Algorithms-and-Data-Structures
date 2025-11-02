//https://codeforces.com/gym/102423/submission/302674192
#include <bits/stdc++.h>
using namespace std;

const int MAX = 500;
int N;
map<string, int>m;
string s[MAX + 3];

vector<int>G[MAX + 3];
int v[MAX + 3];

int L[MAX + 3], R[MAX + 3];

int pairup(int nod) {

    if(v[nod]) {
        return false;
    }
    v[nod] = true;

    for(auto i : G[nod]) {

        if(!R[i]) {
            R[i] = nod;
            L[nod] = i;
            return true;
        }

    }

    for(auto i : G[nod]) {
        if(pairup(R[i])) {
            R[i] = nod;
            L[nod] = i;
            return true;
        }
    }
    return false;
}

int main() {

    //freopen("file.in", "r", stdin);
    //freopen("file.out", "w", stdout);

    cin.tie(0); cout.tie(0);
    ios_base::sync_with_stdio(false);

    cin >> N;

    for(int i = 1; i <= N; i++) {
        cin >> s[i];
        m[s[i]] = i;
    }

    for(int i = 1; i <= N; i++) {

        for(int k = 0; k < s[i].size(); k++) {

            for(int l = k + 1; l < s[i].size(); l++){

                swap(s[i][k], s[i][l]); 

                if(m[s[i]]) {
                    G[m[s[i]]].push_back(i);
                    G[i].push_back(m[s[i]]);
                }

                swap(s[i][k], s[i][l]);
            }

        }

    }

    
    bool ok = true;
    while(ok) {
        ok = false;

        for(int i = 1; i <= N; i++) {
            v[i] = 0;
        }
        
        for(int i = 1; i <= N; i++) {
            if(!L[i]) {
                if(pairup(i)) ok = true;
            }
        }

    }   

    int ans = 0;
    for(int i = 1; i <= N; i++) {
        if(L[i]) ans++;
        //cout << i << ' ' << L[i] << ' ' << R[i] << '\n';
    }

    cout << N - ans / 2;

}

//Source: https://www.pbinfo.ro/probleme/3085/fsecv
#include <bits/stdc++.h>
using namespace std;

const int B = 316;
const int MAX = 100000;
const int AN = 100000;
int N, Q;
int A[MAX + 3];

struct Query{
    int le, ri, k, idx;
}queries[MAX + 3];

int ans[MAX + 3];

struct Cutie{
    int fr[2 * MAX + 3];
    int frfr[2 * MAX + 3];

    void add(int x) {
        x = x + AN;
        frfr[fr[x]]--;
        fr[x]++;
        frfr[fr[x]]++;
    }

    void remove(int x) {
        x = x + AN;
        frfr[fr[x]]--;
        fr[x]--;
        frfr[fr[x]]++;
    }

    int query(int K) {
        return frfr[K];
    }
}C;

int main() {
    freopen("fsecv.in", "r", stdin);
    freopen("fsecv.out", "w", stdout);
    
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    cout.tie(0);

    cin >> N >> Q;

    for(int i = 1; i <= N; i++) {
        cin >> A[i];
    }

    for(int i = 1; i <= Q; i++) {
        cin >> queries[i].le >> queries[i].ri >> queries[i].k;
        queries[i].idx = i;
    }

    sort(queries + 1, queries + Q + 1, [](Query a, Query b) {
        if(a.le / B < b.le / B) return true;
        if(a.le / B == b.le / B && a.ri < b.ri) return true;
        return false;
    });

    int i = 1, j = 0;

    for(int q = 1; q <= Q; q++) {
        auto &query = queries[q];

        while(i < query.le) {
            C.remove(A[i]);
            i++;
        }

        while(i > query.le) {
            i--;
            C.add(A[i]);
        }

        while(j < query.ri) {
            j++;
            C.add(A[j]);
        } 

        while(j > query.ri) {
            C.remove(A[j]);
            j--;
        }
        //cout << query.le << ' ' << query.ri << ' ' << query.idx << '\n';
        // for(int l = 1; l <= N; l++) {
        //     cout << C.frfr[l] << ' ';
        // }
        // cout << '\n';
        ans[query.idx] = C.query(query.k);
    }

    for(int i = 1; i <= Q; i++) {
        cout << ans[i] << '\n';
    }
}

#include <bits/stdc++.h>
using namespace std;

const int MAX = 2e5;
int N, Q;
int A[MAX + 3];

struct node{

    node *nxt[2];
    int time;

    node() {
        time = 0;
        nxt[0] = nxt[1] = NULL;
    }


    node * clone(node *nd) {
        node *ans = new node();   

        if(nd != NULL) {
            ans->time = nd->time;
            ans->nxt[0] = nd->nxt[0];
            ans->nxt[1] = nd->nxt[1];
        }

        return ans;
    }



};

node * v[MAX + 3];
node *last;

void insert(int x, int time) {

    last = last->clone(last);
    v[time] = last;
    v[time]->time = time;
    node * nd = v[time];

    for(int bit = 29; bit >= 0; bit--) {
        int marked = ((x >> bit) & 1);
        node *&child = nd->nxt[marked];
        child = child->clone(child);
        child->time = time;
        nd = child;

    }

}

int query(int l, int r, int x) {

    node *nd = v[r];

    int ans = 0;

    for(int bit = 29; bit >= 0; bit--) {
        int marked = !((x >> bit) & 1);
        if(nd->nxt[marked] != NULL && nd->nxt[marked]->time >= l) {
            nd = nd->nxt[marked];
            ans += (marked << bit);
        }
        else {
            if(nd->nxt[!marked]){ 
            nd = nd->nxt[!marked];
            ans += (!marked << bit);
			}
        }

    }


    return ans;
}

int spxor[MAX + 3];

int main() {
    //freopen("file.in", "r", stdin);
    //freopen("file.out", "w", stdout);

    cin.tie(0); cout.tie(0);
    ios_base::sync_with_stdio(false);

    cin >> N >> Q;

    for(int i = 1; i <= N; i++) {
        cin >> A[i];

        insert(A[i], i);

    }

    for(int i = 1; i <= N; i++) {
        spxor[i] = spxor[i - 1] xor A[i];
    }   

    for(int i = 1; i <= Q; i++) {
        
        int le, ri; cin >> le >> ri;

        int ans = spxor[ri] xor spxor[le - 1];
        ans ^= query(le, ri, ans);
        cout << ans << '\n';
    }

}
//https://kilonova.ro/problems/456

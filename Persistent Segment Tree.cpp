#include <bits/stdc++.h>
using namespace std;
 
const int MAX = 3e5;
 
int A[MAX + 3];
 
 
struct nod{
 
    nod *l, *r;
    long long sum = 0;
 
    nod() {
        sum = 0;
        l = NULL;
        r = NULL;
    }
 
};
 
vector<nod*>roots;
 
long long ans = 0;
 
void build(nod *root, int st, int dr) {
    //cerr << st << ' ' << dr << '\n';
    if(st == dr) {
        root->sum = A[st];
        return ;
    }
 
    int mid = (st + dr) / 2;
    root->l = new nod;
    root->r = new nod;
 
    build(root->l, st, mid);
    build(root->r, mid + 1, dr);
 
    root->sum = root->l->sum + root->r->sum;
 
}
 
void update(nod *prevroot, nod *root, int st, int dr, int poz, int val) {
 
    if(st == dr) {
        root->sum = val;
        return ;
    }   
 
    int mid = (st + dr) / 2;
    if(poz <= mid) {
 
        root->l = new nod;
        root->r = prevroot->r;
 
        update(prevroot->l, root->l, st, mid, poz, val);
    }
    else {
        root->l = prevroot->l;
        root->r = new nod;
 
        update(prevroot->r, root->r, mid + 1, dr, poz, val);
    }
 
    root->sum  = root->l->sum + root->r->sum;
 
}
 
void query(nod *root, int st, int dr, int le, int ri) {
 
    if(le <= st && dr <= ri) {
        ans += root->sum;
        return;
    }
    int mid = (st + dr) / 2;
 
    if(le <= mid) {
        query(root->l, st, mid, le, ri);
    }
 
    if(ri > mid) {
        query(root->r, mid + 1, dr, le, ri);
    }
 
}
 
int N, Q;
 
int main() {
    //freopen("file.in", "r", stdin);
    //freopen("file.out", "w", stdout);
 
    cin.tie(0); cout.tie(0);
    ios_base::sync_with_stdio(false);
 
    cin >> N >> Q;
 
    for(int i = 1; i <= N; i++) {
        cin >> A[i];
    }
 
    nod *root1 = new nod;
    build(root1, 1, N);
 
    roots.push_back(root1);
 
    for(int i = 1; i <= Q; i++) {
        int tip;
        cin >> tip;
 
        if(tip == 1) {
            int k, a, x;
            cin >> k >> a >> x;
            nod *newroot = new nod;
            update(roots[k - 1], newroot, 1, N, a, x);
 
            roots[k - 1] = newroot;
        }
 
        if(tip == 2) {
            int a, b, k;
            cin >> k >> a >> b;
            ans = 0;
            query(roots[k - 1], 1, N, a, b);
            cout << ans << '\n';
        }
 
        if(tip == 3) {
            int k; cin >> k;
            roots.push_back(roots[k - 1]);
        }
    }
 
}

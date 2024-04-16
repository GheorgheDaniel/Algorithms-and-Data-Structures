//Heavy Light Decomposition
#include <bits/stdc++.h>
using namespace std;
 
/*
https://cses.fi/problemset/task/2134/
*/

const int MAX = 2 * 1e5;
int N, Q;
int V[MAX + 3];
vector<int>tree[MAX + 3];
//nivel
int level[MAX + 3];
//greutate
int sz[MAX + 3];
//imi tin heavy child pentru fiecare nod
int heavychild[MAX + 3];
//indicii de intrare si iesire in parcurgerea dfs
int tin[MAX + 3];
int tout[MAX + 3];
//vectorul liniarizat dupa dfs cu proritate
int lnz[MAX + 3];
//cel mai de sus nod din lantul de heavy nodes
int topheavy[MAX + 3];
int x, y;
int timer;
//up[i][j] -> Al 2^j-lea stramos al lui i
int up[MAX + 3][24];
 
int maxglobal;
 
 
class SegTree{
    private:
        int aint[4 * MAX + 20] = {0};
    
    public:
 
    void build(int nod, int st, int dr) {
        if(st == dr) {
            aint[nod] = V[lnz[st]];
        }
        else{
            int mid = (st + dr) / 2;
            build(2 * nod, st, mid);
            build(2 * nod + 1, mid + 1, dr);
            aint[nod] = max(aint[2 * nod], aint[2 * nod + 1]);
        }
    }
 
    void update(int nod, int st, int dr, int poz, int val) {
        if(st == dr) {
            aint[nod] = val;
        }
        else {
            int mid = (st + dr) / 2;
            if(poz <= mid) {
                update(2 * nod, st, mid, poz, val);
            }
            else {
                update(2 * nod + 1, mid + 1, dr, poz, val);
            }
            aint[nod] = max(aint[2 * nod], aint[2 * nod + 1]);
        }
    }
 
    void query(int nod, int st, int dr, int le, int ri) {
        if(le <= st && dr <= ri) {
            maxglobal = max(maxglobal, aint[nod]);
        }
        else {
            int mid = (st + dr) / 2;
            if(le <= mid) {
                query(2 * nod, st, mid, le, ri);
            }
            if(ri > mid) {
                query(2 * nod + 1, mid + 1, dr, le, ri);
            }
        }
    }
}A;
 
 
void dfsh(int nod, int parent = -1) {
    int dim = 0, child = 0;
    for(auto i : tree[nod]) {
        if(i != parent) {
            if(dim < sz[i]) {
                dim = sz[i];
                child = i;
            }
            dfsh(i, nod);
        }
    }
 
    heavychild[nod] = child;
}
 
void dfsz(int nod, int parent = -1) {
    sz[nod] = 1;
    for(auto i : tree[nod]) {
        if(i != parent) {
            dfsz(i, nod);
            sz[nod] += sz[i];
        }
    }
}
 
void dfs(int nod, int parent = -1) {
    for(auto i : tree[nod]) {
        if(i != parent) {
            level[i] = level[nod] + 1;
            dfs(i, nod);
        }
    }
} 
 
void dfscomp(int nod, int parent = -1) {
    tin[nod] = ++timer;
 
    if(heavychild[nod]) {
        topheavy[heavychild[nod]] = topheavy[nod];
        dfscomp(heavychild[nod], nod);
    } 
 
    for(auto i : tree[nod]) {
        if(i != parent && i != heavychild[nod]) {
            dfscomp(i, nod);
        }
    }
 
    tout[nod] = timer;
}   
 
int lca(int a, int b) {
    if(level[a] < level[b]) {
        swap(a, b);
    }
    int l = level[a] - level[b];
    for(int j = 20; j >= 0; j--){
        if(l & (1 << j)) {
            a = up[a][j];
            l -= (1 << j);
        }
    } 
    
    if(a == b) return a;
 
    for(int j = 20; j >= 0; j--) {
        if(up[a][j] != up[b][j]) {
            a = up[a][j];
            b = up[b][j];
        }
    }
    return up[a][0];
}
 
void buildhld() {
    //marcare nivele
    dfs(1);
    //marcare greutati
    dfsz(1);
    //calculare heavychild
    dfsh(1);
    for(int i = 1; i <= N; i++) {
        topheavy[i] = i;
    }
    //marcare indici in parcurgerea dfs cu prioritate pentru 
    //nodurile heavy
    dfscomp(1);
    for(int i = 1; i <= N; i++) {
        lnz[tin[i]] = i;
    }
}
 
int calc(int a, int LCA) {
    int maxx = 0;
    while(level[topheavy[a]] > level[LCA]) {
        maxglobal = 0;

        if(topheavy[a] == a) maxglobal = V[a];
        else A.query(1, 1, N, tin[topheavy[a]], tin[a]);
        maxx = max(maxx, maxglobal);
        a = up[topheavy[a]][0];
    }
    maxglobal = 0;
    A.query(1, 1, N, tin[LCA], tin[a]);
    maxx = max(maxx, maxglobal);
 
    return maxx;
}
 
void queryheavy(int a, int b) {
    int LCA = lca(a, b);
    swap(a, b);
    //computez maximul pentru lantul din stanga LCA-ului
    int maxx = 0;
    maxx = max(maxx, calc(a, LCA));
    //computez maximul pentru lantul din dreapta LCA-ului
    maxx = max(maxx, calc(b, LCA));
    cout << maxx << ' ';
}
 
void dfslca(int nod, int parent = -1) {
    for(auto i : tree[nod]) {
        if(i != parent) {
            up[i][0] = nod;
            dfslca(i, nod);
        }
    }
} 
 
int main() {
    //freopen("file.in", "r", stdin);
    //freopen("file.out", "w", stdout);
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(false);
    cin >> N >> Q;
    for(int i = 1; i <= N; i++) {
        cin >> V[i];
    }
    
    for(int i = 1; i < N; i++) {
        cin >> x >> y;
        tree[x].push_back(y);
        tree[y].push_back(x);
    }
 
    buildhld();
    A.build(1, 1, N);
    dfslca(1);

 
    for(int i = 1; i <= 20; i++) {
        for(int j = 1; j <= N; j++) {
            up[j][i] = up[up[j][i - 1]][i - 1];
        }
    }
 
 
    for(int i = 1; i <= Q; i++) {
        //compute queries
        int type; cin >> type;
        if(type == 1) {
            int nod, val;
            cin >> nod >> val;
            A.update(1, 1, N, tin[nod], val);
            V[nod] = val;
        }
        if(type == 2) {
            int a, b;
            cin >> a >> b;
            queryheavy(a, b);
        }
    }
} 

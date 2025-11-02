//https://www.infoarena.ro/job_detail/3284735?action=view-source
#include <bits/stdc++.h>
using namespace std;

const int MAX = 200;
int N;

int cp[MAX + 3][MAX + 3];
int flux[MAX + 3][MAX + 3];

vector<int>G[MAX + 3];
int v[MAX + 3];
int parent[MAX + 3];

bool bfs() {

    queue<int>q;
    q.push(0);
    v[0] = 1;
    while(!q.empty()) {

        for(auto i : G[q.front()]) {

            if(v[i] == 0 && cp[q.front()][i] - flux[q.front()][i] > 0) {
                q.push(i);
                v[i] = 1;
                parent[i] = q.front();
            }
    
        }
        q.pop();
    }

    return v[2 * N + 1];

}

void flow() {

    int totalflux = 0;

    while(bfs()) {

        int nod = 2 * N + 1;
        int maxflux = INT_MAX;
        while(nod != 0) {
            maxflux = min(maxflux, cp[parent[nod]][nod] - flux[parent[nod]][nod]);
            nod = parent[nod];           
        }

        nod = 2 * N + 1;
        while(nod != 0) {
            flux[parent[nod]][nod] += maxflux;
            flux[nod][parent[nod]] -= maxflux;
            nod = parent[nod];

        }

        for(int i = 0; i <= 2 * N + 1; i++) v[i] = 0;
        totalflux += maxflux;
    }

    cout << totalflux << '\n';

    for(int i = 1; i <= N; i++) {
        for(int j = N + 1; j <= 2 * N; j++) {
    
            if(flux[i][j] == 1) {
                //cout << flux[i][j] << ' ' << cp[i][j] << ' ';
                cout << i << ' ' << j - N << '\n';
            }

        }
    }

}

int main() {
    freopen("harta.in", "r", stdin);
    freopen("harta.out", "w", stdout);

    cin.tie(0); cout.tie(0);
    ios_base::sync_with_stdio(false);

    cin >> N;

    for(int i = 1; i <= N; i++) {
        int in, out;
        cin >> out >> in;

        cp[0][i] = out;
        cp[N + i][2 * N + 1] = in;

        G[0].push_back(i);
        G[i].push_back(0);

        G[N + i].push_back(2 * N + 1);
        G[2 * N + 1].push_back(N + i);
    }   

    for(int i = 1; i <= N; i++) {

        for(int j = N + 1; j <= 2 * N; j++) {
            if(i == j - N) continue;
            G[i].push_back(j);
            G[j].push_back(i);
            cp[i][j] = 1;
        }

    }   

    flow();

}

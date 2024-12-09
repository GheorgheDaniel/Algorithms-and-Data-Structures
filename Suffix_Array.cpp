//https://codeforces.com/contest/1968/problem/G1

#include <bits/stdc++.h>
using namespace std;

const int MAX = 3 * 1e5;
const int MOD = 1e9 + 7;
int N;
int l, r;
string s;
int T; 

int s1[19][MAX + 3];
int lcp[MAX + 3];

int ans1[MAX + 3];

struct tip{
    int p1, p2, idx;
};

 
vector<pair<int, int>>ans;
int p;
 
bool cmp(tip a, tip b) {
    if(a.p1 < b.p1) return true;
    if(a.p1 == b.p1 && a.p2 < b.p2) return true;
    
    return false;
}
 
void buildSUFFIXARRAY(string&s)
{      
    
    for(int p = 0; (1 << (p)) < 2 * s.size(); p++) {
        for(int j = 0; j < N + 1; j++) {
            s1[p][j] = 0;
        }
    }

    for(p = 0; (1 << (p)) < 2 * s.size(); p++) {
        vector<tip>a;
        for(int j = 0; j < s.size(); j++) {
            //if(s[j] == '$') continue;
            if(p == 0) a.push_back({(int)s[j], 0, j}); 
            else a.push_back({s1[p - 1][j], s1[p - 1][j + (1 << (p - 1))] , j});
 
        } 
 
        sort(a.begin(), a.end(), cmp);
        int cnt = 0;
        for(int j = 0; j < s.size(); j++) {
            //if(s[j] == '$') continue;
            if(j == 0 || (a[j].p1 == a[j - 1].p1 && a[j].p2 == a[j - 1].p2)) {
                s1[p][a[j].idx] = cnt;
            }
            else {
                cnt++;
                s1[p][a[j].idx] = cnt;
            }
        }
    }
 
    p--;
 
    for(int i = 0; i < s.size(); i++) {
        ans.push_back({s1[p][i], i});
        //cout << ans.back().first << ' ' << ans.back().second << '\n';
    }
    sort(ans.begin(), ans.end());
    
}

void lcp1() {
    for(int i = 0; i < (int)ans.size() - 1; i++) {
        
        int fi = ans[i].second;
        int se = ans[i + 1].second;
 
        int len = 0;
        for(int p1 = p; p1 >= 0; p1--)
        {
            if(s1[p1][fi] == s1[p1][se]) {
                len += (1 << p1);
                fi += (1 << p1);
                se += (1 << p1);
            }
        }

        lcp[i] = len;

        //cout << len << ' ' << ans[i - 1].second << ' ' << ans[i].second << '\n';
        //cout << fi << ' ';
    
    }
}

int F(int x) {

    vector<int>aux; 
    int first = 0;
    for(int i = 0; i < ans.size(); i++) {
        if(ans[i].second == 0) {
            first = i;
        }
    }
    int minn = lcp[first];
    int i = first + 1;
    while(minn >= x && i < ans.size()) {
        aux.push_back(ans[i].second);
        minn = min(minn, lcp[i]);
        i++;
        
    }
    minn = lcp[first - 1];
    i = first - 1;
    while(minn >= x && i >= 0) {
        aux.push_back(ans[i].second);
        i--;
        minn = min(minn, lcp[i]);
    }

    int ant = 0;
    int cnt = 1;

    //for(auto i : aux) cout << i << ' ';
    //cout << '\n';
    sort(aux.begin(), aux.end());
    for(auto i : aux) {

        if(i >= ant + x && i + x - 1 < N) {
            cnt++;
            ant = i;
            //cout << i << ' ';
        }

    }
    return cnt;
}

void test_case() {
    cin >> N >> l >> r;

    cin >> s;

    buildSUFFIXARRAY(s);
    lcp1();
    int st = 1, dr = N, best = 0;
    while(st <= dr) {
        int mid = (st + dr) / 2;
        //cout << mid << ' ' << F(mid) << '\n';
        if(F(mid) >= l) {
            st = mid + 1;
            best = mid;
        }   
        else dr = mid - 1;
    }
    ans.clear();
    cout << best << '\n';

}

int main() {
    //freopen("file.in", "r", stdin);
    //freopen("file.out", "w", stdout);
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(false);
    cin >> T;
    while(T--) {
        test_case();
    }
}

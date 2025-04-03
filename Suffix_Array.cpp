//https://cses.fi/problemset/task/2106/
#include <bits/stdc++.h>
using namespace std;
 
const int MAX = 4e5;
string s;
int s1[19][MAX + 3];
 
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
    
    for(p = 0; (1 << (p)) < 2 * s.size(); p++) {
        vector<tip>a;
        for(int j = 0; j < s.size(); j++) {
            
            if(p == 0) a.push_back({(int)s[j], 0, j}); 
            else a.push_back({s1[p - 1][j], s1[p - 1][j + (1 << (p - 1))] , j});
 
        } 
 
        sort(a.begin(), a.end(), cmp);
        int cnt = 0;
        for(int j = 0; j < s.size(); j++) {
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
        //cout << ans.back().second << '\n';
    }
    sort(ans.begin(), ans.end());
    
}
int main() {
    //freopen("file.in", "r", stdin);
    //freopen("file.out", "w", stdout);
    cin.tie(0); cout.tie(0);
    ios_base::sync_with_stdio(false);
    cin >> s;
 
    buildSUFFIXARRAY(s);
    int maxx = 0, poz = 0;
 
    for(int i = 1; i < (int)ans.size(); i++) {
        
        int fi = ans[i - 1].second;
        int se = ans[i].second;
 
        int len = 0;
        for(int p1 = p; p1 >= 0; p1--)
        {
            if(s1[p1][fi] == s1[p1][se]) {
                len += (1 << p1);
                fi += (1 << p1);
                se += (1 << p1);
            }
        }
        //cout << len << ' ' << ans[i - 1].second << ' ' << ans[i].second << '\n';
        //cout << fi << ' ';
        if(len > maxx) {
            maxx = len;
            poz = ans[i].second;
        }
    }
    if(maxx == 0) cout << -1;
    for(int i = poz; i < min(poz + maxx, (int)s.size()); i++) {
        cout << s[i];
    }
}

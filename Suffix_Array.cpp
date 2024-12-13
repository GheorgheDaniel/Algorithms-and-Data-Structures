#include <bits/stdc++.h>
using namespace std;
 
int N;
string s, fb;
const int MAX = 3 * 1e5;
struct tip{
    int x, y, idx;
};
 
int le[MAX + 3], ri[MAX + 3];
 
bool cmp(tip a, tip b) {
    if(a.x < b.x) return true;
    if(a.x == b.x && a.y < b.y) return true;
    return false;
}
 
class sufarray{
    int sa[MAX + 3][21];    
    int p1;
    
 
    public: 
    vector<pair<int, int>> order(string &s) {
        int p;
        for(p = 0; (1 << p) <= 2 * N; p++) {
            vector<tip>a1;
            for(int i = 0; i < N; i++) {
                if(p == 0) {a1.push_back({s[i], 0, i});}
                else 
                if(i + (1 << (p - 1)) > 3 * 1e5) {a1.push_back({sa[i][p - 1], 0, i});}
                else {a1.push_back({sa[i][p - 1], sa[i + (1 << (p - 1))][p - 1], i});}
            }
 
            sort(a1.begin(), a1.end(), cmp);
 
            int j = 1;
            for(int i = 0; i < a1.size(); i++) {
                
                if(i == 0) {sa[a1[i].idx][p] = j;}
                else {
                    
                    if(a1[i].x == a1[i - 1].x && a1[i].y == a1[i - 1].y) {
                        sa[a1[i].idx][p] = j;
                    }
                    else {
                        j++;
                        sa[a1[i].idx][p] = j;   
                    }
 
                }
            }
 
        }   
        p--;
        p1 = p;
        vector<pair<int, int>>ans;
        for(int i = 0; i < N; i++) {
            if(fb[i] != '1') {  
                ans.push_back({sa[i][p ], i});
            }
        }
 
        //cout << ans.size() << '\n';
        return ans;
 
    } 
 
    vector<int> lcp(string &s, vector<pair<int, int>>&ord) {
        vector<int>ans;
        ans.push_back(-1);
 
        sort(ord.begin(), ord.end());
 
        for(int i = 0; i < (int)ord.size() - 1; i++) {
            
            int le = ord[i].second;
            int ri = ord[i + 1].second;
            int len = 0;
            for(int p = p1; p >= 0; p--) {
                if(le + (1 << p) > 2 * 1e5 || ri + (1 << p) > 2 * 1e5) continue;
                if(sa[le][p] == sa[ri][p]) {
                    le += (1 << p);
                    ri += (1 << p);
                    len += (1 << p);
                }
 
            }
 
            ans.push_back(len);
        }
        ans.push_back(-1);
        return ans; 
    }
 
 
}C;
 
int main() {
    //freopen("file.in", "r", stdin);
    //freopen("file.out", "w", stdout);
 
    cin.tie(0); cout.tie(0);
    ios_base::sync_with_stdio(false);
 
    cin >> N;
    cin >> s;
    cin >> fb;
 
    reverse(s.begin(), s.end());
    reverse(fb.begin(), fb.end());

    vector<pair<int, int>>ans1 = C.order(s);
    vector<int>lcp = C.lcp(s, ans1);
    vector<int>st;
    st.push_back(0);
    for(int i = 1; i < (int)lcp.size() - 1; i++) {
 
        while(lcp[st.back()] >= lcp[i]) {
            st.pop_back();
        }
        le[i] = st.back();
        st.push_back(i);
    }
 
    st.clear();
    st.push_back((int)lcp.size() - 1);
 
    for(int i = (int)lcp.size() - 2; i >= 1; i--) {
 
        while(lcp[st.back()] >= lcp[i]) {
            st.pop_back();
        }
        ri[i] = st.back();
        st.push_back(i);
 
    }
 
    long long maxx = 0;
    for(int i = 1; i < lcp.size() - 1; i++) {
        maxx = max(maxx, 1LL * lcp[i] * (ri[i] - le[i]));
    }
    fb.push_back('0');
    int i = 0;
    while(fb[i] == '1') i++;
    cout << max((long long)s.size() - i, maxx);
}

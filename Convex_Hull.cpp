//https://infoarena.ro/job_detail/3241967?action=view-source
#include <bits/stdc++.h>
using namespace std;

const int MAX = 2 * 1e5;

struct point{
    double x, y;
}A[MAX + 3];

int N;  
vector<int>s;
vector<int>s1;
bool v[MAX + 3];
double F(point O, point A, point B) {
    return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x); 
}

vector<int>s3;

bool cmp(point a, point b) {
    if(a.x < b.x) return true;
    if(a.x == b.x) return a.y < b.y;
    return false;
}

int main() {
    freopen("infasuratoare.in", "r", stdin);
    freopen("infasuratoare.out", "w", stdout);

    cin >> N;
    for(int i = 1; i <= N; i++) {
        cin >> A[i].x >> A[i].y;
    }
    
    sort(A + 1, A + N + 1, cmp);

    for(int i = 1; i <= N; i++) {
        while(s.size() >= 2 && F(A[s[s.size() - 2]], A[s[s.size() - 1]], A[i]) <= 0) {
            s.pop_back();
        }
        s.push_back(i);
    }


    for(int i = N; i >= 1; i--) {
        while(s1.size() >= 2 && F(A[s1[s1.size() - 2]], A[s1[s1.size() - 1]], A[i]) <= 0) {
            s1.pop_back();
        }

        s1.push_back(i);
    }   

    cout << setprecision(12) << fixed;
    cout << s.size() + s1.size() - 2 << '\n';
    for(int i = 1; i < s.size(); i++) {
        cout << A[s[i]].x << ' ' << A[s[i]].y << '\n';
    }

    for(int i = 1; i < s1.size(); i++) {
        cout << A[s1[i]].x << ' ' << A[s1[i]].y << '\n';
    }
}   

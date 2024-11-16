//https://www.infoarena.ro/job_detail/3257236?action=view-source
#include <bits/stdc++.h>
using namespace std;

const int ALPHA = 2;
const int MAX = 1e5;
int N;
long long A[MAX + 3];
int step;
int l, r;
int leftaux;

string matching;

struct Trie{

    struct Node{
        int cnt;
        Node *next[ALPHA];

        Node() {
            cnt = 0;
            for(int i = 0; i < ALPHA; i++) {
                next[i] = NULL;
            }
        }
    };

    Node *root;

    Trie() {
        root = new Node;
    }

    void insert(string &s) {

        Node *curr = root;
        for(auto it : s) {
            if(curr->next[it - '0'] == NULL) {
                curr->next[it - '0'] = new Node;
            }
            curr = curr->next[it - '0'];
        }
        curr->cnt = step;
    }
    void find(string &s) {
        Node *curr = root;
        for(int it = 0; it < s.size(); it++) {
            if(curr->next[!(s[it] - '0')] != NULL) {
                curr = curr->next[!(s[it] - '0')];
                matching.push_back((!(s[it] - '0')) + '0');
            }
            else {
                curr = curr->next[s[it] - '0'];
                matching.push_back(s[it]);
            }
        }
        leftaux = curr->cnt;
    }
}T;
string s;
int main() {
    freopen("xormax.in", "r", stdin);
    freopen("xormax.out", "w", stdout);

    cin >> N;

    
    for(int i = 0; i <= 31; i++) {
        s.push_back('0');
    }

    T.insert(s);


    long long ans = -1;
    long long xorr = 0;
    for(int i = 1; i <= N; i++) {
        step = i;
        cin >> A[i];
        xorr = xorr xor A[i];
        s.clear();
        for(int j = 31; j >= 0; j--) {
            if((xorr & (1 << j)))
            s.push_back('1');
            else s.push_back('0');
        }
        T.find(s);

        long long aux = 0;
        int jj = 0;
        for(int j = 31; j >= 0; j--) {
            if(matching[j] == '1') {
                aux += (1 << jj);
            }
            jj++;
        }

        T.insert(s);

        if(ans < (aux ^ xorr)) {
            ans = (aux ^ xorr);
            l = leftaux;
            r = i;
        }
        matching.clear();
        
    }

    cout << ans << ' ' << l + 1 << ' ' << r;
}

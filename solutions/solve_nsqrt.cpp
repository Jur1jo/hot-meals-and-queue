#include <iostream>
#include <vector>
#include <algorithm>
 
#define all(a) a.begin(), a.end()
 
using namespace std;
 
const int K = 650;
const int N = 1e5 + K + 228;
const int INF = 1e9 + 228;
 
vector<int> records[N / K];
int add[N / K];
int A[N];
 
int n;
 
void build(int k) {
    int last_max = -INF;
    records[k].clear();
    for (int i = min((k + 1) * K - 1, n - 1); i >= k * K; --i) {
        if (A[i] > last_max) {
            records[k].push_back(A[i]);
            last_max = A[i];
        }
    }
}
 
int get(int l, int r) {
    int last_max = -INF;
    int ans = r - l + 1;
    while (r >= l) {
        if (r % K == K - 1 && r - K + 1 >= l) {
            ans -= (records[r / K].end() - upper_bound(all(records[r / K]), last_max - add[r / K]));
            if (records[r / K].size())
                last_max = max(last_max, records[r / K].back() + add[r / K]);
            r -= K;
        } else {
            if (A[r] + add[r / K] > last_max)
                last_max = A[r] + add[r / K], --ans;
            --r;
        }
    }
    return ans;
}
 
void update(int l, int r, int val) {
    while (l < r) {
        if (l % K == 0 && l + K <= r) {
            add[l / K] += val, l += K;
        } else {
            int nxt = min(l - l % K + K, r);
            for (int j = l; j < nxt; ++j)
                A[j] += val;
            build(l / K);
            l = nxt;
        }
    }
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> A[i];
        A[i] -= i;
    }
    for (int i = 0; i < n; i += K)
        build(i / K);
    cout << get(0, n - 1) << '\n';
 
    int q;
    cin >> q;
    while (q--) {
        int t, l, r;
        cin >> t >> l >> r;
        if (t == 1) {
            cout << get(l - 1, r - 1) << '\n';
        } else {
            int val;
            cin >> val;
            update(l - 1, r, val);
        }
    }
}

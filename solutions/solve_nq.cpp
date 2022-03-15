#include <iostream>
#include <vector>
 
using namespace std;
 
int solve(int n, vector<long long> a) {
    int val = a.back();
    int ans = 0;
    for (int i = n - 2; i >= 0; --i) {
        if (a[i] < val)
            --val, ++ans;
        else
            val = a[i];
    }
    return ans;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    int n;
    cin >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; ++i)
        cin >> a[i];
    cout << solve(n, a) << '\n';
    int q;
    cin >> q;
    while (q--) {
        int t, l, r;
        cin >> t >> l >> r;
        if (t == 1) {
            vector<long long> b;
            for (int i = l - 1; i < r; ++i)
                b.push_back(a[i]);
            cout << solve(b.size(), b) << '\n';
        } else {
            int val;
            cin >> val;
            for (int i = l - 1; i < r; ++i)
                a[i] += val;
        }
    }
}

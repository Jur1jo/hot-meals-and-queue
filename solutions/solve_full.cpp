#include <iostream>
#include <vector>
 
using namespace std;
 
const int N = (1 << 19);
 
pair<int, int> t[2 * N]; // Cnt, maximum
int mod[2 * N];
bool its_list[2 * N];
 
void push(int v) {
    t[v * 2 + 1].second += mod[v];
    t[v * 2].second += mod[v];
    mod[v * 2 + 1] += mod[v];
    mod[v * 2] += mod[v];
    mod[v] = 0;
}
 
int query(int v, int w) {
    if (its_list[v]) {
        if (t[v].second > w)
            return 1;
        return 0;
    }
 
    push(v);
    int r = v * 2, l = v * 2 + 1;
    if (t[r].second <= w)
        return query(l, w);
    else
        return query(r, w) + t[v].first - t[r].first;
}
 
void update(int v, int l, int r, int L, int R, int val) {
    if (R <= l || r <= L)
        return;
    if (L <= l && r <= R) {
        t[v].second += val;
        mod[v] += val;
        return;
    }
 
    push(v);
    int m = (l + r) / 2;
    update(v * 2 + 1, l, m, L, R, val);
    update(v * 2, m, r, L, R, val);
    t[v].first = t[v * 2].first + query(v * 2 + 1, t[v * 2].second);
    t[v].second = max(t[v * 2 + 1].second, t[v * 2].second);
}
 
void build(int v, int l, int r, vector<int> &a) {
    if (r - l == 1) {
        its_list[v] = 1;
        t[v] = make_pair(1, a[l]);
        return;
    }
 
    int m = (l + r) / 2;
    build(v * 2 + 1, l, m, a);
    build(v * 2, m, r, a);
    t[v].first = t[v * 2].first + query(v * 2 + 1, t[v * 2].second);
    t[v].second = max(t[v * 2 + 1].second, t[v * 2].second);
}
 
pair<int, int> get(int v, int l, int r, int L, int R, int max_val) { // ans, max_val
    if (R <= l || r <= L)
        return {0, max_val};
    if (L <= l && r <= R)
        return {query(v, max_val), max(t[v].second, max_val)};
 
    push(v);
    int m = (l + r) / 2;
    auto z1 = get(v * 2, m, r, L, R, max_val);
    auto z2 = get(v * 2 + 1, l, m, L, R, z1.second);
    return {z1.first + z2.first, max(z1.second, z2.second)};
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        a[i] -= i;
    }
    int q;
    cin >> q;
    build(1, 0, n, a);
    cout << n - get(1, 0, n, 0, n, -n).first << '\n';
 
    while (q--) {
        int t, l, r;
        cin >> t >> l >> r;
        if (t == 1) {
            cout << r - l + 1 - get(1, 0, n, l - 1, r, -n).first << '\n';
        } else {
            int val;
            cin >> val;
            update(1, 0, n, l - 1, r, val);
        }
    }
}

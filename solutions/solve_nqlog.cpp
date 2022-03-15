#include <iostream>
#include <vector>
 
using namespace std;
 
struct SegTree {
    vector<int> t, mod;
    int sz = 1, n;
 
    void build(int v, int l, int r, vector<int> &a) {
        if (r - l == 1) {
            t[v] = a[l];
            return;
        }
 
        int m = (l + r) / 2;
        build(v * 2 + 1, l, m, a);
        build(v * 2 , m, r, a);
        t[v] = min(t[v * 2 + 1], t[v * 2]);
    }
 
    void push(int v) {
        t[v * 2 + 1] += mod[v];
        t[v * 2] += mod[v];
        mod[v * 2 + 1] += mod[v];
        mod[v * 2] += mod[v];
        mod[v] = 0;
    }
 
    int get_first_zero(int v, int l, int r) {
        if (r <= l || t[v] > 0)
            return -1;
        if (r - l == 1)
            return l;
 
        push(v);
        int m = (l + r) / 2;
        int res = get_first_zero(v * 2, m, r);
        if (res == -1)
            res = get_first_zero(v * 2 + 1, l, m);
        return res;
    }
 
    int get_first() {
        return get_first_zero(1, 0, n);
    }
 
    int get_val(int v, int l, int r, int L, int R) {
        if (r <= L || R <= l)
            return 1e9;
        if (L <= l && r <= R)
            return t[v];
 
        push(v);
        int m = (l + r) / 2;
        return min(get_val(v * 2 + 1, l, m, L, R), get_val(v * 2, m, r, L, R));
    }
 
    void update(int v, int l, int r, int L, int R, int val) {
        if (r <= L || R <= l)
            return;
        if (L <= l && r <= R) {
            t[v] += val;
            mod[v] += val;
            return;
        }
 
        push(v);
        int m = (l + r) / 2;
        update(v * 2 + 1, l, m, L, R, val);
        update(v * 2, m, r, L, R, val);
        t[v] = min(t[v * 2 + 1], t[v * 2]);
    }
 
    void update(int l, int r, int val) {
        update(1, 0, n, l, r, val);
    }
 
    int get_val(int l, int r) {
        return get_val(1, 0, n, l, r);
    }
 
    SegTree(int _n, vector<int> a) {
        while (sz <= 2 * _n)
            sz *= 2;
        n = _n;
        t.resize(sz);
        mod.resize(sz);
        build(1, 0, n, a);
    }
};
 
int solve(int n, vector<int> a) {
    SegTree val(n, a);
    vector<int> tmp(n);
    for (int i = 0; i < n; ++i)
        tmp[i] = i;
    SegTree num(n, tmp);
    int pos = val.get_first_zero(1, 0, n);
    int ans = 0;
    int now_size = n;
    while (pos != -1 && now_size > -2) {
        // cout << pos << ' ' << now_size << ' ' << num.get_val(pos, pos + 1) << '\n';
        if (num.get_val(pos, pos + 1) != now_size - 1)
            ++ans;
        val.update(pos, pos + 1, 1e9 + 228);
        val.update(1, 0, n, pos + 1, n, -1);
        num.update(pos + 1, n, -1);
 
        --now_size;
        pos = val.get_first_zero(1, 0, n);
    }
    return ans;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i)
        cin >> a[i];
    cout << solve(n, a) << '\n';
    int q;
    cin >> q;
    while (q--) {
        int t, l, r;
        cin >> t >> l >> r;
        if (t == 1) {
            vector<int> b;
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

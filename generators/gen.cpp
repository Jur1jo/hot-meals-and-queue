#include "testlib.h"
#include <unordered_map>
#include <unordered_set>
 
using namespace std;
const long long INF = 1e18;
 
struct SegTree {
    vector<long long> t, mod;
    long long zero_val = INF;
    int n, type;
 
    long long merge(long long a, long long b) {
        if (type == 0)
            return min(a, b);
        return max(a, b);
    }
 
    void build(int v, int l, int r, vector<long long> &a) {
        if (r - l == 1) {
            t[v] = a[l];
            return;
        }
 
        int m = (l + r) / 2;
        build(v * 2 + 1, l, m, a);
        build(v * 2, m, r, a);
        t[v] = merge(t[v * 2 + 1], t[v * 2]);
    }
 
    void push(int v) {
        t[v * 2 + 1] += mod[v];
        t[v * 2] += mod[v];
        mod[v * 2 + 1] += mod[v];
        mod[v * 2] += mod[v];
        mod[v] = 0;
    }
 
    long long get_val(int v, int l, int r, int L, int R) {
        if (R <= l || r <= L)
            return zero_val;
        if (L <= l && r <= R)
            return t[v];
 
        push(v);
        int m = (l + r) / 2;
        return merge(get_val(v * 2 + 1, l, m, L, R), get_val(v * 2, m, r, L, R));
    }
 
    long long get_val(int l, int r) {
        return get_val(1, 0, n, l, r);
    }
 
    int get_first_more(int v, int l, int r, int L, int R, int val) {
        if (R <= l || r <= L || t[v] <= val)
            return n;
        if (r - l == 1)
            return l;
 
        push(v);
        int m = (l + r) / 2;
        int res = get_first_more(v * 2 + 1, l, m, L, R, val);
        if (res == n)
            res = get_first_more(v * 2, m, r, L, R, val);
        return res;
    }
 
    int get_first_more(int l, int r, int val) {
        return get_first_more(1, 0, n, l, r, val);
    }
 
    void update(int v, int l, int r, int L, int R, int val) {
        if (R <= l || r <= L)
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
        t[v] = merge(t[v * 2 + 1], t[v * 2]);
    }
 
    void update(int l, int r, int val) {
        update(1, 0, n, l, r, val);
    }
 
    SegTree(vector<long long> a, int _type) {
        n = a.size(), type = _type;
        if (type == 1)
            zero_val = -INF;
        int sz = 1;
        while (sz <= 2 * n)
            sz *= 2;
        t.resize(sz);
        mod.resize(sz);
        if (type == 1) {
            for (int i = 0; i < n; ++i)
                a[i] -= i;
        }
        build(1, 0, n, a);
    }
};
 
struct sqrt_decomposition {
    const int K = 1555;
    int n;
    vector<long long> a;
    vector<long long> mod;
    vector<unordered_map<long long, int>> in_val;
 
    void build(int k) {
        in_val[k].clear();
        for (int i = k * K; i < min(n, (k + 1) * K); ++i)
            in_val[k][a[i]]++;
    }
 
    void update(int l, int r, int val) {
        while (l < r) {
            if (l % K == 0 && l + K <= r) {
                mod[l / K] += val, l += K;
            } else {
                in_val[l / K][a[l]]--;
                in_val[l / K][a[l] + val]++;
                a[l] += val;
                ++l;
            }
        }
    }
 
    int get(int l) {
        while (l < n) {
            if (l % K == 0 && !in_val[l / K][-mod[l / K]]) {
                l += K;
            } else {
                if (a[l] + mod[l / K] == 0)
                    return l;
                ++l;
            }
        }
        return n;
    }
 
    sqrt_decomposition(vector<long long> _a) {
        a = _a;
        n = a.size();
        mod.resize((n + K - 1) / K);
        in_val.resize((n + K - 1) / K);
        for (int i = 0; i < n; i += K)
            build(i / K);
    }
};
 
struct query {
    int type, l, r, val;
    query(int _type, int _l, int _r) {type = _type, l = _l, r = _r;}
    query(int _type, int _l, int _r, int _val) {type = _type, l = _l, r = _r, val = _val;}
};
 
void print(query a) {
    if (a.type == 0)
        cout << a.type + 1 << ' ' << a.l + 1 << ' ' << a.r + 1 << '\n';
    else
        cout << a.type + 1 << ' ' << a.l + 1 << ' ' << a.r + 1 << ' ' << a.val << '\n';
}
 
void add(vector<query> &a, vector<query> &b) {
    shuffle(b.begin(), b.end());
    while (b.size()) {
        a.push_back(b.back());
        b.pop_back();
    }
}
 
signed main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
 
    /* Параметры
        n - размера массива
        q - количество запросов
        max_start_val - максимальное значение, которое могут принимать элементы массива
        t_start - почти параметр t у wnext при построении массива
 
        max_ans_q - максимальное количество запросов ответа на первом шаге
        max_reduction_q - максимальное количество уменьшений на втором шаге
        max_second_q - максимальное количество изменений в 4 шаге.
        t_query_ans - параметр t в запросах ответа
        t_increase - паметр t у wnext когда возвращаем откат на втором шаге
 
        probability_start - вероятность, что мы попали вначало
    */
 
    int n = atoi(argv[1]);
    int q = atoi(argv[2]);
    int max_start_val = n - rnd.next(1, n / 2);
    int t_start = 1000;
 
    int max_ans_q = atoi(argv[3]);
    int max_reduction_q = atoi(argv[4]);
    int koef = atoi(argv[5]);
    int max_second_q = max_ans_q / koef;
    int t_query_ans = 7;
    int t_increase = 10;
 
    int probability_start = 5;
 
    vector<long long> a(n);
    for (int i = 0; i < n; ++i)
        a[i] = rnd.wnext(0, min(i, max_start_val), 1ll * 1000 * -(((long long) i + t_start - 1) / t_start));
 
    cout << n << '\n';
    for (int i = 0; i < n - 1; ++i)
        cout << a[i] << ' ';
    cout << a[n - 1] << '\n';
    vector<query> ans_query;
 
    SegTree mn(a, 0), mx(a, 1);
    sqrt_decomposition find_zero(a);
 
    while (q) {
        int pos = find_zero.get(rnd.next(0, n - 1)) % n;
        if (!rnd.next(probability_start))
            pos = 0;
        int now_cnt_q = rnd.next(1, min(max_ans_q, q));
        set<pair<int, int>> can_update;
        vector<query> now_q_ans;
        vector<query> second_step;
        while (now_cnt_q--) { // Делаю запросики, милые запросики
            int next_bad = mx.get_first_more(pos, n, -pos);
            now_q_ans.emplace_back(0, pos, rnd.wnext(pos, next_bad - 1, t_query_ans));
            if (find_zero.get(pos + 1) != pos + 1)
                can_update.emplace(pos + 1, find_zero.get(pos + 1) - 1);
            pos = find_zero.get(pos + 1) % n;
            --q;
        }
 
        now_cnt_q = rnd.next(0, min({max_reduction_q, q, (int) can_update.size()}));
        for (auto i : can_update) { // Добавляю изменения
            if (!now_cnt_q--)
                break;
            int l = rnd.next(i.first, i.second);
            int r = rnd.next(l, i.second);
            if (mn.get_val(l, r + 1) < 1)
                exit(1);
            long long val = -rnd.next(1ll, mn.get_val(l, r + 1));
            mn.update(l, r + 1, val);
            mx.update(l, r + 1, val);
            find_zero.update(l, r + 1, val);
            --q;
            second_step.emplace_back(1, l, r, val);
            now_q_ans.push_back(second_step.back());
        }
        add(ans_query, now_q_ans);
 
        int q_random_update = rnd.next(0, min(q / 2, max_second_q));
        q -= 2 * q_random_update;
        vector<query> step_four;
        while (q_random_update--) {
            int l = rnd.next(0, n - 1);
            int r = rnd.next(l, n - 1);
            int val = rnd.next(-n + 1, n - 1);
            step_four.emplace_back(1, l, r, val);
            if (r - l > 0 && q && rnd.next(0, 1)) { // "Вуалирую" запрос изменения, который откачу
                int tmp = rnd.next(l, r - 1);
                step_four.emplace_back(1, l, tmp, -val);
                step_four.emplace_back(1, tmp + 1, r, -val);
                --q;
            } else {
                step_four.emplace_back(1, l, r, -val);
            }
        }
        add(ans_query, step_four);
 
        now_cnt_q = min(q, (int) second_step.size());
        pair<int, int> start_q = {now_cnt_q, second_step.size()};
        vector<query> step_five;
        while (now_cnt_q--) {
            if (!second_step.size()) {
                cerr << start_q.first << ' ' << start_q.second << '\n';
                // exit(1);
            }
            step_five.push_back(second_step.back());
            second_step.pop_back();
            step_five.back().val = rnd.wnext(0, -step_five.back().val, t_increase);
            int l = step_five.back().l, r = step_five.back().r, val = step_five.back().val;
            mx.update(l, r + 1, val);
            mn.update(l, r + 1, val);
            find_zero.update(l, r + 1, val);
            --q;
        }
 
        add(ans_query, step_five);
    }
    cout << ans_query.size() << '\n';
    for (auto i : ans_query)
        print(i);
}

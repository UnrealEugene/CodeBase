#include <bits/stdc++.h>
#define ALL(x) (x).begin(), (x).end()
#define sz(s) (int)(s).size()
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;
int n, len[200500], to[200500][26], suf[200500], l, d = 1;
string a, b;
void add(char ch) {
    int c = ch - 'A', v = d++;
    len[v] = len[l] + 1;
    for (; l != -1 && !to[l][c]; l = suf[l])
        to[l][c] = v;
    if (l == -1)
        suf[v] = 0;
    else {
        int q = to[l][c];
        if (len[q] == len[l] + 1)
            suf[v] = q;
        else {
            int t = d++;
            len[t] = len[l] + 1;
            suf[t] = suf[q];
            memcpy(to[t], to[q], sizeof to[t]);
            for (; l != -1 && to[l][c] == q; l = suf[l])
                to[l][c] = t;
            suf[v] = suf[q] = t;
        }
    }
    l = v;
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    //freopen("input.txt", "r", stdin); //freopen("output.txt", "w", stdout);
    memset(suf, -1, sizeof suf);
    cin >> n >> a >> b;
    for (char c: a)
        add(c);
    int v = 0, l = 0, ans_l = 0, ans_r = 0;
    for (int i = 0; i < n; i++) {
        while (v && !to[v][b[i]-'A']) {
            v = suf[v];
            l = len[v];
        }
        if (to[v][b[i]-'A'])
            v = to[v][b[i]-'A'], ++l;
        if (l > ans_l) {
            ans_l = l;
            ans_r = i;
        }
    }
    cout << b.substr(ans_r - ans_l + 1, ans_l);
}

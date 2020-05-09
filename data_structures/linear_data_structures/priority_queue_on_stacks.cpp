#include <iostream>
#include <memory>
#include <cassert>
#include <string>

#define min(a, b) ((a) < (b) ? (a) : (b))
 
const int INF = 2147483647;

struct my_vector {
    int size = 0, capacity = 0;
    int* p = NULL;
    int* mn = NULL;
};

void init(my_vector &vec) {
    vec.capacity = 1;
    vec.p = (int*)calloc(vec.capacity, sizeof(int));
    vec.mn = (int*)calloc(vec.capacity, sizeof(int));
}

void add(my_vector &vec, int val) {
    if (vec.size + 1 > vec.capacity) {
        vec.capacity *= 2;
        vec.p = (int*)realloc(vec.p, vec.capacity * sizeof(int));
        vec.mn = (int*)realloc(vec.mn, vec.capacity * sizeof(int));
    }
    vec.p[vec.size] = val;
    if (vec.size > 0) {
        vec.mn[vec.size] = min(vec.mn[vec.size-1], val);
    } else {
        vec.mn[vec.size] = val;
    }
    vec.size++;
}

void rem(my_vector &vec) {
    vec.size--;
}

int top(my_vector &vec) {
    assert(vec.size > 0);
    return vec.p[vec.size-1];
}

int get_min(my_vector &vec) {
    if (vec.size == 0)
        return INF;
    return vec.mn[vec.size-1];
}
 
int x[30000500];
 
int main() {
    int n, m, k, a, b, c;
    my_vector st1, st2;
    init(st1);
    init(st2);
    scanf("%d%d%d%d%d%d", &n, &m, &k, &a, &b, &c);
    for (int i = 0; i < k; i++) {
        scanf("%d", &x[i]);
    }
    for (int i = k; i < n; i++) {
        x[i] = a * x[i - 2] + b * x[i - 1] + c;
    }
    for (int i = 0; i < m; i++) {
        add(st1, x[i]);
    }
    long long ans = min(get_min(st1), get_min(st2));
    for (int i = m; i < n; i++) {
        if (st2.size == 0) {
            while (st1.size > 0) {
                add(st2, top(st1));
                rem(st1);
            }
        }
        rem(st2);
        add(st1, x[i]);
        int t = min(get_min(st1), get_min(st2));
        ans += t;
    }
    printf("%lld\n", ans);
}

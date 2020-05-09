#include <iostream>
#include <memory>
#include <cassert>
#include <string>
 
struct my_vector {
    int size = 0, capacity = 0;
    int* p = NULL;
};

void init(my_vector &vec) {
    vec.capacity = 1;
    vec.p = (int*)calloc(vec.capacity, sizeof(int));
}

void add(my_vector &vec, int val) {
    if (vec.size + 1 > vec.capacity) {
        vec.capacity *= 2;
        vec.p = (int*)realloc(vec.p, vec.capacity * sizeof(int));
    }
    vec.p[vec.size] = val;
    vec.size++;
}

int rem(my_vector &vec) {
    if (vec.size <= vec.capacity / 4 && vec.capacity >= 4) {
        vec.capacity /= 2;
        vec.p = (int*)realloc(vec.p, vec.capacity * sizeof(int));
    }
    vec.size--;
    return vec.p[vec.size];
}

int main() {
    std::ios::sync_with_stdio(false); std::cin.tie(NULL);
    int m;
    my_vector st1, st2;
    init(st1);
    init(st2);
    std::cin >> m;
    for (int i = 0; i < m; i++) {
        char c;
        int val;
        std::cin >> c;
        if (c == '+') {
            std::cin >> val;
            add(st1, val);
        } else {
            if (st2.size == 0) {
                while (st1.size > 0) {
                    add(st2, rem(st1));
                }
            }
            std::cout << rem(st2) << std::endl;
        }
    }
}

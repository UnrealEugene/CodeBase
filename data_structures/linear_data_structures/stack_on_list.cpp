#include <iostream>
#include <memory>
#include <cassert>
#include <string>
 
 
struct node {
    node *prev = NULL;
    int value;
};
 
struct my_stack {
    node *top = NULL;
};
 
void add(my_stack &st, int val) {
    node *t = (node*)malloc(sizeof(node));
    t->prev = st.top;
    t->value = val;
    st.top = t;
}

void rem(my_stack &st) {
    assert(st.top != NULL);
    node *t = st.top;
    std::cout << t->value << std::endl;
    st.top = t->prev;
    free(t);
}

int main() {
    std::ios::sync_with_stdio(false); std::cin.tie(NULL);
    int m;
    my_stack st;
    std::cin >> m;
    for (int i = 0; i < m; i++) {
        char c;
        int val;
        std::cin >> c;
        if (c == '+') {
            std::cin >> val;
            add(st, val);
        } else {
            rem(st);
        }
    }
}

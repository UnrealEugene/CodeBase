#include <iostream>
#include <malloc.h>
#include <assert.h>
#include <string.h>
 
 
struct node {
    node *prev = NULL, *next = NULL;
    int value;
};
 
struct my_queue {
    node *front = NULL, *back = NULL;
};
 
void add(my_queue &st, int val) {
    node *t = (node*)malloc(sizeof(node));
    t->prev = st.back;
    t->next = NULL;
    if (t->prev != NULL) {
        t->prev->next = t;
    }
    t->value = val;
    st.back = t;
    if (st.front == NULL) {
        st.front = t;
    }
}

void rem(my_queue &st) {
    assert(st.front != NULL);
    node *t = st.front;
    std::cout << t->value << std::endl;
    st.front = t->next;
    if (st.front == NULL) {
        st.back = NULL;
    } else {
        st.front->prev = NULL;
    }
    free(t);
}

int main() {
    std::ios::sync_with_stdio(false); std::cin.tie(NULL);
    int m;
    my_queue q;
    std::cin >> m;
    for (int i = 0; i < m; i++) {
        char c;
        int val;
        std::cin >> c;
        if (c == '+') {
            std::cin >> val;
            add(q, val);
        } else {
            rem(q);
        }
    }
}

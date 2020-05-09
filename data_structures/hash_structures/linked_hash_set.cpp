#include <bits/stdc++.h>
 
template <class T, class Hash>
class linked_hash_set {
 private:
    struct node {
        T value;
        node* pre;
        node* next;
    } *tail = nullptr;
    std::vector<std::vector<node*>> _list;
    int _capacity;
    int _size;
 
    void _expand() {
        _capacity *= 2;
        _list.assign(_capacity, std::vector<node*>());
        for (node* cur = tail; cur != nullptr; cur = cur->pre) {
            _list[Hash()(cur->value, _capacity)].push_back(cur);
        }
    }
 
 public:
    linked_hash_set() {
        _size = 0;
        _capacity = 2;
        _list.resize(_capacity);
    }
 
    void insert(const T &value) {
        if (exists(value))
            return;
        if (_size == _capacity)
            _expand();
        _size++;
        node* new_node = new node{value, tail, nullptr};
        if (tail)
            tail->next = new_node;
        _list[Hash()(value, _capacity)].push_back(tail = new_node);
    }
 
    bool exists(const T &value) {
        auto& cur = _list[Hash()(value, _capacity)];
        for (auto it = cur.begin(); it != cur.end(); it++) {
            if ((*it)->value == value) {
                return true;
            }
        }
        return false;
    }
 
    void remove(const T &value) {
        auto& cur = _list[Hash()(value, _capacity)];
        for (auto it = cur.begin(); it != cur.end(); it++) {
            if ((*it)->value == value) {
                _size--;
                auto pre = (*it)->pre;
                auto next = (*it)->next;
                if (*it == tail)
                    tail = pre;
                if (pre)
                    pre->next = next;
                if (next)
                    next->pre = pre;
                cur.erase(it);
                break;
            }
        }
    }
 
    std::vector<T> vectorize() {
        std::vector<T> res;
        for (node* cur = tail; cur != nullptr; cur = cur->pre)
            res.emplace_back(cur->value);
        std::reverse(res.begin(), res.end());
        return res;
    }
 
    int size() {
        return _size;
    }
 
    int capacity() {
        return _capacity;
    }
};
 
class my_int_hash {
 public:
    int operator() (const int arg, const int max_value) {
        return (int) abs((int) ((long long) arg * 2895701 + 78126498113)) % max_value;
    }
};
 
int main() {
    std::ios::sync_with_stdio(false); std::cin.tie(nullptr);\
    linked_hash_set<int, my_int_hash> st;
    std::string cmd;
    while (std::cin >> cmd) {
        int key;
        std::cin >> key;
        if (cmd == "insert") {
            st.insert(key);
        } else if (cmd == "exists") {
            std::cout << (st.exists(key) ? "true" : "false") << std::endl;
        } else {
            st.remove(key);
        }
    }
}

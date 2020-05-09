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
 
 
template <class T1, class T2, class Hash>
class linked_hash_multimap {
 private:
    struct node {
        T1 key;
        linked_hash_set<T2, Hash> values;
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
            // cerr << "wat" << endl;
            _list[Hash()(cur->key, _capacity)].push_back(cur);
        }
    }
 
 public:
    linked_hash_multimap() {
        _size = 0;
        _capacity = 2;
        _list.resize(_capacity);
    }
 
    bool has(const T1 &key) {
        auto& cur = _list[Hash()(key, _capacity)];
        for (auto it = cur.begin(); it != cur.end(); it++) {
            if ((*it)->key == key) {
                return true;
            }
        }
        return false;
    }
 
    void insert(const T1 &key, const T2 &value) {
        if (!has(key)) {
            if (_size >= _capacity)
                _expand();
            _size++;
            node* new_node = new node{key, linked_hash_set<T2, Hash>(), tail, nullptr};
            if (tail)
                tail->next = new_node;
            _list[Hash()(key, _capacity)].push_back(tail = new_node);
            tail->values.insert(value);
            return;
        }
        auto& cur = _list[Hash()(key, _capacity)];
        for (auto it = cur.begin(); it != cur.end(); it++) {
            if ((*it)->key == key) {
                (*it)->values.insert(value);
                break;
            }
        }
    }
 
    std::vector<T2> get(const T1 &key) {
        auto& cur = _list[Hash()(key, _capacity)];
        for (auto it = cur.begin(); it != cur.end(); it++) {
            if ((*it)->key == key) {
                return (*it)->values.vectorize();
            }
        }
        return std::vector<T2>();
    }
 
    void remove(const T1 &key, const T2 &value) {
        auto& cur = _list[Hash()(key, _capacity)];
        for (auto it = cur.begin(); it != cur.end(); it++) {
            if ((*it)->key == key) {
                (*it)->values.remove(value);
                break;
            }
        }
    }
 
    void remove_all(const T1 &key) {
        auto& cur = _list[Hash()(key, _capacity)];
        for (auto it = cur.begin(); it != cur.end(); it++) {
            if ((*it)->key == key) {
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
 
    int size() {
        return _size;
    }
 
    int capacity() {
        return _capacity;
    }
};
 
class my_string_hash {
 private:
    static const int BASE = 53;
 
    int char_to_int(char c) {
        if ('a' <= c && c <= 'z')
            return c - 'a';
        if ('A' <= c && c <= 'Z')
            return c - 'A' + 26;
        // assert(true);
        return -1;
    }
 
 public:
    int operator() (const std::string &arg, const int max_value) {
        long long val = 0;
        for (const char &c : arg) {
            val = (val * BASE + char_to_int(c)) % max_value;
        }
        return (int) val;
    }
};
 
class my_int_hash {
 public:
    int operator() (const int arg, const int max_value) {
        return (int) abs((int) ((long long) arg * 2895701 + 78126498113)) % max_value;
    }
};
 
int main() {
    std::ios::sync_with_stdio(false); std::cin.tie(nullptr);
    linked_hash_multimap<std::string, std::string, my_string_hash> st;
    std::string cmd;
    while (std::cin >> cmd) {
        std::string key;
        std::cin >> key;
        if (cmd == "put") {
            std::string val;
            std::cin >> val;
            st.insert(key, val);
        } else if (cmd == "get") {
            auto val = st.get(key);
            std::cout << val.size();
            for (const auto &x : val)
                std::cout << " " << x;
            std::cout << std::endl;
        } else if (cmd == "deleteall") {
            st.remove_all(key);
        } else {  // delete
            std::string val;
            std::cin >> val;
            st.remove(key, val);
        }
    }
}

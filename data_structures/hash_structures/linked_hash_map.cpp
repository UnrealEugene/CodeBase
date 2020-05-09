#include <bits/stdc++.h>
 
template <class T1, class T2, class Hash>
class linked_hash_map {
 private:
    struct node {
        T1 first;
        T2 second;
        node* pre;
        node* next;
    } *tail = nullptr;
    std::vector<std::vector<node*>> _list;
 
 public:
    linked_hash_map() {
        _list.resize(Hash::MAX_VALUE);
    }
 
    void insert(const T1 &key, const T2 &value) {
        auto* ex = get(key);
        if (ex) {
            *ex = value;
            return;
        }
 
        int pos = Hash()(key);
        node* new_node = new node{key, value, tail, nullptr};
        if (tail)
            tail->next = new_node;
        _list[pos].push_back(tail = new_node);
    }
 
    T2* get(const T1 &key) {
        int pos = Hash()(key);
        auto& cur = _list[pos];
        for (auto it = cur.begin(); it != cur.end(); it++) {
            if ((*it)->first == key) {
                return &(*it)->second;
            }
        }
        return nullptr;
    }
 
    void remove(const T1 &key) {
        int pos = Hash()(key);
        auto& cur = _list[pos];
        for (auto it = cur.begin(); it != cur.end(); it++) {
            if ((*it)->first == key) {
                auto pre = (*it)->pre;
                auto next = (*it)->next;
                if (*it == tail)
                    tail = (*it)->pre;
                if (pre)
                    pre->next = next;
                if (next)
                    next->pre = pre;
                cur.erase(it);
                break;
            }
        }
    }
 
    T2* previous(const T1 &key) {
        int pos = Hash()(key);
        auto& cur = _list[pos];
        for (auto it = cur.begin(); it != cur.end(); it++) {
            if ((*it)->first == key) {
                if (!(*it)->pre)
                    return nullptr;
                return &(*it)->pre->second;
            }
        }
        return nullptr;
    }
 
    T2* next(const T1 &key) {
        int pos = Hash()(key);
        auto& cur = _list[pos];
        for (auto it = cur.begin(); it != cur.end(); it++) {
            if ((*it)->first == key) {
                if (!(*it)->next)
                    return nullptr;
                return &(*it)->next->second;
            }
        }
        return nullptr;
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
    static const int MAX_VALUE = 1e6 + 33;
    int operator() (const std::string &arg) {
        long long val = 0;
        for (const char &c : arg) {
            val = (val * BASE + char_to_int(c)) % MAX_VALUE;
        }
        return (int) val;
    }
};
 
int main() {
    std::ios::sync_with_stdio(false); std::cin.tie(nullptr);
    linked_hash_map<std::string, std::string, my_string_hash> st;
    std::string cmd;
    while (std::cin >> cmd) {
        std::string key;
        std::cin >> key;
        if (cmd == "put") {
            std::string val;
            std::cin >> val;
            st.insert(key, val);
        } else if (cmd == "get") {
            auto* val = st.get(key);
            std::cout << (val ? *val : "none") << std::endl;
        } else if (cmd == "prev") {
            auto* val = st.previous(key);
            std::cout << (val ? *val : "none") << std::endl;
        } else if (cmd == "next") {
            auto* val = st.next(key);
            std::cout << (val ? *val : "none") << std::endl;
        } else {  // delete
            st.remove(key);
        }
    }
}

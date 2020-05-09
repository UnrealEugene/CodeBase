#include <bits/stdc++.h>
 
template <class T1, class T2, class Hash>
class hash_map {
 private:
    std::vector<std::vector<std::pair<T1, T2>>> _list;
 
 public:
    hash_map() {
        _list.resize(Hash::MAX_VALUE);
    }
 
    void insert(const T1 &key, const T2 &value) {
        remove(key);
        int pos = Hash()(key);
        _list[pos].emplace_back(key, value);
    }
 
 
    T2* get(const T1 &key) {
        int pos = Hash()(key);
        auto& cur = _list[pos];
        for (auto it = cur.begin(); it != cur.end(); it++) {
            if (it->first == key) {
                return &it->second;
            }
        }
        return nullptr;
    }
 
    void remove(const T1 &key) {
        int pos = Hash()(key);
        auto& cur = _list[pos];
        for (auto it = cur.begin(); it != cur.end(); it++) {
            if (it->first == key) {
                cur.erase(it);
                break;
            }
        }
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
    hash_map<std::string, std::string, my_string_hash> st;
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
        } else {  // delete
            st.remove(key);
        }
    }
}

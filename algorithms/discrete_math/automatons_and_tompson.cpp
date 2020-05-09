#include <iostream>
#include <vector>
#include <functional>
#include <cassert>
#include <queue>
#include <unordered_map>

// Non-deterministic finite automaton
class NFA {
 private:
    size_t states_count__;
    size_t symbols_count__;
    size_t start_state__;
    std::vector<bool> term__;
    std::vector<std::vector<std::vector<size_t>>> transitions__;
    std::function<int(char)> alphabet_func__;

 public:
    NFA(size_t states, size_t start, size_t symbols, const std::function<int(char)>& func) :
        term__(states, false), 
        transitions__(states, std::vector<std::vector<size_t>>(symbols)),
        alphabet_func__(func) {
        assert(states > 0);
        states_count__ = states;
        symbols_count__ = symbols;
        start_state__ = start;
    }

    void set_start(size_t v) {
        assert(0 <= v && v < states_count__);
        start_state__ = v;
    }

    void set_term(size_t v, bool b) {
        term__.at(v) = b;
    }

    void add_transition(size_t u, size_t v, size_t c) {
        transitions__.at(u).at(c).push_back(v);
    }

    void add_transition(size_t u, size_t v, char c) {
        add_transition(u, v, (size_t) alphabet_func__(c));
    }

    void expand(size_t n) {
        assert(n >= states_count__);
        states_count__ = n;
        term__.resize(n);
        while (transitions__.size() != n) {
            transitions__.emplace_back(symbols_count__);
        }
    }

    size_t get_start() const {
        return start_state__;
    }

    bool is_term(size_t v) const {
        return term__.at(v);
    }

    std::vector<size_t> get_transition(size_t u, size_t c) const {
        return transitions__.at(u).at(c);
    }

    std::vector<size_t> get_transition(size_t u, char c) const {
        return get_transition(u, (size_t) alphabet_func__(c));
    }

    size_t get_states_count() const {
        return states_count__;
    }

    size_t get_symbols_count() const {
        return symbols_count__;
    }

    std::function<int(char)> get_symbols_function() const {
        return alphabet_func__;
    }

    bool try_word(const std::string& str) const {
        std::vector<bool> dp(states_count__);
        dp[start_state__] = true;
        for (size_t i = 0; i < str.size(); i++) {
            std::vector<bool> new_dp(states_count__);
            for (size_t v = 0; v < states_count__; v++) {
                if (dp[v]) {
                    for (size_t u : transitions__[v][alphabet_func__(str[i])]) {
                        new_dp[u] = true; 
                    }
                }
            }
            swap(dp, new_dp);
        }
        for (size_t u = 0; u < states_count__; u++) {
            if (term__[u] && dp[u]) {
                return true;
            }
        }
        return false;
    }
};

// Deterministic finite automaton
class DFA {
 private:
    size_t states_count__;
    size_t symbols_count__;
    size_t start_state__;
    std::vector<bool> term__;
    std::vector<std::vector<size_t>> transitions__;
    std::function<int(char)> alphabet_func__;

 public:
    DFA(size_t states, size_t start, size_t symbols, const std::function<int(char)>& func) :
        term__(states, false), 
        transitions__(states, std::vector<size_t>(symbols, (size_t) -1)),
        alphabet_func__(func) {
        assert(states > 0);
        states_count__ = states;
        symbols_count__ = symbols;
        start_state__ = start;
    }

    // Tompson's algorithm transforming NFA to DFA in O(n * 2^n)
    explicit DFA(const NFA& nfa) {
        auto n = nfa.get_states_count();
        states_count__ = 0;
        start_state__ = 0;
        symbols_count__ = nfa.get_symbols_count();
        alphabet_func__ = nfa.get_symbols_function();
        std::queue<std::vector<bool>> q;
        std::unordered_map<std::vector<bool>, size_t> id;

        expand(1);

        std::vector<bool> s(n);
        s[0] = true;
        id[s] = 0;
        if (nfa.is_term(0))
            set_term(0, true);

        q.push(s);

        while (!q.empty()) {
            std::vector<bool> cur = q.front();
            q.pop();
            for (size_t c = 0; c < symbols_count__; c++) {
                std::vector<bool> p(n);
                for (size_t v = 0; v < n; v++) {
                    if (cur[v]) {
                        for (size_t u : nfa.get_transition(v, c)) {
                            p[u] = true;
                        }
                    }
                }
                if (p == std::vector<bool>(n))
                    continue;
                if (!id.count(p)) {
                    expand(id.size() + 1);
                    for (size_t v = 0; v < n; v++) {
                        if (p[v] && nfa.is_term(v)) {
                            set_term(id.size(), true);
                            break;
                        }
                    }
                    id[p] = id.size();
                    q.push(p);
                }
                add_transition(id[cur], id[p], c);
            }
        }
    }

    void set_start(size_t v) {
        assert(0 <= v && v < states_count__);
        start_state__ = v;
    }

    void set_term(size_t v, bool b) {
        term__.at(v) = b;
    }

    void add_transition(size_t u, size_t v, size_t c) {
        transitions__.at(u).at(c) = v;
    }

    void add_transition(size_t u, size_t v, char c) {
        add_transition(u, v, (size_t) alphabet_func__(c));
    }

    void expand(size_t n) {
        assert(n >= states_count__);
        states_count__ = n;
        term__.resize(n);
        while (transitions__.size() != n) {
            transitions__.emplace_back(symbols_count__, (size_t) -1);
        }
    }

    size_t get_start() const {
        return start_state__;
    }

    bool is_term(size_t v) const {
        return term__.at(v);
    }

    size_t get_transition(size_t u, size_t c) const {
        size_t x = transitions__.at(u).at(c);
        return x == states_count__ ? -1 : x;
    }

    size_t get_transition(size_t u, char c) const {
        return get_transition(u, (size_t) alphabet_func__(c));
    }

    size_t get_states_count() const {
        return states_count__;
    }

    size_t get_symbols_count() const {
        return symbols_count__;
    }

    std::function<int(char)> get_symbols_function() const {
        return alphabet_func__;
    }


    bool try_word(const std::string& str) const {
        size_t cur = start_state__;
        for (size_t i = 0; i < str.size(); i++) {
            cur = transitions__[cur].at(alphabet_func__(str[i]));
            if (cur == states_count__)
                return false;
        }
        return term__[cur];
    }
};

int main() {
    std::ios::sync_with_stdio(false); std::cin.tie(nullptr);
 
    auto f = [](char c) {
        if ('a' <= c && c <= 'z')
            return c - 'a';
        return -1;
    };
 
    std::string str;
    std::cin >> str;
 
    size_t n, m, k;
    std::cin >> n >> m >> k;
    NFA nfa(n, 0, 26, f);
     
    for (size_t i = 0; i < k; i++) {
        size_t term;
        std::cin >> term;
        nfa.set_term(term - 1, true);
    }
 
    for (size_t i = 0; i < m; i++) {
        size_t u, v;
        char c;
        std::cin >> u >> v >> c;
        nfa.add_transition(u - 1, v - 1, c);
    }
 
    std::cout << (nfa.try_word(str) ? "Accepts" : "Rejects") << std::endl;
}

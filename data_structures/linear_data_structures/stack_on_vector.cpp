#include <iostream>
#include <cassert>
#include <memory.h>
 
template<typename T> class my_vector {
 private:
    const int START_CAPACITY = 1;
    int _size, _capacity;
    T *_buffer;
 
 public:
    my_vector() {
        _capacity = START_CAPACITY;
        _size = 0;
        _buffer = new T[_capacity];
    }

    void push_back(T obj) {
        if (_size >= _capacity) {
            _capacity *= 2;
            T *_new_buffer = new T[_capacity];
            assert(_new_buffer);
            memcpy(_new_buffer, _buffer, _size * sizeof(T));
            delete [] _buffer;
            _buffer = _new_buffer;
        }
        _buffer[_size++] = obj;
    }

    void pop_back() {
        _size--;
    }

    T& back() {
        assert(_size > 0);
        return _buffer[_size - 1];
    }

    T& operator[](int i) {
        assert(i >= 0 && i < _size);
        return _buffer[i];
    }

    int size() {
        return _size;
    }
};
 
 
int main() {
    std::ios::sync_with_stdio(false); std::cin.tie(0);
    my_vector<int> vec;
    int n;
    std::cin >> n;
    while (n--) {
        char c;
        std::cin >> c;
        if (c == '-') {
            std::cout << vec.back() << std::endl;
            vec.pop_back();
        } else {
            int x;
            std::cin >> x;
            vec.push_back(x);
        }
    }
}

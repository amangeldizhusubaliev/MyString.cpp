#pragma once

#include <cstring>
#include <iostream>
#include <stdexcept>

class MyString {
    char* data;
    int32_t sz, cap;

public:
    // constructors
    MyString() : sz(0), cap(1) {
        data = new char[1];
        data[0] = '\0';
    }
    MyString(const char* b);
    MyString(const MyString& b);
    MyString& operator=(const MyString& b);
    MyString(MyString&& b);
    MyString& operator=(MyString&& b);

    // destructor
    ~MyString() {
        delete[] data;
    }

    inline char& operator[](int32_t n) {
        return data[n];
    }
    
    inline char operator[](int32_t n) const {
        return data[n];
    }

    inline char& at(int32_t n) {
        if (n < 0 || n >= sz) {
            throw std::out_of_range("MyString::at()");
        }
        return data[n];
    }

    inline char at(int32_t n) const {
        if (n < 0 || n >= sz) {
            throw std::out_of_range("MyString::at()");
        }
        return data[n];
    }

    MyString& operator+=(char c);
    MyString& operator+=(const MyString& b);

    inline const char* c_str() {
        return data;
    }

    inline const char* c_str() const {
        return data;
    }

    inline int32_t size() const {
        return sz;
    }

    inline bool empty() const {
        return sz == 0;
    }

    inline char* begin() {
        return this->data;
    }

    inline char* end() {
        return this->data + this->sz;
    }

    inline const char* begin() const {
        return this->data;
    }

    inline const char* end() const {
        return this->data + this->sz;
    }
};

inline MyString operator+(const MyString& a, char b) {
    MyString r(a);
    r += b;
    return r;
}

inline MyString operator+(const MyString& a, const MyString& b) {
    MyString r(a);
    r += b;
    return r;
}

bool operator==(const MyString& a, const MyString& b);

inline bool operator!=(const MyString& a, const MyString& b) {
    return !(a == b);
}

std::istream& operator>>(std::istream& inp, MyString& a);

inline std::ostream& operator<<(std::ostream& out, const MyString& a) {
    return out << a.c_str();
}
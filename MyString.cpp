#include "MyString.hpp"

// constructors

MyString::MyString(const char* b) {
    this->sz = std::strlen(b);
    this->cap = this->sz + 1;
    this->data = new char[this->cap];
    memcpy(this->data, b, this->sz * sizeof(char));
    this->data[this->sz] = '\0';
}

MyString::MyString(const MyString& b) {
    this->sz = b.sz;
    this->cap = b.cap;
    this->data = new char[this->cap];
    memcpy(this->data, b.data, this->sz * sizeof(char));
    this->data[this->sz] = '\0';
}

MyString& MyString::operator=(const MyString& b) {
    if (this == &b) {
        return *this;
    }
    delete[] this->data;
    *this = MyString(b);
    return *this;
}

MyString::MyString(MyString&& b) {
    this->data = b.data;
    this->sz = b.sz;
    this->cap = b.cap;
    b.data = nullptr;
}

MyString& MyString::operator=(MyString&& b) {
    if (this == &b) {
        return *this;
    }
    delete[] this->data;
    this->data = b.data;
    this->sz = b.sz;
    this->cap = b.cap;
    b.data = nullptr;
    return *this;
}

MyString& MyString::operator+=(char c) {
    if (this->cap == this->sz + 1) {
        this->cap = this->cap * 2 - 1;
        char *p = new char[this->cap];
        memcpy(p, this->data, this->sz * sizeof(char));
        delete[] this->data;
        this->data = p;
    }
    this->data[this->sz++] = c;
    this->data[this->sz] = '\0';
    return *this;
}

MyString& MyString::operator+=(const MyString& b) {
    for (auto i : b) {
        *this += i;
    }
    return *this;
}

bool operator==(const MyString& a, const MyString& b) {
    if (a.size() != b.size()) {
        return false;
    }
    for (int32_t i = 0; i < a.size(); i++) {
        if (a[i] != b[i]) {
            return false;
        }
    }
    return true;
}

std::istream& operator>>(std::istream& inp, MyString& a) {
    a = "";
    inp >> std::ws;
    char c;
    while (inp.get(c) && !isspace(c)) {
        a += c;
    }
    return inp;
}